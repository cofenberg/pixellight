/*********************************************************\
 *  File: PLSceneMaterialSRShaderLighting.h              *
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
		*    Parent of the IGame material, can be NULL
		*  @param[in] cIGameMaterial
		*    IGame material this material comes from
		*  @param[in] sName
		*    Name of this material
		*/
		PLSceneMaterialSRShaderLighting(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const std::string &sName);

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
		void ExportFloat(PLGeneral::XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, float fDefault);

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
		void ExportColor(PLGeneral::XmlElement &cMaterialElement, const char *pszIGamePropertyName, const char *pszParameterName, const Point3 &cDefault);


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneMaterial functions             ]
	//[-------------------------------------------------------]
	private:
		virtual void SaveParameters(PLGeneral::XmlElement &cMaterialElement);


};


#endif // __PL_SCENEMATERIAL_SRSHADERLIGHTING_H__
