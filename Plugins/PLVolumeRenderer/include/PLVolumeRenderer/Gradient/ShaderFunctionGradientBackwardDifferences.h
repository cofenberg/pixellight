/*********************************************************\
 *  File: ShaderFunctionGradientBackwardDifferences.h    *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_BACKWARDDIFFERENCES_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_BACKWARDDIFFERENCES_H__
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
*    Backward differences (finite differences) shader function implementation class for on-the-fly gradient (4 volume texture fetches for the gradient)
*
*  @remarks
*    On-the-fly gradient computation approximating gradient vectors using the backward differences scheme
*    as described within the book "Real-Time Volume Graphics", section "5.3.1 Gradient Estimation" (page 109).
*/
class ShaderFunctionGradientBackwardDifferences : public ShaderFunctionGradient {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionGradientBackwardDifferences, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionGradient, "Backward differences (finite differences) shader function implementation class for on-the-fly gradient (4 volume texture fetches for the gradient)")
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
		PLVOLUMERENDERER_API ShaderFunctionGradientBackwardDifferences();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionGradientBackwardDifferences();


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


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_GRADIENT_BACKWARDDIFFERENCES_H__
