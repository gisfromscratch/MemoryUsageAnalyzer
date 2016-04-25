#include "IAllocationScenario.h"

#include <Windows.h>

#ifndef _GROWING_GLOBAL_ALLOCATOR_
#define _GROWING_GLOBAL_ALLOCATOR_

namespace edu {
	namespace memory {

		/*!
		 * Allocates using global allocation and tries to allocate more memory on each cycle.	
		 */
		class GrowingGlobalAllocator : public IAllocationScenario {

		public:
			GrowingGlobalAllocator(size_t bytesToAllocate, size_t chunkSize);
			virtual ~GrowingGlobalAllocator();

			virtual std::wstring scenarioName() override;

			virtual AllocationResult allocate() override;

			virtual void deallocate() override;

		private:
			size_t _bytesToAllocate;
			size_t _chunkSize;

			HGLOBAL _memoryHandle;
		};
	}
}

#endif