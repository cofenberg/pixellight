/*********************************************************\
 *  File: ClassImpl.inl                                  *
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
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return the pointer to the owner class instance wrapping this class implementation
*/
inline Class *ClassImpl::GetClass() const
{
	return m_pClass;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get full class name (with namespace)
*/
inline String ClassImpl::GetClassName() const
{
	// Return name of class and namespace
	return m_sClassName;
}

/**
*  @brief
*    Get full name of base class (with namespace)
*/
inline String ClassImpl::GetBaseClassName() const
{
	// Return base class
	return m_sBaseClass;
}

/**
*  @brief
*    Get class name (without namespace)
*/
inline String ClassImpl::GetName() const
{
	// Return name of class
	return m_sName;
}

/**
*  @brief
*    Get class description
*/
inline String ClassImpl::GetDescription() const
{
	// Return description
	return m_sDescription;
}

/**
*  @brief
*    Get namespace
*/
inline String ClassImpl::GetNamespace() const
{
	// Return namespace
	return m_sNamespace;
}

/**
*  @brief
*    Get properties
*/
inline const HashMap<String, String> &ClassImpl::GetProperties() const
{
	// Check if class has been initialized
	if (!m_bInitialized)
		InitClass();

	// Return property map
	return m_mapProperties;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
