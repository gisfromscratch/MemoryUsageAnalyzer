#include "IAllocationScenario.h"

#include <vector>

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

			virtual void allocate() override;

		private:
			std::size_t _numberOfElements;
			std::vector<std::wstring> _stringCollection;
		};
	}
}