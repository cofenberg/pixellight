/*********************************************************\
 *  File: ElementHandler.h                               *
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


#ifndef __PLGENERAL_ELEMENT_HANDLER_H__
#define __PLGENERAL_ELEMENT_HANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class Element;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Element handler template
*/
template <class AType> class ElementHandler {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Element<AType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ElementHandler();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ElementHandler();

		/**
		*  @brief
		*    Returns a pointer to the handlers element
		*
		*  @return
		*    A pointer to the handlers element, NULL if no element
		*/
		AType *GetElement() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets the handlers element
		*
		*  @param[in] pElement
		*    Element to set, NULL to set no element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If the element manager should delete unused elements automatically,
		*      (see ElementManager::GetUnloadUnused()) the previous element will be
		*      destroyed within this function if the element is no longer used by any
		*      handlers and if the element is not marked as protected.
		*/
		virtual bool SetElement(AType *pElement = NULL);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		AType *m_pElement; /**< Loaded element, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/ElementHandler.inl"


#endif // __PLGENERAL_ELEMENT_HANDLER_H__
