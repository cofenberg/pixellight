/*********************************************************\
 *  File: PLSceneMaterialFX.h                            *
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


#ifndef __PL_SCENEMATERIAL_FX_H__
#define __PL_SCENEMATERIAL_FX_H__
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
*    Exported PixelLight FX material
*/
class PLSceneMaterialFX : public PLSceneMaterial {


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
		PLSceneMaterialFX(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const std::string &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneMaterialFX();


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneMaterial functions             ]
	//[-------------------------------------------------------]
	private:
		virtual void SaveParameters(PLGeneral::XmlElement &cMaterialElement);


};


#endif // __PL_SCENEMATERIAL_FX_H__
