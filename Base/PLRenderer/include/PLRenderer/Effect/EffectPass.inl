/*********************************************************\
 *  File: EffectPass.inl                                 *
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
*    Returns the owner effect technique
*/
inline EffectTechnique &EffectPass::GetTechnique() const
{
	return *m_pTechnique;
}

/**
*  @brief
*    Returns the pass name
*/
inline PLCore::String EffectPass::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Sets the pass name
*/
inline void EffectPass::SetName(const PLCore::String &sName)
{
	m_sName = sName;
}


//[-------------------------------------------------------]
//[ States                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the general color
*/
inline const PLGraphics::Color4 &EffectPass::GetColor() const
{
	return m_cColor;
}

/**
*  @brief
*    Sets the general color
*/
inline void EffectPass::SetColor(const PLGraphics::Color4 &cColor)
{
	m_cColor = cColor;
}

/**
*  @brief
*    Returns the render states
*/
inline RenderStates &EffectPass::GetRenderStates()
{
	return m_cRenderStates;
}

inline const RenderStates &EffectPass::GetRenderStates() const
{
	return m_cRenderStates;
}

/**
*  @brief
*    Returns the fixed functions render states
*/
inline FixedFunctionsRenderStates &EffectPass::GetFixedFunctionsRenderStates()
{
	return m_cFixedFunctionsRenderStates;
}

inline const FixedFunctionsRenderStates &EffectPass::GetFixedFunctionsRenderStates() const
{
	return m_cFixedFunctionsRenderStates;
}

/**
*  @brief
*    Retrieves a material-state value
*/
inline PLCore::uint32 EffectPass::GetMaterialState(FixedFunctions::MaterialState::Enum nState) const
{
	// Check if the state is a value renderer material state member
	return (nState < FixedFunctions::MaterialState::Number) ? m_nMaterialState[nState] : 0;
}

/**
*  @brief
*    Sets a single material-state parameter
*/
inline bool EffectPass::SetMaterialState(FixedFunctions::MaterialState::Enum nState, PLCore::uint32 nValue)
{
	// Check if the state is a value renderer material state member
	if (nState >= FixedFunctions::MaterialState::Number)
		return false; // Error!

	// Set material state value
	m_nMaterialState[nState] = nValue;

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Layers                                                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of texture layers
*/
inline PLCore::uint32 EffectPass::GetNumOfLayers() const
{
	return m_lstLayers.GetNumOfElements();
}

/**
*  @brief
*    Returns a layer
*/
EffectPassLayer *EffectPass::GetLayer(PLCore::uint32 nIndex) const
{
	return m_lstLayers[nIndex];
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
