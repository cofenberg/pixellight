/*********************************************************\
 *  File: PLSceneCamera.cpp                              *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Xml/Xml.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneCamera.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneCamera::PLSceneCamera(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName) :
	PLSceneNode(&cContainer, &cIGameNode, sName, TypeCamera, "PLScene::SNCamera")
{
}

/**
*  @brief
*    Destructor
*/
PLSceneCamera::~PLSceneCamera()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneCamera::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	TimeValue nTime = GetScene().GetMaxInterface().GetTime();
	CameraState cCameraState;
	Interval cValid = FOREVER;
	ObjectState cOS = GetMaxNode()->EvalWorldState(nTime);
	CameraObject *pCamera = static_cast<CameraObject*>(cOS.obj); // Do we need to perform any class check here??
	pCamera->EvalCameraState(nTime, cValid, &cCameraState);

	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName().c_str());
	pNodeElement->SetAttribute("Name",  GetName().c_str());

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pNodeElement);

	// [HACK] FOV... I multiplicate it with '0.74' so the result 'looks' similar to the one within
	// the 3ds Max viewport...
	float fFOV = RadToDeg(cCameraState.fov*0.74f);
	if (fFOV != 45.0f)
		pNodeElement->SetAttribute("FOV", String::Format("%f", fFOV));

	// [TODO] Do we want/need to export this aspect value?
	// Aspect
//	float fAspect = GetScene().GetMaxInterface().GetRendImageAspect();
//	if (fAspect != 1.0f)
//		pNodeElement->SetAttribute("Aspect", String::Format("%f", fAspect));

	// Export z-near and z-far settings?
	if (cCameraState.manualClip) {
		// ZNear (ignore 0 or PL default setting)
		float fRange = cCameraState.hither;
		if (fRange != 0.01f) {
			pNodeElement->SetAttribute("ZNear", String::Format("%f", fRange));

			// 'Normally' the near plane should never ever be <=0! (crazy z-fighting!)
			if (fRange <= 1.0000000e-006 && GetIGameNode())
				g_pLog->LogFLine(PLLog::Warning, "Camera (3ds Max node '%s') near plane is '%f' (really small number) but recommended is '>1.0000000e-006'!", GetIGameNode()->GetName(), fRange);
		}

		// ZFar (ignore 0 or PL default setting)
		fRange = cCameraState.yon;
		if (fRange && fRange != 1000.0f)
			pNodeElement->SetAttribute("ZFar", String::Format("%f", fRange));
	}

	// Write flexible variables
	WriteVariables(*pNodeElement);

	// Write modifiers
	WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

	// Link node element
	cSceneElement.LinkEndChild(*pNodeElement);
}
