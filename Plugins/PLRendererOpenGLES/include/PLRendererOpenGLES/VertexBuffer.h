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


#ifndef __PLRENDEREROPENGLES_VERTEXBUFFER_H__
#define __PLRENDEREROPENGLES_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/VertexBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES vertex buffer
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
		bool BindAndUpdate();


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
		PLCore::uint32  m_nVertexBuffer;	/**< OpenGL ES vertex buffer (VBO) */
		PLCore::uint8  *m_pData;			/**< Dynamic buffer (none VBO) */
		void		   *m_pLockedData;		/**< Locked data */
		bool			m_bLockReadOnly;	/**< Read only lock? */
		bool			m_bUpdateVBO;		/**< Do we need to update the VBO? */
		PLCore::uint32  m_nUsageAPI;		/**< API usage setting */
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
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_VERTEXBUFFER_H__
