/*********************************************************\
 *  File: Ray.inl                                        *
 *      Ray inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor setting all position and direction components to 0
*/
inline Ray::Ray()
{
}

/**
*  @brief
*    Copy constructor
*/
inline Ray::Ray(const Ray &cSource) :
	m_vPos(cSource.m_vPos),
	m_vDir(cSource.m_vDir)
{
}

/**
*  @brief
*    Destructor
*/
inline Ray::~Ray()
{
}

/**
*  @brief
*    Copy operator
*/
inline Ray &Ray::operator =(const Ray &cSource)
{
	m_vPos = cSource.m_vPos;
	m_vDir = cSource.m_vDir;

	// Return this
	return *this;
}

/**
*  @brief
*    Set the current ray using a line
*/
inline void Ray::Set(const Vector3 &vLineStartPos, const Vector3 &vLineEndPos)
{
	m_vPos = vLineStartPos;
	m_vDir = vLineEndPos-vLineStartPos;
}

/**
*  @brief
*    Returns the current position
*/
inline const Vector3 &Ray::GetPos() const
{
	return m_vPos;
}

/**
*  @brief
*    Set the current position
*/
inline void Ray::SetPos(float fX, float fY, float fZ)
{
	m_vPos.SetXYZ(fX, fY, fZ);
}

/**
*  @brief
*    Set the current position
*/
inline void Ray::SetPos(const Vector3 &vPos)
{
	m_vPos = vPos;
}

/**
*  @brief
*    Returns the ray direction
*/
inline const Vector3 &Ray::GetDir() const
{
	return m_vDir;
}

/**
*  @brief
*    Set the ray direction
*/
inline void Ray::SetDir(float fX, float fY, float fZ)
{
	m_vDir.SetXYZ(fX, fY, fZ);
}

/**
*  @brief
*    Set the ray direction
*/
inline void Ray::SetDir(const Vector3 &vDir)
{
	m_vDir = vDir;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
