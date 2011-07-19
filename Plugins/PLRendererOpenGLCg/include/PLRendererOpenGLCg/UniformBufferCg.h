/*********************************************************\
 *  File: UniformBufferCg.h                              *
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


#ifndef __PLRENDEREROPENGLCG_UNIFORMBUFFERCG_H__
#define __PLRENDEREROPENGLCG_UNIFORMBUFFERCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cg.h>
#include <PLRenderer/Renderer/UniformBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg uniform buffer
*/
class UniformBufferCg : public PLRenderer::UniformBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderLanguageCg;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~UniformBufferCg();

		/**
		*  @brief
		*    Returns the dynamic data (none UBO)
		*
		*  @return
		*    Dynamic data, can be a null pointer (if no UBO if used!)
		*/
		void *GetDynamicData() const;

		/**
		*  @brief
		*    Returns the Cg buffer
		*
		*  @return
		*    The Cg buffer, can be a null pointer
		*/
		CGbuffer GetCgBuffer() const;


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
		*  @param[in] sShaderLanguage
		*    The name of the shader language the uniform buffer is using (for example "GLSL" or "Cg")
		*/
		UniformBufferCg(PLRenderer::Renderer &cRenderer, const PLCore::String &sShaderLanguage);

		/**
		*  @brief
		*    Makes this uniform buffer to the renderers current uniform buffer
		*
		*  @return
		*   'true' if all went fine, else 'false'
		*/
		bool MakeCurrent();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String  m_sShaderLanguage;	/**< The name of the shader language the uniform buffer is using (for example "GLSL" or "Cg") */
		CGbuffer	    m_pCgBuffer;		/**< Cg buffer, can be a null pointer */
		void		   *m_pData;			/**< Dynamic buffer, can be a null pointer (none UBO) */
		void		   *m_pLockedData;		/**< Locked data, can be a null pointer */
		bool		    m_bLockReadOnly;	/**< Read only lock? */
		bool		    m_bUpdateUBO;		/**< Do we need to update the UBO? */
		CGbufferusage   m_nUsageAPI;		/**< API usage setting */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::UniformBuffer functions    ]
	//[-------------------------------------------------------]
	public:
		virtual PLCore::String GetShaderLanguage() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Buffer functions           ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsAllocated() const;
		virtual bool Allocate(PLCore::uint32 nElements, PLRenderer::Usage::Enum nUsage = PLRenderer::Usage::Dynamic, bool bManaged = true, bool bKeepData = false);
		virtual bool Clear();
		virtual void *Lock(PLCore::uint32 nFlag = PLRenderer::Lock::ReadWrite);
		virtual void *GetData();
		virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Protected virtual PLRenderer::Resource functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual void BackupDeviceData(PLCore::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLCore::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_UNIFORMBUFFERCG_H__
