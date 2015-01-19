// Analyzer Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <Psapi.h>
#include <VectorAllocator.h>

using namespace edu::memory;
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


int _tmain(int argc, _TCHAR* argv[])
{
	// Print info
	//PrintMemoryUsage();
	PrintMemoryInfo(GetCurrentProcessId());

	// Throw some allocation scenarios in
	std::size_t numberOfElements = 1e6;
	VectorAllocator vectorAllocator(numberOfElements);
	wcout << vectorAllocator.scenarioName() << endl;
	vectorAllocator.allocate();

	// Print info
	//PrintMemoryUsage();
	PrintMemoryInfo(GetCurrentProcessId());

	system("PAUSE");
	return 0;
}

