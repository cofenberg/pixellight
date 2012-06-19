/*********************************************************\
 *  File: ShaderFunctionClassificationPreIntegration.h   *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_CLASSIFICATION_PREINTEGRATION_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_CLASSIFICATION_PREINTEGRATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/Classification/ShaderFunctionClassification.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Pre-integration shader function implementation class for classification
*
*  @remarks
*    The given scalar value is used as index for a pre-integration transfer function.

*    "Pre-Integration" as described within the book "Real-Time Volume Graphics", section "4.5 Pre-Integrated Transfer Functions" (page 92)
*    and section "7.2 Single-Pass GPU Ray Casting for Uniform Grids" (page 167).
*   -> "Pre-integrated transfer functions allow us to use much lower sampling rates than post-interpolative transfer functions when using
*       transfer functions that contain high frequencies." (quote from page 102)
*/
class ShaderFunctionClassificationPreIntegration : public ShaderFunctionClassification {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionClassificationPreIntegration, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionClassification, "Pre-integration shader function implementation class for classification")
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
		PLVOLUMERENDERER_API ShaderFunctionClassificationPreIntegration();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionClassificationPreIntegration();


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunction functions               ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMERENDERER_API virtual PLCore::String GetSourceCode(const PLCore::String &sShaderLanguage, ESourceCodeType nSourceCodeType) override;
		PLVOLUMERENDERER_API virtual void SetProgram(PLRenderer::Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_CLASSIFICATION_PREINTEGRATION_H__
