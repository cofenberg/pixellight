/*********************************************************\
 *  File: Vector2Test.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLTestBase/Math/Vector2Test.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ Vector2Test implementation                            ]
//[-------------------------------------------------------]
const char *Vector2Test::GetName() const
{
	return "Vector2";
}

void Vector2Test::Test()
{
	float fT2[2] = {1.0f, 2.0f};
	Matrix3x3 m3x3;
	Matrix4x4 m4x4;
	float fX, fY;
	bool bResult;
	Vector2 vV;

	// Vector constructors & copy
	StartTask("Vector constructors & copy");
	bResult = true;
	if (vV.x != 0.0f || vV.y != 0.0f) bResult = false;
	vV = Vector2(1.0f, 2.0f);
	if (vV.x != 1.0f || vV.y != 2.0f) bResult = false;
	vV = Vector2(fT2);
	if (vV.x != 1.0f || vV.y != 2.0f) bResult = false;
	vV = Vector2(vV);
	if (vV.x != 1.0f || vV.y != 2.0f) bResult = false;
	EndTask(bResult);

	// Static variables
	StartTask("Static variables");
	bResult = true;
	if (Vector2::Zero.x != 0.0f || Vector2::Zero.y != 0.0f) bResult = false;
	if (Vector2::One.x != 1.0f || Vector2::One.y != 1.0f) bResult = false;
	if (Vector2::UnitX.x != 1.0f || Vector2::UnitX.y != 0.0f) bResult = false;
	if (Vector2::UnitY.x != 0.0f || Vector2::UnitY.y != 1.0f) bResult = false;
	if (Vector2::NegativeUnitX.x != -1.0f || Vector2::NegativeUnitX.y != 0.0f) bResult = false;
	if (Vector2::NegativeUnitY.x != 0.0f || Vector2::NegativeUnitY.y != -1.0f) bResult = false;
	EndTask(bResult);


// Comparison
	// ==
	StartTask("==");
	EndTask(Vector2(1.0f, 2.0f) == Vector2(1.0f, 2.0f) && 
			!(Vector2(1.0f, 2.0f) == Vector2(1.0f, 2.0001f)));
	// !=
	StartTask("!=");
	EndTask(!(Vector2(1.0f, 2.0f) != Vector2(1.0f, 2.0f)) &&
			Vector2(1.0f, 2.0f) != Vector2(1.0f, 2.0001f));
	// >
	StartTask(">");
	EndTask(!(Vector2(1.0f, 2.0f) > Vector2(2.0f, 3.0f)) &&
			Vector2(2.0f, 3.0f) > Vector2(1.0f, 2.0f) &&
			!(Vector2(1.0f, 2.0f) > Vector2(1.0f, 2.0)));
	// <
	StartTask("<");
	EndTask(!(Vector2(2.0f, 3.0f) < Vector2(1.0f, 2.0f)) &&
			Vector2(1.0f, 2.0f) < Vector2(2.0f, 3.0f) &&
			!(Vector2(1.0f, 2.0) < Vector2(1.0f, 2.0f)));
	// >=
	StartTask(">=");
	EndTask(!(Vector2(1.0f, 2.0f) >= Vector2(2.0f, 3.0f)) &&
			Vector2(2.0f, 3.0f) >= Vector2(1.0f, 2.0f) &&
			Vector2(1.0f, 2.0f) >= Vector2(1.0f, 2.0f));
	// <=
	StartTask("<=");
	EndTask(!(Vector2(2.0f, 3.0f) <= Vector2(1.0f, 2.0f)) &&
			Vector2(1.0f, 2.0f) <= Vector2(2.0f, 3.0f) &&
			Vector2(1.0f, 2.0) <= Vector2(1.0f, 2.0f));


// Addition
	// + Vector2
	StartTask("+ Vector2");
	vV = Vector2(1.0f, 2.0f)+Vector2(1.0f, 2.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f);
	// + float
	StartTask("+ float");
	vV = Vector2(1.0f, 2.0f)+2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f);
	// += Vector2
	StartTask("+= Vector2");
	vV = Vector2(1.0f, 2.0f);
	vV += Vector2(1.0f, 2.0f);
	EndTask(vV.x == 2.0f && vV.y == 4.0f);
	// += float
	StartTask("+= float");
	vV = Vector2(1.0f, 2.0f);
	vV += 2.0f;
	EndTask(vV.x == 3.0f && vV.y == 4.0f);


// Subtraction
	// -
	StartTask("-");
	vV = -Vector2(1.0f, 2.0f);
	EndTask(vV.x == -1.0f && vV.y == -2.0f);
	// - Vector2
	StartTask("- Vector2");
	vV = Vector2(1.0f, 2.0f)-Vector2(1.0f, 2.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f);
	// - float
	StartTask("- float");
	vV = Vector2(1.0f, 2.0f)-2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f);
	// -= Vector2
	StartTask("-= Vector2");
	vV = Vector2(1.0f, 2.0f);
	vV -= Vector2(1.0f, 2.0f);
	EndTask(vV.x == 0.0f && vV.y == 0.0f);
	// -= float
	StartTask("-= float");
	vV = Vector2(1.0f, 2.0f);
	vV -= 2.0f;
	EndTask(vV.x == -1.0f && vV.y == 0.0f);
	// Vector2()-(-Vector2())
	StartTask("Vector2()-(-Vector2())");
	vV = Vector2(1.0f, 2.0f)-(-Vector2(1.0f, 2.0f));
	EndTask(vV.x == 2.0f && vV.y == 4.0f);


// Multiplication
	// * Vector2
	StartTask("* Vector2");
	vV = Vector2(1.0f, 2.0f)*Vector2(1.0f, 2.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f);
	// * float
	StartTask("* float");
	vV = Vector2(1.0f, 2.0f)*2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f);
	// *= Vector2
	StartTask("*= Vector2");
	vV = Vector2(1.0f, 2.0f);
	vV *= Vector2(1.0f, 2.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f);
	// *= float
	StartTask("*= float");
	vV = Vector2(1.0f, 2.0f);
	vV *= 2.0f;
	EndTask(vV.x == 2.0f && vV.y == 4.0f);

	// *= Matrix3x3
	StartTask("*= Matrix3x3");
	bResult = true;
	// 90°
	vV = Vector2(1.0f, 0.0f);
	m3x3.FromEulerAngleZ(static_cast<float>(90.0f*Math::DegToRad));
	vV *= m3x3;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f)) bResult = false;
	// -90°
	vV = Vector2(1.0f, 0.0f);
	m3x3.FromEulerAngleZ(-static_cast<float>(90.0f*Math::DegToRad));
	vV *= m3x3;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, -1.0f)) bResult = false;
	EndTask(bResult);

	// *= Matrix4x4
	StartTask("*= Matrix4x4");
	bResult = true;
	// 90°
	vV = Vector2(1.0f, 0.0f);
	m4x4.FromEulerAngleZ(static_cast<float>(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f)) bResult = false;
	// -90°
	vV = Vector2(1.0f, 0.0f);
	m4x4.FromEulerAngleZ(-static_cast<float>(90.0f*Math::DegToRad));
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, -1.0f)) bResult = false;
	// -90° + translation (2, 3, 4)
	vV = Vector2(1.0f, 0.0f);
	m4x4.FromEulerAngleZ(-static_cast<float>(90.0f*Math::DegToRad));
	m4x4.SetTranslation(2.0f, 3.0f, 4.0f);
	vV *= m4x4;
	if (!Math::AreEqual(vV.x, 2.0f) || !Math::AreEqual(vV.y, 2.0f)) bResult = false;
	EndTask(bResult);


// Division
	// / Vector2
	StartTask("/ Vector2");
	vV = Vector2(1.0f, 2.0f)/Vector2(1.0f, 2.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f);
	// / float
	StartTask("/ float");
	vV = Vector2(1.0f, 2.0f)/2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f);
	// /= Vector2
	StartTask("/= Vector2");
	vV = Vector2(1.0f, 2.0f);
	vV /= Vector2(1.0f, 2.0f);
	EndTask(vV.x == 1.0f && vV.y == 1.0f);
	// /= float
	StartTask("/= float");
	vV = Vector2(1.0f, 2.0f);
	vV /= 2.0f;
	EndTask(vV.x == 0.5f && vV.y == 1.0f);


// Get and set
	{ // operator float *()
		StartTask("operator float *()");
		vV.x = 0.0f; vV.y = 1.0f;
		float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f);
	}

	{ // const operator float *()
		StartTask("const operator float *()");
		vV.x = 0.0f; vV.y = 1.0f;
		const float *pf = vV;
		EndTask(pf[0] == 0.0f && pf[1] == 1.0f);
	}

	// float &operator [](int)
	StartTask("float &operator [](int)");
	vV.x = 0.0f; vV.y = 1.0f;
	EndTask(vV[0] == 0.0f && vV[1] == 1.0f);

	// GetXY()
	StartTask("GetXY()");
	vV.x = 0.0f; vV.y = 1.0f;
	vV.GetXY(fX, fY);
	EndTask(fX == 0.0f && fY == 1.0f);

	// GetX()
	StartTask("GetX()");
	vV.x = 0.0f; vV.y = 1.0f;
	EndTask(vV.GetX() == 0.0f);

	// GetY()
	StartTask("GetY()");
	vV.x = 0.0f; vV.y = 1.0f;
	EndTask(vV.GetY() == 1.0f);

	// SetXY(float, float)
	StartTask("SetXY(float, float)");
	vV.SetXY(0.0f, 1.0f);
	EndTask(vV.x == 0.0f && vV.y == 1.0f);

	// SetXY(const float[])
	StartTask("SetXY(const float[])");
	vV.SetXY(fT2);
	EndTask(vV.x == 1.0f && vV.y == 2.0f);

	// SetX()
	StartTask("SetX()");
	vV.x = 1.0f; vV.y = 2.0f;
	vV.SetX(0.0f);
	EndTask(vV.x == 0.0f && vV.y == 2.0f);

	// SetY()
	StartTask("SetY()");
	vV.x = 1.0f; vV.y = 2.0f;
	vV.SetY(0.0f);
	EndTask(vV.x == 1.0f && vV.y == 0.0f);

	// IncXY(float, float)
	StartTask("IncXY(float, float)");
	vV.x = 0.0f; vV.y = 1.0f;
	vV.IncXY(1.0f, 2.0f);
	EndTask(vV.x == 1.0f && vV.y == 3.0f);

	// IncXY(const float[])
	StartTask("IncXY(const float[])");
	vV.x = 0.0f; vV.y = 1.0f;
	vV.IncXY(fT2);
	EndTask(vV.x == 1.0f && vV.y == 3.0f);

	// IncX()
	StartTask("IncX()");
	vV.x = 1.0f; vV.y = 2.0f;
	vV.IncX(2.0f);
	EndTask(vV.x == 3.0f && vV.y == 2.0f);

	// IncY()
	StartTask("IncY()");
	vV.x = 1.0f; vV.y = 2.0f;
	vV.IncY(2.0f);
	EndTask(vV.x == 1.0f && vV.y == 4.0f);

	// ToString()
	StartTask("ToString()");
	vV.x = 1.0f; vV.y = 2.0f;
	EndTask(vV.ToString() == "1 2");

	// FromString()
	StartTask("FromString()");
	vV.x = 0.0f; vV.y = 0.0f;
	vV.FromString("1 2");
	EndTask(vV.x == 1.0f && vV.y == 2.0f);


// Misc
	// IsNull()
	StartTask("IsNull()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f;
	if (vV.IsNull()) bResult = false;
	vV.x = 0.0f; vV.y = 0.0f;
	if (!vV.IsNull()) bResult = false;
	EndTask(bResult);

	// IsPacked()
	StartTask("IsPacked()");
	bResult = true;
	vV.x = 1.0f; vV.y = 2.0f;
	if (vV.IsPacked()) bResult = false;
	vV.x = 0.3f; vV.y = 0.8f;
	if (!vV.IsPacked()) bResult = false;
	EndTask(bResult);

	// PackTo01()
	StartTask("PackTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.72360682f) || !Math::AreEqual(vV.y, 0.94721359f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f;
	vV.PackTo01();
	if (!Math::AreEqual(vV.x, 0.03576165f) || !Math::AreEqual(vV.y, 0.6856953f)) bResult = false;
	EndTask(bResult);

	// GetPackedTo01()
	StartTask("GetPackedTo01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.72360682f) || !Math::AreEqual(vV.y, 0.94721359f)) bResult = false;
	//
	vV.x = -5.0f; vV.y = 2.0f;
	vV = vV.GetPackedTo01();
	if (!Math::AreEqual(vV.x, 0.03576165f) || !Math::AreEqual(vV.y, 0.6856953f)) bResult = false;
	EndTask(bResult);

	// UnpackFrom01()
	StartTask("UnpackFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f;
	vV.UnpackFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f)) bResult = false;
	EndTask(bResult);

	// GetUnpackedFrom01()
	StartTask("GetUnpackedFrom01()");
	bResult = true;
	//
	vV.x = 0.5f; vV.y = 1.0f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 1.0f)) bResult = false;
	//
	vV.x = 0.2f; vV.y = 0.6f;
	vV = vV.GetUnpackedFrom01();
	if (!Math::AreEqual(vV.x, -0.6f) || !Math::AreEqual(vV.y, 0.2f)) bResult = false;
	EndTask(bResult);

	// GetSmallestComponent()
	StartTask("GetSmallestComponent()");
	vV.x = 1.0f; vV.y = 2.0f;
	EndTask(vV.GetSmallestComponent() == Vector2::X);

	// GetSmallestValue()
	StartTask("GetSmallestValue()");
	vV.x = 1.0f; vV.y = 2.0f;
	EndTask(vV.GetSmallestValue() == 1.0f);

	// GetGreatestComponent()
	StartTask("GetGreatestComponent()");
	vV.x = 1.0f; vV.y = 2.0f;
	EndTask(vV.GetGreatestComponent() == Vector2::Y);

	// GetGreatestValue()
	StartTask("GetGreatestValue()");
	vV.x = 1.0f; vV.y = 2.0f;
	EndTask(vV.GetGreatestValue() == 2.0f);

	// Invert()
	StartTask("Invert()");
	vV.x = 0.2f; vV.y = -0.6f;
	vV.Invert();
	EndTask(vV.x == -0.2f && vV.y == 0.6f);

	// GetInverted()
	StartTask("GetInverted()");
	vV.x = 0.2f; vV.y = -0.6f;
	vV = vV.GetInverted();
	EndTask(vV.x == -0.2f && vV.y == 0.6f);

	// GetLength()
	bResult = true;
	StartTask("GetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f;
	if (!Math::AreEqual(vV.GetLength(), 0.6324555f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f;
	if (!Math::AreEqual(vV.GetLength(), 1.0f)) bResult = false;
	EndTask(bResult);

	// GetSquaredLength()
	bResult = true;
	StartTask("GetSquaredLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 0.4f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f;
	if (!Math::AreEqual(vV.GetSquaredLength(), 1.0f)) bResult = false;
	EndTask(bResult);

	// SetLength()
	bResult = true;
	StartTask("SetLength()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) || !Math::AreEqual(vV.y, -0.9486832f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f;
	vV.SetLength(1.0f);
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	EndTask(bResult);

	// Normalize()
	bResult = true;
	StartTask("Normalize()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) || !Math::AreEqual(vV.y, -0.9486832f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f;
	vV.Normalize();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	EndTask(bResult);

	// GetNormalized()
	bResult = true;
	StartTask("GetNormalized()");
	// Any vector
	vV.x = 0.2f; vV.y = -0.6f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 0.3162277f) || !Math::AreEqual(vV.y, -0.9486832f)) bResult = false;
	// Null vector
	vV.x = 0.0f; vV.y = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 0.0f) || !Math::AreEqual(vV.x, 0.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	// Unit vector
	vV.x = 1.0f; vV.y = 0.0f;
	vV = vV.GetNormalized();
	if (!Math::AreEqual(vV.GetLength(), 1.0f) || !Math::AreEqual(vV.x, 1.0f) || !Math::AreEqual(vV.y, 0.0f)) bResult = false;
	EndTask(bResult);

	// GetDistance()
	StartTask("GetDistance()");
	vV.x = 0.2f; vV.y = -0.6f;
	EndTask(Math::AreEqual(vV.GetDistance(Vector2(0.0f, 0.0f)), 0.6324555f));

	// GetSquaredDistance()
	StartTask("GetSquaredDistance()");
	vV.x = 0.2f; vV.y = -0.6f;
	EndTask(Math::AreEqual(vV.GetSquaredDistance(Vector2(0.0f, 0.0f)), 0.4f));

	// DotProduct()
	StartTask("DotProduct()");
	vV.x = 0.2f; vV.y = -0.6f;
	EndTask(Math::AreEqual(vV.DotProduct(Vector2(0.0f, 0.0f)), 0.0f) &&
			Math::AreEqual(vV.DotProduct(Vector2(0.2f, -0.6f)), 0.4f));

	// GetAngle()
	StartTask("GetAngle()");
	bResult = true;
	// ~74.7°
	vV.x = 1.0f; vV.y = 4.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector2(-3.0f, 3.0f)), 1.0303768f)) bResult = false;
	// 45°
	vV.x = 0.0f; vV.y = 1.0f;
	if (!Math::AreEqual(vV.GetAngle(Vector2(1.0f, 1.0f)), 0.7853981f)) bResult = false;
	// Now use normalized vectors and use the dot product... (~74.7°)
	vV.x = 1.0f; vV.y = 4.0f;
	vV.Normalize();
	if (!Math::AreEqual(Math::ACos(vV.DotProduct(Vector2(-3.0f, 3.0f).Normalize())), 1.0303768f)) bResult = false;
	EndTask(bResult);
}
