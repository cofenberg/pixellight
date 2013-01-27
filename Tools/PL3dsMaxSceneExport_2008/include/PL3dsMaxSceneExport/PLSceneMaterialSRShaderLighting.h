/*********************************************************\
 *  File: PLSceneMaterialSRShaderLighting.h              *
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


#ifndef __PL_SCENEMATERIAL_SRSHADERLIGHTING_H__
#define __PL_SCENEMATERIAL_SRSHADERLIGHTING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLSceneMaterial.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight 'Forward.sr' & 'Deferred.sr' material
*/
class PLSceneMaterialSRShaderLighting : public PLSceneMaterial {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLSceneMaterial;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScene
		*    Scene this material is in
		*  @param[in] pParentIGameMaterial
		*    Parent of the IGame material, can be a null pointer
		*  @param[in] cIGameMaterial
		*    IGame material this material comes from
		*  @param[in] sName
		*    Name of this material
		*/
		PLSceneMaterialSRShaderLighting(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const PLCore::String &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneMaterialSRShaderLighting();

		/**
		*  @brief
		*    Exports a float
		*
		*  @param[in] cMaterialElement
		*    Material XML element to insert into
		*  @param[in] pszIGamePropertyName
		*    IGame property name
		*  @param[in] pszParameterName
		*    Resulting material parameter name
		*  @param[in] fDefault
		*    Default setting
		*/
		void ExportFloat(PLCore::XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, float fDefault);

		/**
		*  @brief
		*    Exports a color
		*
		*  @param[in] cMaterialElement
		*    Material XML element to insert into
		*  @param[in] pszIGamePropertyName
		*    IGame property name
		*  @param[in] pszParameterName
		*    Resulting material parameter name
		*  @param[in] cDefault
		*    Default setting
		*/
		void ExportColor(PLCore::XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, const Point3 &cDefault);


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneMaterial functions             ]
	//[-------------------------------------------------------]
	private:
		virtual void SaveParameters(PLCore::XmlElement &cMaterialElement) override;


};


#endif // __PL_SCENEMATERIAL_SRSHADERLIGHTING_H__
