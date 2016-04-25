#include "AllocationResult.h"

#include <string>

#ifndef _ALLOCATION_SCENARIO_
#define _ALLOCATION_SCENARIO_

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

			virtual AllocationResult allocate() = 0;

			virtual void deallocate() = 0;
		};
	}
}

#endif