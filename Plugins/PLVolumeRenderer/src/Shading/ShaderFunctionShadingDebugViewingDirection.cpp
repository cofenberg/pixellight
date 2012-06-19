/*********************************************************\
 *  File: ShaderFunctionShadingDebugViewingDirection.cpp *
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
#include "PLVolumeRenderer/Shading/ShaderFunctionShadingDebugViewingDirection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
using namespace PLRenderer;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionShadingDebugViewingDirection)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionShadingDebugViewingDirection::ShaderFunctionShadingDebugViewingDirection()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionShadingDebugViewingDirection::~ShaderFunctionShadingDebugViewingDirection()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionShadingDebugViewingDirection::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "DebugViewingDirection_GLSL.h"

		// Return the requested source code
		if (nSourceCodeType == FragmentShaderBody)
			return sSourceCode_Fragment;
	} else if (sShaderLanguage == Cg) {
		#include "DebugViewingDirection_Cg.h"

		// Return the requested source code
		if (nSourceCodeType == FragmentShaderBody)
			return sSourceCode_Fragment;
	}

	// Error!
	return "";
}

void ShaderFunctionShadingDebugViewingDirection::SetProgram(Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Get the view space to object space matrix
	Matrix4x4 mViewSpaceToObjectSpace = cVisNode.GetWorldViewMatrix();
	mViewSpaceToObjectSpace.Invert();

	{ // Set viewing direction
		// Bring the normalized view space viewing direction vector into scene node space
		Vector3 vObjectSpaceViewingDirection = mViewSpaceToObjectSpace.RotateVector(Vector3::NegativeUnitZ);	// Vector from surface point to camera (in view space, the camera looks along the negative z-axis)
		vObjectSpaceViewingDirection.Normalize();

		// Set the normalized viewing direction in scene node space
		cProgramWrapper.Set("ViewingDirection", vObjectSpaceViewingDirection);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
