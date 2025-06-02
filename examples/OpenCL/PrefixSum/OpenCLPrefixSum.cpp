/*!*********************************************************************************************************************
\File         OpenCLPrefixSum.cpp
\Title        Prefix Sum example
\Author       PowerVR by Imagination, Developer Technology Team.
\Copyright    Copyright(c) Imagination Technologies Limited.
\brief        An example to illustrate Prefix Sum.
***********************************************************************************************************************/
#include "PVRCore/PVRCore.h"

#include "PVRUtils/OpenCL/OpenCLUtils.h"
#include <iostream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <memory>
#include <array>

#if defined(_WIN32)
#include "PVRCore/Windows/WindowsResourceStream.h"
#elif defined(__ANDROID__)
#include "PVRCore/Android/AndroidAssetStream.h"
#endif

// The type of data the scan is performed on
typedef float TYPE;
// The absolute operator for this type of data
#define ABS fabs
// The maximum difference permitted for a test pass
constexpr auto DIFF_THRESH = 1.0f;

// Defaults. Can be overriden on command line (see help below).
constexpr auto defaultDataSize = 4 * 1024 * 1024;
constexpr auto defaultIterations = 100;	
constexpr auto defaultKernelFile = "kernel.cl";

// Print the supported command line parameters
static void printHelp()
{
	std::cout << std::endl;
	std::cout << "Supported command line options:" << std::endl;
	std::cout << "    -h                    : Displays this help message" << std::endl;
	std::cout << "    -v                    : Verbose mode. Adds a lot more timing information." << std::endl;
	std::cout << "    -va                   : Validate mode: Will use a CPU-side implementation to validate all results against." << std::endl;
	std::cout << "    -k                    : Name of kernel files (default = " << defaultKernelFile << ")" << std::endl;
	std::cout << "    -n                    : Size of input vector (default = " << defaultDataSize << ")" << std::endl;
	std::cout << "    -i                    : Number of iterations to run (default = " << defaultIterations << ")" << std::endl;
}

// Program globals, decoded from the command line
static bool VERBOSE = false;
static bool VALIDATE = false;

// Algorithms implemented
enum AlgorithmId
{
	HillisSteele = 0,
	Blelloch,
	NumAlgorithms
};
struct Algorithm
{
	AlgorithmId id;
	const char* name;
	const char* scanKernelName;
	int sizeDivider;	// Blelloch process in pairs, this idea is encoded here
	size_t blockSize;	// And because of the above, block size could vary with algorithm
};
struct Algorithm algorithms[] = { { HillisSteele, "Hillis-Steele", "scanHillisSteele", 1, 0 }, { Blelloch, "Blelloch", "scanBlelloch", 2, 0 } };

// Setup, including OpenCL objects, needed by all algorithms
struct Setup
{
	size_t dataSize;
	int iterations;
	cl_platform_id platform;
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;
	cl_program program;
	cl_mem inputBuffer;
};

// Host data buffers
struct Data
{
	TYPE* inputData;
	TYPE* resultData;
	TYPE* correctData;
};

// Timings recorded on each algorithm run
struct Timings
{
	float kernelsTime;
	float uploadTime;
};

// In practice, the scan of the input buffer is performed in a number of iterations.
// Each iteration needs all of the below.
struct ScanIteration
{
	cl_mem resultBuffer;
	cl_mem sumBuffer;
	cl_kernel scanKernel;
	cl_kernel sumKernel;
	size_t dataSize;
	size_t numBlocks;
};

// Prints and returns elapsed time
static float measureTimeDiff(pvr::Time& time, const char* desc, bool reset = true)
{
	float ms = time.getElapsedMilliSecsF();
	if (VERBOSE) { std::cout << desc << ": " << ms << " millseconds" << std::endl; }
	if (reset) { time.Reset(); }
	return ms;
}

// Verifies result against correct data
static void verifyResult(const TYPE* resultData, const TYPE* correctData, size_t dataSize)
{
	bool passed = true;
	int failedIndex = 0;
	for (int i = 0; i < dataSize; i++)
	{
		TYPE diff = resultData[i] - correctData[i];
		if (ABS(diff) > DIFF_THRESH)
		{
			passed = false;
			failedIndex = i;
			break;
		}
	}
	if (passed) { std::cout << "++++" << " PASSED" << std::endl; }
	else
	{
		std::cout << "----" << " FAILED at index = " << failedIndex << std::endl;
		int halfSpan = 10;
		int startIndex = failedIndex - halfSpan;
		int endIndex = failedIndex + halfSpan;
		if (startIndex < 0) startIndex = 0;
		if (endIndex < 0) endIndex = 0;
		for (int i = startIndex; i < endIndex; i++) { std::cout << i << ": " << resultData[i] << ", " << correctData[i] << std::endl; }
	}
}

