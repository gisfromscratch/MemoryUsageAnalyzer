#include "RandomGlobalAllocator.h"

namespace edu {
	namespace memory {

		RandomGlobalAllocator::RandomGlobalAllocator() : _memoryHandle(0)
		{
			// Random percent
			const double LowerDistributionBound = 0.3;
			const double UpperDistributionBound = 0.7;
			_distribution = uniform_real_distribution<double>(LowerDistributionBound, UpperDistributionBound);
			random_device randomDevice;
			_randomEngine = mt19937(randomDevice());
		}

		RandomGlobalAllocator::~RandomGlobalAllocator()
		{
		}

		std::wstring RandomGlobalAllocator::scenarioName()
		{
			return L"Random Global Allocator";
		}

		AllocationResult RandomGlobalAllocator::allocate()
		{
			// Random percent calculating
			double memoryPercent = _distribution(_randomEngine);

			// Query the memory state
			MEMORYSTATUS memoryStatus;
			GlobalMemoryStatus(&memoryStatus);

			// Allocate memory
			auto bytesToAllocate = memoryPercent * memoryStatus.dwAvailVirtual;
			_memoryHandle = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, bytesToAllocate);
			if (0 == _memoryHandle)
			{
				return AllocationResult(false, bytesToAllocate);
			}

			return AllocationResult(true, bytesToAllocate);
		}

		void RandomGlobalAllocator::deallocate()
		{
			if (0 == _memoryHandle)
			{
				return;
			}

			GlobalFree(_memoryHandle);
			_memoryHandle = 0;
		}
	}
}