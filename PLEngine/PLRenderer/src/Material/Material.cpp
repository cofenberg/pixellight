/*********************************************************\
 *  File: Material.cpp                                   *
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
#include <PLGeneral/File/Url.h>
#include <PLGeneral/Log/Log.h>
#include <PLCore/Tools/LoadableManager.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Material/Parameter.h"
#include "PLRenderer/Texture/Texture.h"
#include "PLRenderer/Texture/TextureHandler.h"
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Material/MaterialManager.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Material/MaterialHandler.h"
#include "PLRenderer/Material/Material.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const String Material::DiffuseMap			= "DiffuseMap";
const String Material::LightMap				= "LightMap";
const String Material::AmbientOcclusionMap	= "AmbientOcclusionMap";
const String Material::EmissiveMap			= "EmissiveMap";
const String Material::ReflectionMap		= "ReflectionMap";
const String Material::ReflectivityMap		= "ReflectivityMap";
const String Material::NormalMap			= "NormalMap";
const String Material::SpecularMap			= "SpecularMap";
const String Material::HeightMap			= "HeightMap";


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Material::~Material()
{
	// First at all: Unload the material
	Unload();

	// Destroy the parameter manager
	delete m_pParameterManager;
}

/**
*  @brief
*    Returns the material manager this material is in
*/
MaterialManager &Material::GetMaterialManager() const
{
	// There MUST always be a manager!
	return static_cast<MaterialManager&>(*m_pManager);
}

/**
*  @brief
*    Copy operator
*/
Material &Material::operator =(const Material &cSource)
{
	// [TODO] Copy parameters
//	*m_pParameterManager = *cSource.m_pParameterManager;

	// Copy materials
	RemoveAllMaterials();
	for (uint32 i=0; i<cSource.m_lstMaterials.GetNumOfElements(); i++) {
		Material *pMaterial = cSource.m_lstMaterials.Get(i)->GetResource();
		if (pMaterial)
			AddMaterial(*pMaterial);
	}

	// Copy effect
	SetEffect(cSource.GetEffect());

	// Done
	return *this;
}

/**
*  @brief
*    Gets a material/effect parameter
*/
Parameter *Material::GetParameter(const String &sName) const
{
	// Get the parameter
	Parameter *pParameter = m_pParameterManager->GetParameter(sName);
	if (pParameter)
		return pParameter;
	else {
		// Check materials
		for (uint32 i=0; i<m_lstMaterials.GetNumOfElements(); i++) {
			const Material *pMaterial = m_lstMaterials.Get(i)->GetResource();
			if (pMaterial) {
				pParameter = pMaterial->GetParameter(sName);
				if (pParameter)
					return pParameter;
			}
		}

		// Check effect
		return GetEffect() ? GetEffect()->GetParameterManager().GetParameter(sName) : nullptr;
	}
}

