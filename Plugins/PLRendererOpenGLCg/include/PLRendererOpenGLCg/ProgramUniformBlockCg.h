/*********************************************************\
 *  File: ProgramUniformBlockCg.h                        *
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


#ifndef __PLRENDEREROPENGLCG_PROGRAMUNIFORMBLOCKCG_H__
#define __PLRENDEREROPENGLCG_PROGRAMUNIFORMBLOCKCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cgGL.h>
#include <PLCore/String/String.h>
#include <PLRenderer/Renderer/ProgramUniformBlock.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg renderer program uniform block
*/
class ProgramUniformBlockCg : public PLRenderer::ProgramUniformBlock {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ProgramCg;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pCgParameter
		*    Cg program parameter, must be valid!
		*  @param[in] sShaderLanguage
		*    The name of the shader language the uniform block is using (for example "GLSL" or "Cg")
		*/
		ProgramUniformBlockCg(CGparameter pCgParameter, const PLCore::String &sShaderLanguage);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramUniformBlockCg();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sShaderLanguage;	/**< The name of the shader language the uniform block is using (for example "GLSL" or "Cg") */
		CGparameter	   m_pCgParameter;		/**< Cg program parameter, always valid! */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramUniformBlock functions ]
	//[-------------------------------------------------------]
	public:
		virtual bool SetUniformBuffer(PLRenderer::UniformBuffer *pUniformBuffer, PLCore::uint32 nBindingPoint) override;
		virtual PLCore::uint32 GetIndex() const override;
		virtual PLCore::uint32 GetSize() const override;
		virtual PLCore::uint32 GetUniformOffset(const PLCore::String &sUniformName) const override;
		virtual PLCore::uint32 GetUniformSize(const PLCore::String &sUniformName) const override;
		virtual PLCore::uint32 GetUniformNumOfArrayElements(const PLCore::String &sUniformName) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_PROGRAMUNIFORMBLOCKCG_H__
