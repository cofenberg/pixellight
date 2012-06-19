/*********************************************************\
 *  File: ShaderFunctionClipPositionBox.cpp              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLVolume/Scene/SNClip.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/ClipPosition/ShaderFunctionClipPositionBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionClipPositionBox)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionClipPositionBox::ShaderFunctionClipPositionBox()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionClipPositionBox::~ShaderFunctionClipPositionBox()
{
}

/**
*  @brief
*    Sets the clip box parameters
*/
void ShaderFunctionClipPositionBox::SetBox(Program &cProgram, const VisNode &cVolumeVisNode, const VisNode &cBoxVisNode, int nIndex)
{
	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Calculate the volume space to clip box space matrix
	// Volume space to view space
	Matrix4x4 mVolumeSpaceToClipBoxSpace = cVolumeVisNode.GetWorldViewMatrix();
	// View space to clip box space
	mVolumeSpaceToClipBoxSpace = cBoxVisNode.GetWorldViewMatrix().GetInverted()*mVolumeSpaceToClipBoxSpace;

	// Set the volume space to clip box space matrix
	cProgramWrapper.Set((nIndex < 0) ? "VolumeSpaceToClipBoxSpace_x_" : (String("VolumeSpaceToClipBoxSpace_") + nIndex + '_'), mVolumeSpaceToClipBoxSpace);

	// Set invert clipping
	cProgramWrapper.Set((nIndex < 0) ? "InvertClipping_x_" : (String("InvertClipping_") + nIndex + '_'), (cBoxVisNode.GetSceneNode()->GetFlags() & PLVolume::SNClip::InvertClipping) != 0);
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunctionClipPosition functions   ]
//[-------------------------------------------------------]
void ShaderFunctionClipPositionBox::SetBoxes(PLRenderer::Program &cProgram, const PLScene::VisNode &cVolumeVisNode, const PLCore::Array<const PLScene::VisNode*> &lstClipBoxes)
{
	// None-template version

	// We only know a single clip box, ignore the rest
	if (lstClipBoxes.GetNumOfElements())
		SetBox(cProgram, cVolumeVisNode, *lstClipBoxes[0], -1);
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionClipPositionBox::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "Box_GLSL.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	} else if (sShaderLanguage == Cg) {
		#include "Box_Cg.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	}

	// Error!
	return "";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
