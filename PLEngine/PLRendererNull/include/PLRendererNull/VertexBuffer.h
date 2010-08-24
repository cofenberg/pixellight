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


#ifndef __PLRENDERERNULL_VERTEXBUFFER_H__
#define __PLRENDERERNULL_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null vertex buffer
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
		*  @param[in] nOffset
		*    Vertex offset
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This function is used by the renderer when SetVertexBuffer() was called
		*/
		bool MakeCurrent(PLGeneral::uint32 nOffset = 0);

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
		PLGeneral::uint32 GetVertexOffset() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint8 *m_pData;			/**< Dynamic buffer (none VBO) */
		void			 *m_pLockedData;	/**< Locked data */
		// Offsets
		int				  m_nOffset[NumOfSemantics][MaxPipelineChannels];
		PLGeneral::uint32 m_nVertexOffset;


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


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererNull


#endif // __PLRENDERERNULL_VERTEXBUFFER_H__
