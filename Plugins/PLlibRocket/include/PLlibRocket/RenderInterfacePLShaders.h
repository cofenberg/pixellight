/*********************************************************\
 *  File: RenderInterfacePLShaders.h                     *
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
