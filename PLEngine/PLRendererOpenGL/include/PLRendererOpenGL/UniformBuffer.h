/*********************************************************\
 *  File: UniformBuffer.h                                *
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


#ifndef __PLRENDEREROPENGL_UNIFORMBUFFER_H__
#define __PLRENDEREROPENGL_UNIFORMBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/UniformBuffer.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL uniform buffer
*/
class UniformBuffer : public PLRenderer::UniformBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderLanguageGLSL;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~UniformBuffer();

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
		*    Returns the OpenGL uniform buffer
		*
		*  @return
		*    The OpenGL uniform buffer, 0 on error
		*/
		PLGeneral::uint32 GetOpenGLUniformBuffer() const;


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
		UniformBuffer(PLRenderer::Renderer &cRenderer, const PLGeneral::String &sShaderLanguage);

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
		PLGeneral::String  m_sShaderLanguage;	/**< The name of the shader language the uniform buffer is using (for example "GLSL" or "Cg") */
		PLGeneral::uint32  m_nUniformBuffer;	/**< OpenGL uniform buffer (UBO) */
		void			  *m_pData;				/**< Dynamic buffer, can be a null pointer (none UBO) */
		void			  *m_pLockedData;		/**< Locked data, can be a null pointer */
		bool			   m_bLockReadOnly;		/**< Read only lock? */
		bool			   m_bUpdateUBO;		/**< Do we need to update the UBO? */
		PLGeneral::uint32  m_nUsageAPI;			/**< API usage setting */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::UniformBuffer functions    ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetShaderLanguage() const;


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
	//[ Protected virtual PLRenderer::Resource functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_UNIFORMBUFFER_H__
