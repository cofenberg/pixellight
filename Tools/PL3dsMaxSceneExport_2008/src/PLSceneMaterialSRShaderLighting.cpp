/*********************************************************\
 *  File: PLSceneMaterialSRShaderLighting.cpp            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
#include <IGame/IGameFX.h>
#include <iparamb2.h>
#include <pbbitmap.h>
#include <IDxMaterial.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneMaterialSRShaderLighting.h"


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
PLSceneMaterialSRShaderLighting::PLSceneMaterialSRShaderLighting(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const String &sName) :
	PLSceneMaterial(cScene, pParentIGameMaterial, &cIGameMaterial, sName)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneMaterialSRShaderLighting::~PLSceneMaterialSRShaderLighting()
{
}

/**
*  @brief
*    Exports a float
*/
void PLSceneMaterialSRShaderLighting::ExportFloat(XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, float fDefault)
{
	// Check the parameters
	if (pszIGamePropertyName && pszParameterName) {
		// Get the property container
		IPropertyContainer *pPropertyContainer = m_pIGameMaterial->GetIPropertyContainer();
		if (pPropertyContainer) {
			// Get the property
			IGameProperty *pProperty = pPropertyContainer->QueryProperty(String(pszIGamePropertyName));
			if (pProperty) {
				if (pProperty->GetType() == IGAME_FLOAT_PROP) {
					// Get the property value
					float fFloat;
					if (pProperty->GetPropertyValue(fFloat)) {
						// Default value?
						if (!g_SEOptions.bSmartMaterialParameters || fFloat != fDefault) {
							// Add to material
							XmlElement *pFloatElement = new XmlElement("Float");
							pFloatElement->SetAttribute("Name", pszParameterName);

							// Add value
							XmlText *pValue = new XmlText(String::Format("%f", fFloat));
							pFloatElement->LinkEndChild(*pValue);

							// Link float element
							cMaterialElement.LinkEndChild(*pFloatElement);
						}
					}
				} else if (pProperty->GetType() == IGAME_INT_PROP) {
					// Get the property value
					int nInt;
					if (pProperty->GetPropertyValue(nInt)) {
						// Default value?
						if (!g_SEOptions.bSmartMaterialParameters || nInt != fDefault) {
							// Add to material
							XmlElement *pFloatElement = new XmlElement("Float");
							pFloatElement->SetAttribute("Name", pszParameterName);

							// Add value
							XmlText *pValue = new XmlText(String::Format("%d", nInt));
							pFloatElement->LinkEndChild(*pValue);

							// Link float element
							cMaterialElement.LinkEndChild(*pFloatElement);
						}
					}
				}
			}
		}
	}
}

