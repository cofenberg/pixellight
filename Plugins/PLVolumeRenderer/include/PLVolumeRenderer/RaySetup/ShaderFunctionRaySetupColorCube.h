/*********************************************************\
 *  File: ShaderFunctionRaySetupColorCube.h              *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_RAYSETUP_COLORCUBE_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_RAYSETUP_COLORCUBE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/RaySetup/ShaderFunctionRaySetup.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Plane;
}
namespace PLRenderer {
	class Program;
	class VertexBuffer;
	class SurfaceTextureBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Color cube rasterization shader function implementation class for ray setup
*/
class ShaderFunctionRaySetupColorCube : public ShaderFunctionRaySetup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionRaySetupColorCube, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionRaySetup, "Color cube rasterization shader function implementation class for ray setup")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunctionRaySetupColorCube();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionRaySetupColorCube();


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunction functions               ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMERENDERER_API virtual PLCore::String GetSourceCode(const PLCore::String &sShaderLanguage, ESourceCodeType nSourceCodeType) override;
		PLVOLUMERENDERER_API virtual void SetProgram(PLRenderer::Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Updates the front texture of the color cube
		*
		*  @param[in] cProgram
		*    The used GPU program
		*  @param[in] cCullQuery
		*    The used cull query
		*  @param[in] cVisNode
		*    The used visibility node
		*  @param[in] cSRPVolume
		*    The used volume scene renderer pass
		*/
		void UpdateFrontTexture(const PLRenderer::Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, const SRPVolume &cSRPVolume);

		/**
		*  @brief
		*    Returns the GPU program for rendering the front side of the color cube
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] sShaderLanguage
		*    The name of the shader language (for example "GLSL" or "Cg")
		*
		*  @return
		*    The GPU program for rendering the front side of the color cube, null pointer on error
		*
		*  @note
		*    - Creates the GPU program if it hasn't been created, yet
		*/
		PLRenderer::Program *GetProgramFront(PLRenderer::Renderer &cRenderer, const PLCore::String &sShaderLanguage);

		void UpdateNearCap(const PLMath::Plane &cPlane);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Program				 *m_pProgramFront;		/**< GPU program for rendering the front side of the color cube, can be a null pointer */
		PLRenderer::SurfaceTextureBuffer *m_pColorTargetFront;	/**< Color render target for rendering the front side of the color cube, can be a null pointer */
		PLRenderer::VertexBuffer		 *m_pCapVertexBuffer;	/**< Near cap vertex buffer, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_RAYSETUP_COLORCUBE_H__
