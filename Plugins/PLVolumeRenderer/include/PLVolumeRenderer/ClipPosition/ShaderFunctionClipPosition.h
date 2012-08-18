/*********************************************************\
 *  File: ShaderFunctionClipPosition.h                   *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_H__
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
*    Abstract shader function base class for clip position
*
*  @remarks
*    Shader functions derived from this class will clip individual positions inside
*    the volume. There's no guarantee that due to clip operations the ray is only
*    clipped by modifying the ray origin or the maximum travel length. The ray will
*    potentially be segmented. Thus, while performing clip operations, the performance
*    may be reduced due to additional calculations performed while traveling through the
*    volume.
*/
class ShaderFunctionClipPosition : public ShaderFunction {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionClipPosition, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunction, "Abstract shader function base class for clip position")
		// Properties
		pl_properties
			pl_property("FunctionTitle",			"2.1 - Clip Position")
			pl_property("FunctionName",				"ClipPosition")
			pl_property("FunctionSignature_GLSL",	"bool ClipPosition(vec3 Position)")
			pl_property("FunctionSignature_Cg",		"bool ClipPosition(float3 Position)")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunctionClipPosition functions   ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets the clip boxes
		*
		*  @param[in] cProgram
		*    Used GPU program
		*  @param[in] cVolumeVisNode
		*    Volume visibility node
		*  @param[in] lstClipBoxes
		*    List of found clip boxes, the visibility scene nodes must be clip boxes, there's no internal additional security check
		*
		*  @note
		*    - The default implementation does nothing
		*/
		PLVOLUMERENDERER_API virtual void SetBoxes(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipBoxes);

		/**
		*  @brief
		*    Sets the clip ellipsoids
		*
		*  @param[in] cProgram
		*    Used GPU program
		*  @param[in] cVolumeVisNode
		*    Volume visibility node
		*  @param[in] lstClipEllipsoids
		*    List of found clip ellipsoids, the visibility scene nodes must be clip ellipsoids, there's no internal additional security check
		*
		*  @note
		*    - The default implementation does nothing
		*/
		PLVOLUMERENDERER_API virtual void SetEllipsoids(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipEllipsoids);

		/**
		*  @brief
		*    Sets the clip volume textures
		*
		*  @param[in] cProgram
		*    Used GPU program
		*  @param[in] cVolumeVisNode
		*    Volume visibility node
		*  @param[in] lstClipVolumeTextures
		*    List of found clip volume textures, the visibility scene nodes must be clip volume textures, there's no internal additional security check
		*
		*  @note
		*    - The default implementation does nothing
		*/
		PLVOLUMERENDERER_API virtual void SetVolumeTextures(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipVolumeTextures);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunctionClipPosition();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionClipPosition();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_H__
