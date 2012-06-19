/*********************************************************\
 *  File: ShaderFunctionClipRayPlane.cpp                 *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule W�rzburg-Schweinfurt
 *    Fakult�t Informatik, Wirtschaftsinformatik (FIW)
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
#include "PLVolumeRenderer/ClipRay/ShaderFunctionClipRayPlane.h"


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
pl_implement_class(ShaderFunctionClipRayPlane)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionClipRayPlane::ShaderFunctionClipRayPlane()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionClipRayPlane::~ShaderFunctionClipRayPlane()
{
}

/**
*  @brief
*    Sets the clip plane parameters
*/
void ShaderFunctionClipRayPlane::SetPlane(Program &cProgram, const VisNode &cVolumeVisNode, const Plane &cViewSpaceClipPlane, int nIndex)
{
	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Bring the view space clip plane into scene node space
	Matrix4x4 mViewMatrix = cVolumeVisNode.GetWorldViewMatrix();
	mViewMatrix.Invert();
	const Plane cClipPlane = cViewSpaceClipPlane*mViewMatrix;

	// Set the clip plane in Hesse normal form
	cProgramWrapper.Set((nIndex < 0) ? "ClipPlane_x_" : (String("ClipPlane_") + nIndex + '_'), cClipPlane.a, cClipPlane.b, cClipPlane.c, cClipPlane.d);
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunctionClipRay functions        ]
//[-------------------------------------------------------]
void ShaderFunctionClipRayPlane::SetPlanes(Program &cProgram, const VisNode &cVolumeVisNode, const Array<const VisNode*> &lstClipPlanes)
{
	// None-template version

	// We only know a single clip plane, ignore the rest
	if (lstClipPlanes.GetNumOfElements()) {
		const VisNode *pVisNode = lstClipPlanes[0];

		// Invert clipping?
		const bool bInvertClipping = (pVisNode->GetSceneNode()->GetFlags() & PLVolume::SNClip::InvertClipping) != 0;

		// Get the view space clip plane
		Plane cViewSpaceClipPlane;
		cViewSpaceClipPlane.ComputeND(pVisNode->GetWorldViewMatrix()*Vector3::Zero, pVisNode->GetWorldViewMatrix().RotateVector(bInvertClipping ? Vector3::NegativeUnitZ : Vector3::UnitZ));

		// Set clip plane
		SetPlane(cProgram, cVolumeVisNode, cViewSpaceClipPlane, -1);
	}
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionClipRayPlane::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "Plane_GLSL.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	} else if (sShaderLanguage == Cg) {
		#include "Plane_Cg.h"

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