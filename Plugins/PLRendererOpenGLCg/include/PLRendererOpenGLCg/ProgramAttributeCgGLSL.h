/*********************************************************\
 *  File: ProgramAttributeCgGLSL.h                       *
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


#ifndef __PLRENDEREROPENGLCG_PROGRAMATTRIBUTECGGLSL_H__
#define __PLRENDEREROPENGLCG_PROGRAMATTRIBUTECGGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLCg/ProgramAttributeCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg GLSL renderer program attribute
*
*  @remarks
*    When using Cg on a modern AMD/ATI graphics card, we only have a choice between the profiles
*    "arbvp1", "arbfp1", "glslv", "glslf", "glslg" - meaning we don't have a choice and have to stick
*    to GLSL because "arbvp1" & "arbfp1" are heavily out-dated.
*    Sadly, there are several issues when using Cg with GLSL profiles. When using no GLSL version hint,
*    old school GLSL is used which is related to fixed function stuff. This is causing heavy issues when
*    using VBO because the Cg compiler is now throwing e.g. glMultiTexCoord0 into the resulting GLSL code
*    as source of vertex data, but not using VBO is not an option. So, we need to provide the Cg compiler with a
*    GLSL version like 150... then the next thing happens: Cg just tells us "The parameter used is invalid." when
*    using "cgGLSetParameterPointer()"/"cgGLEnableClientState()". So, we have to figure out the OpenGL attribute
*    location and then falling back to "glVertexAttribPointerARB()"/"glEnableVertexAttribArrayARB()" instead
*    of using buggy Cg OpenGL functions. Long story, short conclusion: Using the combination
*    Cg & OpenGL & GLSL & AMD-hardware is painful, but sadly NVIDIA appears to be not interested to changing anything
*    on this situation... this issue is not new and nearly as old as Cg itself and I'am already fighting with this topic
*    for years. Still, Cg is worth all this efforts... a shader cross-compiler is a fantastic thing...
*/
class ProgramAttributeCgGLSL : public ProgramAttributeCg {


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
		*/
		ProgramAttributeCgGLSL(CGparameter pCgParameter);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramAttributeCgGLSL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		int m_nOpenGLAttributeLocation;	/**< OpenGL attribute location, <0 if invalid */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramAttribute functions ]
	//[-------------------------------------------------------]
	public:
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLCore::uint32 nIndex) override;
		virtual bool Set(PLRenderer::VertexBuffer *pVertexBuffer, PLRenderer::VertexBuffer::ESemantic nSemantic, PLCore::uint32 nChannel = 0) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_PROGRAMATTRIBUTECGGLSL_H__
