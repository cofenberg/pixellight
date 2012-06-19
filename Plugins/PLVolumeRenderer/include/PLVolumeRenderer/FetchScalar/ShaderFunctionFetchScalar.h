/*********************************************************\
 *  File: ShaderFunctionFetchScalar.h                    *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_FETCHSCALAR_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_FETCHSCALAR_H__
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
*    Abstract shader function base class for fetch scalar
*
*  @remarks
*    There are many ways how the volume data can be stored on the GPU (2D, 2D array, 3D)
*    and the kind of underlying volume data (just scalar, scalar and normal etc.) is also varying.
*/
class ShaderFunctionFetchScalar : public ShaderFunction {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionFetchScalar, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunction, "Abstract shader function base class for fetch scalar")
		// Properties
		pl_properties
			pl_property("FunctionTitle",			"2.2 - Fetch Scalar")
			pl_property("FunctionName",				"FetchScalar")
			pl_property("FunctionSignature_GLSL",	"float FetchScalar(vec3 Position)")
			pl_property("FunctionSignature_Cg",		"float FetchScalar(float3 Position)")
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
		PLVOLUMERENDERER_API ShaderFunctionFetchScalar();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionFetchScalar();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_FETCHSCALAR_H__
