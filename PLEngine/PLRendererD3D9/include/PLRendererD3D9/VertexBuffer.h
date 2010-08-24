/*********************************************************\
 *  File: VertexBuffer.h                                 *
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


#ifndef __PLRENDERERD3D9_VERTEXBUFFER_H__
#define __PLRENDERERD3D9_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>
#include "PLRendererD3D9/PLRendererD3D9.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D 9 vertex buffer
*/
class VertexBuffer : public PLRenderer::VertexBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;
	friend class FixedFunctions;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VertexBuffer();


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

		/**
		*  @brief
		*    Makes this vertex buffer to the renderers current vertex buffer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This function is used by the renderer when SetVertexBuffer() was called
		*/
		bool MakeCurrent();

		/**
		*  @brief
		*    Makes this vertex buffer to the renderers current vertex buffer
		*
		*  @param[in] nStreamNumber
		*    Vertex stream ID
		*  @param[in] nOffset
		*    Vertex offset
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This function is used by the renderer when SetVertexBuffer() was called
		*/
		bool MakeCurrent(PLGeneral::uint32 nStreamNumber = 0, PLGeneral::uint32 nOffset = 0);

		/**
		*  @brief
		*    Returns the vertex declaration
		*
		*  @return
		*    Vertex declaration, can be NULL
		*/
		LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration() const;

		/**
		*  @brief
		*    Returns the API vertex buffer
		*
		*  @return
		*    The API vertex buffer, NULL on error
		*/
		LPDIRECT3DVERTEXBUFFER9 GetAPIVertexBuffer() const;

		/**
		*  @brief
		*    Create a vertex declaration so we can describe to Direct3D how we'll
		*    be passing our data to it
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool CreateVertexDeclaration();

		/**
		*  @brief
		*    Destroy the vertex declaration
		*/
		void DestroyVertexDeclaration();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		LPDIRECT3DVERTEXBUFFER9		  m_pVertexBuffer;		/**< Direct3D 9 vertex buffer, can be NULL (VBO) */
		LPDIRECT3DVERTEXDECLARATION9  m_pVertexDeclaration;	/**< Vertex declaration, can be NULL (VBO) */
		PLGeneral::uint8			 *m_pData;				/**< Dynamic buffer, can be NULL (none VBO) */
		void						 *m_pLockedData;		/**< Locked data, can be NULL */
		PLGeneral::uint32			  m_nUsageAPI;			/**< API usage setting */
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
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_VERTEXBUFFER_H__
