/*********************************************************\
 *  File: ShaderFunctionGradientForwardDifferences.h     *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_FORWARDDIFFERENCES_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_FORWARDDIFFERENCES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/Gradient/ShaderFunctionGradient.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Forward differences (finite differences) shader function implementation class for on-the-fly gradient (4 volume texture fetches for the gradient)
*
*  @remarks
*    On-the-fly gradient computation approximating gradient vectors using the forward differences scheme
*    as described within the book "Real-Time Volume Graphics", section "5.3.1 Gradient Estimation" (page 109).
*    -> Also described within "ACM SIGGRAPH Asia 2008 - Course : Advanced Illumination Techniques for GPU Volume Raycasting"
*       (http://www.voreen.org/files/sa08-coursenotes_1.pdf), section "3.2 Gradient Computation"
*/
class ShaderFunctionGradientForwardDifferences : public ShaderFunctionGradient {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionGradientForwardDifferences, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionGradient, "Forward differences (finite differences) shader function implementation class for on-the-fly gradient (4 volume texture fetches for the gradient)")
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
		PLVOLUMERENDERER_API ShaderFunctionGradientForwardDifferences();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionGradientForwardDifferences();


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunction functions               ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMERENDERER_API virtual PLCore::String GetSourceCode(const PLCore::String &sShaderLanguage, ESourceCodeType nSourceCodeType) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_FORWARDDIFFERENCES_H__
