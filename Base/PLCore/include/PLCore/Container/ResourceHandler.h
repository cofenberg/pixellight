/*********************************************************\
 *  File: ResourceHandler.h                              *
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


#ifndef __PLCORE_RESOURCE_HANDLER_H__
#define __PLCORE_RESOURCE_HANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class Resource;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Resource handler template
*/
template <class AType> class ResourceHandler {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Resource<AType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ResourceHandler();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ResourceHandler();

		/**
		*  @brief
		*    Returns a pointer to the handlers resource
		*
		*  @return
		*    A pointer to the handlers resource, a null pointer if no resource
		*/
		AType *GetResource() const;


	//[-------------------------------------------------------]
	//[ Public virtual ResourceHandler functions              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets the handlers resource
		*
		*  @param[in] pResource
		*    Resouce to set, a null pointer to set no element
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If the resource manager should delete unused resources automatically,
		*      (see ResourceManager::GetUnloadUnused()) the previous resource will be
		*      destroyed within this function if the resource is no longer used by any
		*      handlers and if the resource is not marked as protected.
		*/
		virtual bool SetResource(AType *pResource = nullptr);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		AType *m_pResource; /**< Loaded resource, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/ResourceHandler.inl"


#endif // __PLCORE_RESOURCE_HANDLER_H__
