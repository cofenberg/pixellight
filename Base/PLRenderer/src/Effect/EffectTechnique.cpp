/*********************************************************\
 *  File: EffectTechnique.cpp                            *
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
#include "PLRenderer/Effect/EffectPass.h"
#include "PLRenderer/Effect/EffectTechnique.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a pass
*/
EffectPass *EffectTechnique::AddPass(int nIndex)
{
	// Create pass
	EffectPass *pFXPass = new EffectPass(*this);
	m_lstPass.AddAtIndex(pFXPass, nIndex);

	// Return the new pass
	return pFXPass;
}

/**
*  @brief
*    Removes a pass
*/
bool EffectTechnique::RemovePass(uint32 nIndex)
{
	EffectPass *pFXPass = m_lstPass[nIndex];
	if (pFXPass) {
		delete pFXPass;

		// Done
		return m_lstPass.RemoveAtIndex(nIndex);
	} else {
		// Error!
		return false;
	}
}

/**
*  @brief
*    Removes all passes
*/
void EffectTechnique::RemoveAllPasses()
{
	for (uint32 i=0; i<m_lstPass.GetNumOfElements(); i++)
		delete m_lstPass[i];
	m_lstPass.Clear();
}

/**
*  @brief
*    Setup the given path
*/
bool EffectTechnique::SetupPass(uint32 nIndex, ParameterManager *pParameterManager) const
{
	EffectPass *pPass = m_lstPass[nIndex];
	return (pPass && pPass->Bind(pParameterManager));
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
EffectTechnique::EffectTechnique(Effect &cFX) :
	m_pFX(&cFX),
	m_bValid(true)
{
}

/**
*  @brief
*    Destructor
*/
EffectTechnique::~EffectTechnique()
{
	RemoveAllPasses();
}

/**
*  @brief
*    Copy operator
*/
EffectTechnique &EffectTechnique::operator =(const EffectTechnique &cSource)
{
	// Copy attributes
	m_bValid = cSource.m_bValid;
	m_sName  = cSource.m_sName;

	// Copy passes
	uint32 nNumOfPasses = cSource.m_lstPass.GetNumOfElements();
	for (uint32 nPass=0; nPass<nNumOfPasses; nPass++)
		*AddPass() = *cSource.m_lstPass[nPass];

	// Return this
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
