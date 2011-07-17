/*********************************************************\
 *  File: SamplerStates.cpp                              *
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
#include <PLGeneral/Tools/Tools.h>
#include "PLRenderer/Renderer/SamplerStates.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SamplerStates)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
// Address modes
TextureAddressing::Enum SamplerStates::GetAddressU() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressU]);
}

void SamplerStates::SetAddressU(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressU] = nValue;
}

TextureAddressing::Enum SamplerStates::GetAddressV() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressV]);
}

void SamplerStates::SetAddressV(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressV] = nValue;
}

TextureAddressing::Enum SamplerStates::GetAddressW() const
{
	return static_cast<TextureAddressing::Enum>(m_nSS[Sampler::AddressW]);
}

void SamplerStates::SetAddressW(TextureAddressing::Enum nValue)
{
	m_nSS[Sampler::AddressW] = nValue;
}

// Filter
TextureFiltering::Enum SamplerStates::GetMagFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MagFilter]);
}

void SamplerStates::SetMagFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MagFilter] = nValue;
}

TextureFiltering::Enum SamplerStates::GetMinFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MinFilter]);
}

void SamplerStates::SetMinFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MinFilter] = nValue;
}

TextureFiltering::Enum SamplerStates::GetMipFilter() const
{
	return static_cast<TextureFiltering::Enum>(m_nSS[Sampler::MipFilter]);
}

void SamplerStates::SetMipFilter(TextureFiltering::Enum nValue)
{
	m_nSS[Sampler::MipFilter] = nValue;
}

// Filter
float SamplerStates::GetMipmapLODBias() const
{
	return Tools::UInt32ToFloat(m_nSS[Sampler::MipmapLODBias]);
}

void SamplerStates::SetMipmapLODBias(float fValue)
{
	m_nSS[Sampler::MipmapLODBias] = Tools::FloatToUInt32(fValue);
}

uint32 SamplerStates::GetMaxMapLevel() const
{
	return m_nSS[Sampler::MaxMapLevel];
}

void SamplerStates::SetMaxMapLevel(int nValue)
{
	m_nSS[Sampler::MaxMapLevel] = nValue;
}

uint32 SamplerStates::GetMaxAnisotropy() const
{
	return m_nSS[Sampler::MaxAnisotropy];
}

void SamplerStates::SetMaxAnisotropy(uint32 nValue)
{
	m_nSS[Sampler::MaxAnisotropy] = nValue;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SamplerStates::SamplerStates() :
	AddressU(this),
	AddressV(this),
	AddressW(this),
	MagFilter(this),
	MinFilter(this),
	MipFilter(this),
	MipmapLODBias(this),
	MaxMapLevel(this),
	MaxAnisotropy(this)
{
	// Set default sampler states
	// Address modes
	m_nSS[Sampler::AddressU] = TextureAddressing::Wrap;
	m_nSS[Sampler::AddressV] = TextureAddressing::Wrap;
	m_nSS[Sampler::AddressW] = TextureAddressing::Wrap;
	// Filter
	m_nSS[Sampler::MagFilter] = TextureFiltering::Linear;
	m_nSS[Sampler::MinFilter] = TextureFiltering::Linear;
	m_nSS[Sampler::MipFilter] = TextureFiltering::Linear;
	// Misc
	m_nSS[Sampler::MipmapLODBias] = 0;
	m_nSS[Sampler::MaxMapLevel]   = 1000;
	m_nSS[Sampler::MaxAnisotropy] = 1;
}

/**
*  @brief
*    Copy constructor
*/
SamplerStates::SamplerStates(const SamplerStates &cSource) :
	AddressU(this),
	AddressV(this),
	AddressW(this),
	MagFilter(this),
	MinFilter(this),
	MipFilter(this),
	MipmapLODBias(this),
	MaxMapLevel(this),
	MaxAnisotropy(this)
{
	// Copy states
	for (uint32 i=0; i<Sampler::Number; i++)
		m_nSS[i] = cSource.m_nSS[i];
}

/**
*  @brief
*    Destructor
*/
SamplerStates::~SamplerStates()
{
}

/**
*  @brief
*    Retrieves a sampler-state value
*/
uint32 SamplerStates::Get(Sampler::Enum nState) const
{
	// Check whether the state is a valid sampler member
	return (nState < Sampler::Number) ? m_nSS[nState] : 0;
}

/**
*  @brief
*    Sets a single sampler-state parameter
*/
bool SamplerStates::Set(Sampler::Enum nState, uint32 nValue)
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
SamplerStates &SamplerStates::operator =(const SamplerStates &cSource)
{
	// Copy states
	for (uint32 i=0; i<Sampler::Number; i++)
		m_nSS[i] = cSource.m_nSS[i];

	// Return this
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
