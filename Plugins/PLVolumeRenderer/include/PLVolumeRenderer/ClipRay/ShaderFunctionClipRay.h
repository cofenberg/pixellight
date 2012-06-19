/*********************************************************\
 *  File: ShaderFunctionClipRay.h                        *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/ShaderFunction.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class VisNode;
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
*    Abstract shader function base class for clip ray
*
*  @remarks
*    Shader functions derived from this class will only clip the ray by modifying the
*    ray origin or the maximum travel length. The ray will not be segmented. Thus, while
*    performing clip operations, the performance will also be improved significantly due
*    to reduce maximum travel length within the volume.
*/
class ShaderFunctionClipRay : public ShaderFunction {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionClipRay, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunction, "Abstract shader function base class for clip ray")
		// Properties
		pl_properties
			pl_property("FunctionTitle",			"1.1 - Clip Ray")
			pl_property("FunctionName",				"ClipRay")
			pl_property("FunctionSignature_GLSL",	"void ClipRay(inout vec3 RayOrigin, vec3 RayDirection, inout float MaximumTravelLength)")
			pl_property("FunctionSignature_Cg",		"void ClipRay(inout float3 RayOrigin, float3 RayDirection, inout float MaximumTravelLength)")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunctionClipRay functions        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets the clip planes
		*
		*  @param[in] cProgram
		*    Used GPU program
		*  @param[in] cVolumeVisNode
		*    Volume visibility node
		*  @param[in] lstClipPlanes
		*    List of found clip planes, the visibility scene nodes must be clip planes, there's no internal additional security check
		*
		*  @note
		*    - The default implementation does nothing
		*/
		PLVOLUMERENDERER_API virtual void SetPlanes(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipPlanes);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunctionClipRay();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionClipRay();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_CLIPRAY_H__
