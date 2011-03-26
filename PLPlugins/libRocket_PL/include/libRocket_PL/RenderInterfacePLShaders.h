/*********************************************************\
 *  File: RenderInterfacePLShaders.h                     *
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


#ifndef __LIBROCKET_PL_RENDERINTERFACE_SHADERS_H__
#define __LIBROCKET_PL_RENDERINTERFACE_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "libRocket_PL/RenderInterfacePL.h"


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
	class VertexShader;
	class FragmentShader;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A render interface for Rocket into PixelLight using shaders
*/
class RenderInterfacePLShaders : public RenderInterfacePL {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    The used renderer context
		*  @param[in] nWindowWidth
		*    Window width
		*  @param[in] nWindowHeight
		*    Window height
		*/
		LIBROCKET_PL_API RenderInterfacePLShaders(PLRenderer::RendererContext &cRendererContext, PLGeneral::uint32 nWindowWidth, PLGeneral::uint32 nWindowHeight);

		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API virtual ~RenderInterfacePLShaders();


	//[-------------------------------------------------------]
	//[ Public virtual RenderInterfacePL functions            ]
	//[-------------------------------------------------------]
	public:
		LIBROCKET_PL_API virtual bool ConfigureRenderSystem();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::RenderInterface functions ]
	//[-------------------------------------------------------]
	public:
		LIBROCKET_PL_API virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		RenderInterfacePLShaders(const RenderInterfacePLShaders &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		RenderInterfacePLShaders &operator =(const RenderInterfacePLShaders &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexShader	*m_pVertexShader;	/**< Vertex shader, can be a null pointer */
		PLRenderer::FragmentShader	*m_pFragmentShader;	/**< Fragment shader, can be a null pointer */
		PLRenderer::Program			*m_pProgram;		/**< GPU program, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_RENDERINTERFACE_SHADERS_H__
