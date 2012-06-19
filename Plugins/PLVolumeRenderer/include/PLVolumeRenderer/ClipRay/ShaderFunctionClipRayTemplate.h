/*********************************************************\
 *  File: ShaderFunctionClipRayTemplate.h                *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_TEMPLATE_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_TEMPLATE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/ClipRay/ShaderFunctionClipRay.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Template shader function implementation class for clip ray
*/
class ShaderFunctionClipRayTemplate : public ShaderFunctionClipRay {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionClipRayTemplate, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionClipRay, "Template shader function implementation class for clip ray")
		// Properties
		pl_properties
			pl_property("FunctionTemplate",	"1")
		pl_properties_end
		// Constructors
		pl_constructor_2(ParamsConstructor,	PLCore::uint8,	PLCore::uint8,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sShaderLanguage
		*    Number of clip planes
		*  @param[in] sShaderLanguage
		*    Number of depth textures
		*/
		PLVOLUMERENDERER_API ShaderFunctionClipRayTemplate(PLCore::uint8 nNumOfClipPlanes, PLCore::uint8 nNumOfDepthTextures);

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionClipRayTemplate();


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunctionClipRay functions        ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMERENDERER_API virtual void SetPlanes(PLRenderer::Program &cProgram, const PLScene::VisNode &cVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipPlanes) override;


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
		*    Generates a template instance source code
		*
		*  @param[in] sShaderLanguage
		*    The name of the shader language (for example "GLSL" or "Cg") to return the source code for
		*
		*  @return
		*    Generated template instance source code
		*/
		PLCore::String GenerateSourceCode(const PLCore::String &sShaderLanguage);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint8				   m_nNumOfClipPlanes;		/**< Number of clip planes */
		PLCore::uint8				   m_nNumOfDepthTextures;	/**< Number of depth textures */
		PLCore::Array<ShaderFunction*> m_lstShaderFunction;		/**< Shader function instances this shader composition consists of, the given instance are just shared (do not destroy them) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_TEMPLATE_H__