/**
*  @brief
*    Exports a color
*/
void PLSceneMaterialSRShaderLighting::ExportColor(XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, const Point3 &cDefault)
{
	// Check the parameters
	if (pszIGamePropertyName && pszParameterName) {
		// Get the property container
		IPropertyContainer *pPropertyContainer = m_pIGameMaterial->GetIPropertyContainer();
		if (pPropertyContainer) {
			// Get the property
			IGameProperty *pProperty = pPropertyContainer->QueryProperty(String(pszIGamePropertyName));
			if (pProperty && pProperty->GetType() == IGAME_POINT4_PROP) {
				// Get the property value, as RGBA because just as RGB is not working...
				Point4 cColor;
				if (pProperty->GetPropertyValue(cColor)) {
					// Default value?
					if (!g_SEOptions.bSmartMaterialParameters || cColor.x != cDefault.x || cColor.y != cDefault.y || cColor.z != cDefault.z) {
						// Add to material
						XmlElement *pFloat3Element = new XmlElement("Float3");
						pFloat3Element->SetAttribute("Name", pszParameterName);

						// Add value
						XmlText *pValue = new XmlText(String::Format("%f %f %f", cColor.x, cColor.y, cColor.z));
						pFloat3Element->LinkEndChild(*pValue);

						// Link float element
						cMaterialElement.LinkEndChild(*pFloat3Element);
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneMaterial functions             ]
//[-------------------------------------------------------]
void PLSceneMaterialSRShaderLighting::SaveParameters(XmlElement &cMaterialElement)
{
	// Get the 3ds Max material... I don't use IGame for this because I didn't get it working using it...
	Mtl *pMaxMaterial = m_pIGameMaterial->GetMaxMaterial();
	if (pMaxMaterial) {
		// DxMaterial or extend?
		IDxMaterial2 *pFXMaterial = static_cast<IDxMaterial2*>(m_pIGameMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL2_INTERFACE));
		if (!pFXMaterial && m_pParentIGameMaterial)
			pFXMaterial = static_cast<IDxMaterial2*>(m_pParentIGameMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL2_INTERFACE));
		if (pFXMaterial) { // Get information from the DirectX Shader material
			bool bReflectionMap = false;

			// Get the parameter block containing the other data
			IParamBlock2 *pParamBlock = pMaxMaterial->GetParamBlock(0);
			if (pParamBlock) {
				TimeValue t = m_pScene->GetMaxInterface().GetTime();
				Interval ivalid;

				// Because I can't find such a quite useful parameter/name-map, I create my own...
				std::map<TSTR, int> mapParams;
				int nNumOfParams = pParamBlock->NumParams();
				for (int i=0; i<nNumOfParams; i++) {
					TSTR pszName = pParamBlock->GetLocalName(i);
					if (pszName)
						mapParams.insert(std::make_pair(pszName, i));
				}

				// Export some general parameters
				ExportFloat(cMaterialElement, "twoSided",					"TwoSided",					0.0f);
				ExportFloat(cMaterialElement, "opacity",					"Opacity",					1.0f);
				ExportColor(cMaterialElement, "diffuseColor",				"DiffuseColor",				Point3(1.0f, 1.0f, 1.0f));
				ExportFloat(cMaterialElement, "specularExponent",			"SpecularExponent",			128.0f);
				ExportColor(cMaterialElement, "specularColor",				"SpecularColor",			Point3(1.0f, 1.0f, 1.0f));
				ExportFloat(cMaterialElement, "indexOfRefraction",			"IndexOfRefraction",		0.0f);

				// Loop through all parameters
				for (int i=0; i<nNumOfParams; i++) {
					ParamType2 nParamType = pParamBlock->GetParameterType(i);
					switch (nParamType) {
						case TYPE_BITMAP:
						{
							// Get the name of the parameter
							const String sName = pParamBlock->GetLocalName(i);

							// diffuseMap
							if (sName.CompareNoCase("diffuseMap")) {
								// Get alpha reference
								float fAlphaReference = 0.0f;
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("alphaReference"));
								if (pIterator != mapParams.end() && pParamBlock->GetValue(pIterator->second, t, fAlphaReference, ivalid)) {
									// If 'useDiffuseMapAlpha' is false, set alpha reference to 0
									pIterator = mapParams.find(_T("useDiffuseMapAlpha"));
									if (pIterator != mapParams.end() && !pParamBlock->GetInt(pIterator->second, t))
										fAlphaReference = 0.0f;
								}

								// [TODO] What if no diffuse map, but alpha within PL?
								// useDiffuseMap
								pIterator = mapParams.find(_T("useDiffuseMap"));
								bool bUseDiffuseMap = (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t));
								if (bUseDiffuseMap || fAlphaReference) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();

										// If the 'diffuse color' is black, we still NEED the map because of lights!
										if (!sName.CompareNoCase("None")) {
											// [TODO] Check whether the used bitmap has an alpha channel!
//											if (fAlphaReference)
												ExportFloat(cMaterialElement, "alphaReference", "AlphaReference", 127.0f);
											SaveTexture(cMaterialElement, sName, "DiffuseMap");
										}
									}
								}

							// normalMap
							} else if (sName.CompareNoCase("normalMap")) {
								// useNormalMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useNormalMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None")) {
											// Save the texture and take 'compressedNormalMap' into account ('plt'-file...)
											pIterator = mapParams.find(_T("compressedNormalMap"));
											SaveTexture(cMaterialElement, sName, "NormalMap", pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t));
										}
									}
								}

							// specularMap
							} else if (sName.CompareNoCase("specularMap")) {
								// useSpecularMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useSpecularMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None")) {
											// If the 'specular color' is black, we DON'T need the map!
											Point4 cValue(1.0f, 1.0f, 1.0f, 1.0f);
											pIterator = mapParams.find(_T("specularColor"));
											if (pIterator != mapParams.end())
												pParamBlock->GetValue(pIterator->second, t, cValue, ivalid);
											if (cValue.x || cValue.y || cValue.z) {
												// [TODO] useSpecularMapGloss
												SaveTexture(cMaterialElement, sName, "SpecularMap");
											}
										}
									}
								}

							// reflection2DMap
							} else if (sName.CompareNoCase("reflection2DMap")) {
								// We can ONLY use 2D OR cube reflection NOT both... within the fx-shader
								// I found no way to setup the parameters dialog correctly...
								if (!bReflectionMap) {
									// useReflection2DMap
									std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useReflection2DMap"));
									if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
										// Get parameter value
										PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
										if (pBitmap) {
											BitmapInfo &cBInfo = pBitmap->bi;
											const String sName = cBInfo.Name();
											if (!sName.CompareNoCase("None")) {
												// If the 'reflection color' is black, we DON'T need the map!
												Point4 cValue(1.0f, 1.0f, 1.0f, 1.0f);
												pIterator = mapParams.find(_T("reflectionColor"));
												if (pIterator != mapParams.end())
													pParamBlock->GetValue(pIterator->second, t, cValue, ivalid);
												if (cValue.x || cValue.y || cValue.z) {
													// [TODO] useReflectionNormalMap
													SaveTexture(cMaterialElement, sName, "ReflectionMap");
													ExportColor(cMaterialElement, "reflectionColor", "ReflectionColor", Point3(1.0f, 1.0f, 1.0f));
													bReflectionMap = true;
												}
											}
										}
									}
								}

							// reflectionCubeMap
							} else if (sName.CompareNoCase("reflectionCubeMap")) {
								// We can ONLY use 2D OR cube reflection NOT both... within the fx-shader
								// I found no way to setup the parameters dialog correctly...
								if (!bReflectionMap) {
									// useReflectionCubeMap
									std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useReflectionCubeMap"));
									if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
										// Get parameter value
										PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
										if (pBitmap) {
											BitmapInfo &cBInfo = pBitmap->bi;
											const String sName = cBInfo.Name();
											if (!sName.CompareNoCase("None")) {
												// If the 'reflection map color' is black, we DON'T need the map!
												Point4 cValue(1.0f, 1.0f, 1.0f, 1.0f);
												pIterator = mapParams.find(_T("reflectionColor"));
												if (pIterator != mapParams.end())
													pParamBlock->GetValue(pIterator->second, t, cValue, ivalid);
												if (cValue.x || cValue.y || cValue.z) {
													// [TODO] useReflectionNormalMap
													SaveTexture(cMaterialElement, sName, "ReflectionMap");
													ExportColor(cMaterialElement, "reflectionColor", "ReflectionColor", Point3(1.0f, 1.0f, 1.0f));
													bReflectionMap = true;
												}
											}
										}
									}
								}

							// reflectivityMap
							} else if (sName.CompareNoCase("reflectivityMap")) {
								// useReflectivityMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useReflectivityMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None"))
											SaveTexture(cMaterialElement, sName, "ReflectivityMap");
									}
								}

							// emissiveMap
							} else if (sName.CompareNoCase("emissiveMap")) {
								// useEmissiveMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useEmissiveMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None")) {
											// If the 'emissive map color' is black, we DON'T need the map!
											Point4 cValue(1.0f, 1.0f, 1.0f, 1.0f);
											pIterator = mapParams.find(_T("emissiveMapColor"));
											if (pIterator != mapParams.end())
												pParamBlock->GetValue(pIterator->second, t, cValue, ivalid);
											if (cValue.x || cValue.y || cValue.z) {
												SaveTexture(cMaterialElement, sName, "EmissiveMap");
												ExportColor(cMaterialElement, "emissiveMapColor", "EmissiveMapColor", Point3(1.0f, 1.0f, 1.0f));
											}
										}
									}
								}

							// lightMap
							} else if (sName.CompareNoCase("lightMap")) {
								// useLightMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useLightMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None")) {
											// If the 'light map color' is black, we DON'T need the map!
											Point4 cValue(1.0f, 1.0f, 1.0f, 1.0f);
											pIterator = mapParams.find(_T("lightMapColor"));
											if (pIterator != mapParams.end())
												pParamBlock->GetValue(pIterator->second, t, cValue, ivalid);
											if (cValue.x || cValue.y || cValue.z) {
												SaveTexture(cMaterialElement, sName, "LightMap");
												ExportColor(cMaterialElement, "lightMapColor", "LightMapColor", Point3(1.0f, 1.0f, 1.0f));
											}
										}
									}
								}

							// heightMap
							} else if (sName.CompareNoCase("heightMap")) {
								// useParallaxMapping
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useParallaxMapping"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None")) {
											// If the 'parallax' is null, we DON'T need the map!
											float fValue = 0.04f;
											pIterator = mapParams.find(_T("parallax"));
											if (pIterator != mapParams.end())
												pParamBlock->GetValue(pIterator->second, t, fValue, ivalid);
											if (fValue) {
												ExportFloat(cMaterialElement, "parallax", "Parallax", 0.04f);
												SaveTexture(cMaterialElement, sName, "HeightMap");
											}
										}
									}
								}

							// diffuseRampMap
							} else if (sName.CompareNoCase("diffuseRampMap")) {
								// useDiffuseRampMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useDiffuseRampMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None"))
											SaveTexture(cMaterialElement, sName, "DiffuseRampMap");
									}
								}

							// specularRampMap
							} else if (sName.CompareNoCase("specularRampMap")) {
								// useSpecularRampMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useSpecularRampMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None"))
											SaveTexture(cMaterialElement, sName, "SpecularRampMap");
									}
								}

							// edgeRampMap
							} else if (sName.CompareNoCase("edgeRampMap")) {
								// useEdgeRampMap
								std::map<TSTR, int>::iterator pIterator = mapParams.find(_T("useEdgeRampMap"));
								if (pIterator != mapParams.end() && pParamBlock->GetInt(pIterator->second, t)) {
									// Get parameter value
									PBBitmap *pBitmap = pParamBlock->GetBitmap(i, t);
									if (pBitmap) {
										BitmapInfo &cBInfo = pBitmap->bi;
										const String sName = cBInfo.Name();
										if (!sName.CompareNoCase("None"))
											SaveTexture(cMaterialElement, sName, "EdgeRampMap");
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}
