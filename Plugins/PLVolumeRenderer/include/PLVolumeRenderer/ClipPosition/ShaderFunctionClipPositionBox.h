/*********************************************************\
 *  File: ShaderFunctionClipPositionBox.h                *
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


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_BOX_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_BOX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeRenderer/ClipPosition/ShaderFunctionClipPosition.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Box shader function implementation class for clip position
*/
class ShaderFunctionClipPositionBox : public ShaderFunctionClipPosition {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunctionClipPositionBox, "PLVolumeRenderer", PLVolumeRenderer::ShaderFunctionClipPosition, "Box shader function implementation class for clip position")
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
		PLVOLUMERENDERER_API ShaderFunctionClipPositionBox();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunctionClipPositionBox();

		/**
		*  @brief
		*    Sets the clip box parameters
		*
		*  @param[in] cProgram
		*    Used GPU program
		*  @param[in] cVolumeVisNode
		*    Volume visibility node
		*  @param[in] cBoxVisNode
		*    Clip box visibility node
		*  @param[in] nIndex
		*    Clip box uniform index, <0 if no index
		*/
		PLVOLUMERENDERER_API void SetBox(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLScene::VisNode &cBoxVisNode, int nIndex);


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunctionClipPosition functions   ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMERENDERER_API virtual void SetBoxes(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipBoxes) override;


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


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_CLIPPOSITION_BOX_H__
