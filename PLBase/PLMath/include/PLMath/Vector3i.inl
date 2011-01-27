/*********************************************************\
 *  File: Vector3i.inl                                   *
 *      3D integer vector inline implementation
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
inline Vector3i::Vector3i() :
	x(0),
	y(0),
	z(0)
{
}

/**
*  @brief
*    Constructor
*/
inline Vector3i::Vector3i(int nX, int nY, int nZ) :
	x(nX),
	y(nY),
	z(nZ)
{
}

/**
*  @brief
*    Destructor
*/
inline Vector3i::~Vector3i()
{
}

inline Vector3i::operator int *()
{
	return &x;
}

inline Vector3i::operator const int *() const
{
	return &x;
}

inline int &Vector3i::operator [](int nIndex)
{
	return nV[nIndex];
}

inline const int &Vector3i::operator [](int nIndex) const
{
	return nV[nIndex];
}

/**
*  @brief
*    Set X, Y and Z value
*/
inline void Vector3i::Set(int nX, int nY, int nZ)
{
	x = nX;
	y = nY;
	z = nZ;
}

/**
*  @brief
*    Set x
*/
inline void Vector3i::SetX(int nX)
{
	x = nX;
}

/**
*  @brief
*    Set y
*/
inline void Vector3i::SetY(int nY)
{
	y = nY;
}

/**
*  @brief
*    Set z
*/
inline void Vector3i::SetZ(int nZ)
{
	z = nZ;
}

/**
*  @brief
*    Assignment operator
*/
inline Vector3i &Vector3i::operator =(const Vector3i &vV)
{
	x = vV.x;
	y = vV.y;
	z = vV.z;
	return *this;
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator ==(const Vector3i &vV) const
{
	return (x == vV.x && y == vV.y && z == vV.z);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator !=(const Vector3i &vV) const
{
	return (x != vV.x || y != vV.y || z != vV.z);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator >(const Vector3i &vV) const
{
	return (x > vV.x && y > vV.y && z > vV.z);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator <(const Vector3i &vV) const
{
	return (x < vV.x && y < vV.y && z < vV.z);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator >=(const Vector3i &vV) const
{
	return (x >= vV.x && y >= vV.y && z >= vV.z);
}

/**
*  @brief
*    Compare operator
*/
inline bool Vector3i::operator <=(const Vector3i &vV) const
{
	return (x <= vV.x && y <= vV.y && z <= vV.z);
}

/**
*  @brief
*    Addition operator
*/
inline Vector3i Vector3i::operator +(const Vector3i &vV) const
{
	return Vector3i(x + vV.x, y + vV.y, z + vV.z);
}

/**
*  @brief
*    Addition operator
*/
inline Vector3i &Vector3i::operator +=(const Vector3i &vV)
{
	x += vV.x;
	y += vV.y;
	z += vV.z;
	return *this;
}

/**
*  @brief
*    Subtraction operator
*/
inline Vector3i Vector3i::operator -(const Vector3i &vV) const
{
	return Vector3i(x - vV.x, y - vV.y, z - vV.z);
}

/**
*  @brief
*    Subtraction operator
*/
inline Vector3i &Vector3i::operator -=(const Vector3i &vV)
{
	x -= vV.x;
	y -= vV.y;
	z -= vV.z;
	return *this;
}

/**
*  @brief
*    Multiplication operator
*/
inline Vector3i Vector3i::operator *(float fFactor) const
{
	return Vector3i(static_cast<int>(x*fFactor), static_cast<int>(y*fFactor), static_cast<int>(z*fFactor));
}

/**
*  @brief
*    Multiplication operator
*/
inline Vector3i &Vector3i::operator *=(float fFactor)
{
	x = static_cast<int>(x*fFactor);
	y = static_cast<int>(y*fFactor);
	z = static_cast<int>(z*fFactor);
	return *this;
}

/**
*  @brief
*    Division operator
*/
inline Vector3i Vector3i::operator /(float fFactor) const
{
	return Vector3i(static_cast<int>(x/fFactor), static_cast<int>(y/fFactor), static_cast<int>(z/fFactor));
}

/**
*  @brief
*    Division operator
*/
inline Vector3i &Vector3i::operator /=(float fFactor)
{
	x = static_cast<int>(x/fFactor);
	y = static_cast<int>(y/fFactor);
	z = static_cast<int>(z/fFactor);
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
