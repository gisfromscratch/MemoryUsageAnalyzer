// Analyzer Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <Psapi.h>
#include <random>
#include <VectorAllocator.h>

using namespace edu::memory;
using namespace std::chrono;
using namespace std;

void PrintMemoryInfo(DWORD processID)
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS_EX pmc;

	// Print the process identifier.

	printf("\nProcess ID: %u\n", processID);

	// Print information about the memory usage of the process.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;

	if (GetProcessMemoryInfo(hProcess, reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc)))
	{
		printf("\tPageFaultCount: %u\n", pmc.PageFaultCount);
		printf("\tPeakWorkingSetSize: %u\n",
			pmc.PeakWorkingSetSize);
		printf("\tWorkingSetSize: %u\n", pmc.WorkingSetSize);
		printf("\tQuotaPeakPagedPoolUsage: %u\n",
			pmc.QuotaPeakPagedPoolUsage);
		printf("\tQuotaPagedPoolUsage: %u\n",
			pmc.QuotaPagedPoolUsage);
		printf("\tQuotaPeakNonPagedPoolUsage: %u\n",
			pmc.QuotaPeakNonPagedPoolUsage);
		printf("\tQuotaNonPagedPoolUsage: %u\n",
			pmc.QuotaNonPagedPoolUsage);
		printf("\tPagefileUsage: %u\n", pmc.PagefileUsage);
		printf("\tPeakPagefileUsage: %u\n",
			pmc.PeakPagefileUsage);

		printf("\tPrivate Bytes: %u MB\n\n", pmc.PrivateUsage / 1024 / 1024);
	}

	CloseHandle(hProcess);
}

static void PrintMemoryUsage()
{
	// Get the list of process identifiers.
	DWORD processes[1024], processIdentifierCount, numberOfProcesses;
	unsigned int i;

	if (!EnumProcesses(processes, sizeof(processes), &processIdentifierCount))
	{
		wcerr << "Failed to retrieve the processor informations!" << endl;
		return;
	}

	// Calculate how many process identifiers were returned.
	numberOfProcesses = processIdentifierCount / sizeof(DWORD);

	// Print the memory usage for each process
	for (auto index = 0; index < processIdentifierCount; index++)
	{
		PrintMemoryInfo(processes[index]);
	}
}

static void PrintTableRow(time_point<system_clock> &startTime, int bytesToAllocate)
{
	const int conversionToBytes = 1024 * 1024;

	// Query the memory state
	MEMORYSTATUS memoryStatus;
	GlobalMemoryStatus(&memoryStatus);

	std::chrono::duration<double> elapsedSeconds = system_clock::now() - startTime;
	GlobalMemoryStatus(&memoryStatus);
	wcout << right << setw(6) << fixed << setprecision(2) << elapsedSeconds.count() << L" [sec]\t";
	wcout << right << setw(13) << fixed << memoryStatus.dwAvailPhys / conversionToBytes << L" [MB]\t";
	wcout << right << setw(12) << fixed << memoryStatus.dwAvailVirtual / conversionToBytes << L" [MB]\t";
	wcout << right << setw(11) << fixed << bytesToAllocate / conversionToBytes << L" [MB]" << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// Command line parsing
	auto duration = 3;
	auto cycleCount = 8;
	
	switch (argc)
	{
		case 2:
		{
			// Assume unicode
			wstring durationArgument(argv[1]);
			if (0 == durationArgument.find_first_of(L"-d"))
			{
				duration = stoi(durationArgument.substr(2, durationArgument.size()));
			}
			break;
		}

		default:
			if (0 < argc)
			{
				wcout << endl << argv[0] << L" [-d]" << endl;
				wcout << endl << L"  -d\tDefines the duration of the allocation scenarios." << endl;
			}
			break;
	}

	wcout << endl << L"Allocating memory for " << duration << L" minutes." << endl << endl;

	try
	{
		// Random percent
		const double LowerDistributionBound = 0.3;
		const double UpperDistributionBound = 0.7;
		uniform_real_distribution<double> distribution(LowerDistributionBound, UpperDistributionBound);
		random_device randomDevice;
		std::mt19937 randomEngine(randomDevice());

		// Print header
		auto consoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO originalColors;
		GetConsoleScreenBufferInfo(consoleOutHandle, &originalColors);
		wcout << L"Elapsed Time\tAvailable Physical\tAvailable Virtual\tAllocated Memory" << endl;

		// Start time
		time_point<system_clock> startTime = system_clock::now();
		time_point<system_clock> endTime = startTime + minutes(duration);
		DWORD BreakDuration = 3000;
		while (system_clock::now() < endTime)
		{
			for (auto cycle = 0; cycle < cycleCount; cycle++)
			{
				// Random percent calculating
				double memoryPercent = distribution(randomEngine);

				// Query the memory state
				MEMORYSTATUS memoryStatus;
				GlobalMemoryStatus(&memoryStatus);

				// Allocate memory
				auto bytesToAllocate = memoryPercent * memoryStatus.dwAvailVirtual;
				auto memoryHandle = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, bytesToAllocate);
				if (0 == memoryHandle)
				{
					SetConsoleTextAttribute(consoleOutHandle, RED | BGBLACK);
					PrintTableRow(startTime, bytesToAllocate);
					wcerr << L"Allocation failed. Trying again" << endl;
					SetConsoleTextAttribute(consoleOutHandle, originalColors.wAttributes);
					continue;
				}

				// Print the memory infos
				PrintTableRow(startTime, bytesToAllocate);

				// Free the allocated memory
				GlobalFree(memoryHandle);
			}
			Sleep(BreakDuration);
		}
	}
	catch (...)
	{
		wcerr << L"Running the allocation scenarios failed!" << endl;
	}

	system("PAUSE");
	return 0;
}

