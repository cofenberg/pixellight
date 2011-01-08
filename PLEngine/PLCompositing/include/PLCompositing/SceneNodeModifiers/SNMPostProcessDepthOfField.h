/*********************************************************\
 *  File: SNMPostProcessDepthOfField.h                   *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_SCENENODEMODIFIER_DEPTHOFFIELD_H__
#define __PLSCENE_SCENENODEMODIFIER_DEPTHOFFIELD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include "PLCompositing/SceneNodeModifiers/SNMPostProcess.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Depth of field camera scene node post process modifier class
*
*  @remarks
*    The used scene renderer MUST support this effect by writing DOF data into the alpha
*    channel of the frame buffer this effect is using to combine the blured and original
*    images.
*
*  @note
*    - The implementation is basing on "Advanced Depth of Field": http://ati.amd.com/developer/gdc/Scheuermann_DepthOfField.pdf
*    - Only the first instance of this modifier inside a camera is used
*/
class SNMPostProcessDepthOfField : public SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SNMPostProcessDepthOfField, "PLCompositing", PLCompositing::SNMPostProcess, "Depth of field camera scene node post process modifier class")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
		pl_attribute(NearBlurDepth,		float,				0.15f,									ReadWrite,	DirectValue,	"Near blur depth",													"")
		pl_attribute(FocalPlaneDepth,	float,				0.25f,									ReadWrite,	DirectValue,	"Focal plane depth",												"")
		pl_attribute(FarBlurDepth,		float,				25.0f,									ReadWrite,	DirectValue,	"Far blur depth",													"")
		pl_attribute(BlurrinessCutoff,	float,				0.8f,									ReadWrite,	DirectValue,	"Blurriness cutoff constant for objects behind the focal plane",	"")
		pl_attribute(BloomScale,		float,				1.0f,									ReadWrite,	DirectValue,	"Bloom scale",														"")
		pl_attribute(Strength,			PLMath::Vector2,	PLMath::Vector2(4.0f, 4.0f),			ReadWrite,	DirectValue,	"Blur strength",													"")
		// Overloaded SNMPostProcess variables
		pl_attribute(Filename,			PLGeneral::String,	"Data/PostProcesses/DepthOfField.pp",	ReadWrite,	ModifyAttr,		"Filename of the post process to use",								"Type='PostProcess'")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLCOM_API SNMPostProcessDepthOfField(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SNMPostProcessDepthOfField();


	//[-------------------------------------------------------]
	//[ Public virtual SNMPostProcess functions               ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API virtual void SetParameters();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLSCENE_SCENENODEMODIFIER_DEPTHOFFIELD_H__
