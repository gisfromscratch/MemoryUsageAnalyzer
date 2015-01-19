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
	PROCESS_MEMORY_COUNTERS pmc;

	// Print the process identifier.

	printf("\nProcess ID: %u\n", processID);

	// Print information about the memory usage of the process.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		printf("\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount);
		printf("\tPeakWorkingSetSize: 0x%08X\n",
			pmc.PeakWorkingSetSize);
		printf("\tWorkingSetSize: 0x%08X\n", pmc.WorkingSetSize);
		printf("\tQuotaPeakPagedPoolUsage: 0x%08X\n",
			pmc.QuotaPeakPagedPoolUsage);
		printf("\tQuotaPagedPoolUsage: 0x%08X\n",
			pmc.QuotaPagedPoolUsage);
		printf("\tQuotaPeakNonPagedPoolUsage: 0x%08X\n",
			pmc.QuotaPeakNonPagedPoolUsage);
		printf("\tQuotaNonPagedPoolUsage: 0x%08X\n",
			pmc.QuotaNonPagedPoolUsage);
		printf("\tPagefileUsage: 0x%08X\n", pmc.PagefileUsage);
		printf("\tPeakPagefileUsage: 0x%08X\n",
			pmc.PeakPagefileUsage);
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

