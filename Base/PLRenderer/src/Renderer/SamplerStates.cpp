/*********************************************************\
 *  File: SamplerStates.cpp                              *
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
#include "PLRenderer/Renderer/SamplerStates.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SamplerStates)


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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
