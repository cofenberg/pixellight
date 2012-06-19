/*********************************************************\
 *  File: ShaderFunctionRaySetupBoundingBoxIntersection.cpp *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLScene/Visibility/VisContainer.h>
#include <PLVolume/Volume.h>
#include <PLVolume/Scene/SNVolume.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/RaySetup/ShaderFunctionRaySetupBoundingBoxIntersection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionRaySetupBoundingBoxIntersection)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionRaySetupBoundingBoxIntersection::ShaderFunctionRaySetupBoundingBoxIntersection()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionRaySetupBoundingBoxIntersection::~ShaderFunctionRaySetupBoundingBoxIntersection()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionRaySetupBoundingBoxIntersection::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "BoundingBoxIntersection_GLSL.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case VertexShaderBody:
				return sSourceCode_Vertex;

			case FragmentShaderHeader:
				return sSourceCode_Fragment_Header;

			case FragmentShaderBody:
				return sSourceCode_Fragment;
		}
	} else if (sShaderLanguage == Cg) {
		#include "BoundingBoxIntersection_Cg.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case VertexShaderBody:
				return sSourceCode_Vertex;

			case FragmentShaderHeader:
				return sSourceCode_Fragment_Header;

			case FragmentShaderBody:
				return sSourceCode_Fragment;
		}
	}

	// Error!
	return "";
}

void ShaderFunctionRaySetupBoundingBoxIntersection::SetProgram(Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Get the volume scene node
	PLVolume::SNVolume *pSNVolume = static_cast<PLVolume::SNVolume*>(cVisNode.GetSceneNode());
	if (!pSNVolume)
		return;	// Early escape, there's no sense in continuing

	// Get the volume resource
	PLVolume::Volume *pVolume = pSNVolume->GetVolume();
	if (!pVolume)
		return;	// Early escape, there's no sense in continuing

	// Get used renderer instance
	Renderer &cRenderer = cProgram.GetRenderer();

	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Set object space to clip space matrix
	cProgramWrapper.Set("ObjectSpaceToClipSpaceMatrix", cVisNode.GetWorldViewProjectionMatrix());

	// Set window size
	cProgramWrapper.Set("WindowSize", static_cast<int>(cRenderer.GetViewport().GetWidth()), static_cast<int>(cRenderer.GetViewport().GetHeight()));

	{ // Set clip space to object space matrix
		// Get object space to clip space matrix, and invert it
		Matrix4x4 mClipSpaceToObjectSpace = cVisNode.GetWorldViewProjectionMatrix();
		mClipSpaceToObjectSpace.Invert();

		// Set clip space to object space matrix
		cProgramWrapper.Set("ClipSpaceToObjectSpace", mClipSpaceToObjectSpace);
	}

	{ // Set ray origin in volume object space
		// Bring the view space origin into scene node space
		Matrix4x4 mViewMatrix = cVisNode.GetWorldViewMatrix();
		mViewMatrix.Invert();
		const Vector3 vRayOrigin = mViewMatrix*Vector3::Zero;

		// Set ray origin in volume object space
		cProgramWrapper.Set("RayOrigin", vRayOrigin);
	}

	// Set step size
	cProgramWrapper.Set("StepSize", pVolume->GetStepSize(pSNVolume->VolumeTextureLOD.Get() + cSRPVolume.GetGlobalVolumeTextureLOD(), pSNVolume->SampleRateFactor.Get()*cSRPVolume.GetGlobalSampleRateFactor()));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
