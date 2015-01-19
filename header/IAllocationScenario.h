#include <string>

namespace edu {
	namespace memory {
		
		/*!
		 * Scenario allocating memory.
		*/
		class IAllocationScenario {

		public:
			IAllocationScenario() {}
			virtual ~IAllocationScenario() {}

			virtual std::wstring scenarioName() = 0;

			virtual void allocate() = 0;
		};
	}
}