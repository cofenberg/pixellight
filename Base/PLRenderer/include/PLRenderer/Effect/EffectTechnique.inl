/*********************************************************\
 *  File: EffectTechnique.inl                            *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the owner effect
*/
inline Effect &EffectTechnique::GetEffect() const
{
	return *m_pFX;
}

/**
*  @brief
*    Returns whether the technique is valid or not
*/
inline bool EffectTechnique::IsValid() const
{
	return m_bValid;
}

/**
*  @brief
*    Sets whether the technique is valid or not
*/
inline void EffectTechnique::SetValid(bool bValid)
{
	m_bValid = bValid;
}

/**
*  @brief
*    Gets the name of the technique
*/
inline PLCore::String EffectTechnique::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the name of the technique
*/
inline void EffectTechnique::SetName(const PLCore::String &sName)
{
	m_sName = sName;
}

/**
*  @brief
*    Gets the number of render passes the technique is using
*/
inline PLCore::uint32 EffectTechnique::GetNumOfPasses() const
{
	return m_lstPass.GetNumOfElements();
}

/**
*  @brief
*    Gets a pass
*/
inline EffectPass *EffectTechnique::GetPass(PLCore::uint32 nIndex) const
{
	return m_lstPass[nIndex];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
