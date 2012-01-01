/*********************************************************\
 *  File: Effect.cpp                                     *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Material/Parameter.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Effect/EffectTechnique.h"
#include "PLRenderer/Effect/EffectManager.h"
#include "PLRenderer/Effect/EffectPass.h"
#include "PLRenderer/Effect/Effect.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Effect::~Effect()
{
	// First at all: Unload the effect
	Unload();

	// Destroy the parameter manager
	delete m_pParameterManager;
}

/**
*  @brief
*    Copy operator
*/
Effect &Effect::operator =(const Effect &cSource)
{
	// Clear effect
	Unload();
	m_sFilename			 = cSource.m_sFilename;
	m_nFlags			 = cSource.GetFlags();
	m_bBlend			 = cSource.GetBlend();
	m_nSelectedTechnique = cSource.GetSelectedTechniqueIndex();
	for (uint32 i=0; i<cSource.m_lstTechnique.GetNumOfElements(); i++)
		*AddTechnique() = *cSource.m_lstTechnique[i];

	/* [TODO] Check me
	for (uint32 i=0; i<cSource.m_lstParameters.GetNumOfElements(); i++) {
		m_lstParameters.Add();
		*m_lstParameters[i] = *cSource.m_lstParameters[i];
	}
	*/

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Technique functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a technique
*/
EffectTechnique *Effect::AddTechnique(int nTechnique)
{
	EffectTechnique *pTechnique = new EffectTechnique(*this);
	pTechnique->SetName(String("Technique_") + m_lstTechnique.GetNumOfElements());
	m_lstTechnique.AddAtIndex(pTechnique, nTechnique);
	return pTechnique;
}

/**
*  @brief
*    Removes a technique
*/
bool Effect::RemoveTechnique(int nTechnique)
{
	if (nTechnique < 0)
		nTechnique = m_nSelectedTechnique;
	if (nTechnique == m_nSelectedTechnique)
		m_nSelectedTechnique = -1;
	EffectTechnique *pTechnique = m_lstTechnique[nTechnique];
	if (pTechnique) {
		delete pTechnique;
		return m_lstTechnique.RemoveAtIndex(nTechnique);
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Removes all techniques
*/
void Effect::RemoveAllTechniques()
{
	for (uint32 i=0; i<m_lstTechnique.GetNumOfElements(); i++)
		delete m_lstTechnique[i];
	m_lstTechnique.Clear();
	m_nSelectedTechnique = -1;
}

/**
*  @brief
*    Select the current technique by name
*/
bool Effect::SelectTechnique(const String &sName)
{
	// Loop through all techniques
	for (uint32 i=0; i<m_lstTechnique.GetNumOfElements(); i++) {
		if (m_lstTechnique[i]->GetName() == sName) {
			m_nSelectedTechnique = i;

			// Done
			return true;
		}
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
Effect::Effect(EffectManager &cManager, const String &sName) : PLCore::Resource<Effect>(sName, &cManager),
	m_pParameterManager(new ParameterManager(cManager.GetRendererContext())),
	m_nFlags(0),
	m_bBlend(false),
	m_nSelectedTechnique(-1)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool Effect::Reload()
{
	// Call base implementation
	if (!PLCore::Resource<Effect>::Reload())
		return false; // Error!

	// Reload textures
	return m_pParameterManager->ReloadTextures();
}

bool Effect::Unload()
{
	// Remove all parameters
	m_pParameterManager->RemoveAllParameters();

	// Remove all techniques
	RemoveAllTechniques();

	// Reset data
	m_nFlags			 = 0;
	m_bBlend			 = false;
	m_nSelectedTechnique = -1;

	// Call base implementation
	return PLCore::Resource<Effect>::Unload();
}

String Effect::GetLoadableTypeName() const
{
	static const String sString = "Effect";
	return sString;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
