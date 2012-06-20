/*********************************************************\
 *  File: ShaderFunctionClipPositionEllipsoid.cpp        *
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
