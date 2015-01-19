#include "VectorAllocator.h"

namespace edu {
	namespace memory {

		VectorAllocator::VectorAllocator(std::size_t numberOfElements) : _numberOfElements(numberOfElements)
		{
			_stringCollection.reserve(0);
		}

		VectorAllocator::~VectorAllocator()
		{
		}

		std::wstring VectorAllocator::scenarioName()
		{
			return L"STL Vector allocation";
		}

		void VectorAllocator::allocate()
		{
			_stringCollection.reserve(_numberOfElements);
		}
	}
}