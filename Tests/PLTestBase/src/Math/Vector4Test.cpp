/*********************************************************\
 *  File: Vector4Test.cpp                                *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include "PLTestBase/Math/Vector4Test.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ Vector2Test implementation                            ]
//[-------------------------------------------------------]
const char *Vector4Test::GetName() const
{
	return "Vector4";
}

void Vector4Test::Test()
{
	float fT4[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	Matrix4x4 m4x4;
	float fX, fY, fZ, fW;
	bool bResult;
	Vector3 vV3;
	Vector4 vV;

	// Vector constructors & copy
	StartTask("Vector constructors & copy");
	bResult = true;
	if (vV.x != 0.0f || vV.y != 0.0f || vV.z != 0.0f || vV.w != 1.0f) bResult = false;
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f || vV.w != 4.0f) bResult = false;
	vV = Vector4(fT4);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f || vV.w != 4.0f) bResult = false;
	vV = Vector4(vV);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f || vV.w != 4.0f) bResult = false;
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Vector4::Zero.x != 0.0f || Vector4::Zero.y != 0.0f || Vector4::Zero.z != 0.0f || Vector4::Zero.w != 0.0f) bResult = false;
	if (Vector4::One.x != 1.0f || Vector4::One.y != 1.0f || Vector4::One.z != 1.0f || Vector4::One.w != 1.0f) bResult = false;
	if (Vector4::UnitX.x != 1.0f || Vector4::UnitX.y != 0.0f || Vector4::UnitX.z != 0.0f || Vector4::UnitX.w != 1.0f) bResult = false;
	if (Vector4::UnitY.x != 0.0f || Vector4::UnitY.y != 1.0f || Vector4::UnitY.z != 0.0f || Vector4::UnitY.w != 1.0f) bResult = false;
	if (Vector4::UnitZ.x != 0.0f || Vector4::UnitZ.y != 0.0f || Vector4::UnitZ.z != 1.0f || Vector4::UnitZ.w != 1.0f) bResult = false;
	if (Vector4::UnitW.x != 0.0f || Vector4::UnitW.y != 0.0f || Vector4::UnitW.z != 0.0f || Vector4::UnitW.w != 1.0f) bResult = false;
	if (Vector4::NegativeUnitX.x != -1.0f || Vector4::NegativeUnitX.y != 0.0f || Vector4::NegativeUnitX.z != 0.0f || Vector4::NegativeUnitX.w != 1.0f) bResult = false;
	if (Vector4::NegativeUnitY.x != 0.0f || Vector4::NegativeUnitY.y != -1.0f || Vector4::NegativeUnitY.z != 0.0f || Vector4::NegativeUnitY.w != 1.0f) bResult = false;
	if (Vector4::NegativeUnitZ.x != 0.0f || Vector4::NegativeUnitZ.y != 0.0f || Vector4::NegativeUnitZ.z != -1.0f || Vector4::NegativeUnitZ.w != 1.0f) bResult = false;
	if (Vector4::NegativeUnitW.x != 0.0f || Vector4::NegativeUnitW.y != 0.0f || Vector4::NegativeUnitW.z != 0.0f || Vector4::NegativeUnitW.w != -1.0f) bResult = false;
	EndTask(bResult);


// Comparison
	// ==
	StartTask("==");
	EndTask(Vector4(1.0f, 2.0f, 3.0f, 4.0f) == Vector4(1.0f, 2.0f, 3.0f, 4.0f) &&
			!(Vector4(1.0f, 2.0f, 3.0f, 4.0f) == Vector4(1.0f, 2.0001f, 3.0f, 4.0f)));
	// !=
	StartTask("!=");
	EndTask(!(Vector4(1.0f, 2.0f, 3.0f, 4.0f) != Vector4(1.0f, 2.0f, 3.0f, 4.0f)) &&
			Vector4(1.0f, 2.0f, 3.0f, 4.0f) != Vector4(1.0f, 2.0001f, 3.0f, 4.0f));
	// >
	StartTask(">");
	EndTask(!(Vector4(1.0f, 2.0f, 3.0f, 4.0f) > Vector4(2.0f, 3.0f, 4.0f, 5.0f)) &&
			Vector4(2.0f, 3.0f, 4.0f, 5.0f) > Vector4(1.0f, 2.0f, 3.0f, 4.0f) &&
			!(Vector4(1.0f, 2.0f, 3.0f, 4.0f) > Vector4(1.0f, 2.0, 3.0f, 4.0f)));
	// <
	StartTask("<");
	EndTask(!(Vector4(2.0f, 3.0f, 4.0f, 5.0f) < Vector4(1.0f, 2.0f, 3.0f, 4.0f)) &&
			Vector4(1.0f, 2.0f, 3.0f, 4.0f) < Vector4(2.0f, 3.0f, 4.0f, 5.0f) &&
			!(Vector4(1.0f, 2.0, 3.0f, 4.0f) < Vector4(1.0f, 2.0f, 3.0f, 4.0f)));
	// >=
	StartTask(">=");
	EndTask(!(Vector4(1.0f, 2.0f, 3.0f, 4.0f) >= Vector4(2.0f, 3.0f, 4.0f, 5.0f)) &&
			Vector4(2.0f, 3.0f, 4.0f, 5.0f) >= Vector4(1.0f, 2.0f, 3.0f, 4.0f) &&
			Vector4(1.0f, 2.0f, 3.0f, 4.0f) >= Vector4(1.0f, 2.0f, 3.0f, 4.0f));
	// <=
	StartTask("<=");
	EndTask(!(Vector4(2.0f, 3.0f, 4.0f, 5.0f) <= Vector4(1.0f, 2.0f, 3.0f, 4.0f)) &&
			Vector4(1.0f, 2.0f, 3.0f, 4.0f) <= Vector4(2.0f, 3.0f, 4.0f, 5.0f) &&
			Vector4(1.0f, 2.0, 3.0f, 4.0f) <= Vector4(1.0f, 2.0f, 3.0f, 4.0f));


// Addition
	// + Vector4
	StartTask("+ Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)+Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f && vV.w == 8.0f);
	// + float
	StartTask("+ float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)+2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f && vV.z == 5.0f && vV.w == 6.0f);
	// += Vector4
	StartTask("+= Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV += Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f && vV.w == 8.0f);
	// += float
	StartTask("+= float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV += 2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f && vV.z == 5.0f && vV.w == 6.0f);


// Subtraction
	// -
	StartTask("-");
	vV = -Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == -1.0f && vV.y == -2.0f && vV.z == -3.0f && vV.w == -4.0f);
	// - Vector4
	StartTask("- Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)-Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f && vV.z == 0.0f && vV.w == 0.0f);
	// - float
	StartTask("- float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)-2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f && vV.z == 1.0f && vV.w == 2.0f);
	// -= Vector4
	StartTask("-= Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV -= Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f && vV.z == 0.0f && vV.w == 0.0f);
	// -= float
	StartTask("-= float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV -= 2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f && vV.z == 1.0f && vV.w == 2.0f);
	// Vector4()-(-Vector4())
	StartTask("Vector4()-(-Vector4())");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)-(-Vector4(1.0f, 2.0f, 3.0f, 4.0f));
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f && vV.w == 8.0f);


// Multiplication
	// * Vector4
	StartTask("* Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)*Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 9.0f && vV.w == 16.0f);
	// * float
	StartTask("* float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)*2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f && vV.w == 8.0f);
	// *= Vector4
	StartTask("*= Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV *= Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 9.0f && vV.w == 16.0f);
	// *= float
	StartTask("*= float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV *= 2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f && vV.w == 8.0f);

	// *= Matrix4x4
	StartTask("*= Matrix4x4");
	bResult = true;
	// 90°
	vV = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m4x4.FromEulerAngleY(static_cast<float>(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, -1.0f) || !Math::AreEqual(vV.w, 1.0f)) bResult = false;
	// -90°
	vV = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m4x4.FromEulerAngleY(-static_cast<float>(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f) || !Math::AreEqual(vV.w, 1.0f)) bResult = false;
	// -90° + translation (2, 3, 4)
	vV = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m4x4.FromEulerAngleY(-static_cast<float>(90.0f*Math::DegToRad));
	m4x4.SetTranslation(2.0f, 3.0f, 4.0f);
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 2.0f) || !Math::AreEqual(vV.y, 3.0f) || !Math::AreEqual(vV.z, 5.0f) || !Math::AreEqual(vV.w, 1.0f)) bResult = false;
	EndTask(bResult);


// Division
	// / Vector4
	StartTask("/ Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)/Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f && vV.z == 1.0f && vV.w == 1.0f);
	// / float
	StartTask("/ float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f)/2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f && vV.z == 1.5f && vV.w == 2.0f);
	// /= Vector4
	StartTask("/= Vector4");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV /= Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f && vV.z == 1.0f && vV.w == 1.0f);
	// /= float
	StartTask("/= float");
	vV = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
	vV /= 2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f && vV.z == 1.5f && vV.w == 2.0f);


// Get and set
	/* [TODO]
	// operator Vector3()
	StartTask("operator Vector3()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
//	vV3 = vV;
	EndTask(vV3.x == 0.0f && vV3.y == 1.0f && vV3.z == 2.0f);
	*/

	{ // operator float *()
		StartTask("operator float *()");
		vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
		float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f && pf[2] == 2.0f && pf[3] == 3.0f);
	}

	{ // const operator float *()
		StartTask("const operator float *()");
		vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
		const float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f && pf[2] == 2.0f && pf[3] == 3.0f);
	}

	// float &operator [](int)
	StartTask("float &operator [](int)");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	EndTask(vV[0] == 0.0f && vV[1] == 1.0f && vV[2] == 2.0f && vV[3] == 3.0f);

	// GetXYZW()
	StartTask("GetXYZW()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	vV.GetXYZW(fX, fY, fZ, fW);
	EndTask(fX == 0.0f && fY == 1.0f && fZ == 2.0f && fW == 3.0f);

	// GetX()
	StartTask("GetX()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	EndTask(vV.GetX() == 0.0f);

	// GetY()
	StartTask("GetY()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	EndTask(vV.GetY() == 1.0f);

	// GetZ()
	StartTask("GetZ()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	EndTask(vV.GetZ() == 2.0f);

	// GetW()
	StartTask("GetW()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	EndTask(vV.GetW() == 3.0f);

	// SetXYZ(float, float, float)
	StartTask("SetXYZ(float, float, float)");
	vV.w = 99.0f;
	vV.SetXYZ(0.0f, 1.0f, 2.0f);
	EndTask(vV.x == 0.0f && vV.y == 1.0f && vV.z == 2.0f && vV.w == 99.0f);

	// SetXYZ(const float[])
	StartTask("SetXYZ(const float[])");
	vV.w = 99.0f;
	vV.SetXYZ(fT4);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 99.0f);

	// SetXYZ(const Vector3 &)
	StartTask("SetXYZ(const Vector3 &)");
	vV3.x = 0.0f; vV3.y = 1.0f; vV3.z = 2.0f;
	vV.SetXYZ(vV3);
	EndTask(vV.x == 0.0f && vV.y == 1.0f && vV.z == 2.0f);

	// SetXYZW(float, float, float, float)
	StartTask("SetXYZW(float, float, float, float)");
	vV.SetXYZW(0.0f, 1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 0.0f && vV.y == 1.0f && vV.z == 2.0f && vV.w == 3.0f);

	// SetXYZW(const float[])
	StartTask("SetXYZW(const float[])");
	vV.SetXYZW(fT4);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 4.0f);

	// SetXYZW(const Vector3 &, float)
	StartTask("SetXYZW(const Vector3 &, float)");
	vV3.x = 0.0f; vV3.y = 1.0f; vV3.z = 2.0f;
	vV.SetXYZW(vV3, 1.0f);
	EndTask(vV.x == 0.0f && vV.y == 1.0f && vV.z == 2.0f && vV.w == 1.0f);

	// SetX()
	StartTask("SetX()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.SetX(0.0f);
	EndTask(vV.x == 0.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 4.0f);

	// SetY()
	StartTask("SetY()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.SetY(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 0.0f && vV.z == 3.0f && vV.w == 4.0f);

	// SetZ()
	StartTask("SetZ()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.SetZ(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 0.0f && vV.w == 4.0f);

	// SetW()
	StartTask("SetW()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.SetW(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 0.0f);

	// IncXYZW(float, float, float, float)
	StartTask("IncXYZW(float, float, float, float)");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	vV.IncXYZW(1.0f, 2.0f, 3.0f, 4.0f);
	EndTask(vV.x == 1.0f && vV.y == 3.0f && vV.z == 5.0f && vV.w == 7.0f);

	// IncXYZW(const float[])
	StartTask("IncXYZW(const float[])");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f; vV.w = 3.0f;
	vV.IncXYZW(fT4);
	EndTask(vV.x == 1.0f && vV.y == 3.0f && vV.z == 5.0f && vV.w == 7.0f);

	// IncX()
	StartTask("IncX()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.IncX(2.0f);
	EndTask(vV.x == 3.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 4.0f);

	// IncY()
	StartTask("IncY()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.IncY(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 3.0f && vV.w == 4.0f);

	// IncZ()
	StartTask("IncZ()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.IncZ(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 5.0f && vV.w == 4.0f);

	// IncW()
	StartTask("IncW()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	vV.IncW(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 6.0f);

	// ToString()
	StartTask("ToString()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	EndTask(vV.ToString() == "1 2 3 4");

	// FromString()
	StartTask("FromString()");
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV.FromString("1 2 3 4");
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f && vV.w == 4.0f);


// Misc
	// IsNull()
	StartTask("IsNull()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 5.0f; vV.w = 0.0f;
	if (vV.IsNull()) bResult = false;
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!vV.IsNull()) bResult = false;
	EndTask(bResult);

	// IsPacked()
	StartTask("IsPacked()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 5.0f; vV.w = 0.0f;
	if (vV.IsPacked()) bResult = false;
	vV.x = 0.3f; vV.y = 0.8f; vV.z = 0.0f; vV.w = 1.0f;
	if (!vV.IsPacked()) bResult = false;
	EndTask(bResult);

	// PackTo01()
	StartTask("PackTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f; vV.w = 0.1f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.7227177f) || !Math::AreEqual(vV.y, 0.9454354f) || 
		!Math::AreEqual(vV.z, 0.5f) || !Math::AreEqual(vV.w, 0.5445435f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f; vV.z = 1.0f; vV.w = 0.1f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.04364058f) || !Math::AreEqual(vV.y, 0.6825437f) || 
		!Math::AreEqual(vV.z, 0.5912718f) || !Math::AreEqual(vV.w, 0.5091272f)) bResult = false;
	EndTask(bResult);

	// GetPackedTo01()
	StartTask("GetPackedTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f; vV.w = 0.1f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.7227177f) || !Math::AreEqual(vV.y, 0.9454354f) || 
		!Math::AreEqual(vV.z, 0.5f) || !Math::AreEqual(vV.w, 0.5445435f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f; vV.z = 1.0f; vV.w = 0.1f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.04364058f) || !Math::AreEqual(vV.y, 0.6825437f) || 
		!Math::AreEqual(vV.z, 0.5912718f) || !Math::AreEqual(vV.w, 0.5091272f)) bResult = false;
	EndTask(bResult);

	// UnpackFrom01()
	StartTask("UnpackFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f; vV.w = 0.1f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f) || 
		!Math::AreEqual(vV.z, -1.0f) || !Math::AreEqual(vV.w, -0.8f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f; vV.z = 0.0f; vV.w = 0.1f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f) || 
		!Math::AreEqual(vV.z, -1.0f) || !Math::AreEqual(vV.w, -0.8f)) bResult = false;
	EndTask(bResult);

	// GetUnpackedFrom01()
	StartTask("GetUnpackedFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f; vV.w = 0.1f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f) || 
		!Math::AreEqual(vV.z, -1.0f) || !Math::AreEqual(vV.w, -0.8f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f; vV.z = 0.0f; vV.w = 0.1f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f) || 
		!Math::AreEqual(vV.z, -1.0f) || !Math::AreEqual(vV.w, -0.8f)) bResult = false;
	EndTask(bResult);

	// GetSmallestComponent()
	StartTask("GetSmallestComponent()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	EndTask(vV.GetSmallestComponent() == Vector4::X);

	// GetSmallestValue()
	StartTask("GetSmallestValue()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	EndTask(vV.GetSmallestValue() == 1.0f);

	// GetGreatestComponent()
	StartTask("GetGreatestComponent()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	EndTask(vV.GetGreatestComponent() == Vector4::W);

	// GetGreatestValue()
	StartTask("GetGreatestValue()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f; vV.w = 4.0f;
	EndTask(vV.GetGreatestValue() == 4.0f);

	// Invert()
	StartTask("Invert()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	vV.Invert();
	EndTask(vV.x == -0.2f && vV.y == 0.6f && vV.z == 0.0f && vV.w == -1.0f);

	// GetInverted()
	StartTask("GetInverted()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	vV = vV.GetInverted();
	EndTask(vV.x == -0.2f && vV.y == 0.6f && vV.z == 0.0f && vV.w == -1.0f);

	// GetLength()
	bResult = true;
	StartTask("GetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	if (!Math::AreEqual(vV.GetLength(), 1.183216f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 1.0f)) bResult = false;
	EndTask(bResult);

	// GetSquaredLength()
	bResult = true;
	StartTask("GetSquaredLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 1.4f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 1.0f)) bResult = false;
	EndTask(bResult);
	
	// SetLength()
	bResult = true;
	StartTask("SetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.1690308f) || 
		!Math::AreEqual(vV.y, -0.5070926f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.8451542f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) || 
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) || 
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f)) bResult = false;
	EndTask(bResult);

	// Normalize()
	bResult = true;
	StartTask("Normalize()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.1690308f) ||
		!Math::AreEqual(vV.y, -0.5070926f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.8451542f))  bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f))  bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f))  bResult = false;
	EndTask(bResult);

	// GetNormalized()
	bResult = true;
	StartTask("GetNormalized()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.1690308f) ||
		!Math::AreEqual(vV.y, -0.5070926f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.8451542f))  bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f))  bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f; vV.w = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f) || !Math::AreEqual(vV.w, 0.0f))  bResult = false;
	EndTask(bResult);

	// GetDistance()
	StartTask("GetDistance()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	EndTask(Math::AreEqual(vV.GetDistance(Vector4(0.0f, 0.0f, 0.0f, 0.0f)), 1.183216f));

	// GetSquaredDistance()
	StartTask("GetSquaredDistance()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	EndTask(Math::AreEqual(vV.GetSquaredDistance(Vector4(0.0f, 0.0f, 0.0f, 0.0f)), 1.4f));

	// DotProduct()
	StartTask("DotProduct()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f; vV.w = 1.0f;
	EndTask(Math::AreEqual(vV.DotProduct(Vector4(0.0f, 0.0f, 0.0f, 0.0f)), 0.0f) &&
			Math::AreEqual(vV.DotProduct(Vector4(0.2f, -0.6f, 0.0f, 1.0f)), 1.4f));

	// GetAngle()
	StartTask("GetAngle()");
	bResult = true;
	// ~69.5°
	vV.x = 1.0f; vV.y = 4.0f; vV.z = -2.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector4(-3.0f, 3.0f, 1.0f, 0.0f)), 1.2127572f)) bResult = false;
	// 45°
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 0.0f; vV.w = 0.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector4(1.0f, 1.0f, 0.0f, 0.0f)), 0.7853981f)) bResult = false;
	// Now use normalized vectors and use the dot product... (~69.5°)
	vV.x = 1.0f; vV.y = 4.0f; vV.z = -2.0f; vV.w = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(Math::ACos(vV.DotProduct(Vector4(-3.0f, 3.0f, 1.0f, 0.0f).Normalize())), 1.2127573f)) bResult = false;
	EndTask(bResult);
	
/* [TODO]
		PLMATH_API Vector4 ProjectVector(const Vector4 &vA, const Vector4 &vB) const;
		PLMATH_API Vector4 &GetProjection(const Vector4 &vX, const Vector4 &vN);
		PLMATH_API Vector4 &ProjectPlane(const Vector4 &vV1, const Vector4 &vV2);
	// 
	StartTask("");
	EndTask();

	// 
	StartTask("");
	EndTask();
*/
}
