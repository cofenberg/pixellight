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


#ifndef __PLLIBROCKET_RENDERINTERFACE_SHADERS_H__
#define __PLLIBROCKET_RENDERINTERFACE_SHADERS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLlibRocket/RenderInterfacePL.h"


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
namespace PLlibRocket {


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
		*/
		PLLIBROCKET_API RenderInterfacePLShaders(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		PLLIBROCKET_API virtual ~RenderInterfacePLShaders();


	//[-------------------------------------------------------]
	//[ Public virtual RenderInterfacePL functions            ]
	//[-------------------------------------------------------]
	public:
		PLLIBROCKET_API virtual bool ConfigureRenderSystem() override;


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::RenderInterface functions ]
	//[-------------------------------------------------------]
	public:
		PLLIBROCKET_API virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation) override;


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
} // PLlibRocket


#endif // __PLLIBROCKET_RENDERINTERFACE_SHADERS_H__
