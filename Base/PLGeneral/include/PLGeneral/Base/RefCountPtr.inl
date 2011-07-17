/*********************************************************\
 *  File: RefCountPtr.inl                                *
 *      Reference counted pointer template implementation
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
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType>
RefCountPtr<AType>::RefCountPtr(AType *pPointer) :
	m_pPointer(pPointer)
{
}

/**
*  @brief
*    Destructor
*/
template <class AType>
RefCountPtr<AType>::~RefCountPtr()
{
	// Delete the referenced object
	if (m_pPointer)
		delete m_pPointer;
}

/**
*  @brief
*    Get a pointer to the object
*/
template <class AType>
const AType *RefCountPtr<AType>::GetPointer() const
{
	return m_pPointer;
}

template <class AType>
AType *RefCountPtr<AType>::GetPointer()
{
	return m_pPointer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
