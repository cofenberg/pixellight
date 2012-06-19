/*********************************************************\
 *  File: ShaderFunctionShadingDebug.h                   *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_SHADING_DEBUG_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_SHADING_DEBUG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/Shading/ShaderFunctionShading.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract debug shader function implementation base class for shading
*
*  @remarks
*    We could do just one single debug shader function and then using a switch statement within the
*    shader in order to decide which debug feature to show. Tests have shown that even
*    for debugging, the performance would be unacceptable (in the region of 20 FPS instead of 50 FPS).
*    So, in order to have also for debugging a decent performance, we go the way requiring more
*    writing. It's really worth the effort and this way we're also able to debug the performance.
*/
class ShaderFunctionShadingDebug : public ShaderFunctionShading {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionShadingDebug, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionShading, "Abstract debug shader function implementation base class for shading")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunctionShadingDebug();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionShadingDebug();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_SHADING_DEBUG_H__
