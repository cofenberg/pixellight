/*********************************************************\
 *  File: ShaderFunctionJitterPosition.h                 *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_JITTERPOSITION_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_JITTERPOSITION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/ShaderFunction.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shader function base class for jitter position
*
*  @remarks
*    Jitter the start position of the ray in order to reduce wooden grain effect.
*/
class ShaderFunctionJitterPosition : public ShaderFunction {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionJitterPosition, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunction, "Abstract shader function base class for jitter position")
		// Properties
		pl_properties
			pl_property("FunctionTitle",			"1.2 - Jitter Position")
			pl_property("FunctionName",				"JitterPosition")
			pl_property("FunctionSignature_GLSL",	"float JitterPosition(vec3 Position)")
			pl_property("FunctionSignature_Cg",		"float JitterPosition(float3 Position)")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunctionJitterPosition();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionJitterPosition();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_JITTERPOSITION_H__
