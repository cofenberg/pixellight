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
	TEST(IsNotANumber) {
		CHECK(!Math::IsNotANumber(0.0000001f));
		CHECK(!Math::IsNotANumber(0.0000000000000001));
	}

	TEST(IsFinite) {
		CHECK(Math::IsFinite(0.0000001f));
		CHECK(Math::IsFinite(0.0000000000000000000000000001));
	}

	TEST(IsPowerOfTwo) {
		// [TODO] 0 is NOT a power of two!
		CHECK(!Math::IsPowerOfTwo(0));
		CHECK(Math::IsPowerOfTwo(1));
		CHECK(Math::IsPowerOfTwo(2));
		CHECK(Math::IsPowerOfTwo(2147483648U));
		CHECK(!Math::IsPowerOfTwo(2147483649U));
	}

	TEST(GetNearestPowerOfTwo) {
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

	TEST(AreEqual_default_epsi) {
		CHECK(Math::AreEqual(0.0f, 0.0f));
		CHECK(Math::AreEqual(4.0f, 4.0f));
	}

	TEST(AreEqual_custom_epsi) {
		CHECK(Math::AreEqual(4.0f, 4.0f, 0.1f));
		CHECK(Math::AreEqual(4.0f, 3.9f, 0.1f));
		CHECK(!Math::AreEqual(4.0f, 3.89f, 0.1f));
	}

	TEST(Min_two_float) {
		CHECK_EQUAL(0.0f, Math::Min(0.0f, 0.0f));
		CHECK_EQUAL(0.0f, Math::Min(0.0f, 5.0f));

		CHECK_EQUAL(4.0f, Math::Min(4.0f, 5.0f));
		CHECK_EQUAL(5.0f, Math::Min(5.0000001f, 5.0f));
	}

	TEST(Min_four_float) {
		CHECK_EQUAL(0.0f, Math::Min(0.0f, 0.0f, 0.0f, 0.0f));
		CHECK_EQUAL(0.0f, Math::Min(0.0f, 5.0f, 3.0f, 2.3f));

		CHECK_EQUAL(4.0f, Math::Min(4.0f, 5.0f, 4.65f, 5.6f));
		CHECK_EQUAL(5.0f, Math::Min(5.0000001f, 5.0f, 6.2f, 7.0f));
	}

	TEST(Max_two_float) {
		CHECK_EQUAL(0.0f, Math::Max(0.0f, 0.0f));
		CHECK_EQUAL(5.0f, Math::Max(0.0f, 5.0f));

		CHECK_EQUAL(5.0f, Math::Max(4.0f, 5.0f));
		CHECK_EQUAL(5.0000001f, Math::Max(5.0000001f, 5.0f));
	}

	TEST(Max_four_float) {
		CHECK_EQUAL(0.0f, Math::Max(0.0f, 0.0f, 0.0f, 0.0f));
		CHECK_EQUAL(5.0f, Math::Max(0.0f, 5.0f, 3.0f, 2.3f));

		CHECK_EQUAL(5.6f, Math::Max(4.0f, 5.0f, 4.65f, 5.6f));
		CHECK_EQUAL(7.0f, Math::Max(5.0000001f, 5.0f, 6.2f, 7.0f));
	}

	TEST(Sign) {
		CHECK_EQUAL(1.0f, Math::Sign(0.0f));
		CHECK_EQUAL(1.0f, Math::Sign(-0.0f));
		CHECK_EQUAL(1.0f, Math::Sign(5.0f));
		CHECK_EQUAL(-1.0f, Math::Sign(-5.0f));
	}

	TEST(ClampToInterval_positive) {
		CHECK_EQUAL(1.0f, Math::ClampToInterval(0.0f, 1.0f, 2.0f));
		CHECK_EQUAL(1.0f, Math::ClampToInterval(1.0f, 1.0f, 2.0f));
		CHECK_EQUAL(1.5f, Math::ClampToInterval(1.5f, 1.0f, 2.0f));
		CHECK_EQUAL(2.0f, Math::ClampToInterval(2.1f, 1.0f, 2.0f));

		// TODO: catch this case? lower bound > upper bound
		CHECK_EQUAL(2.0f, Math::ClampToInterval(1.5f, 2.0f, 1.0f));
	}

	TEST(ClampToInterval_negative) {
		CHECK_EQUAL(-1.0f, Math::ClampToInterval(0.0f, -2.0f, -1.0f));
		CHECK_EQUAL(-1.0f, Math::ClampToInterval(-1.0f, -2.0f, -1.0f));
		CHECK_EQUAL(-1.5f, Math::ClampToInterval(-1.5f, -2.0f, -1.0f));
		CHECK_EQUAL(-2.0f, Math::ClampToInterval(-2.1f, -2.0f, -1.0f));
	}

	TEST(WrapToInterval_positive) {
		CHECK_EQUAL(1.0f, Math::WrapToInterval(0.0f, 1.0f, 2.0f));
		CHECK_EQUAL(1.0f, Math::WrapToInterval(1.0f, 1.0f, 2.0f));
		CHECK_EQUAL(1.5f, Math::WrapToInterval(1.5f, 1.0f, 2.0f));
		CHECK_EQUAL(2.0f, Math::WrapToInterval(2.1f, 1.0f, 2.0f));

		// TODO: catch this case?
		CHECK_EQUAL(2.0f, Math::WrapToInterval(1.5f, 2.0f, 1.0f));
	}

	TEST(Abs_float) {
		CHECK_EQUAL(1.0f, Math::Abs(1.0f));
		CHECK_EQUAL(1.0f, Math::Abs(-1.0f));
		CHECK_EQUAL(0.0f, Math::Abs(0.0f));
	}

	TEST(Abs_double) {
		CHECK_EQUAL(1.0, Math::Abs(1.0));
		CHECK_EQUAL(1.0, Math::Abs(-1.0));
		CHECK_EQUAL(0.0, Math::Abs(0.0));
	}

	TEST(Swap_float) {
		float a, b;
		a=5.0f;
		b=2.0f;
		Math::Swap(a, b);

		CHECK_EQUAL(5.0f, b);
		CHECK_EQUAL(2.0f, a);
	}

	TEST(RadToDeg) {
		float f = static_cast<float>(50.0f*Math::RadToDeg);
		double d = 50.0*Math::RadToDeg;

		CHECK_EQUAL(50.0f, static_cast<float>(f*Math::DegToRad));
		CHECK_EQUAL(50.0, d*Math::DegToRad);
	}

	TEST(DegToRad) {
		float f = static_cast<float>(50.0f*Math::DegToRad);
		double d = 50.0*Math::DegToRad;

		CHECK_EQUAL(50.0f, static_cast<float>(f*Math::RadToDeg));
		CHECK_EQUAL(50.0, d*Math::RadToDeg);
	}
} 