/*********************************************************\
 *  File: SmartPtr.inl                                   *
 *      Smart pointer template implementation
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
#include "PLGeneral/Base/RefCountPtr.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType>
SmartPtr<AType>::SmartPtr() :
	m_pPtr(nullptr)
{
}

/**
*  @brief
*    Constructor
*/
template <class AType>
SmartPtr<AType>::SmartPtr(AType *pPtr) :
	m_pPtr(nullptr)
{
	SetPtr(pPtr);
}

/**
*  @brief
*    Constructor
*/
template <class AType>
SmartPtr<AType>::SmartPtr(const SmartPtr<AType> &pPtr) :
	m_pPtr(nullptr)
{
	SetPtr(pPtr.GetPtr());
}

/**
*  @brief
*    Destructor
*/
template <class AType>
SmartPtr<AType>::~SmartPtr()
{
	SetPtr(static_cast<RefCount<AType>*>(nullptr));
}

/**
*  @brief
*    Assign a pointer
*/
template <class AType>
SmartPtr<AType> &SmartPtr<AType>::operator =(AType *pPtr)
{
	if (GetPointer() != pPtr)
		SetPtr(pPtr);
	return *this;
}

/**
*  @brief
*    Assign a smart pointer
*/
template <class AType>
SmartPtr<AType> &SmartPtr<AType>::operator =(const SmartPtr<AType> &cPtr)
{
	if (GetPointer() != cPtr.GetPointer())
		SetPtr(cPtr.GetPtr());
	return *this;
}

/**
*  @brief
*    Get a direct pointer to the object
*/
template <class AType>
AType *SmartPtr<AType>::GetPointer() const
{
	return m_pPtr ? m_pPtr->GetPointer() : nullptr;
}

/**
*  @brief
*    Get a pointer to access the object
*/
template <class AType>
AType *SmartPtr<AType>::operator ->() const
{
	return GetPointer();
}

/**
*  @brief
*    Cast to a pointer to the object
*/
template <class AType>
SmartPtr<AType>::operator AType*() const
{
	return GetPointer();
}

/**
*  @brief
*    Check if the pointer is not a null pointer
*/
template <class AType>
bool SmartPtr<AType>::operator !() const
{
	return (GetPointer() == nullptr);
}

/**
*  @brief
*    Check for equality
*/
template <class AType>
bool SmartPtr<AType>::operator ==(AType *pPtr) const
{
	return (GetPointer() == pPtr);
}

/**
*  @brief
*    Check for equality
*/
template <class AType>
bool SmartPtr<AType>::operator ==(const SmartPtr<AType> &cPtr) const
{
	return (GetPointer() == cPtr.GetPointer());
}

/**
*  @brief
*    Check for equality
*/
template <class AType>
bool SmartPtr<AType>::operator !=(AType *pPtr) const
{
	return (GetPointer() != pPtr);
}

/**
*  @brief
*    Check for equality
*/
template <class AType>
bool SmartPtr<AType>::operator !=(const SmartPtr<AType> &cPtr) const
{
	return (GetPointer() != cPtr.GetPointer());
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Assign a pointer to an object that does not implement RefCount
*/
template <class AType>
void SmartPtr<AType>::SetPtr(void *pPtr)
{
	// Create a reference counter for the object, then assign it
	SetPtr(pPtr ? new RefCountPtr<AType>(static_cast<AType*>(pPtr)) : static_cast<RefCount<AType>*>(nullptr));
}

/**
*  @brief
*    Assign a pointer to an object that implements RefCount
*/
template <class AType>
void SmartPtr<AType>::SetPtr(RefCount<AType> *pPtr)
{
	// Release old pointer
	if (m_pPtr)
		m_pPtr->Release();

	// Assign new pointer
	if (pPtr)
		pPtr->AddReference();
	m_pPtr = pPtr;
}

/**
*  @brief
*    Get pointer to the reference counted object
*/
template <class AType>
RefCount<AType> *SmartPtr<AType>::GetPtr() const
{
	// Return pointer
	return m_pPtr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
