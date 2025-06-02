=========
PrefixSum
=========

This command-line example demonstrates a couple of algorithms for Prefix Sum.

API
---
* OpenCL

Description
-----------
The Prefix Sum operation involves computing the cumulative sums of a sequence of numbers,
where each element in the resulting sequence is the sum of all previous elements up to that position in the original sequence,
either including or excluding the element at that position (the Prefix Sum can be inclusive or exlusive).

The implementations in this example are all exclusive.

So to illustrate the exclusive case:

If the input vector is x0, x1, x2, x3, ..., then the computed output vector would be:

y0 = 0
y1 = x0
y2 = x0 + x1
y3 = x0 + x1 + x2

i.e.

y0 = 0
yn = y(n-1) + x(n-1) for n >= 1

For the inclusive case it would be:

y0 = x0
yn = y(n-1) + xn for n >= 1

Prefix Sum is a particular case of the more general scan operation, where the sum operation could be replaced by any binary associative operator.
It can be used as a building block in other algorithms, like Radix Sort.

The CPU sequential implementation is trivial. In contrast, trying to parallelise Prefix Sum is non-trivial, due to yn being derived from y(n-1).
However, there are two well-known algorithms out there:

* Hillis-Steele, 1986
This algorithm is simpler but is work-inefficient.

* Blelloch, 1990
This algorithm is work-efficient but is more complex.

There are diagrams in the docs directory illustrating the above algorithms.

Comparing the algorithms alongside the sequential one:

+---------------------+-------------------------+-------------------------+-----------------------------------+
| Aspect              | Sequential Algorithm    | Hillis-Steele Algorithm | Blelloch Algorithm                |
+=====================+=========================+=========================+===================================+
| Time Complexity     | O(n)                    | O(log n)                | O(log n)                          |
+---------------------+-------------------------+-------------------------+-----------------------------------+
| Work Efficiency     | O(n)                    | O(n log n)              | O(n)                              |
+---------------------+-------------------------+-------------------------+-----------------------------------+
| Approach            | Single phase, linear    | Single phase, parallel  | Two phases: upsweep and downsweep |
+---------------------+-------------------------+-------------------------+-----------------------------------+
| Implementation      | Simplest                | Simpler                 | More complex                      |
+---------------------+-------------------------+-------------------------+-----------------------------------+

Note: All logarithms (log n) are to base 2.

The target machine of Hillis and Steele's 1986 paper was not a GPU and the work-inefficency of the algorithm was maybe less of an issue in their context.
It has been included in this example as a simpler algorithm to consider first, however, most likely, the Blelloch algorithm will server as a better starting point for a GPU implementation.
This could be further enhanced, to factor in problems like avoiding bank conflicts but this is considered outside the scope of the work here, whose aim is to be more of an introduction.

In the OpenCL implementations of the parallel algorithms, in the general case where the input vector is larger than the local work group size,
the input vector must be processed in a number of blocks, and the prefix sum accumulation "starts again" at the beginning of each of these blocks.
Therefore, it becomes necessary to "sum blocks" afterwards, as illustrated by another diagram in the docs directory.
This is fully implemented in this example.

The example here will run both algorithms in turn on an input vector of floats.
Typically a given run of an algorithm is pretty quick, so it is run for a certain number of iterations to make the timing information more averaged.

The size of the input vector and the number of iterations have defaults that can be overridden on the command line.

Please see the command line parameters in more detail by using -h, i.e. "OpenCLPrefixSum -h".
