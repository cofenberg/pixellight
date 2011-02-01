/*********************************************************\
 *  File: RendererContext.cpp                            *
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
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/Tools/Profiling.h>
#include "PLRenderer/Renderer/Renderer.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Material/MaterialManager.h"
#include "PLRenderer/RendererContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a renderer context instance
*/
RendererContext *RendererContext::CreateInstance(const String &sBackend, Renderer::EMode nMode, uint32 nZBufferBits, uint32 nStencilBits, uint32 nMultisampleAntialiasingSamples, const String &sDefaultShaderLanguage)
{
	// Create renderer instance
	const Class *pClass = ClassManager::GetInstance()->GetClass(sBackend);
	if (pClass && pClass->IsDerivedFrom("PLRenderer::Renderer")) {
		const Object *pObject = pClass->Create(Params<Object*, pl_enum_type(Renderer::EMode), uint32, uint32, uint32, String>(nMode, nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage));
		if (pObject)
			 return &static_cast<const Renderer*>(pObject)->GetRendererContext();
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
RendererContext::~RendererContext()
{
	// Destroy the renderer instance and all resource managers
	if (m_pMaterialManager)
		delete m_pMaterialManager;
	if (m_pEffectManager)
		delete m_pEffectManager;
	if (m_pTextureManager)
		delete m_pTextureManager;
	if (m_pRenderer)
		delete m_pRenderer;
}

/**
*  @brief
*    Returns the used renderer
*/
Renderer &RendererContext::GetRenderer() const
{
	return *m_pRenderer;
}

/**
*  @brief
*    Returns the texture manager of this renderer context
*/
TextureManager &RendererContext::GetTextureManager()
{
	if (!m_pTextureManager)
		m_pTextureManager = new TextureManager(*this);
	return *m_pTextureManager;
}

/**
*  @brief
*    Returns the effect manager of this renderer context
*/
EffectManager &RendererContext::GetEffectManager()
{
	if (!m_pEffectManager)
		m_pEffectManager = new EffectManager(*this);
	return *m_pEffectManager;
}

/**
*  @brief
*    Returns the material manager of this renderer context
*/
MaterialManager &RendererContext::GetMaterialManager()
{
	if (!m_pMaterialManager)
		m_pMaterialManager = new MaterialManager(*this);
	return *m_pMaterialManager;
}

/**
*  @brief
*    Updates the render context
*/
void RendererContext::Update()
{
	// Start stopwatch
	Stopwatch cStopwatch;
	cStopwatch.Start();

	// Emit the update event
	EventUpdate.Emit();

	// Update renderer
	if (m_pRenderer)
		m_pRenderer->Update();

	// Stop stopwatch
	cStopwatch.Stop();

	// Update profiling information
	Profiling *pProfiling = Profiling::GetInstance();
	if (pProfiling->IsActive()) {
		if (m_pTextureManager)
			pProfiling->Set("Renderer context", "Number of textures",  String::Format("%d", m_pTextureManager->GetNumOfElements()));
		if (m_pEffectManager)
			pProfiling->Set("Renderer context", "Number of effects",   String::Format("%d", m_pEffectManager->GetNumOfElements()));
		if (m_pMaterialManager)
			pProfiling->Set("Renderer context", "Number of materials", String::Format("%d", m_pMaterialManager->GetNumOfElements()));
		pProfiling->Set("Renderer context", "Update time", String::Format("%.3g ms", cStopwatch.GetMilliseconds()));
	}
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RendererContext::RendererContext(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pTextureManager(nullptr),
	m_pEffectManager(nullptr),
	m_pMaterialManager(nullptr)
{
}

/**
*  @brief
*    Copy operator
*/
RendererContext &RendererContext::operator =(const RendererContext &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
