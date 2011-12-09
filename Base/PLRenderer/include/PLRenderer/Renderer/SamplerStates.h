/*********************************************************\
 *  File: SamplerStates.h                                *
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


#ifndef __PLRENDERER_SAMPLERSTATES_H__
#define __PLRENDERER_SAMPLERSTATES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLRenderer/PLRenderer.h"
#include "PLRenderer/Renderer/Types.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sampler states RTTI wrapper class
*/
class SamplerStates : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, SamplerStates, "PLRenderer", PLCore::Object, "Sampler states RTTI wrapper class")
		// Attributes
			// Address modes
		pl_attribute(AddressU,		pl_enum_type(TextureAddressing::Enum),	TextureAddressing::Wrap,	ReadWrite,	GetSet,	"Texture-address mode for the u/s coordinate",											"")
		pl_attribute(AddressV,		pl_enum_type(TextureAddressing::Enum),	TextureAddressing::Wrap,	ReadWrite,	GetSet,	"Texture-address mode for the v/t coordinate",											"")
		pl_attribute(AddressW,		pl_enum_type(TextureAddressing::Enum),	TextureAddressing::Wrap,	ReadWrite,	GetSet,	"Texture-address mode for the w/r coordinate",											"")
			// Filter
		pl_attribute(MagFilter,		pl_enum_type(TextureFiltering::Enum),	TextureFiltering::Linear,	ReadWrite,	GetSet,	"Magnification filter",																	"")
		pl_attribute(MinFilter,		pl_enum_type(TextureFiltering::Enum),	TextureFiltering::Linear,	ReadWrite,	GetSet,	"Minification filter",																	"")
		pl_attribute(MipFilter,		pl_enum_type(TextureFiltering::Enum),	TextureFiltering::Linear,	ReadWrite,	GetSet,	"Mipmap filter to use during minification",												"")
			// Filter
		pl_attribute(MipmapLODBias,	float,									0.0f,						ReadWrite,	GetSet,	"Mipmap level of detail (LOD) bias",													"")
		pl_attribute(MaxMapLevel,	PLCore::uint32,							1000,						ReadWrite,	GetSet,	"LOD index of largest map to use. Values range from 0 to (n-1) where 0 is the largest",	"")
		pl_attribute(MaxAnisotropy,	PLCore::uint32,							1,							ReadWrite,	GetSet,	"Maximum anisotropy",																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		// Address modes
		inline TextureAddressing::Enum GetAddressU() const;
		inline void SetAddressU(TextureAddressing::Enum nValue);
		inline TextureAddressing::Enum GetAddressV() const;
		inline void SetAddressV(TextureAddressing::Enum nValue);
		inline TextureAddressing::Enum GetAddressW() const;
		inline void SetAddressW(TextureAddressing::Enum nValue);
		// Filter
		inline TextureFiltering::Enum GetMagFilter() const;
		inline void SetMagFilter(TextureFiltering::Enum nValue);
		inline TextureFiltering::Enum GetMinFilter() const;
		inline void SetMinFilter(TextureFiltering::Enum nValue);
		inline TextureFiltering::Enum GetMipFilter() const;
		inline void SetMipFilter(TextureFiltering::Enum nValue);
		// Filter
		inline float GetMipmapLODBias() const;
		inline void SetMipmapLODBias(float fValue);
		inline PLCore::uint32 GetMaxMapLevel() const;
		inline void SetMaxMapLevel(int nValue);
		inline PLCore::uint32 GetMaxAnisotropy() const;
		inline void SetMaxAnisotropy(PLCore::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API SamplerStates();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLRENDERER_API SamplerStates(const SamplerStates &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SamplerStates();

		/**
		*  @brief
		*    Retrieves a sampler-state value
		*
		*  @param[in] nState
		*    State variable that is being queried. This parameter can
		*    be any member of the sampler enumerated type.
		*
		*  @return
		*    The value of the queried sampler state variable
		*/
		inline PLCore::uint32 Get(Sampler::Enum nState) const;

		/**
		*  @brief
		*    Sets a single sampler-state parameter
		*
		*  @param[in] nState
		*    State variable that is being modified. This parameter
		*    can be any member of the sampler enumerated type.
		*  @param[in] nValue
		*    New value for the sampler state to be set. The meaning of
		*    this parameter is dependent on the value specified for nState.
		*    For example, if nState is Sampler::AddressU, the second parameter
		*    must be one member of the Sampler::AddressU enumerated type. (e.g. TextureAddressing::Wrap)
		*    You can also set the value to unknown - then this state is ignored.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		inline bool Set(Sampler::Enum nState, PLCore::uint32 nValue);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This class
		*/
		inline SamplerStates &operator =(const SamplerStates &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLCore::uint32 m_nSS[Sampler::Number];	/**< List of sampler states (see Sampler) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/SamplerStates.inl"


#endif // __PLRENDERER_SAMPLERSTATES_H__
