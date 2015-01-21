#include "IAllocationScenario.h"
#include "AllocationResult.h"

#include <vector>

#ifndef _VECTOR_ALLOCATOR_
#define _VECTOR_ALLOCATOR_

namespace edu {
	namespace memory {

		/*!
		 * Allocator using STL vector.
		*/
		class VectorAllocator : public IAllocationScenario {

		public:
			VectorAllocator(std::size_t numberOfElements);
			virtual ~VectorAllocator();

			virtual std::wstring scenarioName() override;

			virtual AllocationResult allocate() override;

			virtual void deallocate() override;

		private:
			std::size_t _numberOfElements;
			std::vector<std::wstring> _stringCollection;
		};
	}
}

#endif