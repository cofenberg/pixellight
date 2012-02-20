//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/EulerAngles.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Quaternion.h>
#include "UnitTest++AddIns/PLCheckMacros.h"
#include "UnitTest++AddIns/PLChecks.h"

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
			PI  = static_cast<float>(Math::Pi);
		}
		~ConstructTest() {
			/* some teardown */
		}

		// Objects for testing
		float PI;

		float fX, fY, fZ;
		Matrix3x3 mRotX, mRotY, mRotZ;
		Matrix3x3 mEulX, mEulY, mEulZ;
		Matrix3x3 mRot, mEul;
	};

	TEST(CHECK_MATRIX3X3_MACRO) {
		// checking testmacro: CHECK_MATRIX3X3
		Matrix3x3 m1, m2;

		m1.Set(1,2,3,4,5,6,7,8,9);
		m2.Set(1,2,3,4,5,6,7,8,9);

		CHECK_MATRIX3X3(m1, m2, 0.01f);
	}

	TEST_FIXTURE(ConstructTest, Matrix_Functions) {
		int steps = 10;

		// actual test
		for (float x=0.0; x<=2*PI; x+=PI/steps) {
			mRotX.FromEulerAngleX(x);

			for (float y=0.0; y<=2*PI; y+=PI/steps) {
				mRotY.FromEulerAngleY(y);

				for (float z=0.0; z<=2*PI; z+=PI/steps) {
					mRotZ.FromEulerAngleZ(z);

					mRot =  mRotX * mRotY * mRotZ;

					EulerAngles::FromMatrix(mRot, fX, fY, fZ);

					// rotate back to get expected result
					mEulX.FromEulerAngleX(fX);
					mEulY.FromEulerAngleY(fY);
					mEulZ.FromEulerAngleZ(fZ);

					// [TODO] is this order ok?
					mEul = mEulZ * mEulY * mEulX;

					//printf("x=%f y=%f z=%f\n", x, y, z);
					CHECK_MATRIX3X3(mEul, mRot, 0.0001f);

					EulerAngles::ToMatrix(fX, fY, fZ, mRot);

					CHECK_MATRIX3X3(mEul, mRot, 0.0001f);
				}
			}
		}
	}

	TEST_FIXTURE(ConstructTest, Matrix_Functions_SingleCase) {
            fX=PI/4;
            fY=0;
            fZ=0;

            mRotX.FromEulerAngleX(fX);
            mRotY.FromEulerAngleY(fY);
            mRotZ.FromEulerAngleZ(fZ);

            mRot =  mRotX * mRotY * mRotZ;

            EulerAngles::FromMatrix(mRot, fX, fY, fZ);

            mEulX.FromEulerAngleX(fX);
            mEulY.FromEulerAngleY(fY);
            mEulZ.FromEulerAngleZ(fZ);

            mEul = mEulZ * mEulY * mEulX;

            //printf("x=%f y=%f z=%f\n", fX, fY, fZ);
            CHECK_MATRIX3X3(mEul, mRot, 0.01f);
    }

	TEST_FIXTURE(ConstructTest, Quaternion_Functions) {
		CHECK_IMPLEMENT;
	}
}