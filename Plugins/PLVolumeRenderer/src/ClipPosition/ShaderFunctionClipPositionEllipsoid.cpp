/*********************************************************\
 *  File: ShaderFunctionClipPositionEllipsoid.cpp        *
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
#include "PLVolumeRenderer/ClipPosition/ShaderFunctionClipPositionEllipsoid.h"


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
pl_implement_class(ShaderFunctionClipPositionEllipsoid)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionClipPositionEllipsoid::ShaderFunctionClipPositionEllipsoid()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionClipPositionEllipsoid::~ShaderFunctionClipPositionEllipsoid()
{
}

/**
*  @brief
*    Sets the clip ellipsoid parameters
*/
void ShaderFunctionClipPositionEllipsoid::SetEllipsoid(Program &cProgram, const VisNode &cVolumeVisNode, const VisNode &cEllipsoidVisNode, int nIndex)
{
	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Calculate the volume space to clip ellipsoid space matrix
	// Volume space to view space
	Matrix4x4 mVolumeSpaceToClipEllipsoidSpace = cVolumeVisNode.GetWorldViewMatrix();
	// View space to clip ellipsoid space
	mVolumeSpaceToClipEllipsoidSpace = cEllipsoidVisNode.GetWorldViewMatrix().GetInverted()*mVolumeSpaceToClipEllipsoidSpace;

	// Set the volume space to clip ellipsoid space matrix
	cProgramWrapper.Set((nIndex < 0) ? "VolumeSpaceToClipEllipsoidSpace_x_" : (String("VolumeSpaceToClipEllipsoidSpace_") + nIndex + '_'), mVolumeSpaceToClipEllipsoidSpace);

	// Set invert clipping
	cProgramWrapper.Set((nIndex < 0) ? "InvertClipping_x_" : (String("InvertClipping_") + nIndex + '_'), (cEllipsoidVisNode.GetSceneNode()->GetFlags() & PLVolume::SNClip::InvertClipping) != 0);
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunctionClipPosition functions   ]
//[-------------------------------------------------------]
void ShaderFunctionClipPositionEllipsoid::SetEllipsoids(Program &cProgram, const VisNode &cVolumeVisNode, const Array<const VisNode*> &lstClipEllipsoids)
{
	// None-template version

	// We only know a single clip ellipsoid, ignore the rest
	if (lstClipEllipsoids.GetNumOfElements())
		SetEllipsoid(cProgram, cVolumeVisNode, *lstClipEllipsoids[0], -1);
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionClipPositionEllipsoid::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "Ellipsoid_GLSL.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	} else if (sShaderLanguage == Cg) {
		#include "Ellipsoid_Cg.h"

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
