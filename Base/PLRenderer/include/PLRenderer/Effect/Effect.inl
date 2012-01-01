/*********************************************************\
 *  File: Effect.inl                                     *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the effect manager this effect is in
*/
inline EffectManager &Effect::GetEffectManager() const
{
	// There MUST always be a manager!
	return reinterpret_cast<EffectManager&>(*m_pManager);
}

/**
*  @brief
*    Returns the parameter manager of the effect
*/
inline ParameterManager &Effect::GetParameterManager() const
{
	return *m_pParameterManager;
}

/**
*  @brief
*    Returns whether the effect should be blend or not
*/
inline bool Effect::GetBlend() const
{
	return m_bBlend;
}

/**
*  @brief
*    Activates/deactivates the effect blending
*/
inline void Effect::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

/**
*  @brief
*    Returns whether the effect is loaded or not
*/
inline bool Effect::IsLoaded() const
{
	return (m_sFilename.GetLength() != 0);
}


//[-------------------------------------------------------]
//[ General                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the flags
*/
inline PLCore::uint32 Effect::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the flags
*/
inline void Effect::SetFlags(PLCore::uint32 nFlags)
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
inline PLCore::uint32 Effect::GetNumOfTechniques() const
{
	return m_lstTechnique.GetNumOfElements();
}

/**
*  @brief
*    Gets a technique
*/
inline EffectTechnique *Effect::GetTechnique(PLCore::uint32 nIndex) const
{
	return m_lstTechnique[nIndex];
}

/**
*  @brief
*    Gets the current selected technique
*/
inline EffectTechnique *Effect::GetSelectedTechnique() const
{
	return m_lstTechnique[m_nSelectedTechnique];
}

/**
*  @brief
*    Gets the index of the current selected technique
*/
inline int Effect::GetSelectedTechniqueIndex() const
{
	return m_nSelectedTechnique;
}

/**
*  @brief
*    Select the current technique by index
*/
inline bool Effect::SelectTechnique(PLCore::uint32 nIndex)
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
