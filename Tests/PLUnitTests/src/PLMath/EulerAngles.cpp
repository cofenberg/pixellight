//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/EulerAngles.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Quaternion.h>

using namespace PLMath;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(EulerAngles) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTest
	{
		ConstructTest() { 
			/* some setup */
			EPSI = 1.0E-5f;
		}
		~ConstructTest() {
			/* some teardown */
		}

		void ClearData() {
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			fAngleZ = 0.0f;
			mRot.SetIdentity();
			qRot.SetWXYZ(1.0f, 0.0f, 0.0f, 0.0f);
		}

		void CheckEulerAngleX(float fAngle, float fExpectedAngle)
		{
			this->ClearData();

			// Degree to radian
			fAngle         = static_cast<float>(fAngle*Math::DegToRad);
			fExpectedAngle = static_cast<float>(fExpectedAngle*Math::DegToRad);

			// FromEulerAngleX() & FromMatrix()
			mRot.FromEulerAngleX(fAngle);
			EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);

			CHECK_CLOSE(fAngleX, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleY);
			CHECK_EQUAL(0.0f, fAngleZ);

			// The other functions must return the same values...
			Matrix3x3 mRotT;
			EulerAngles::ToMatrix(fAngle, 0.0f, 0.0f, mRot);

			// [TODO]: is this comparison implemented?
			if (mRot != mRotT)
				CHECK(false); // Error!
			// CHECK(mRot == mRotT);

			// ToQuaternion() & FromQuaternion()
			EulerAngles::ToQuaternion(fAngle, 0.0f, 0.0f, qRot);
			EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);

			CHECK_CLOSE(fAngleX, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleY);
			CHECK_EQUAL(0.0f, fAngleZ);
		}

		void CheckEulerAngleY(float fAngle, float fExpectedAngle)
		{
			this->ClearData();

			// Degree to radian
			fAngle         = static_cast<float>(fAngle*Math::DegToRad);
			fExpectedAngle = static_cast<float>(fExpectedAngle*Math::DegToRad);

			// FromEulerAngleY() & FromMatrix()
			mRot.FromEulerAngleY(fAngle);
			EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);

			CHECK_CLOSE(fAngleY, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleX);
			CHECK_EQUAL(0.0f, fAngleZ);

			// The other functions must return the same values...
			Matrix3x3 mRotT;
			EulerAngles::ToMatrix(0.0f, fAngle, 0.0f, mRot);

			// [TODO]: is this comparison implemented?
			if (mRot != mRotT)
				CHECK(false); // Error!
			// CHECK(mRot == mRotT);

			// ToQuaternion() & FromQuaternion()
			EulerAngles::ToQuaternion(0.0f, fAngle, 0.0f, qRot);
			EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);
		
			CHECK_CLOSE(fAngleY, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleX);
			CHECK_EQUAL(0.0f, fAngleZ);
		}

		void CheckEulerAngleZ(float fAngle, float fExpectedAngle)
		{
			this->ClearData();

			// Degree to radian
			fAngle         = static_cast<float>(fAngle*Math::DegToRad);
			fExpectedAngle = static_cast<float>(fExpectedAngle*Math::DegToRad);

			// FromEulerAngleY() & FromMatrix()
			mRot.SetZero();
			mRot.FromEulerAngleZ(fAngle);
			EulerAngles::FromMatrix(mRot, fAngleX, fAngleY, fAngleZ);

			CHECK_CLOSE(fAngleZ, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleX);
			CHECK_EQUAL(0.0f, fAngleY);

			// The other functions must return the same values...
			Matrix3x3 mRotT;
			EulerAngles::ToMatrix(0.0f, fAngle, 0.0f, mRot);

			// [TODO]: is this comparison implemented?
			if (mRot != mRotT)
				CHECK(false); // Error!
			// CHECK(mRot == mRotT);

			// ToQuaternion() & FromQuaternion()
			EulerAngles::ToQuaternion(0.0f, fAngle, 0.0f, qRot);
			EulerAngles::FromQuaternion(qRot, fAngleX, fAngleY, fAngleZ);
		
			CHECK_CLOSE(fAngleZ, fExpectedAngle, EPSI);
			CHECK_EQUAL(0.0f, fAngleX);
			CHECK_EQUAL(0.0f, fAngleY);
		}
		
		// Objects for testing
		float fAngleX, fAngleY, fAngleZ;
		Matrix3x3 mRot;
		Quaternion qRot;

		// epsilon
		float EPSI;
	};

	// copied from PLTestBase
	TEST_FIXTURE(ConstructTest, EulerAngle_360) {
		CheckEulerAngleX(360.0f, 0.0f);

		CheckEulerAngleY(360.0f, 0.0f);

		CheckEulerAngleZ(360.0f, 0.0f);
	}
}