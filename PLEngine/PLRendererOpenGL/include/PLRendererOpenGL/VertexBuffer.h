/*********************************************************\
 *  File: VertexBuffer.h                                 *
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


#ifndef __PLRENDEREROPENGL_VERTEXBUFFER_H__
#define __PLRENDEREROPENGL_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL vertex buffer
*/
class VertexBuffer : public PLRenderer::VertexBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDEREROPENGL_API virtual ~VertexBuffer();

		/**
		*  @brief
		*    Returns the OpenGL vertex buffer
		*
		*  @return
		*    OpenGL vertex buffer
		*/
		PLRENDEREROPENGL_API PLGeneral::uint32 GetOpenGLVertexBuffer() const;

		/**
		*  @brief
		*    Returns the dynamic buffer (none VBO)
		*
		*  @return
		*    The dynamic buffer, can be a null pointer
		*/
		PLRENDEREROPENGL_API const PLGeneral::uint8 *GetDynamicBuffer() const;

		/**
		*  @brief
		*    Binds and updates the vertex buffer if required
		*
		*  @return
		*    'true' if an update was performed, else 'false' if everything was already up-to-date
		*
		*  @note
		*    - Should be called before the vertex buffer is used for rendering to ensure that the data on the GPU side is up-to-date
		*/
		PLRENDEREROPENGL_API bool BindAndUpdate();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		VertexBuffer(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32  m_nVertexBuffer;	/**< OpenGL vertex buffer (VBO) */
		PLGeneral::uint8  *m_pData;			/**< Dynamic buffer (none VBO) */
		void			  *m_pLockedData;	/**< Locked data */
		bool			   m_bLockReadOnly;	/**< Read only lock? */
		bool			   m_bUpdateVBO;	/**< Do we need to update the VBO? */
		PLGeneral::uint32  m_nUsageAPI;		/**< API usage setting */
		/** Offsets */
		int m_nOffset[NumOfSemantics][MaxPipelineChannels];


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::VertexBuffer functions     ]
	//[-------------------------------------------------------]
	public:
		virtual void *GetData(PLGeneral::uint32 nIndex, PLGeneral::uint32 nSemantic, PLGeneral::uint32 nChannel = 0);
		virtual PLGraphics::Color4 GetColor(PLGeneral::uint32 nIndex, PLGeneral::uint32 nChannel = 0);
		virtual bool SetColor(PLGeneral::uint32 nIndex, const PLGraphics::Color4 &cColor, PLGeneral::uint32 nChannel = 0);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::VertexBuffer functions    ]
	//[-------------------------------------------------------]
	private:
		virtual void VertexAttributeAdded(Attribute &cAttribute);


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Buffer functions           ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsAllocated() const;
		virtual bool Allocate(PLGeneral::uint32 nElements, PLRenderer::Usage::Enum nUsage = PLRenderer::Usage::Dynamic, bool bManaged = true, bool bKeepData = false);
		virtual bool Clear();
		virtual void *Lock(PLGeneral::uint32 nFlag = PLRenderer::Lock::ReadWrite);
		virtual void *GetData();
		virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_VERTEXBUFFER_H__
