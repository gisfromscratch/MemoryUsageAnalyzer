#ifndef _ALLOCATION_RESULT_
#define _ALLOCATION_RESULT_

namespace edu {
	namespace memory {

		/*!
		* Result of an allocation.
		*/
		class AllocationResult {

		public:
			AllocationResult(bool succeeded, size_t bytes) : _succeeded(succeeded), _bytes(bytes)
			{}
			~AllocationResult()
			{}

			bool succeeded()
			{
				return _succeeded;
			}

			size_t bytes()
			{
				return _bytes;
			}

		private:
			bool _succeeded;
			size_t _bytes;
		};
	}
}

#endif