/*********************************************************\
 *  File: CubicSpline.inl                                *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
inline CubicSpline::CubicSpline()
{
}

/**
*  @brief
*    Constructor
*/
inline CubicSpline::CubicSpline(float _a, float _b, float _c, float _d) :
	a(_a),
	b(_b),
	c(_c),
	d(_d)
{
}

/**
*  @brief
*    Copy constructor
*/
inline CubicSpline::CubicSpline(const CubicSpline &cSource) :
	a(cSource.a),
	b(cSource.b),
	c(cSource.c),
	d(cSource.d)
{
}

/**
*  @brief
*    Destructor
*/
inline CubicSpline::~CubicSpline()
{
}

/**
*  @brief
*    Copy operator
*/
inline CubicSpline &CubicSpline::operator =(const CubicSpline &cSource)
{
	// Copy coefficients
	a = cSource.a;
	b = cSource.b;
	c = cSource.c;
	d = cSource.d;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
inline bool CubicSpline::operator ==(const CubicSpline &cOther) const
{
	// Compare coefficients (no epsilon environment in here)
	return (a == cOther.a && b == cOther.b && c == cOther.c && d == cOther.d);
}

/**
*  @brief
*    Evaluate value using a cubic equation
*/
inline float CubicSpline::GetValueOnSpline(float fValue) const
{
	return (((d*fValue) + c)*fValue + b)*fValue + a;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
