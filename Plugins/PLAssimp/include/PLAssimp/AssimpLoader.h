/*********************************************************\
 *  File: AssimpLoader.h                                 *
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


#ifndef __PLASSIMP_ASSIMPLOADER_H__
#define __PLASSIMP_ASSIMPLOADER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct aiString;
struct aiMaterial;
namespace PLRenderer {
	class Material;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader using Assimp base class
*/
class AssimpLoader {


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		AssimpLoader();

		/**
		*  @brief
		*    Destructor
		*
		*  @note
		*    - Intentionally not virtual because there's no need to make it virtual
		*/
		~AssimpLoader();

		/**
		*  @brief
		*    Converts a given Assimp string into a PixelLight string
		*
		*  @param[in] sAssimpString
		*    Assimp string to convert
		*
		*  @return
		*    PixelLight string
		*/
		PLCore::String AssimpStringToPL(const aiString &sAssimpString) const;

		/**
		*  @brief
		*    Converts a given Assimp material into a PixelLight material
		*
		*  @param[in]  cAssimpMaterial
		*    Assimp material to convert
		*  @param[out] cPLMaterial
		*    PixelLight material to fill by using the given Assimp material (PixelLight material is not cleared before it's filled)
		*/
		void AssimpMaterialToPL(const aiMaterial &cAssimpMaterial, PLRenderer::Material &cPLMaterial) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		AssimpLoader(const AssimpLoader &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		AssimpLoader &operator =(const AssimpLoader &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_ASSIMPLOADER_H__
