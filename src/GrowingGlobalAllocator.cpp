#include "GrowingGlobalAllocator.h"

namespace edu {
	namespace memory {

		GrowingGlobalAllocator::GrowingGlobalAllocator(size_t bytesToAllocate, size_t chunkSize) :
			_bytesToAllocate(bytesToAllocate),
			_chunkSize(chunkSize)
		{
		}

		GrowingGlobalAllocator::~GrowingGlobalAllocator()
		{
		}

		std::wstring GrowingGlobalAllocator::scenarioName()
		{
			return L"Growing Global Allocator";
		}

		AllocationResult GrowingGlobalAllocator::allocate()
		{
			_memoryHandle = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, _bytesToAllocate);
			if (0 == _memoryHandle)
			{
				return AllocationResult(false, _bytesToAllocate);
			}

			AllocationResult result(true, _bytesToAllocate);
			// Raise the number of bytes for the next cycle
			_bytesToAllocate += _chunkSize;
			return result;
		}

		void GrowingGlobalAllocator::deallocate()
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