/*********************************************************\
 *  File: PLSceneCamera.cpp                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
PLSceneCamera::PLSceneCamera(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName) :
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
void PLSceneCamera::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	TimeValue nTime = GetScene().GetMaxInterface().GetTime();
	CameraState cCameraState;
	Interval cValid = FOREVER;
	ObjectState cOS = GetMaxNode()->EvalWorldState(nTime);
	CameraObject *pCamera = static_cast<CameraObject*>(cOS.obj); // Do we need to perform any class check here??
	pCamera->EvalCameraState(nTime, cValid, &cCameraState);

	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName());
	pNodeElement->SetAttribute("Name",  GetName());

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
