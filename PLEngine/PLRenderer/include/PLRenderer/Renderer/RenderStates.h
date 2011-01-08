/*********************************************************\
 *  File: RenderStates.h                                 *
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


#ifndef __PLRENDERER_RENDERSTATES_H__
#define __PLRENDERER_RENDERSTATES_H__
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
*    Render states RTTI wrapper class
*/
class RenderStates : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, RenderStates, "PLRenderer", PLCore::Object, "Render states RTTI wrapper class")
		// Modes
		pl_attribute(FillMode,				pl_enum_type(Fill::Enum),				Fill::Solid,				ReadWrite,	GetSet,	"Fill mode",																			"")
		pl_attribute(CullMode,				pl_enum_type(Cull::Enum),				Cull::CCW,					ReadWrite,	GetSet,	"Cull mode",																			"")
		// Z buffer
		pl_attribute(ZEnable,				bool,									true,						ReadWrite,	GetSet,	"Enable/disable z buffer test",															"")
		pl_attribute(ZWriteEnable,			bool,									true,						ReadWrite,	GetSet,	"Enable/disable z buffer writing",														"")
		pl_attribute(ZFunc,					pl_enum_type(Compare::Enum),			Compare::LessEqual,			ReadWrite,	GetSet,	"Z buffer function",																	"")
		pl_attribute(ZBias,					float,									0.0f,						ReadWrite,	GetSet,	"Z bias/polygon offset factor",															"")
		pl_attribute(SlopeScaleDepthBias,	float,									0.0f,						ReadWrite,	GetSet,	"Slope scale bias/polygon offset factor",												"")
		pl_attribute(DepthBias,				float,									0.0f,						ReadWrite,	GetSet,	"Depth bias/polygon offset units",														"")
		// Blend
		pl_attribute(BlendEnable,			bool,									false,						ReadWrite,	GetSet,	"Enable/disable blending",																"")
		pl_attribute(SrcBlendFunc,			pl_enum_type(BlendFunc::Enum),			BlendFunc::SrcAlpha,		ReadWrite,	GetSet,	"Source blend function",																"")
		pl_attribute(DstBlendFunc,			pl_enum_type(BlendFunc::Enum),			BlendFunc::InvSrcAlpha,		ReadWrite,	GetSet,	"Destination blend function",															"")
		// Stencil
		pl_attribute(StencilEnable,			bool,									false,						ReadWrite,	GetSet,	"Enable/disable stencil test",															"")
		pl_attribute(StencilFunc,			pl_enum_type(Compare::Enum),			Compare::Always,			ReadWrite,	GetSet,	"Stencil test passes if ((ref & mask) stencilfn (stencil & mask)) is true",				"")
		pl_attribute(StencilRef,			PLGeneral::uint32,						0,							ReadWrite,	GetSet,	"Reference value used in stencil test",													"")
		pl_attribute(StencilMask,			PLGeneral::uint32,						0xFFFFFFFF,					ReadWrite,	GetSet,	"Mask value used in stencil test",														"")
		pl_attribute(StencilFail,			pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if stencil test fails",											"")
		pl_attribute(StencilZFail,			pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if stencil test passes and Z test fails",							"")
		pl_attribute(StencilPass,			pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if both stencil and Z tests pass",								"")
		pl_attribute(TwoSidedStencilMode,	bool,									false,						ReadWrite,	GetSet,	"Enable/disable 2 sided stenciling",													"")
		pl_attribute(CCWStencilFunc,		pl_enum_type(Compare::Enum),			Compare::Always,			ReadWrite,	GetSet,	"Stencil test passes if ((ref & mask) stencilfn (stencil & mask)) is true",				"")
		pl_attribute(CCWStencilFail,		pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if ccw stencil test fails",										"")
		pl_attribute(CCWStencilZFail,		pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if ccw stencil test passes and Z test fails",						"")
		pl_attribute(CCWStencilPass,		pl_enum_type(StencilOp::Enum),			StencilOp::Keep,			ReadWrite,	GetSet,	"Operation to perform if both ccw stencil and Z tests pass",							"")
		// Point and line
		pl_attribute(PointSize,				float,									1.0f,						ReadWrite,	GetSet,	"Point size when it is not specified for each vertex",									"")
		pl_attribute(PointScaleEnable,		bool,									false,						ReadWrite,	GetSet,	"Controls computation of size for point primitives",									"")
		pl_attribute(PointSizeMin,			float,									1.0f,						ReadWrite,	GetSet,	"Minimum size of point primitives",														"")
		pl_attribute(PointSizeMax,			float,									64.0f,						ReadWrite,	GetSet,	"Maximum size of point primitives, must be greater than or equal to m_fPointSizeMin",	"")
		pl_attribute(PointScaleA,			float,									1.0f,						ReadWrite,	GetSet,	"Controls for distance-based size attenuation for point primitives",					"")
		pl_attribute(PointScaleB,			float,									0.0f,						ReadWrite,	GetSet,	"Controls for distance-based size attenuation for point primitives",					"")
		pl_attribute(PointScaleC,			float,									0.0f,						ReadWrite,	GetSet,	"Controls for distance-based size attenuation for point primitives",					"")
		pl_attribute(LineWidth,				float,									1.0f,						ReadWrite,	GetSet,	"Line width",																			"")
		// Tessellation
		pl_attribute(TessellationFactor,	PLGeneral::uint32,						1,							ReadWrite,	GetSet,	"Tessellation factor",																	"Min=1")
// [TODO] Linux GCC: "error: changes meaning of ‘TessellationMode’ from ‘class PLRenderer::TessellationMode"
//		pl_attribute(TessellationMode,		pl_enum_type(TessellationMode::Enum),	TessellationMode::Discrete,	ReadWrite,	GetSet,	"Tessellation mode",																	"")
		// Misc
		pl_attribute(PointSpriteEnable,		bool,									false,						ReadWrite,	GetSet,	"When true, use point texture mapping",													"")
		pl_attribute(DitherEnable,			bool,									false,						ReadWrite,	GetSet,	"Enable/disable dithering",																"")
		pl_attribute(ScissorTestEnable,		bool,									false,						ReadWrite,	GetSet,	"Enable/disable the scissor test",														"")
		pl_attribute(MultisampleEnable,		bool,									true,						ReadWrite,	GetSet,	"When true, use multisample",															"")
		pl_attribute(InvCullMode,			bool,									false,						ReadWrite,	GetSet,	"Controls computation of size for point primitives",									"")
		pl_attribute(FixedFillMode,			pl_enum_type(Fill::Enum),				Fill::Unknown,				ReadWrite,	GetSet,	"General fill mode which is normally set once",											"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		// Modes
		PLRENDERER_API Fill::Enum GetFillMode() const;
		PLRENDERER_API void SetFillMode(Fill::Enum nValue);
		PLRENDERER_API Cull::Enum GetCullMode() const;
		PLRENDERER_API void SetCullMode(Cull::Enum nValue);
		// Z buffer
		PLRENDERER_API bool GetZEnable() const;
		PLRENDERER_API void SetZEnable(bool bValue);
		PLRENDERER_API bool GetZWriteEnable() const;
		PLRENDERER_API void SetZWriteEnable(bool bValue);
		PLRENDERER_API Compare::Enum GetZFunc() const;
		PLRENDERER_API void SetZFunc(Compare::Enum nValue);
		PLRENDERER_API float GetZBias() const;
		PLRENDERER_API void SetZBias(float fValue);
		PLRENDERER_API float GetSlopeScaleDepthBias() const;
		PLRENDERER_API void SetSlopeScaleDepthBias(float fValue);
		PLRENDERER_API float GetDepthBias() const;
		PLRENDERER_API void SetDepthBias(float fValue);
		// Blend
		PLRENDERER_API bool GetBlendEnable() const;
		PLRENDERER_API void SetBlendEnable(bool bValue);
		PLRENDERER_API BlendFunc::Enum GetSrcBlendFunc() const;
		PLRENDERER_API void SetSrcBlendFunc(BlendFunc::Enum nValue);
		PLRENDERER_API BlendFunc::Enum GetDstBlendFunc() const;
		PLRENDERER_API void SetDstBlendFunc(BlendFunc::Enum nValue);
		// Stencil
		PLRENDERER_API bool GetStencilEnable() const;
		PLRENDERER_API void SetStencilEnable(bool bValue);
		PLRENDERER_API Compare::Enum GetStencilFunc() const;
		PLRENDERER_API void SetStencilFunc(Compare::Enum nValue);
		PLRENDERER_API PLGeneral::uint32 GetStencilRef() const;
		PLRENDERER_API void SetStencilRef(PLGeneral::uint32 nValue);
		PLRENDERER_API PLGeneral::uint32 GetStencilMask() const;
		PLRENDERER_API void SetStencilMask(PLGeneral::uint32 nValue);
		PLRENDERER_API StencilOp::Enum GetStencilFail() const;
		PLRENDERER_API void SetStencilFail(StencilOp::Enum nValue);
		PLRENDERER_API StencilOp::Enum GetStencilZFail() const;
		PLRENDERER_API void SetStencilZFail(StencilOp::Enum nValue);
		PLRENDERER_API StencilOp::Enum GetStencilPass() const;
		PLRENDERER_API void SetStencilPass(StencilOp::Enum nValue);
		PLRENDERER_API bool GetTwoSidedStencilMode() const;
		PLRENDERER_API void SetTwoSidedStencilMode(bool bValue);
		PLRENDERER_API Compare::Enum GetCCWStencilFunc() const;
		PLRENDERER_API void SetCCWStencilFunc(Compare::Enum nValue);
		PLRENDERER_API StencilOp::Enum GetCCWStencilFail() const;
		PLRENDERER_API void SetCCWStencilFail(StencilOp::Enum nValue);
		PLRENDERER_API StencilOp::Enum GetCCWStencilZFail() const;
		PLRENDERER_API void SetCCWStencilZFail(StencilOp::Enum nValue);
		PLRENDERER_API StencilOp::Enum GetCCWStencilPass() const;
		PLRENDERER_API void SetCCWStencilPass(StencilOp::Enum nValue);
		// Point and line
		PLRENDERER_API float GetPointSize() const;
		PLRENDERER_API void SetPointSize(float fValue);
		PLRENDERER_API bool GetPointScaleEnable() const;
		PLRENDERER_API void SetPointScaleEnable(bool bValue);
		PLRENDERER_API float GetPointSizeMin() const;
		PLRENDERER_API void SetPointSizeMin(float fValue);
		PLRENDERER_API float GetPointSizeMax() const;
		PLRENDERER_API void SetPointSizeMax(float fValue);
		PLRENDERER_API float GetPointScaleA() const;
		PLRENDERER_API void SetPointScaleA(float fValue);
		PLRENDERER_API float GetPointScaleB() const;
		PLRENDERER_API void SetPointScaleB(float fValue);
		PLRENDERER_API float GetPointScaleC() const;
		PLRENDERER_API void SetPointScaleC(float fValue);
		PLRENDERER_API float GetLineWidth() const;
		PLRENDERER_API void SetLineWidth(float fValue);
		// Tessellation
		PLRENDERER_API PLGeneral::uint32 GetTessellationFactor() const;
		PLRENDERER_API void SetTessellationFactor(PLGeneral::uint32 nValue);
		PLRENDERER_API TessellationMode::Enum GetTessellationMode() const;
		PLRENDERER_API void SetTessellationMode(TessellationMode::Enum nValue);
		// Misc
		PLRENDERER_API bool GetPointSpriteEnable() const;
		PLRENDERER_API void SetPointSpriteEnable(bool bValue);
		PLRENDERER_API bool GetDitherEnable() const;
		PLRENDERER_API void SetDitherEnable(bool bValue);
		PLRENDERER_API bool GetScissorTestEnable() const;
		PLRENDERER_API void SetScissorTestEnable(bool bValue);
		PLRENDERER_API bool GetMultisampleEnable() const;
		PLRENDERER_API void SetMultisampleEnable(bool bValue);
		PLRENDERER_API bool GetInvCullMode() const;
		PLRENDERER_API void SetInvCullMode(bool bValue);
		PLRENDERER_API Fill::Enum GetFixedFillMode() const;
		PLRENDERER_API void SetFixedFillMode(Fill::Enum nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API RenderStates();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLRENDERER_API RenderStates(const RenderStates &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~RenderStates();

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
		*    - Some settings like stencil, fog and scissor test aren't set
		*      by the material through the default setting
		*/
		PLRENDERER_API PLGeneral::uint32 Get(RenderState::Enum nState) const;

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
		*    For example, if nState is Shade, the second parameter
		*    must be one member of the Shade enumerated type. (e.g. Shade::Flat)
		*    You can also set the value to unknown - then this state is ignored.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool Set(RenderState::Enum nState, PLGeneral::uint32 nValue);

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
		PLRENDERER_API RenderStates &operator =(const RenderStates &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Exported variables
		PLGeneral::uint32 m_nRS[RenderState::Number];	/**< List of render states (see RenderState) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_RENDERSTATES_H__
