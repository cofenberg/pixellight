/*********************************************************\
 *  File: SamplerStates.inl                              *
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
#include <PLCore/Tools/Tools.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
// Address modes
inline TextureAddressing::Enum SamplerStates::GetAddressU() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressU]);
}

inline void SamplerStates::SetAddressU(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressU] = nValue;
}

inline TextureAddressing::Enum SamplerStates::GetAddressV() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressV]);
}

inline void SamplerStates::SetAddressV(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressV] = nValue;
}

inline TextureAddressing::Enum SamplerStates::GetAddressW() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressW]);
}

inline void SamplerStates::SetAddressW(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressW] = nValue;
}

// Filter
inline TextureFiltering::Enum SamplerStates::GetMagFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MagFilter]);
}

inline void SamplerStates::SetMagFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MagFilter] = nValue;
}

inline TextureFiltering::Enum SamplerStates::GetMinFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MinFilter]);
}

inline void SamplerStates::SetMinFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MinFilter] = nValue;
}

inline TextureFiltering::Enum SamplerStates::GetMipFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MipFilter]);
}

inline void SamplerStates::SetMipFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MipFilter] = nValue;
}

// Filter
inline float SamplerStates::GetMipmapLODBias() const
{
	return PLCore::Tools::UInt32ToFloat(m_nSS[Sampler::MipmapLODBias]);
}

inline void SamplerStates::SetMipmapLODBias(float fValue)
{
	m_nSS[Sampler::MipmapLODBias] = PLCore::Tools::FloatToUInt32(fValue);
}

inline PLCore::uint32 SamplerStates::GetMaxMapLevel() const
{
	return m_nSS[Sampler::MaxMapLevel];
}

inline void SamplerStates::SetMaxMapLevel(int nValue)
{
	m_nSS[Sampler::MaxMapLevel] = nValue;
}

inline PLCore::uint32 SamplerStates::GetMaxAnisotropy() const
{
	return m_nSS[Sampler::MaxAnisotropy];
}

inline void SamplerStates::SetMaxAnisotropy(PLCore::uint32 nValue)
{
	m_nSS[Sampler::MaxAnisotropy] = nValue;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Retrieves a sampler-state value
*/
inline PLCore::uint32 SamplerStates::Get(Sampler::Enum nState) const
{
	// Check whether the state is a valid sampler member
	return (nState < Sampler::Number) ? m_nSS[nState] : 0;
}

/**
*  @brief
*    Sets a single sampler-state parameter
*/
inline bool SamplerStates::Set(Sampler::Enum nState, PLCore::uint32 nValue)
{
	// Check whether the state is a valid sampler member
	if (nState >= Sampler::Number)
		return false; // Error!

	// Set sampler state value
	m_nSS[nState] = nValue;

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
inline SamplerStates &SamplerStates::operator =(const SamplerStates &cSource)
{
	// Copy states
	for (PLCore::uint32 i=0; i<Sampler::Number; i++)
		m_nSS[i] = cSource.m_nSS[i];

	// Return this
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
