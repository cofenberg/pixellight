/*********************************************************\
 *  File: Vector3Test.cpp                                *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Quaternion.h>
#include "PLTestBase/Math/Vector3Test.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ Vector3Test implementation                            ]
//[-------------------------------------------------------]
const char *Vector3Test::GetName() const
{
	return "Vector3";
}

void Vector3Test::Test()
{
	float fT3[3] = {1.0f, 2.0f, 3.0f};
	Matrix3x3 m3x3;
	Matrix4x4 m4x4;
	float fX, fY, fZ;
	Quaternion qQ;
	bool bResult;
	Vector3 vV;

	// Vector constructors & copy
	StartTask("Vector constructors & copy");
	bResult = true;
	if (vV.x != 0.0f || vV.y != 0.0f || vV.z != 0.0f) bResult = false;
	vV = Vector3(1.0f, 2.0f, 3.0f);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f) bResult = false;
	vV = Vector3(fT3);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f) bResult = false;
	vV = Vector3(vV);
	if (vV.x != 1.0f || vV.y != 2.0f || vV.z != 3.0f) bResult = false;
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Vector3::Zero.x != 0.0f || Vector3::Zero.y != 0.0f || Vector3::Zero.z != 0.0f) bResult = false;
	if (Vector3::One.x != 1.0f || Vector3::One.y != 1.0f || Vector3::One.z != 1.0f) bResult = false;
	if (Vector3::UnitX.x != 1.0f || Vector3::UnitX.y != 0.0f || Vector3::UnitX.z != 0.0f) bResult = false;
	if (Vector3::UnitY.x != 0.0f || Vector3::UnitY.y != 1.0f || Vector3::UnitY.z != 0.0f) bResult = false;
	if (Vector3::UnitZ.x != 0.0f || Vector3::UnitZ.y != 0.0f || Vector3::UnitZ.z != 1.0f) bResult = false;
	if (Vector3::NegativeUnitX.x != -1.0f || Vector3::NegativeUnitX.y != 0.0f || Vector3::NegativeUnitX.z != 0.0f) bResult = false;
	if (Vector3::NegativeUnitY.x != 0.0f || Vector3::NegativeUnitY.y != -1.0f || Vector3::NegativeUnitY.z != 0.0f) bResult = false;
	if (Vector3::NegativeUnitZ.x != 0.0f || Vector3::NegativeUnitZ.y != 0.0f || Vector3::NegativeUnitZ.z != -1.0f) bResult = false;
	EndTask(bResult);


// Comparison
	// ==
	StartTask("==");
	EndTask(Vector3(1.0f, 2.0f, 3.0f) == Vector3(1.0f, 2.0f, 3.0f) &&
			!(Vector3(1.0f, 2.0f, 3.0f) == Vector3(1.0f, 2.0001f, 3.0f)));
	// !=
	StartTask("!=");
	EndTask(!(Vector3(1.0f, 2.0f, 3.0f) != Vector3(1.0f, 2.0f, 3.0f)) &&
			Vector3(1.0f, 2.0f, 3.0f) != Vector3(1.0f, 2.0001f, 3.0f));
	// >
	StartTask(">");
	EndTask(!(Vector3(1.0f, 2.0f, 3.0f) > Vector3(2.0f, 3.0f, 4.0f)) &&
			Vector3(2.0f, 3.0f, 4.0f) > Vector3(1.0f, 2.0f, 3.0f) &&
			!(Vector3(1.0f, 2.0f, 3.0f) > Vector3(1.0f, 2.0, 3.0f)));
	// <
	StartTask("<");
	EndTask(!(Vector3(2.0f, 3.0f, 4.0f) < Vector3(1.0f, 2.0f, 3.0f)) &&
			Vector3(1.0f, 2.0f, 3.0f) < Vector3(2.0f, 3.0f, 4.0f) &&
			!(Vector3(1.0f, 2.0, 3.0f) < Vector3(1.0f, 2.0f, 3.0f)));
	// >=
	StartTask(">=");
	EndTask(!(Vector3(1.0f, 2.0f, 3.0f) >= Vector3(2.0f, 3.0f, 4.0f)) &&
			Vector3(2.0f, 3.0f, 4.0f) >= Vector3(1.0f, 2.0f, 3.0f) &&
			Vector3(1.0f, 2.0f, 3.0f) >= Vector3(1.0f, 2.0f, 3.0f));
	// <=
	StartTask("<=");
	EndTask(!(Vector3(2.0f, 3.0f, 4.0f) <= Vector3(1.0f, 2.0f, 3.0f)) &&
			Vector3(1.0f, 2.0f, 3.0f) <= Vector3(2.0f, 3.0f, 4.0f) &&
			Vector3(1.0f, 2.0, 3.0f) <= Vector3(1.0f, 2.0f, 3.0f));


// Addition
	// + Vector3
	StartTask("+ Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f)+Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f);
	// + float
	StartTask("+ float");
	vV = Vector3(1.0f, 2.0f, 3.0f)+2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f && vV.z == 5.0f);
	// += Vector3
	StartTask("+= Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV += Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f);
	// += float
	StartTask("+= float");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV += 2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f && vV.z == 5.0f);


// Subtraction
	// -
	StartTask("-");
	vV = -Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == -1.0f && vV.y == -2.0f && vV.z == -3.0f);
	// - Vector3
	StartTask("- Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f)-Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f && vV.z == 0.0f);
	// - float
	StartTask("- float");
	vV = Vector3(1.0f, 2.0f, 3.0f)-2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f && vV.z == 1.0f);
	// -= Vector3
	StartTask("-= Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV -= Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f && vV.z == 0.0f);
	// -= float
	StartTask("-= float");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV -= 2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f && vV.z == 1.0f);
	// Vector3()-(-Vector3())
	StartTask("Vector3()-(-Vector3())");
	vV = Vector3(1.0f, 2.0f, 3.0f)-(-Vector3(1.0f, 2.0f, 3.0f));
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f);


// Multiplication
	// * Vector3
	StartTask("* Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f)*Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 9.0f);
	// * float
	StartTask("* float");
	vV = Vector3(1.0f, 2.0f, 3.0f)*2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f);
	// *= Vector3
	StartTask("*= Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV *= Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 9.0f);
	// *= float
	StartTask("*= float");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV *= 2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f && vV.z == 6.0f);

	// *= Matrix3x3
	StartTask("*= Matrix3x3");
	bResult = true;
	// 90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	m3x3.FromEulerAngleY(float(90.0f*Math::DegToRad));
	vV *= m3x3;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	// -90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	m3x3.FromEulerAngleY(-float(90.0f*Math::DegToRad));
	vV *= m3x3;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	EndTask(bResult);

	// *= Matrix4x4
	StartTask("*= Matrix4x4");
	bResult = true;
	// 90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	m4x4.FromEulerAngleY(float(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	// -90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	m4x4.FromEulerAngleY(-float(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	// -90° + translation (2, 3, 4)
	vV = Vector3(1.0f, 0.0f, 0.0f);
	m4x4.FromEulerAngleY(-float(90.0f*Math::DegToRad));
	m4x4.SetTranslation(2.0f, 3.0f, 4.0f);
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 2.0f) || !Math::AreEqual(vV.y, 3.0f) || !Math::AreEqual(vV.z, 5.0f)) bResult = false;
	EndTask(bResult);

	// [TODO] At the moment, Quaternion*Vector3 and Vector3*=Quaternion will return different results
/*	// *= Quaternion
	StartTask("*= Quaternion");
	bResult = true;
	// 90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	qQ.FromEulerAnglesXYZ(0.0f, float(90.0f*Math::DegToRad), 0.0f);
	vV *= qQ;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	// -90°
	vV = Vector3(1.0f, 0.0f, 0.0f);
	qQ.FromEulerAnglesXYZ(0.0f, -float(90.0f*Math::DegToRad), 0.0f);
	vV *= qQ;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	EndTask(bResult);
*/

