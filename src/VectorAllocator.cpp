#include "VectorAllocator.h"

namespace edu {
	namespace memory {

		VectorAllocator::VectorAllocator(std::size_t numberOfElements) : _numberOfElements(numberOfElements)
		{
			// Do not allow default size reserving
			_stringCollection.reserve(0);
		}

		VectorAllocator::~VectorAllocator()
		{
		}

		std::wstring VectorAllocator::scenarioName()
		{
			return L"STL Vector allocation";
		}

		AllocationResult VectorAllocator::allocate()
		{
			_stringCollection.reserve(_numberOfElements);
			AllocationResult result(true, sizeof(_stringCollection) * _numberOfElements);
			return result;
		}

		void VectorAllocator::deallocate()
		{
			std::vector<std::wstring> empty;
			empty.reserve(0);
			_stringCollection.swap(empty);
		}
	}
}