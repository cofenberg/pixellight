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
	class ParameterManager;
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
		*    Constructor
		*
		*  @param[in] sDefaultTextureFileExtension
		*    Default texture file extension (completely in lower case is highly recommended)
		*
		*  @see
		*   - "GetDefaultTextureFileExtension()"
		*/
		AssimpLoader(const PLCore::String &sDefaultTextureFileExtension);

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
		*    Returns the default texture file extension
		*
		*  @return
		*    Default texture file extension
		*
		*  @remarks
		*    Within some files, textures are addressed by using e.g. "Houses" (without directory, without extension) and we have to guess
		*    which resource should be used. This is of course a really nasty situation, but by providing a default texture file extension
		*    like "dds" there's at least a slim chance that we're able to load in the requested resources.
		*/
		PLCore::String GetDefaultTextureFileExtension() const;

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
		*    Returns the Assimp post processing flags for the given quality step
		*
		*  @param[in] nQuality
		*    Integer parameter for post processing quality (0=none ... 3=maximum quality but slowest processing)
		*/
		unsigned int QualityToAssimpFlags(PLCore::uint8 nQuality) const;

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

		/**
		*  @brief
		*    Sets the texture of a material parameter
		*
		*  @param[in] cParameterManager
		*    Parameter manager of the material
		*  @param[in] sName
		*    Name of the material parameter where to set the texture
		*  @param[in] sFilename
		*    Texture filename
		*/
		void SetParameterTexture(PLRenderer::ParameterManager &cParameterManager, const PLCore::String &sName, const PLCore::String &sFilename) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		const PLCore::String m_sDefaultTextureFileExtension;	/**< Default texture file extension (e.g. "dds") */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_ASSIMPLOADER_H__
