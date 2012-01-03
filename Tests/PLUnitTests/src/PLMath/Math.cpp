//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Math.h>

using namespace PLMath;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Math) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTest
	{
		ConstructTest() { 
			/* some setup */
		}
		~ConstructTest() {
			/* some teardown */
		}
	};

	// copied from PLTestBase
	TEST_FIXTURE(ConstructTest, IsNotANumber) {
		CHECK(!Math::IsNotANumber(0.0000001f));
		CHECK(!Math::IsNotANumber(0.0000000000000001));
	}

	TEST_FIXTURE(ConstructTest, IsFinite) {
		CHECK(Math::IsFinite(0.0000001f));
		CHECK(Math::IsFinite(0.0000000000000000000000000001));
	}

	TEST_FIXTURE(ConstructTest, IsPowerOfTwo) {
		// [TODO] 0 is NOT a power of two!
		CHECK(!Math::IsPowerOfTwo(0));
		CHECK(Math::IsPowerOfTwo(1));
		CHECK(Math::IsPowerOfTwo(2));
		CHECK(Math::IsPowerOfTwo(2147483648));
		CHECK(!Math::IsPowerOfTwo(2147483649));
	}

	TEST_FIXTURE(ConstructTest, GetNearestPowerOfTwo) {
		// [TODO] function assumes only unsigned integers! why not use uint? negative inputs are totally useless here...
		// lowest integer number
		CHECK_EQUAL(
			static_cast<int>(Math::Pow(2, sizeof(int)*8-1)),
			Math::GetNearestPowerOfTwo(static_cast<int>(Math::Pow(2, sizeof(int)*8-1)), true)
		);
		CHECK_EQUAL(-1, Math::GetNearestPowerOfTwo(-1, true));

		CHECK_EQUAL(0, Math::GetNearestPowerOfTwo(0, true));
		// [TODO] shouldn't this return 1 as its the nearest power of two above 0?
		//			Note: this function consideres the range 2^1 to 2^14 only! shouldn't it be 2^0 to 2^32?		
		CHECK_EQUAL(1, Math::GetNearestPowerOfTwo(0, false));
		CHECK_EQUAL(1, Math::GetNearestPowerOfTwo(1, true));
		CHECK_EQUAL(1, Math::GetNearestPowerOfTwo(1, false));
		CHECK_EQUAL(2, Math::GetNearestPowerOfTwo(3, true));
		CHECK_EQUAL(4, Math::GetNearestPowerOfTwo(3, false));

		CHECK_EQUAL(8192, Math::GetNearestPowerOfTwo(16383, true));
		CHECK_EQUAL(16384, Math::GetNearestPowerOfTwo(16383, false));
		
		// [TODO] function can't find these! it consideres the range 2^1 to 2^14 only!
		CHECK_EQUAL(536870912, Math::GetNearestPowerOfTwo(1073741823, true));
		CHECK_EQUAL(1073741824, Math::GetNearestPowerOfTwo(1073741823, false));

		// Test upper bound of integer range :)
		int upper = static_cast<int>(Math::Pow(2, sizeof(int)*8-1)-1);	// highest positive integer that is NOT a power of two
		int expect = static_cast<int>(Math::Pow(2, sizeof(int)*8-2));	// highest positive power of two

		// printf("upper: %d\nexpect: %d\n", upper, expect);

		// [TODO] what to expect here? should be hackable!
		// SCENARIO: nearest LOWER power of two of highest integer
		CHECK_EQUAL(expect, Math::GetNearestPowerOfTwo(upper, true));

		// thats OK, can't find the power of two higher than that, it's out of integer range
		// SCENARIO: nearest HIGHER power of two of highest integer
		CHECK_EQUAL(upper, Math::GetNearestPowerOfTwo(upper, false));
	}
}