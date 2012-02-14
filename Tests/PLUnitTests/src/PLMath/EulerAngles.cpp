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
		// checking CHECK_MATRIX3X3 macro
		Matrix3x3 m1, m2;

		m1.Set(1,2,3,4,5,6,7,8,9);
		m2.Set(1,2,3,4,5,6,7,8,9);

		CHECK_MATRIX3X3(m1, m2, 0.01f);
	}

	TEST_FIXTURE(ConstructTest, FromMatrix) {
		// actual test
		for (float x=0.0; x<=2*PI; x+=PI/4) {
			mRotX.FromEulerAngleX(x);

			for (float y=0.0; y<=2*PI; y+=PI/4) {
				mRotY.FromEulerAngleY(y);

				for (float z=0.0; z<=2*PI; z+=PI/4) {
					mRotZ.FromEulerAngleZ(z);

					mRot =  mRotX * mRotY * mRotZ;

					EulerAngles::FromMatrix(mRot, fX, fY, fZ);

					mEulX.FromEulerAngleX(fX);
					mEulY.FromEulerAngleY(fY);
					mEulZ.FromEulerAngleZ(fZ);

					mEul = mEulZ * mEulY * mEulX;

					printf("x=%f y=%f z=%f\n", x, y, z);
					CHECK_MATRIX3X3(mEul, mRot, 0.01f);
				}
			}
		}
	}

	TEST_FIXTURE(ConstructTest, konkret) {
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

            printf("x=%f y=%f z=%f\n", fX, fY, fZ);
            CHECK_MATRIX3X3(mEul, mRot, 0.01f);
    }
}