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
		pl_attribute(MaxMapLevel,	PLGeneral::uint32,						1000,						ReadWrite,	GetSet,	"LOD index of largest map to use. Values range from 0 to (n-1) where 0 is the largest",	"")
		pl_attribute(MaxAnisotropy,	PLGeneral::uint32,						1,							ReadWrite,	GetSet,	"Maximum anisotropy",																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		// Address modes
		PLRENDERER_API TextureAddressing::Enum GetAddressU() const;
		PLRENDERER_API void SetAddressU(TextureAddressing::Enum nValue);
		PLRENDERER_API TextureAddressing::Enum GetAddressV() const;
		PLRENDERER_API void SetAddressV(TextureAddressing::Enum nValue);
		PLRENDERER_API TextureAddressing::Enum GetAddressW() const;
		PLRENDERER_API void SetAddressW(TextureAddressing::Enum nValue);
		// Filter
		PLRENDERER_API TextureFiltering::Enum GetMagFilter() const;
		PLRENDERER_API void SetMagFilter(TextureFiltering::Enum nValue);
		PLRENDERER_API TextureFiltering::Enum GetMinFilter() const;
		PLRENDERER_API void SetMinFilter(TextureFiltering::Enum nValue);
		PLRENDERER_API TextureFiltering::Enum GetMipFilter() const;
		PLRENDERER_API void SetMipFilter(TextureFiltering::Enum nValue);
		// Filter
		PLRENDERER_API float GetMipmapLODBias() const;
		PLRENDERER_API void SetMipmapLODBias(float fValue);
		PLRENDERER_API PLGeneral::uint32 GetMaxMapLevel() const;
		PLRENDERER_API void SetMaxMapLevel(int nValue);
		PLRENDERER_API PLGeneral::uint32 GetMaxAnisotropy() const;
		PLRENDERER_API void SetMaxAnisotropy(PLGeneral::uint32 nValue);


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
		PLRENDERER_API PLGeneral::uint32 Get(Sampler::Enum nState) const;

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
		PLRENDERER_API bool Set(Sampler::Enum nState, PLGeneral::uint32 nValue);

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
		PLRENDERER_API SamplerStates &operator =(const SamplerStates &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLGeneral::uint32 m_nSS[Sampler::Number];	/**< List of sampler states (see Sampler) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SAMPLERSTATES_H__