// Division
	// / Vector3
	StartTask("/ Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f)/Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f && vV.z == 1.0f);
	// / float
	StartTask("/ float");
	vV = Vector3(1.0f, 2.0f, 3.0f)/2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f && vV.z == 1.5f);
	// /= Vector3
	StartTask("/= Vector3");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV /= Vector3(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f && vV.z == 1.0f);
	// /= float
	StartTask("/= float");
	vV = Vector3(1.0f, 2.0f, 3.0f);
	vV /= 2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f && vV.z == 1.5f);


// Get and set
	{ // operator float *()
		StartTask("operator float *()");
		vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
		float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f && pf[2] == 2.0f);
	}

	{ // const operator float *()
		StartTask("const operator float *()");
		vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
		const float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f && pf[2] == 2.0f);
	}

	// float &operator [](int)
	StartTask("float &operator [](int)");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	EndTask(vV[0] == 0.0f && vV[1] == 1.0f && vV[2] == 2.0f);

	// GetXYZ()
	StartTask("GetXYZ()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	vV.GetXYZ(fX, fY, fZ);
	EndTask(fX == 0.0f && fY == 1.0f && fZ == 2.0f);

	// GetX()
	StartTask("GetX()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	EndTask(vV.GetX() == 0.0f);

	// GetY()
	StartTask("GetY()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	EndTask(vV.GetY() == 1.0f);

	// GetZ()
	StartTask("GetZ()");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	EndTask(vV.GetZ() == 2.0f);

	// SetXYZ(float, float, float)
	StartTask("SetXYZ(float, float, float)");
	vV.SetXYZ(0.0f, 1.0f, 2.0f);
	EndTask(vV.x == 0.0f && vV.y == 1.0f && vV.z == 2.0f);

	// SetXYZ(const float[])
	StartTask("SetXYZ(const float[])");
	vV.SetXYZ(fT3);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f);

	// SetX()
	StartTask("SetX()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.SetX(0.0f);
	EndTask(vV.x == 0.0f && vV.y == 2.0f && vV.z == 3.0f);

	// SetY()
	StartTask("SetY()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.SetY(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 0.0f && vV.z == 3.0f);

	// SetZ()
	StartTask("SetZ()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.SetZ(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 0.0f);

	// IncXYZ(float, float, float)
	StartTask("IncXYZ(float, float, float)");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	vV.IncXYZ(1.0f, 2.0f, 3.0f);
	EndTask(vV.x == 1.0f && vV.y == 3.0f && vV.z == 5.0f);

	// IncXYZ(const float[])
	StartTask("IncXYZ(const float[])");
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 2.0f;
	vV.IncXYZ(fT3);
	EndTask(vV.x == 1.0f && vV.y == 3.0f && vV.z == 5.0f);

	// IncX()
	StartTask("IncX()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.IncX(2.0f);
	EndTask(vV.x == 3.0f && vV.y == 2.0f && vV.z == 3.0f);

	// IncY()
	StartTask("IncY()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.IncY(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f && vV.z == 3.0f);

	// IncZ()
	StartTask("IncZ()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	vV.IncZ(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 5.0f);

	// ToString()
	StartTask("ToString()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	EndTask(vV.ToString() == "1 2 3");

	// FromString()
	StartTask("FromString()");
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV.FromString("1 2 3");
	EndTask(vV.x == 1.0f && vV.y == 2.0f && vV.z == 3.0f);


// Misc
	// IsNull()
	StartTask("IsNull()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 5.0f;
	if (vV.IsNull()) bResult = false;
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	if (!vV.IsNull()) bResult = false;
	EndTask(bResult);

	// IsPacked()
	StartTask("IsPacked()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 5.0f;
	if (vV.IsPacked()) bResult = false;
	vV.x = 0.3f; vV.y = 0.8f; vV.z = 0.0f;
	if (!vV.IsPacked()) bResult = false;
	EndTask(bResult);

	// PackTo01()
	StartTask("PackTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.72360682f) || !Math::AreEqual(vV.y, 0.94721359f) || !Math::AreEqual(vV.z, 0.5f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f; vV.z = 1.0f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.04356455f) || !Math::AreEqual(vV.y, 0.6825741f) || !Math::AreEqual(vV.z, 0.591287f)) bResult = false;
	EndTask(bResult);

	// GetPackedTo01()
	StartTask("GetPackedTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.72360682f) || !Math::AreEqual(vV.y, 0.94721359f) || !Math::AreEqual(vV.z, 0.5f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f; vV.z = 1.0f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.04356455f) || !Math::AreEqual(vV.y, 0.6825741f) || !Math::AreEqual(vV.z, 0.591287f)) bResult = false;
	EndTask(bResult);

	// UnpackFrom01()
	StartTask("UnpackFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f; vV.z = 0.0f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	EndTask(bResult);

	// GetUnpackedFrom01()
	StartTask("GetUnpackedFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f; vV.z = 0.0f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f; vV.z = 0.0f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f) || !Math::AreEqual(vV.z, -1.0f)) bResult = false;
	EndTask(bResult);

	// GetSmallestComponent()
	StartTask("GetSmallestComponent()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	EndTask(vV.GetSmallestComponent() == Vector3::X);

	// GetSmallestValue()
	StartTask("GetSmallestValue()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	EndTask(vV.GetSmallestValue() == 1.0f);

	// GetGreatestComponent()
	StartTask("GetGreatestComponent()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	EndTask(vV.GetGreatestComponent() == Vector3::Z);

	// GetGreatestValue()
	StartTask("GetGreatestValue()");
	vV.x = 1.0f; vV.y = 2.0f; vV.z = 3.0f;
	EndTask(vV.GetGreatestValue() == 3.0f);

	// Invert()
	StartTask("Invert()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	vV.Invert();
	EndTask(vV.x == -0.2f && vV.y == 0.6f && vV.z == 0.0f);

	// GetInverted()
	StartTask("GetInverted()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	vV = vV.GetInverted();
	EndTask(vV.x == -0.2f && vV.y == 0.6f && vV.z == 0.0f);

	// GetLength()
	bResult = true;
	StartTask("GetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 0.6324555f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 1.0f)) bResult = false;
	EndTask(bResult);

	// GetSquaredLength()
	bResult = true;
	StartTask("GetSquaredLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 0.4f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 1.0f)) bResult = false;
	EndTask(bResult);

	// SetLength()
	bResult = true;
	StartTask("SetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) ||
		!Math::AreEqual(vV.y, -0.9486832f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	EndTask(bResult);

	// Normalize()
	bResult = true;
	StartTask("Normalize()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) ||
		!Math::AreEqual(vV.y, -0.9486832f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f)) bResult = false;
	EndTask(bResult);

	// GetNormalized()
	bResult = true;
	StartTask("GetNormalized()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) ||
		!Math::AreEqual(vV.y, -0.9486832f) || !Math::AreEqual(vV.z, 0.0f))  bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f))  bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) ||
		!Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 0.0f))  bResult = false;
	EndTask(bResult);

	// GetDistance()
	StartTask("GetDistance()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	EndTask(Math::AreEqual(vV.GetDistance(Vector3(0.0f, 0.0f, 0.0f)), 0.6324555f));

	// GetSquaredDistance()
	StartTask("GetSquaredDistance()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	EndTask(Math::AreEqual(vV.GetSquaredDistance(Vector3(0.0f, 0.0f, 0.0f)), 0.4f));

	// DotProduct()
	StartTask("DotProduct()");
	vV.x = 0.2f; vV.y = -0.6f; vV.z = 0.0f;
	EndTask(Math::AreEqual(vV.DotProduct(Vector3(0.0f, 0.0f, 0.0f)), 0.0f) &&
			Math::AreEqual(vV.DotProduct(Vector3(0.2f, -0.6f, 0.0f)), 0.4f));

	// GetAngle()
	StartTask("GetAngle()");
	bResult = true;
	// ~69.5°
	vV.x = 1.0f; vV.y = 4.0f; vV.z = -2.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector3(-3.0f, 3.0f, 1.0f)), 1.2127572f)) bResult = false;
	// 45°
	vV.x = 0.0f; vV.y = 1.0f; vV.z = 0.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector3(1.0f, 1.0f, 0.0f)), 0.7853981f)) bResult = false;
	// Now use normalized vectors and use the dot product... (~69.5°)
	vV.x = 1.0f; vV.y = 4.0f; vV.z = -2.0f;
	vV.Normalize();
	if (!Math::AreEqual(Math::ACos(vV.DotProduct(Vector3(-3.0f, 3.0f, 1.0f).Normalize())), 1.2127573f)) bResult = false;
	EndTask(bResult);
	
	// CrossProduct(Vector3)
	StartTask("CrossProduct(Vector3)");
	bResult = true;
	//
	vV.x = 1.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV = vV.CrossProduct(Vector3(0.0f, 1.0f, 0.0f));
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	//
	vV.x = -1.0f; vV.y = 0.0f; vV.z = 0.0f;
	vV = vV.CrossProduct(Vector3(0.0f, -1.0f, 0.0f));
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	EndTask(bResult);

	// CrossProduct(Vector3, Vector3)
	StartTask("CrossProduct(Vector3, Vector3)");
	bResult = true;
	//
	vV.CrossProduct(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	//
	vV.CrossProduct(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f) || !Math::AreEqual(vV.z, 1.0f)) bResult = false;
	EndTask(bResult);


/* [TODO]
		PLMATH_API void GetRightUp(Vector3 &vRight, Vector3 &vUp) const;
		PLMATH_API void GetRightUp(float fRight[], float fUp[]) const;
		PLMATH_API void GetFaceNormal(const Vector3 &vV1, const Vector3 &vV2, const Vector3 &vV3);
		PLMATH_API Vector3 &RotateAxis(Vector3 &vV, float fAngle);
		PLMATH_API Quaternion GetRotationTo(const Vector3 &vDest) const;
		PLMATH_API Vector3 ProjectVector(const Vector3 &vA, const Vector3 &vB) const;
		PLMATH_API Vector3 &GetProjection(const Vector3 &vX, const Vector3 &vN);
		PLMATH_API Vector3 &ProjectPlane(const Vector3 &vV1, const Vector3 &vV2);
		PLMATH_API Vector3 &Reflect(const Vector3 &vIncidentNormal, const Vector3 &vNormal);
		PLMATH_API Vector3 &Refract(const Vector3 &vIncidentNormal, const Vector3 &vNormal, float fEtaRatio);
		PLMATH_API Vector3 ClosestPointOnLine(const Vector3 &vV1, const Vector3 &vV2);
		PLMATH_API bool IsPointInTriangle(const Vector3 &vV1, const Vector3 &vV2, const Vector3 &vV3);
		PLMATH_API Vector3 ClosestPointOnTriangle(const Vector3 &vV1, const Vector3 &vV2, const Vector3 &vV3);
		PLMATH_API bool ClosestPointOnTriangle(const Vector3 &vV1, const Vector3 &vV2,
											   const Vector3 &vV3, float fRadius, Vector3 &vClosest);
	// 
	StartTask("");
	EndTask();
*/
}
