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


#ifndef __PLRENDERERD3D11_VERTEXBUFFER_H__
#define __PLRENDERERD3D11_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D11 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    D3D11 vertex buffer
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
		*  @param[in] nOffset
		*    Vertex offset
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This function is used by the renderer when SetVertexBuffer() was called
		*/
		bool MakeCurrent(PLCore::uint32 nOffset = 0);

		/**
		*  @brief
		*    Returns the vertex offset
		*
		*  @return
		*    Vertex offset
		*
		*  @see
		*    - See vertex offset parameter in MakeCurrent()
		*/
		PLCore::uint32 GetVertexOffset() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint8 *m_pData;			/**< Dynamic buffer (none VBO) */
		void		  *m_pLockedData;	/**< Locked data */
		// Offsets
		int			   m_nOffset[NumOfSemantics][MaxPipelineChannels];
		PLCore::uint32 m_nVertexOffset;


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


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D11


#endif // __PLRENDERERD3D11_VERTEXBUFFER_H__
