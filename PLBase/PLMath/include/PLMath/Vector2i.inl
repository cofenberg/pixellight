/*********************************************************\
 *  File: Vector2i.inl                                   *
 *      2D integer vector inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor setting all components to 0
*/
inline Vector2i::Vector2i() :
	x(0),
	y(0)
{
}

/**
*  @brief
*    Constructor
*/
inline Vector2i::Vector2i(int nX, int nY) :
	x(nX),
	y(nY)
{
}

/**
*  @brief
*    Destructor
*/
inline Vector2i::~Vector2i()
{
}

inline Vector2i::operator int *() const
{
	return (int*)&x;
}

inline Vector2i::operator const int *() const
{
	return (const int*)&x;
}

inline int &Vector2i::operator [](int nIndex)
{
	return nV[nIndex];
}

inline const int &Vector2i::operator [](int nIndex) const
{
	return nV[nIndex];
}

/**
*  @brief
*    Set X and Y value
*/
inline void Vector2i::Set(int nX, int nY)
{
	x = nX;
	y = nY;
}

/**
*  @brief
*    Set x
*/
inline void Vector2i::SetX(int nX)
{
	x = nX;
}

/**
*  @brief
*    Set y
*/
inline void Vector2i::SetY(int nY)
{
	y = nY;
}

/**
*  @brief
*    Assignment operator
*/
inline Vector2i &Vector2i::operator =(const Vector2i &vV)
{
	x = vV.x;
	y = vV.y;
	return *this;
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator ==(const Vector2i &vV) const
{
	return (x == vV.x && y == vV.y);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator !=(const Vector2i &vV) const
{
	return (x != vV.x || y != vV.y);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator >(const Vector2i &vV) const
{
	return (x > vV.x && y > vV.y);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator <(const Vector2i &vV) const
{
	return (x < vV.x && y < vV.y);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator >=(const Vector2i &vV) const
{
	return (x >= vV.x && y >= vV.y);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector2i::operator <=(const Vector2i &vV) const
{
	return (x <= vV.x && y <= vV.y);
}

/**
*  @brief
*    Addition operator
*/
inline Vector2i Vector2i::operator +(const Vector2i &vV) const
{
	return Vector2i(x + vV.x, y + vV.y);
}

/**
*  @brief
*    Addition operator
*/
inline Vector2i &Vector2i::operator +=(const Vector2i &vV)
{
	x += vV.x;
	y += vV.y;
	return *this;
}

/**
*  @brief
*    Subtraction operator
*/
inline Vector2i Vector2i::operator -(const Vector2i &vV) const
{
	return Vector2i(x - vV.x, y - vV.y);
}

/**
*  @brief
*    Subtraction operator
*/
inline Vector2i &Vector2i::operator -=(const Vector2i &vV)
{
	x -= vV.x;
	y -= vV.y;
	return *this;
}

/**
*  @brief
*    Multiplication operator
*/
inline Vector2i Vector2i::operator *(float fFactor) const
{
	return Vector2i((int)(x*fFactor), (int)(y*fFactor));
}

/**
*  @brief
*    Multiplication operator
*/
inline Vector2i &Vector2i::operator *=(float fFactor)
{
	x = (int)(x*fFactor);
	y = (int)(y*fFactor);
	return *this;
}

/**
*  @brief
*    Division operator
*/
inline Vector2i Vector2i::operator /(float fFactor) const
{
	return Vector2i((int)(x/fFactor), (int)(y/fFactor));
}

/**
*  @brief
*    Division operator
*/
inline Vector2i &Vector2i::operator /=(float fFactor)
{
	x = (int)(x/fFactor);
	y = (int)(y/fFactor);
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