// Cleans up a scan iteration
static void cleanupScanIteration(ScanIteration* scanIteration)
{
	if (scanIteration->resultBuffer) { cl::ReleaseMemObject(scanIteration->resultBuffer); }
	if (scanIteration->sumBuffer) { cl::ReleaseMemObject(scanIteration->sumBuffer); }
	if (scanIteration->scanKernel) { cl::ReleaseKernel(scanIteration->scanKernel); }
	if (scanIteration->sumKernel) { cl::ReleaseKernel(scanIteration->sumKernel); }
}

// Performs a scan
static void performScan(Algorithm& algorithm, Setup& setup, Data& data, Timings& timings)
{
	pvr::Time time;
	std::vector<ScanIteration*> scanIterations;
	cl_int err;
	ScanIteration* scanIteration = nullptr;

	try
	{
		// Create scan iterations
		size_t thisDataSize = setup.dataSize;
		cl_mem thisInputBuffer = setup.inputBuffer;
		cl_mem prevResultBuffer = nullptr;
		while (thisDataSize > 0)
		{
			size_t thisNumBlocks = thisDataSize / algorithm.blockSize;
			thisNumBlocks = thisNumBlocks == 0 ? 1 : thisNumBlocks;

			scanIteration = new ScanIteration;
			if (!scanIteration) { throw std::runtime_error("Failed to allocate scan iteration"); }
			memset(scanIteration, 0, sizeof(ScanIteration));
			scanIteration->dataSize = thisDataSize;
			scanIteration->numBlocks = thisNumBlocks;

			cl_mem resultBuffer = cl::CreateBuffer(setup.context, CL_MEM_READ_WRITE, thisDataSize * sizeof(TYPE), NULL, &err);
			clutils::throwOnFailure(err, "Create result buffer");
			scanIteration->resultBuffer = resultBuffer;
			cl_mem sumBuffer = cl::CreateBuffer(setup.context, CL_MEM_READ_WRITE, thisNumBlocks * sizeof(TYPE), NULL, &err);
			clutils::throwOnFailure(err, "Create sum buffer");
			scanIteration->sumBuffer = sumBuffer;
			cl_kernel scanKernel = cl::CreateKernel(setup.program, algorithm.scanKernelName, &err);
			clutils::throwOnFailure(err, "Create scan kernel");
			scanIteration->scanKernel = scanKernel;

			err = cl::SetKernelArg(scanKernel, 0, sizeof(cl_mem), &thisInputBuffer);
			clutils::throwOnFailure(err, "Set scan kernel arg 0");
			err = cl::SetKernelArg(scanKernel, 1, sizeof(cl_mem), &resultBuffer);
			clutils::throwOnFailure(err, "Set scan kernel arg 1");
			err = cl::SetKernelArg(scanKernel, 2, sizeof(cl_mem), &sumBuffer);
			clutils::throwOnFailure(err, "Set scan kernel arg 2");
			err = cl::SetKernelArg(scanKernel, 3, algorithm.blockSize * sizeof(TYPE), NULL);
			clutils::throwOnFailure(err, "Set scan kernel arg 3");

			cl_kernel sumKernel;
			if (prevResultBuffer)
			{
				sumKernel = cl::CreateKernel(setup.program, "sumBlocks", &err);
				clutils::throwOnFailure(err, "Create sum kernel");
				scanIteration->sumKernel = sumKernel;
				err = cl::SetKernelArg(sumKernel, 0, sizeof(cl_mem), &prevResultBuffer);
				clutils::throwOnFailure(err, "Set sum kernel arg 0");
				err = cl::SetKernelArg(sumKernel, 1, sizeof(cl_mem), &resultBuffer);
				clutils::throwOnFailure(err, "Set sum kernel arg 1");
			}
			else { sumKernel = nullptr; }

			scanIterations.push_back(scanIteration);

			thisDataSize /= algorithm.blockSize;
			thisInputBuffer = sumBuffer;
			prevResultBuffer = resultBuffer;
		}

		scanIteration = nullptr;

		// Copy the input data to the inputBuffer
		err = cl::EnqueueWriteBuffer(setup.queue, setup.inputBuffer, CL_TRUE, 0, setup.dataSize * sizeof(TYPE), data.inputData, 0, NULL, NULL);
		clutils::throwOnFailure(err, "Write input buffer");

		// Run the kernels
		time.Reset();
		for (int i = 0; i < setup.iterations; i++)
		{
			size_t globalSize, localSize;
			for (auto it = scanIterations.begin(); it != scanIterations.end(); ++it)
			{
				auto& iter = *it;
				globalSize = iter->dataSize;
				localSize = iter->dataSize > algorithm.blockSize ? algorithm.blockSize : globalSize;
				globalSize /= algorithm.sizeDivider;
				localSize /= algorithm.sizeDivider;
				err = cl::EnqueueNDRangeKernel(setup.queue, iter->scanKernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
				clutils::throwOnFailure(err, "Run scan kernel");
			}
			cl_kernel prevSumKernel = nullptr;
			for (auto it = scanIterations.rbegin(); it != scanIterations.rend(); ++it)
			{
				auto& iter = *it;
				if (prevSumKernel)
				{
					globalSize = iter->dataSize;
					localSize = algorithm.blockSize;
					err = cl::EnqueueNDRangeKernel(setup.queue, prevSumKernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
					clutils::throwOnFailure(err, "Run sum kernel");
				}
				prevSumKernel = iter->sumKernel;
			}
		}
		cl::Finish(setup.queue);
		timings.kernelsTime = measureTimeDiff(time, "Kernels");

		if (VALIDATE)
		{
			// Read the result back to host memory
			err = cl::EnqueueReadBuffer(setup.queue, scanIterations[0]->resultBuffer, CL_TRUE, 0, setup.dataSize * sizeof(TYPE), data.resultData, 0, NULL, NULL);
			clutils::throwOnFailure(err, "Read result buffer");
			cl::Finish(setup.queue);
			timings.uploadTime = measureTimeDiff(time, "Upload ");

			// Check result
			verifyResult(data.resultData, data.correctData, setup.dataSize);
		}
	}
	catch (const std::exception err)
	{
		if (scanIteration) { cleanupScanIteration(scanIteration); }
		for (auto& iter : scanIterations) { cleanupScanIteration(iter); }
		throw(err);
	}

	for (auto& iter : scanIterations) { cleanupScanIteration(iter); }
}

// Fills input data
static void fillInput(TYPE* inputData, size_t dataSize)
{
	for (int i = 0; i < dataSize; i++) { inputData[i] = pvr::randomrange(-20.f, 20.f); }
}

// Calculates correct result data
static void calcCorrect(TYPE* inputData, TYPE* outputData, size_t dataSize)
{
	outputData[0] = 0;
	for (int i = 1; i < dataSize; i++) { outputData[i] = outputData[i - 1] + inputData[i - 1]; }
}

// Sets things up
static void doSetup(Setup& setup, const char* argv0, std::string& kernelFile)
{
	cl_int err;

	pvr::FilePath path(argv0);
	auto fs = pvr::FileStream::createFileStream(kernelFile, "r", false);

	if (!fs->isReadable())
	{
		fs = pvr::FileStream::createFileStream(
			path.getDirectory() + pvr::FilePath::getDirectorySeparator() + "Assets_" + path.getFilenameNoExtension() + pvr::FilePath::getDirectorySeparator() + kernelFile, "r", false);
	}
#ifdef _WIN32
	if (!fs->isReadable()) { fs.reset(new pvr::WindowsResourceStream(kernelFile, false)); }
#endif

	if (!fs->isReadable()) { throw pvr::FileNotFoundError(kernelFile); }

	clutils::createOpenCLContext(setup.platform, setup.device, setup.context, setup.queue);

	// Query the maximun work group size (block size)
	size_t maxBlockSize;
	cl::GetDeviceInfo(setup.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxBlockSize), &maxBlockSize, NULL);

	// Set the block size used on each algorithm.
	// Given the size divider on Blelloch, we could try and double its block size. However, in practice, no performance advantage was found, so keep block size the same for all algorithms.
	// The default is to set this block size to the maximum queried above.
	// However, on IMG GPU, crudely identified here via __ANDROID__, the maxBlockSize comes back suprisingly large (1024), yet best results are obtained with smaller value below.
	size_t blockSize;
#ifdef __ANDROID__
	blockSize = 32;
#else
	blockSize = maxBlockSize;
#endif
	for (int i = 0; i < NumAlgorithms; i++)
	{
		auto& algorithm = algorithms[i];
		algorithm.blockSize = blockSize;
	}

	// Create program from kernel source
	const char* defines[] = { "#define TYPE float" };
	const char* options = "-cl-fast-relaxed-math";
	fs->seek(0, pvr::Stream::SeekOrigin::SeekOriginFromStart);
	setup.program = clutils::loadKernelProgram(setup.context, setup.device, *fs, options, defines, 1);

	// Build the program
	err = cl::BuildProgram(setup.program, 1, &setup.device, NULL, NULL, NULL);
	clutils::throwOnFailure(err, "Build program");

	// Create memory buffers on the device
	setup.inputBuffer = cl::CreateBuffer(setup.context, CL_MEM_READ_ONLY, setup.dataSize * sizeof(TYPE), NULL, &err);
	clutils::throwOnFailure(err, "Create input buffer");
}

// Cleans up setup
static void cleanupSetup(Setup& setup)
{
	if (setup.inputBuffer) { cl::ReleaseMemObject(setup.inputBuffer); }
	if (setup.program) { cl::ReleaseProgram(setup.program); }
	if (setup.queue) { cl::ReleaseCommandQueue(setup.queue); }
	if (setup.context) { cl::ReleaseContext(setup.context); }
}

// Compares time measurements, printing out result
static void compareTimeMeasurements(float cpuMs, float gpuMs, const char* note = "")
{
	float gpuBetterMs = cpuMs - gpuMs;
	bool worse = false;
	float absGpuBetterMs = gpuBetterMs;
	if (gpuBetterMs < 0.0f)
	{
		absGpuBetterMs = -gpuBetterMs;
		worse = true;
	}
	const char* betterWorseSym = worse ? "----" : "++++";
	const char* betterWorseMsg = worse ? "worse" : "better";
	float gpuBetterPercent = 100.0f * (gpuBetterMs / cpuMs);
	std::cout << betterWorseSym << " " << note << "GPU is " << betterWorseMsg << " by " << absGpuBetterMs << " ms (" << gpuBetterPercent << "%)" << std::endl;
}

int main(int argc, char** argv)
{	
	Setup setup;
	memset(&setup, 0, sizeof(Setup));
	
	try
	{
		std::cout << "\nSingle Precision Prefix Sum benchmarking test." << std::endl;
		
		// Parse command line
		pvr::platform::CommandLineParser parser(argc - 1, argv + 1);
		const pvr::CommandLine& cmdLine = parser.getParsedCommandLine();
		std::string kernelFile(defaultKernelFile);
		cmdLine.getStringOption("-k", kernelFile);
		cmdLine.getBoolOptionSetTrueIfPresent("-v", VERBOSE);
		cmdLine.getBoolOptionSetTrueIfPresent("-va", VALIDATE);
		bool help = false;
		cmdLine.getBoolOptionSetTrueIfPresent("-h", help);
		if (help)
		{
			printHelp();
			return 0;
		}
		int32_t dataSize = defaultDataSize;
		cmdLine.getIntOption("-n", dataSize);
		setup.dataSize = dataSize;
		int32_t iterations = defaultIterations;
		cmdLine.getIntOption("-i", iterations);
		setup.iterations = iterations;

		std::cout << "Data size = " << setup.dataSize << std::endl;
		std::cout << "Number of iterations = " << setup.iterations << std::endl;
		
		std::vector<TYPE> inputVector(setup.dataSize), resultVector(setup.dataSize), correctVector(setup.dataSize);
		Data data = { inputVector.data(), resultVector.data(), correctVector.data() };

		pvr::Time time;
		time.Reset();

		// Setup
		doSetup(setup, argv[0], kernelFile);
		measureTimeDiff(time, "Setup");

		// Generate input data
		fillInput(data.inputData, setup.dataSize);
		measureTimeDiff(time, "Generate input data");

		// Calculate correct result
		for (int i = 0; i < iterations; i++) { calcCorrect(data.inputData, data.correctData, setup.dataSize); }
		float cpuMs = measureTimeDiff(time, "Calculate correct data");

		// Run algorithms
		for (int i = 0; i < NumAlgorithms; i++)
		{
			Timings timings;
			auto& algorithm = algorithms[i];
			std::cout << ">>>> " << algorithm.name << std::endl;
			std::cout << "Block size = " << algorithm.blockSize << std::endl;
			performScan(algorithm, setup, data, timings);
			compareTimeMeasurements(cpuMs, timings.kernelsTime, "Kernels: ");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		cleanupSetup(setup);
		return 1;
	}

	cleanupSetup(setup);
	return 0;
}
