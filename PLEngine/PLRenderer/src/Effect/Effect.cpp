/*********************************************************\
 *  File: Effect.cpp                                     *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/Matrix4x4.h>
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
using namespace PLGeneral;
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
*    Returns the effect manager this effect is in
*/
EffectManager &Effect::GetEffectManager() const
{
	// There MUST always be a manager!
	return static_cast<EffectManager&>(*m_pManager);
}

/**
*  @brief
*    Returns the parameter manager of the effect
*/
ParameterManager &Effect::GetParameterManager() const
{
	return *m_pParameterManager;
}

/**
*  @brief
*    Returns whether the effect should be blend or not
*/
bool Effect::GetBlend() const
{
	return m_bBlend;
}

/**
*  @brief
*    Activates/deactivates the effect blending
*/
void Effect::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

/**
*  @brief
*    Returns whether the effect is loaded or not
*/
bool Effect::IsLoaded() const
{
	return (m_sFilename.GetLength() != 0);
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
//[ General                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the flags
*/
uint32 Effect::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the flags
*/
void Effect::SetFlags(uint32 nFlags)
{
	m_nFlags = nFlags;
}


//[-------------------------------------------------------]
//[ Technique functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gets the number of techniques
*/
uint32 Effect::GetNumOfTechniques() const
{
	return m_lstTechnique.GetNumOfElements();
}

/**
*  @brief
*    Adds a technique
*/
EffectTechnique *Effect::AddTechnique(int nTechnique)
{
	EffectTechnique *pTechnique = new EffectTechnique(*this);
	pTechnique->SetName(String::Format("Technique_%d", m_lstTechnique.GetNumOfElements()));
	m_lstTechnique.AddAtIndex(pTechnique, nTechnique);
	return pTechnique;
}

/**
*  @brief
*    Gets a technique
*/
EffectTechnique *Effect::GetTechnique(uint32 nIndex) const
{
	return m_lstTechnique[nIndex];
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
*    Gets the current selected technique
*/
EffectTechnique *Effect::GetSelectedTechnique() const
{
	return m_lstTechnique[m_nSelectedTechnique];
}

/**
*  @brief
*    Gets the index of the current selected technique
*/
int Effect::GetSelectedTechniqueIndex() const
{
	return m_nSelectedTechnique;
}

/**
*  @brief
*    Select the current technique by index
*/
bool Effect::SelectTechnique(uint32 nIndex)
{
	if (m_lstTechnique[nIndex]) {
		m_nSelectedTechnique = nIndex;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
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
