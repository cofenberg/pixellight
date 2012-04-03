/*********************************************************\
 *  File: PLSceneCamera.cpp                              *
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
#include <PLCore/Xml/Xml.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneCamera.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


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
	PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "FOV", RadToDeg(cCameraState.fov*0.74f), 45.0f);

	// [TODO] Do we want/need to export this aspect value?
	// Aspect
//	PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "Aspect", GetScene().GetMaxInterface().GetRendImageAspect(), 1.0f);

	// Export z-near and z-far settings?
	if (cCameraState.manualClip) {
		// ZNear (ignore 0 or PL default setting)
		float fRange = cCameraState.hither;
		if (fRange != 0.1f) {
			PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "ZNear", fRange, 0.1f);

			// 'Normally' the near plane should never ever be <=0! (crazy z-fighting!)
			if (fRange <= 1.0000000e-006 && GetIGameNode())
				g_pLog->LogFLine(PLLog::Warning, "Camera (3ds Max node '%s') near plane is '%f' (really small number) but recommended is '>1.0000000e-006'!", GetIGameNode()->GetName(), fRange);
		}

		// ZFar (ignore 0 or PL default setting)
		fRange = cCameraState.yon;
		if (fRange)
			PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "ZFar", fRange, 1000.0f);
	}

	// Write flexible variables
	WriteVariables(*pNodeElement);

	// Write modifiers
	WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

	// Link node element
	cSceneElement.LinkEndChild(*pNodeElement);
}
