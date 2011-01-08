/*********************************************************\
 *  File: FixedFunctionsRenderStates.h                   *
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


#ifndef __PLRENDERER_FIXEDFUNCTIONSRENDERSTATES_H__
#define __PLRENDERER_FIXEDFUNCTIONSRENDERSTATES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLGraphics/Color/Color4.h>
#include "PLRenderer/Renderer/FixedFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fixed functions render states RTTI wrapper class
*/
class FixedFunctionsRenderStates : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, FixedFunctionsRenderStates, "PLRenderer", PLCore::Object, "Fixed functions render states RTTI wrapper class")
		// Fog
		pl_attribute(FogEnable,				bool,										false,										ReadWrite,	GetSet,	"Enable/disable fog",				"")
		pl_attribute(FogColor,				PLGraphics::Color4,							PLGraphics::Color4(0.0f, 0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"RGBA fog color",					"")
		pl_attribute(FogDensity,			float,										1.0f,										ReadWrite,	GetSet,	"Fog density",						"")
		pl_attribute(FogStart,				float,										0.0f,										ReadWrite,	GetSet,	"Fog start",						"")
		pl_attribute(FogEnd,				float,										1.0f,										ReadWrite,	GetSet,	"Fog end",							"")
		pl_attribute(FogMode,				pl_enum_type(FixedFunctions::Fog::Enum),	FixedFunctions::Fog::Exp,					ReadWrite,	GetSet,	"Fog mode",							"")
		// Alpha test
		pl_attribute(AlphaTestEnable,		bool,										false,										ReadWrite,	GetSet,	"Enable/disable alpha test",		"")
		pl_attribute(AlphaTestFunction,		pl_enum_type(Compare::Enum),				Compare::GreaterEqual,						ReadWrite,	GetSet,	"Alpha test comparison function",	"")
		pl_attribute(AlphaTestReference,	float,										1.0f,										ReadWrite,	GetSet,	"Alpha test reference value",		"")
		// Misc
		pl_attribute(Lighting,				bool,										true,										ReadWrite,	GetSet,	"Enable/disable lighting",			"")
		pl_attribute(Ambient,				PLGraphics::Color4,							PLGraphics::Color4(0.0f, 0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"General RGBA ambient color",		"")
		pl_attribute(NormalizeNormals,		bool,										true,										ReadWrite,	GetSet,	"Enable/disable normalize normals",	"")
		pl_attribute(ShadeMode,				pl_enum_type(FixedFunctions::Shade::Enum),	FixedFunctions::Shade::Smooth,				ReadWrite,	GetSet,	"Shade mode",						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		// Fog
		PLRENDERER_API bool GetFogEnable() const;
		PLRENDERER_API void SetFogEnable(bool bValue);
		PLRENDERER_API PLGraphics::Color4 GetFogColor() const;
		PLRENDERER_API void SetFogColor(const PLGraphics::Color4 &cValue);
		PLRENDERER_API float GetFogDensity() const;
		PLRENDERER_API void SetFogDensity(float fValue);
		PLRENDERER_API float GetFogStart() const;
		PLRENDERER_API void SetFogStart(float fValue);
		PLRENDERER_API float GetFogEnd() const;
		PLRENDERER_API void SetFogEnd(float fValue);
		PLRENDERER_API FixedFunctions::Fog::Enum GetFogMode() const;
		PLRENDERER_API void SetFogMode(FixedFunctions::Fog::Enum nValue);
		// Alpha test
		PLRENDERER_API bool GetAlphaTestEnable() const;
		PLRENDERER_API void SetAlphaTestEnable(bool bValue);
		PLRENDERER_API Compare::Enum GetAlphaTestFunction() const;
		PLRENDERER_API void SetAlphaTestFunction(Compare::Enum nValue);
		PLRENDERER_API float GetAlphaTestReference() const;
		PLRENDERER_API void SetAlphaTestReference(float fValue);
		// Misc
		PLRENDERER_API bool GetLighting() const;
		PLRENDERER_API void SetLighting(bool bValue);
		PLRENDERER_API PLGraphics::Color4 GetAmbient() const;
		PLRENDERER_API void SetAmbient(const PLGraphics::Color4 &cValue);
		PLRENDERER_API bool GetNormalizeNormals() const;
		PLRENDERER_API void SetNormalizeNormals(bool bValue);
		PLRENDERER_API FixedFunctions::Shade::Enum GetShadeMode() const;
		PLRENDERER_API void SetShadeMode(FixedFunctions::Shade::Enum nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API FixedFunctionsRenderStates();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLRENDERER_API FixedFunctionsRenderStates(const FixedFunctionsRenderStates &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~FixedFunctionsRenderStates();

		/**
		*  @brief
		*    Retrieves a render-state value
		*
		*  @param[in] nState
		*    State variable that is being queried. This parameter can
		*    be any member of the render state enumerated type.
		*
		*  @return
		*    The value of the queried render state variable
		*
		*  @note
		*    - Some settings aren't set by the material through the default setting
		*/
		PLRENDERER_API PLGeneral::uint32 Get(FixedFunctions::RenderState::Enum nState) const;

		/**
		*  @brief
		*    Sets a single render-state parameter
		*
		*  @param[in] nState
		*    State variable that is being modified. This parameter can
		*    be any member of the render state enumerated type.
		*  @param[in] nValue
		*    New value for the render state to be set. The meaning of
		*    this parameter is dependent on the value specified for nState.
		*    For example, if nState is FogMode, the second parameter
		*    must be one member of the FogMode enumerated type. (e.g. Fog::Exp)
		*    You can also set the value to unknown - then this state is ignored.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool Set(FixedFunctions::RenderState::Enum nState, PLGeneral::uint32 nValue);

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
		PLRENDERER_API FixedFunctionsRenderStates &operator =(const FixedFunctionsRenderStates &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLGeneral::uint32 m_nRS[FixedFunctions::RenderState::Number];	/**< List of render states (see FixedFunctions::RenderState) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_FIXEDFUNCTIONSRENDERSTATES_H__