/**
*  @brief
*    Gets a texture buffer
*/
TextureBuffer *Material::GetParameterTextureBuffer(const String &sName) const
{
	// Get the parameter
	const Parameter *pParameter = GetParameter(sName);
	if (pParameter) {
		// Get the texture
		const Texture *pTexture = pParameter->GetValueTexture();
		if (pTexture)
			return pTexture->GetTextureBuffer();
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Returns the parameter manager of the material
*/
ParameterManager &Material::GetParameterManager() const
{
	return *m_pParameterManager;
}

/**
*  @brief
*    Reloads all textures used direct or indirect by the material
*/
bool Material::ReloadTextures()
{
	bool bResult = true; // No error by default

	// Are there any parameters?
	uint32 nNumOfParameters = m_pParameterManager->GetNumOfParameters();
	if (nNumOfParameters) {
		// Loop through all parameters and collect the textures we have to reload. In this
		// way we avoid reloading the same texture multiple times if it is used by multiple parameters. :)
		List<Texture*> lstTextures;
		for (uint32 i=0; i<nNumOfParameters; i++) {
			// Get the parameter
			const Parameter *pParameter = m_pParameterManager->GetParameter(i);

			// Is this a texture?
			if (pParameter->GetType() == ParameterManager::TextureBuffer) {
				// Get the texture
				Texture *pTexture = pParameter->GetValueTexture();
				if (pTexture) {
					// Is this texture already within the list?
					if (!lstTextures.IsElement(pTexture))
						lstTextures.Add(pTexture); // Nope, add it right now!
				}
			}
		}

		// We need to collect the textures of the used effect, too
		const Effect *pFX = GetEffect();
		if (pFX && pFX->GetParameterManager().GetNumOfParameters()) {
			nNumOfParameters = pFX->GetParameterManager().GetNumOfParameters();
			for (uint32 i=0; i<nNumOfParameters; i++) {
				// Get the parameter
				const Parameter *pParameter = pFX->GetParameterManager().GetParameter(i);

				// Is this a texture?
				if (pParameter->GetType() == ParameterManager::TextureBuffer) {
					// Get the texture
					Texture *pTexture = pParameter->GetValueTexture();
					if (pTexture) {
						// Is this texture already within the list?
						if (!lstTextures.IsElement(pTexture))
							lstTextures.Add(pTexture); // Nope, add it right now!
					}
				}
			}
		}

		// Reload the collected textures
		Iterator<Texture*> cIterator = lstTextures.GetIterator();
		while (cIterator.HasNext()) {
			if (!cIterator.Next()->Reload())
				bResult = false; // Error!
		}
	}

	// Done
	return bResult;
}

/**
*  @brief
*    Returns the number of materials
*/
uint32 Material::GetNumOfMaterials() const
{
	return m_lstMaterials.GetNumOfElements();
}

/**
*  @brief
*    Adds a material
*/
bool Material::AddMaterial(Material &cMaterial)
{
	MaterialHandler *pMaterialHandler = new MaterialHandler();
	pMaterialHandler->SetResource(&cMaterial);
	if (m_lstMaterials.Add(pMaterialHandler))
		return true; // Done
	else {
		// Cleanup
		delete pMaterialHandler;

		// Error!
		return false;
	}
}

/**
*  @brief
*    Returns a material
*/
Material *Material::GetMaterial(uint32 nIndex) const
{
	const MaterialHandler *pMaterialHandler = m_lstMaterials.Get(nIndex);
	return pMaterialHandler ? pMaterialHandler->GetResource() : nullptr;
}

/**
*  @brief
*    Removes a material
*/
bool Material::RemoveMaterial(uint32 nIndex)
{
	MaterialHandler *pMaterialHandler = m_lstMaterials.Get(nIndex);
	if (pMaterialHandler) {
		m_lstMaterials.RemoveAtIndex(nIndex);
		delete pMaterialHandler;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Removes all materials
*/
bool Material::RemoveAllMaterials()
{
	for (uint32 i=0; i<m_lstMaterials.GetNumOfElements(); i++)
		delete m_lstMaterials.Get(i);
	m_lstMaterials.Clear();

	// Done
	return true;
}

/**
*  @brief
*    Returns the effect of the material
*/
Effect *Material::GetEffect() const
{
	return m_pFXHandler ? static_cast<Effect*>(m_pFXHandler->GetResource()) : nullptr;
}

/**
*  @brief
*    Sets the effect of the material
*/
void Material::SetEffect(Effect *pFX)
{
	if (pFX) {
		if (!m_pFXHandler)
			m_pFXHandler = new EffectHandler();
		m_pFXHandler->SetResource(pFX);
	} else {
		if (m_pFXHandler) {
			delete m_pFXHandler;
			m_pFXHandler = nullptr;
		}
	}
}

/**
*  @brief
*    Returns whether the material should be blend or not
*/
bool Material::GetBlend() const
{
	const Effect *pFX = GetEffect();
	return (pFX && pFX->GetBlend());
}

/**
*  @brief
*    Gets the number of render passes the current technique is using
*/
uint32 Material::GetNumOfPasses() const
{
	const Effect *pFX = GetEffect();
	if (pFX) {
		const EffectTechnique *pTechnique = pFX->GetSelectedTechnique();
		if (pTechnique)
			return pTechnique->GetNumOfPasses();
	}

	// Error!
	return 0;
}

/**
*  @brief
*    Setup the given path
*/
bool Material::SetupPass(uint32 nIndex) const
{
	const Effect *pFX = GetEffect();
	if (pFX) {
		const EffectTechnique *pTechnique = pFX->GetSelectedTechnique();
		if (pTechnique)
			pTechnique->SetupPass(nIndex, m_pParameterManager);
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Material::Material(MaterialManager &cManager, const String &sName) : PLCore::Resource<Material>(sName, &cManager),
	m_pParameterManager(new ParameterManager(cManager.GetRendererContext())),
	m_pFXHandler(nullptr)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Material::Load(const String &sFilename, const String &sParams, const String &sMethod)
{
	// Unload old data
	Unload();

	// Get the filename extension for material/effect detection
	const String sExtension = Url(sFilename).GetExtension();
	if (sExtension.GetLength()) {
		// Material file given?
		if (LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "Material")) {
			// Call base implementation, m_sAbsFilename is set automatically :)
			return PLCore::Resource<Material>::Load(sFilename, sParams, sMethod);

		// Effect given?
		} else if (LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "Effect")) {
			// Load the effect
			Effect *pFX = GetMaterialManager().GetRendererContext().GetEffectManager().LoadResource(sFilename);
			if (pFX) {
				// Backup the absolute filename of the effect
				m_sUrl = pFX->GetUrl();

				// Set this effect
				SetEffect(pFX);

				// Done
				return true;
			} else {
				// Error!
				return false;
			}
		}

	// If there's no extension, maybe it's an automatic texture?
	} else {
		if (sFilename.Compare("Create ", 0, 7)) {
			// Create a 'DiffuseMap' texture parameter
			Parameter *pParameter = m_pParameterManager->CreateParameter(ParameterManager::TextureBuffer, DiffuseMap);
			if (pParameter)
				pParameter->SetValueTexture(sFilename);

			// Just backup the given 'filename'
			m_sUrl = sFilename;

			// Done
			return true;
		}
	}

	// Still there? Must be a simple texture... please note that it is NOT a good idea to check to perform a check like this:
	//  } else if (LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "Image") ||
	//             LoadableManager::GetInstance()->IsFormatLoadSupported(sExtension, "TextureAni")) {
	// -> because then your're artificially limited to only 'supported' file formats and have for example problems
	// when using dynamic texture that have no or no known 'filename extension'!

	// Create a 'DiffuseMap' texture parameter
	Parameter *pParameter = m_pParameterManager->CreateParameter(ParameterManager::TextureBuffer, DiffuseMap);
	if (pParameter && pParameter->SetValueTexture(sFilename)) {
		const Texture *pTexture = pParameter->GetValueTexture();
		if (pTexture) {
			// Backup the absolute filename of the texture
			m_sUrl = pTexture->GetUrl();
			
			// Done
			return true;
		}
	} else {
		// Error!
		PL_LOG(Error, '\'' + sFilename + "' is no known texture!");
	}

	// Cleanup on error
	m_pParameterManager->RemoveAllParameters();

	// Error!
	return false;
}

bool Material::Reload()
{
	// Call base implementation
	if (!PLCore::Resource<Material>::Reload())
		return false; // Error!

	// Reload textures
	return ReloadTextures();
}

bool Material::Unload()
{
	// Cleanup the material
	RemoveAllMaterials();
	SetEffect();
	m_pParameterManager->RemoveAllParameters();

	// Call base implementation
	return PLCore::Resource<Material>::Unload();
}

String Material::GetLoadableTypeName() const
{
	static const String sString = "Material";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
