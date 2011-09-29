/*********************************************************\
 *  File: AssimpLoader.cpp                                *
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
#include <Assimp/aiMaterial.h>
#include <PLRenderer/Material/Material.h>
#include <PLRenderer/Material/ParameterManager.h>
#include "PLAssimp/AssimpLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
AssimpLoader::AssimpLoader()
{
}

/**
*  @brief
*    Destructor
*/
AssimpLoader::~AssimpLoader()
{
}

/**
*  @brief
*    Converts a given Assimp string into a PixelLight string
*/
String AssimpLoader::AssimpStringToPL(const aiString &sAssimpString) const
{
	return String::FromUTF8(sAssimpString.data, -1, sAssimpString.length);
}

/**
*  @brief
*    Converts a given Assimp material into a PixelLight material
*/
void AssimpLoader::AssimpMaterialToPL(const aiMaterial &cAssimpMaterial, Material &cPLMaterial) const
{
	// Get the parameter manager of the material
	ParameterManager &cParameterManager = cPLMaterial.GetParameterManager();

	{ // AI_MATKEY_TWOSIDED - default: 0
		int nTwoSided = 0;
		aiGetMaterialInteger(&cAssimpMaterial, AI_MATKEY_TWOSIDED, &nTwoSided);
		if (nTwoSided)
			cParameterManager.SetParameter1i("TwoSided", 1);
	}

	// AI_MATKEY_SHADING_MODEL - not supported
	// AI_MATKEY_ENABLE_WIREFRAME - not supported
	// AI_MATKEY_BLEND_FUNC - not supported

	{ // AI_MATKEY_OPACITY - default: 1.0
		float fOpacity = 1.0f;
		aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_OPACITY, &fOpacity);
		if (fOpacity < 1.0f)
			cParameterManager.SetParameter1f("Opacity", fOpacity);
	}

	{ // AI_MATKEY_BUMPSCALING - default: 1.0
		float fBumpScaling = 1.0f;
		aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_BUMPSCALING, &fBumpScaling);
		if (fBumpScaling != 1.0f)
			cParameterManager.SetParameter1f("NormalMapBumpiness", fBumpScaling);
	}

	{ // AI_MATKEY_SHININESS - default: 45.0
		float fShininess = 45.0f;
		aiGetMaterialFloat(&cAssimpMaterial, AI_MATKEY_SHININESS, &fShininess);
		if (fShininess != 45.0f)
			cParameterManager.SetParameter1f("SpecularExponent", fShininess);
	}

	// AI_MATKEY_REFLECTIVITY - not supported
	// AI_MATKEY_SHININESS_STRENGTH - not supported
	// AI_MATKEY_REFRACTI - not supported

	{ // AI_MATKEY_COLOR_DIFFUSE - default: 1.0 1.0 1.0
		aiColor3D cColor(1.0f, 1.0f, 1.0f);
		if (cAssimpMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, cColor) == AI_SUCCESS)
			cParameterManager.SetParameter3f("DiffuseColor", cColor.r, cColor.g, cColor.b);
	}

	// AI_MATKEY_COLOR_AMBIENT - not supported

	{ // AI_MATKEY_COLOR_SPECULAR - default: 1.0 1.0 1.0
		aiColor3D cColor(1.0f, 1.0f, 1.0f);
		if (cAssimpMaterial.Get(AI_MATKEY_COLOR_SPECULAR, cColor) == AI_SUCCESS)
			cParameterManager.SetParameter3f("SpecularColor", cColor.r, cColor.g, cColor.b);
	}

	{ // AI_MATKEY_COLOR_EMISSIVE - default: 1.0 1.0 1.0
		aiColor3D cColor(1.0f, 1.0f, 1.0f);
		if (cAssimpMaterial.Get(AI_MATKEY_COLOR_EMISSIVE, cColor) == AI_SUCCESS)
			cParameterManager.SetParameter3f("EmissiveMapColor", cColor.r, cColor.g, cColor.b);
	}

	// AI_MATKEY_COLOR_TRANSPARENT - not supported
	// AI_MATKEY_COLOR_REFLECTIVE - not supported
	// AI_MATKEY_GLOBAL_BACKGROUND_IMAGE - not supported

	{ // aiTextureType_DIFFUSE
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_DIFFUSE, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("DiffuseMap", AssimpStringToPL(sAssimpFilename));
	}

	{ // aiTextureType_SPECULAR
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_SPECULAR, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("SpecularMap", AssimpStringToPL(sAssimpFilename));
	}

	{ // aiTextureType_SPECULAR
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_SPECULAR, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("SpecularMap", AssimpStringToPL(sAssimpFilename));
	}

	// aiTextureType_AMBIENT - not supported

	{ // aiTextureType_EMISSIVE
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_EMISSIVE, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("EmissiveMap", AssimpStringToPL(sAssimpFilename));
	}

	{ // aiTextureType_HEIGHT
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_HEIGHT, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("HeightMap", AssimpStringToPL(sAssimpFilename));
	}

	{ // aiTextureType_NORMALS
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_NORMALS, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("NormalMap", AssimpStringToPL(sAssimpFilename));
	}

	//  aiTextureType_SHININESS - not supported
	//  aiTextureType_OPACITY - not supported
	//  aiTextureType_DISPLACEMENT - not supported

	{ // aiTextureType_LIGHTMAP
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_LIGHTMAP, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("LightMap", AssimpStringToPL(sAssimpFilename));
	}

	{ // aiTextureType_REFLECTION
		aiString sAssimpFilename;
		if (cAssimpMaterial.GetTexture(aiTextureType_REFLECTION, 0, &sAssimpFilename) == AI_SUCCESS)
			cParameterManager.SetParameterTexture("ReflectionColor", AssimpStringToPL(sAssimpFilename));
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
AssimpLoader::AssimpLoader(const AssimpLoader &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
AssimpLoader &AssimpLoader::operator =(const AssimpLoader &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
