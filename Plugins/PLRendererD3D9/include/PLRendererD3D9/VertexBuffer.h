/*********************************************************\
 *  File: VertexBuffer.h                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
		bool MakeCurrent(PLCore::uint32 nStreamNumber = 0, PLCore::uint32 nOffset = 0);

		/**
		*  @brief
		*    Returns the vertex declaration
		*
		*  @return
		*    Vertex declaration, can be a null pointer
		*/
		LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration() const;

		/**
		*  @brief
		*    Returns the API vertex buffer
		*
		*  @return
		*    The API vertex buffer, a null pointer on error
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
		LPDIRECT3DVERTEXBUFFER9		  m_pVertexBuffer;		/**< Direct3D 9 vertex buffer, can be a null pointer (VBO) */
		LPDIRECT3DVERTEXDECLARATION9  m_pVertexDeclaration;	/**< Vertex declaration, can be a null pointer (VBO) */
		PLCore::uint8				 *m_pData;				/**< Dynamic buffer, can be a null pointer (none VBO) */
		void						 *m_pLockedData;		/**< Locked data, can be a null pointer */
		PLCore::uint32				  m_nUsageAPI;			/**< API usage setting */
		/** Offsets */
		int m_nOffset[NumOfSemantics][MaxPipelineChannels];


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::VertexBuffer functions     ]
	//[-------------------------------------------------------]
	public:
		virtual void *GetData(PLCore::uint32 nIndex, PLCore::uint32 nSemantic, PLCore::uint32 nChannel = 0) override;
		virtual PLGraphics::Color4 GetColor(PLCore::uint32 nIndex, PLCore::uint32 nChannel = 0) override;
		virtual bool SetColor(PLCore::uint32 nIndex, const PLGraphics::Color4 &cColor, PLCore::uint32 nChannel = 0) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::VertexBuffer functions    ]
	//[-------------------------------------------------------]
	private:
		virtual void VertexAttributeAdded(Attribute &cAttribute) override;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Buffer functions           ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsAllocated() const override;
		virtual bool Allocate(PLCore::uint32 nElements, PLRenderer::Usage::Enum nUsage = PLRenderer::Usage::Dynamic, bool bManaged = true, bool bKeepData = false) override;
		virtual bool Clear() override;
		virtual void *Lock(PLCore::uint32 nFlag = PLRenderer::Lock::ReadWrite) override;
		virtual void *GetData() override;
		virtual bool Unlock() override;


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLCore::uint8 **ppBackup) override;
		virtual void RestoreDeviceData(PLCore::uint8 **ppBackup) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_VERTEXBUFFER_H__
