/*********************************************************\
 *  File: ResourceHandler.h                              *
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


#ifndef __PLRENDERER_RESOURCE_HANDLER_H__
#define __PLRENDERER_RESOURCE_HANDLER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Resource;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Resource handler
*/
class ResourceHandler {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API ResourceHandler();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLRENDERER_API ResourceHandler(const ResourceHandler &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ResourceHandler();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLRENDERER_API ResourceHandler &operator =(const ResourceHandler &cSource);

		/**
		*  @brief
		*    Returns the resource handlers resource
		*
		*  @return
		*    The resource handlers resource, can be a null pointer
		*/
		inline Resource *GetResource() const;

		/**
		*  @brief
		*    Sets the resource handlers resource
		*
		*  @param[in] pResource
		*    Resource to set, can be a null pointer
		*/
		PLRENDERER_API void SetResource(Resource *pResource = nullptr);


	//[-------------------------------------------------------]
	//[ Public virtual ResourceHandler functions              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Is called when the resource was lost
		*/
		PLRENDERER_API virtual void OnLost();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Resource *m_pResource;	/**< Resource of the handler, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/ResourceHandler.inl"


#endif // __PLRENDERER_RESOURCE_HANDLER_H__
