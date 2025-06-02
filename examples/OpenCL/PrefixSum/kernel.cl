__kernel
void
sumBlocks(
    __global TYPE* restrict inputOutput,
    __global TYPE* restrict sumBuffer)
{
    int gid = get_global_id(0);
    int lid = get_local_id(0);	  
	int bid = get_group_id(0);	
    __local TYPE sum;

	// Only 1 thread of a group will read from global buffer
	if (lid == 0)
	{
        sum = sumBuffer[bid];
	}
	barrier(CLK_LOCAL_MEM_FENCE);

	inputOutput[gid] += sum;
}

__kernel void scanHillisSteele(
    __global TYPE* restrict input,
    __global TYPE* restrict output,
    __global TYPE* restrict sumBuffer,
    __local TYPE* restrict block)
{
    int gid = get_global_id(0);
    int lid = get_local_id(0);
    int bid = get_group_id(0);
    int bsize = get_local_size(0);

    // Load input into shared memory
    block[lid] = (lid > 0) ? input[gid - 1] : 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    // Perform Hillis-Steele scan
    for (int s = 1; s < bsize; s <<= 1) {
        TYPE val = (lid >= s) ? block[lid - s] : 0;
        barrier(CLK_LOCAL_MEM_FENCE);
        block[lid] += val;
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Write the results back to global memory
    output[gid] = block[lid];

    // Store the total sum of the work-group
    if (lid == (bsize - 1)) {
        sumBuffer[bid] = block[lid] + input[gid];
    }
}

__kernel
void
scanBlelloch(
    __global TYPE* restrict input,
    __global TYPE* restrict output,
    __global TYPE* restrict sumBuffer,
    __local TYPE* restrict block)
{
    int gid = get_global_id(0);    
    int lid = get_local_id(0);
    int bid = get_group_id(0);
    int bsize = 2*get_local_size(0);

    int s = 1;

    // Load into into shared memory
    block[2 * lid] = input[2 * gid];
    block[2 * lid + 1] = input[2 * gid + 1];

    // Build the sum in place up the tree
    for (int d = bsize >> 1; d > 0; d >>= 1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);

        if (lid < d)
        {
            int ai = s * (2 * lid + 1) - 1;
            int bi = s * (2 * lid + 2) - 1;

            block[bi] += block[ai];
        }
        s *= 2;
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    // Store the total sum of the work-group (before we zero this below)
    sumBuffer[bid] = block[bsize - 1];

    barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

    // Zero the last element
    block[bsize - 1] = 0;

    // Traverse down the tree building the scan in place
    for (int d = 1; d < bsize; d <<= 1)
    {
        s >>= 1;
        barrier(CLK_LOCAL_MEM_FENCE);

        if (lid < d)
        {
            int ai = s * (2 * lid + 1) - 1;
            int bi = s * (2 * lid + 2) - 1;

            TYPE t = block[ai];
            block[ai] = block[bi];
            block[bi] += t;
        }
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    // Write the results back to global memory
    output[2 * gid] = block[2 * lid];
    output[2 * gid + 1] = block[2 * lid + 1];
}
