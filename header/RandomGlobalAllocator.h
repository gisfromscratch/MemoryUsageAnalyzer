#include "IAllocationScenario.h"

#include <random>
#include <Windows.h>

using namespace std;

#ifndef _RANDOM_GLOBAL_ALLOCATOR_
#define _RANDOM_GLOBAL_ALLOCATOR_

namespace edu {
	namespace memory {

		/*!
		 * Random allocator using global allocation.
		*/
		class RandomGlobalAllocator : public IAllocationScenario {

		public:
			RandomGlobalAllocator();
			virtual ~RandomGlobalAllocator();

			virtual wstring scenarioName() override;

			virtual AllocationResult allocate() override;

			virtual void deallocate() override;

		private:
			uniform_real_distribution<double> _distribution;
			mt19937 _randomEngine;

			HGLOBAL _memoryHandle;
		};
	}
}

#endif