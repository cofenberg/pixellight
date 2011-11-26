/*********************************************************\
 *  File: Resource.h                                     *
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


#ifndef __PLRENDERER_RESOURCE_H__
#define __PLRENDERER_RESOURCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;
class ResourceHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Renderer resource base class
*/
class Resource {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class RendererBackend;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Resource types
		*/
		enum EType {
			TypeIndexBuffer            =  0,	/**< Index buffer (IBO) */
			TypeVertexBuffer           =  1,	/**< Vertex buffer (VBO) */
			TypeUniformBuffer          =  2,	/**< Uniform buffer (UBO) */
			TypeTextureBuffer1D        =  3,	/**< 1D texture buffer */
			TypeTextureBuffer2D        =  4,	/**< 2D texture buffer */
			TypeTextureBuffer2DArray   =  5,	/**< 2D array texture buffer (kind of 3D texture, but without filtering between the depth layers) */
			TypeTextureBufferRectangle =  6,	/**< Rectangle texture buffer */
			TypeTextureBuffer3D        =  7,	/**< 3D texture buffer */
			TypeTextureBufferCube      =  8,	/**< Cube texture buffer */
			TypeOcclusionQuery         =  9,	/**< Occlusion query */
			TypeVertexShader           = 10,	/**< Vertex shader */
			TypeGeometryShader         = 11,	/**< Geometry shader */
			TypeFragmentShader         = 12,	/**< Fragment shader */
			TypeProgram                = 13,	/**< Program */
			TypeFont                   = 14		/**< Font */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Resource();

		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;

		/**
		*  @brief
		*    Returns the resource type
		*
		*  @return
		*    Resource type
		*/
		PLRENDERER_API EType GetType() const;

		/**
		*  @brief
		*    Returns the number of resource handlers
		*
		*  @return
		*    The number of resource handlers
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfHandlers() const;

		/**
		*  @brief
		*    Returns whether a resource handler is using this resource
		*
		*  @param[in] cHandler
		*    Resource handler to check
		*
		*  @return
		*    'true' if the given resource handler is using this resource, else 'false'
		*
		*  @note
		*    - The handlers will be informed if the resource was lost
		*    - The handlers itself are not deleted etc. they are only 'added' to a list
		*/
		PLRENDERER_API bool IsHandler(ResourceHandler &cHandler) const;

		/**
		*  @brief
		*    Adds a resource handler
		*
		*  @param[in] cHandler
		*    Resource handler which should be added
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - IsHandler()
		*/
		PLRENDERER_API bool AddHandler(ResourceHandler &cHandler);

		/**
		*  @brief
		*    Removes a resource handler
		*
		*  @param[in] cHandler
		*    Resource handler to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - IsHandler()
		*/
		PLRENDERER_API bool RemoveHandler(ResourceHandler &cHandler);

		/**
		*  @brief
		*    Clears the list of handlers
		*
		*  @see
		*    - IsHandler()
		*/
		PLRENDERER_API void ClearHandlers();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nType
		*    Resource type
		*/
		PLRENDERER_API Resource(Renderer &cRenderer, EType nType);


	//[-------------------------------------------------------]
	//[ Protected virtual Resource functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Backups the resource device data
		*
		*  @param[in, out] ppBackup
		*    Pointer to a pointer for the data backup (MUST be ALWAYS VALID or a null pointer!)
		*
		*  @note
		*    - Used for instance if the display mode is changed to backup/restore
		*      all resource device data
		*    - Normally only used inside Renderer::BackupDeviceObjects()/Renderer::RestoreDeviceObjects()
		*/
		PLRENDERER_API virtual void BackupDeviceData(PLCore::uint8 **ppBackup);

		/**
		*  @brief
		*    Restores the resource device data
		*
		*  @param[in, out] ppBackup
		*    Pointer to a pointer for the data backup (MUST be ALWAYS VALID or a null pointer!)
		*
		*  @see
		*    - BackupDeviceData()
		*/
		PLRENDERER_API virtual void RestoreDeviceData(PLCore::uint8 **ppBackup);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Resource(const Resource &cSource);

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
		Resource &operator =(const Resource &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer					   *m_pRenderer;	/**< Owner renderer (always valid!) */
		EType						    m_nType;		/**< Resource type */
		PLCore::List<ResourceHandler*>  m_lstHandlers;	/**< List of resource handlers */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_RESOURCE_H__
