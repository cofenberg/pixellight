/*********************************************************\
 *  File: EffectPassLayer.inl                            *
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
*    Returns the layer owner
*/
inline EffectPass &EffectPassLayer::GetPass() const
{
	return *m_pFXPass;
}

/**
*  @brief
*    Returns the name of the used texture parameter
*/
inline PLCore::String EffectPassLayer::GetTexture() const
{
	return m_sTexture;
}

/**
*  @brief
*    Sets the name of the used texture parameter
*/
inline void EffectPassLayer::SetTexture(const PLCore::String &sTexture)
{
	m_sTexture = sTexture;
}

/**
*  @brief
*    Returns the sampler states
*/
inline SamplerStates &EffectPassLayer::GetSamplerStates()
{
	return m_cSamplerStates;
}

inline const SamplerStates &EffectPassLayer::GetSamplerStates() const
{
	return m_cSamplerStates;
}

/**
*  @brief
*    Returns the fixed functions texture stage states
*/
inline FixedFunctionsTextureStageStates &EffectPassLayer::GetFixedFunctionsTextureStageStates()
{
	return m_cFixedFunctionsTextureStageStates;
}

inline const FixedFunctionsTextureStageStates &EffectPassLayer::GetFixedFunctionsTextureStageStates() const
{
	return m_cFixedFunctionsTextureStageStates;
}

/**
*  @brief
*    Copy operator
*/
inline EffectPassLayer &EffectPassLayer::operator =(const EffectPassLayer &cSource)
{
	// Texture
	m_sTexture = cSource.m_sTexture;

	// Copy states
	m_cSamplerStates				    = cSource.m_cSamplerStates;
	m_cFixedFunctionsTextureStageStates = cSource.m_cFixedFunctionsTextureStageStates;

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline EffectPassLayer::EffectPassLayer(EffectPass &cFXPass) :
	m_pFXPass(&cFXPass)
{
}

/**
*  @brief
*    Destructor
*/
inline EffectPassLayer::~EffectPassLayer()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
