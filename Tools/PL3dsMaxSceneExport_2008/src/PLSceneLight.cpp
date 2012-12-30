/*********************************************************\
 *  File: PLSceneLight.cpp                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
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
#include "PL3dsMaxSceneExport/PLSceneTexture.h"
#include "PL3dsMaxSceneExport/PLSceneLight.h"


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
PLSceneLight::PLSceneLight(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName) :
	PLSceneNode(&cContainer, &cIGameNode, sName, TypeLight, "")
{
}

/**
*  @brief
*    Destructor
*/
PLSceneLight::~PLSceneLight()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneLight::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	bool bError = true; // Error by default

	// Get the IGame light object of the given IGame node
	IGameObject *pIGameObject = GetIGameNode()->GetIGameObject();
	if (pIGameObject) {
		// One thing... if the light is for example a 'VRay'-light 'GetLightType()' will crash!
		// So we have to do this quite complicated...
		Object *pMaxObject = pIGameObject->GetMaxObject();
		if (pMaxObject && pMaxObject->SuperClassID() == LIGHT_CLASS_ID &&
			(pMaxObject->CanConvertToType(Class_ID(OMNI_LIGHT_CLASS_ID,  0)) ||
			 pMaxObject->CanConvertToType(Class_ID(SPOT_LIGHT_CLASS_ID,  0)) ||
			 pMaxObject->CanConvertToType(Class_ID(DIR_LIGHT_CLASS_ID,   0)) ||
			 pMaxObject->CanConvertToType(Class_ID(FSPOT_LIGHT_CLASS_ID, 0)) ||
			 pMaxObject->CanConvertToType(Class_ID(TDIR_LIGHT_CLASS_ID,  0)))) {
			// Check the type of the IGame object
			IGameLight &cIGameLight = *static_cast<IGameLight*>(pIGameObject);
			if (pIGameObject->GetIGameType() == IGameObject::IGAME_LIGHT &&
				cIGameLight.GetLightType() != IGameLight::IGAME_UNKNOWN) {
				// Initialize the data of the IGame object - because of the 'clever' default implementation
				// that returns 'false' if nothing was to do, we can't call this function and have to be
				// 'inconsistent'...
	//			if (cIGameLight.InitializeData()) {
					// Is the light not hidden and is rendered but should still not be used?
					if (!GetIGameNode()->IsNodeHidden() && GetIGameNode()->GetMaxNode()->Renderable() && !cIGameLight.IsLightOn())
						AddFlag("Invisible");

					// Get a GenLight from the node
					GenLight &cMaxLight = *static_cast<GenLight*>(pMaxObject);

					// Cast shadows?
					if (cIGameLight.CastShadows()) {
						// Shadow active? (jap, another state we have to check :)
						if (cMaxLight.GetShadow()) {
							// We only accept shadow mapping
							if (cMaxLight.GetShadowMethod() == LIGHTSHADOW_MAPPED && !cMaxLight.GetShadowType())
								AddFlag("CastShadow|ReceiveShadow");
							else
								g_pLog->LogFLine(PLLog::Hint, "Light node '%s' shadow casting is deactivated because only shadow mapping is supported.", GetIGameNode()->GetName());
						}
					}

					// Get the projector map... I found no way to do this using IGame...
					BitmapTex *pBitmapTex = nullptr;
					Texmap *pMap = cMaxLight.GetProjector() ? cMaxLight.GetProjMap() : nullptr;
					if (pMap && pMap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
						pBitmapTex = static_cast<BitmapTex*>(pMap);

					// Add scene node
					XmlElement *pNodeElement = new XmlElement("Node");

					// Spot light
					String sClassName;
					bool bDirectionalLight = false;
					bool bSpotLight = (cIGameLight.GetLightType() == IGameLight::IGAME_TSPOT || cIGameLight.GetLightType() == IGameLight::IGAME_FSPOT);
					if (bSpotLight) {
						// Is this a projective spot light?
						if (pBitmapTex) {
							sClassName = "PLScene::SNProjectiveSpotLight";

							// Light shape
							if (cIGameLight.GetSpotLightShape() != RECT_LIGHT) {
								// [HACK] Just a 'dummy'-flag because if no flags are set the default setting
								// is used which is 'NoCone'...
								AddFlag("Cone");
							}
						} else {
							sClassName = "PLScene::SNSpotLight";

							// Light shape
							if (cIGameLight.GetSpotLightShape() == RECT_LIGHT)
								AddFlag("NoCone");
						}

					// Directional light
					} else if (cIGameLight.GetLightType() == IGameLight::IGAME_DIR || cIGameLight.GetLightType() == IGameLight::IGAME_TDIR) {
						sClassName = "PLScene::SNDirectionalLight";
						bDirectionalLight = true;

					// Omni directional light
					} else {
						sClassName = pBitmapTex ? "PLScene::SNProjectivePointLight" : "PLScene::SNPointLight";
					}

					// Class name
					if (GetClassName().GetLength())
						sClassName = GetClassName(); // Overwrite the default PixelLight class name
					pNodeElement->SetAttribute("Class", sClassName);

					// Name
					pNodeElement->SetAttribute("Name", GetName());

					// Write position, rotation, scale, bounding box and flags
					WriteToFilePosRotScaleBoxFlags(*pNodeElement);

					// Color
					IGameProperty *pIGameProperty = cIGameLight.GetLightColor();
					if (pIGameProperty) {
						// Get the light multiplier data
						float fMultiplier = 1.0f;
						IGameProperty *pIGameMultiplierProperty = cIGameLight.GetLightMultiplier();
						if (pIGameMultiplierProperty)
							pIGameMultiplierProperty->GetPropertyValue(fMultiplier);

						// Get light color
						Point3 vColor;
						if (pIGameProperty->GetPropertyValue(vColor)) {
							vColor *= fMultiplier;
							if (vColor.x != 1.0f || vColor.y != 1.0f || vColor.z != 1.0f)
								pNodeElement->SetAttribute("Color", String::Format("%f %f %f", vColor.x, vColor.y, vColor.z));
						}
					}

					// Directional light?
					if (bDirectionalLight) {
						// No special parameters
					} else {
						// Range ('far attenuation - end')
						pIGameProperty = cIGameLight.GetLightAttenEnd();
						if (pIGameProperty) {
							float fRange;
							if (pIGameProperty->GetPropertyValue(fRange))
								PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "Range", fRange, 1.0f);
						}

						// Special spot light settings
						if (bSpotLight) {
							// OuterAngle
							pIGameProperty = cIGameLight.GetLightFallOff();
							if (pIGameProperty) {
								float fFallOff;
								if (pIGameProperty->GetPropertyValue(fFallOff))
									PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "OuterAngle", fFallOff, 45.0f);
							}

							// InnerAngle
							pIGameProperty = cIGameLight.GetLightHotSpot();
							if (pIGameProperty) {
								float fHotSpot;
								if (pIGameProperty->GetPropertyValue(fHotSpot))
									PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "InnerAngle", fHotSpot, 35.0f);
							}

							// ZNear ('near attenuation - start')
							pIGameProperty = cIGameLight.GetLightAttenStart();
							if (pIGameProperty) {
								float fAttenStart;
								if (pIGameProperty->GetPropertyValue(fAttenStart) && fAttenStart != 0.1f) {
									PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "ZNear", fAttenStart, 0.1f);

									// 'Normally' the near plane should never ever be <=0! (crazy z-fighting!)
									if (fAttenStart <= 1.0000000e-006 && GetIGameNode())
										g_pLog->LogFLine(PLLog::Warning, "Light (3ds Max node '%s') 'near attenuation' (= near plane) '%f' (really small number) but recommended is '>1.0000000e-006'!", GetIGameNode()->GetName(), fAttenStart);
								}
							}

							// Aspect (only used for rectangle light shape!)
							if (cIGameLight.GetSpotLightShape() == RECT_LIGHT) {
								pIGameProperty = cIGameLight.GetLightAspectRatio();
								if (pIGameProperty) {
									float fAspectRatio;
									if (pIGameProperty->GetPropertyValue(fAspectRatio))
										PLTools::XmlElementSetAttributeWithDefault(*pNodeElement, "Aspect", fAspectRatio, 1.0f);
								}
							}
						}
					}

					// Projected material
					if (pBitmapTex) {
						// Copy the texture
						PLSceneTexture *pTexture = GetScene().CopyTexture(pBitmapTex->GetMapName());
						if (pTexture) {
							// Add as light variable
							pNodeElement->SetAttribute("ProjectedMaterial", pTexture->GetName());
						}
					}

					// Write flexible variables
					WriteVariables(*pNodeElement);

					// Write modifiers
					WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

					// Link node element
					cSceneElement.LinkEndChild(*pNodeElement);

					// No error occurred
					bError = false;
			//	}
			} else {
				g_pLog->LogFLine(PLLog::Error, "%s: IGame object is no known light object!", GetIGameNode()->GetName());
			}
		} else {
			g_pLog->LogFLine(PLLog::Error, "%s: IGame object is no known light object!", GetIGameNode()->GetName());
		}

		// Release the IGame object
		GetIGameNode()->ReleaseIGameObject();
	} else {
		g_pLog->LogFLine(PLLog::Error, "%s: IGame node has no IGame object!", GetIGameNode()->GetName());
	}

	// Was there an error? If yes we replace this light node through an 'unknown' node.
	if (bError) {
		// Update the statistics
		GetContainer()->m_sStatistics.nNumOfLights--;
		GetContainer()->m_sStatistics.nNumOfUnknown++;
		GetScene().m_sSceneStatistics.nNumOfLights--;
		GetScene().m_sSceneStatistics.nNumOfUnknown++;

		// Add scene node
		XmlElement *pNodeElement = new XmlElement("Node");
		pNodeElement->SetAttribute("Class", GetClassName().GetLength() ? GetClassName() : "PLScene::SNUnknown");
		pNodeElement->SetAttribute("Name",  GetName());

		// Write position, rotation, scale, bounding box and flags
		WriteToFilePosRotScaleBoxFlags(*pNodeElement);

		// Write flexible variables
		WriteVariables(*pNodeElement);

		// Write modifiers
		WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

		// Link node element
		cSceneElement.LinkEndChild(*pNodeElement);
	}
}
