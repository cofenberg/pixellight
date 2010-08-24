/*********************************************************\
 *  File: Types.h                                        *
 *      Renderer types
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_TYPES_H__
#define __PLRENDERER_TYPES_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Rtti.h>
#include <PLMath/Vector2i.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Clear flags
*/
class Clear {
	public:
	enum Enum {
		Color   = 1<<0,	/**< Clear color buffer */
		ZBuffer = 1<<1,	/**< Clear z buffer */
		Stencil = 1<<2	/**< Clear stencil buffer */
	};
};

/**
*  @brief
*    Fill modes
*/
class Fill {
	public:
	enum Enum {
		Point   = 0,	/**< Point fill mode */
		Line    = 1,	/**< Line fill mode */
		Solid   = 2,	/**< Solid fill mode */
		// End
		Number  = 3,	/**< Number of fill modes */
		Unknown = 4		/**< Unknown fill mode */
	};
	pl_enum(Enum)
		pl_enum_value(Point,	"Point fill mode")
		pl_enum_value(Line,		"Line fill mode")
		pl_enum_value(Solid,	"Solid fill mode")
		pl_enum_value(Unknown,	"Unknown fill mode")
	pl_enum_end
};

/**
*  @brief
*    Cull modes
*/
class Cull {
	public:
	enum Enum {
		None    = 0,	/**< No culling */
		CW      = 1,	/**< Selects clockwise polygons as front-facing */
		CCW     = 2,	/**< Selects counterclockwise polygons as front-facing */
		// End
		Number  = 3,	/**< Number of cull modes */
		Unknown = 4		/**< Unknown cull mode */
	};
	pl_enum(Enum)
		pl_enum_value(None,	"No culling")
		pl_enum_value(CW,	"Selects clockwise polygons as front-facing")
		pl_enum_value(CCW,	"Selects counterclockwise polygons as front-facing")
	pl_enum_end
};

/**
*  @brief
*    Blend modes
*/
class BlendFunc {
	public:
	enum Enum {
		// Source & Destination
		Zero        = 0,	/**< Zero */
		One         = 1,	/**< One */
		// Source
		SrcColor    = 2,	/**< Source color */
		InvSrcColor = 3,	/**< Inverted src color */
		SrcAlpha    = 4,	/**< Source alpha */
		InvSrcAlpha = 5,	/**< Inverted source alpha */
		SrcAlphaSat = 6,	/**< Source alpha saturate */
		// Destination
		DstColor    = 7,	/**< Destination color */
		InvDstColor = 8,	/**< Inverted destination color */
		DstAlpha    = 9,	/**< Destination alhpa */
		InvDstAlpha = 10,	/**< Inverted destination alpha */
		// End
		Number      = 11,	/**< Number of blend functions */
		Unknown     = 12	/**< Unknown blend function */
	};
	pl_enum(Enum)
		// Source & Destination
		pl_enum_value(Zero,			"Zero")
		pl_enum_value(One,			"One")
		// Source
		pl_enum_value(SrcColor,		"Source color")
		pl_enum_value(InvSrcColor,	"Inverted src color")
		pl_enum_value(SrcAlpha,		"Source alpha")
		pl_enum_value(InvSrcAlpha,	"Inverted source alpha")
		pl_enum_value(SrcAlphaSat,	"Source alpha saturate")
		// Destination
		pl_enum_value(DstColor,		"Destination color")
		pl_enum_value(InvDstColor,	"Inverted destination color")
		pl_enum_value(DstAlpha,		"Destination alhpa")
		pl_enum_value(InvDstAlpha,	"Inverted destination alpha")
	pl_enum_end
};

/**
*  @brief
*    Comparison modes
*/
class Compare {
	public:
	enum Enum {
		Never        = 0,	/**< Never passes */
		Less         = 1,	/**< Passes if the incoming value is less than the stored value */
		Equal        = 2,	/**< Passes if the incoming value is equal to the stored value */
		LessEqual    = 3,	/**< Passes if the incoming value is less than or equal to the stored value */
		Greater      = 4,	/**< Passes if the incoming value is greater than the stored value */
		NotEqual     = 5,	/**< Passes if the incoming value is not equal to the stored value */
		GreaterEqual = 6,	/**< Passes if the incoming value is greater than or equal to the stored value */
		Always       = 7,	/**< Always passes */
		// End
		Number       = 8,	/**< Number of comparison functions */
		Unknown      = 9	/**< Unknown comparison function */
	};
	pl_enum(Enum)
		pl_enum_value(Never,		"Never passes")
		pl_enum_value(Less,			"Passes if the incoming value is less than the stored value")
		pl_enum_value(Equal,		"Passes if the incoming value is equal to the stored value")
		pl_enum_value(LessEqual,	"Passes if the incoming value is less than or equal to the stored value")
		pl_enum_value(Greater,		"Passes if the incoming value is greater than the stored value")
		pl_enum_value(NotEqual,		"Passes if the incoming value is not equal to the stored value")
		pl_enum_value(GreaterEqual,	"Passes if the incoming value is greater than or equal to the stored value")
		pl_enum_value(Always,		"Always passes")
	pl_enum_end
};

/**
*  @brief
*    Stencil operations
*/
class StencilOp {
	public:
	enum Enum {
		Keep     = 0,	/**< Keeps the current value */
		Zero     = 1,	/**< Sets the stencil buffer value to zero */
		Replace  = 2,	/**< Sets the stencil buffer value to ref, as specified by RenderState::StencilRef */
		Incr     = 3,	/**< Increments the current stencil buffer value. Clamps to the maximum representable unsigned value. */
		Decr     = 4,	/**< Decrements the current stencil buffer value. Clamps to zero. */
		IncrWrap = 5,	/**< Increments the current stencil buffer value. Wraps the result. (See Capabilities::bStencilWrap) */
		DecrWrap = 6,	/**< Decrements the current stencil buffer value. Wraps the result. (See Capabilities::bStencilWrap) */
		Invert   = 7,	/**< Bitwise inverts the current stencil buffer value */
		// End
		Number   = 8,	/**< Number of stencil operations */
		Unknown  = 9	/**< Unknown stencil operation */
	};
	pl_enum(Enum)
		pl_enum_value(Keep,		"Keeps the current value")
		pl_enum_value(Zero,		"Sets the stencil buffer value to zero")
		pl_enum_value(Replace,	"Sets the stencil buffer value to ref, as specified by RenderState::StencilRef")
		pl_enum_value(Incr,		"Increments the current stencil buffer value. Clamps to the maximum representable unsigned value.")
		pl_enum_value(Decr,		"Decrements the current stencil buffer value. Clamps to zero.")
		pl_enum_value(IncrWrap,	"Increments the current stencil buffer value. Wraps the result. (See Capabilities::bStencilWrap)")
		pl_enum_value(DecrWrap,	"Decrements the current stencil buffer value. Wraps the result. (See Capabilities::bStencilWrap)")
		pl_enum_value(Invert,	"Bitwise inverts the current stencil buffer value")
	pl_enum_end
};

/**
*  @brief
*    Tessellation mode
*/
class TessellationMode {
	public:
	enum Enum {
		Discrete   = 0,	/**< Discrete mode (only integer tessellation factor) */
		Continuous = 1,	/**< Continuous (floating point tessellation factor) */
		// End
		Number     = 2,	/**< Number of tessellation modes */
		Unknown    = 3	/**< Unknown tessellation mode */
	};
	pl_enum(Enum)
		pl_enum_value(Discrete,		"Discrete mode (only integer tessellation factor)")
		pl_enum_value(Continuous,	"Continuous (floating point tessellation factor)")
	pl_enum_end
};

/**
*  @brief
*    Render states
*/
class RenderState {
	public:
	enum Enum {
		// Modes
		FillMode            = 0,	/**< Fill mode (see Fill, default: Fill::Solid) */
		CullMode            = 1,	/**< Cull mode (see Cull, RenderState::InvCullMode, default: Cull::CCW) */
		// Z buffer
		ZEnable             = 2,	/**< Enable/disable z buffer test (false/true, default: true) */
		ZWriteEnable        = 3,	/**< Enable/disable z buffer writing (false/true, default: true) */
		ZFunc               = 4,	/**< Z buffer function (see Compare, default: Compare::LessEqual) */
		ZBias               = 5,	/**< Z bias/polygon offset factor, < 0 = towards camera (float to PLGeneral::uint32 example PLGeneral::Tools::FloatToUInt32(-0.001f), default: 0)
										 Because RenderState::SlopeScaleDepthBias and RenderState::DepthBias below are API and
										 GPU dependent, their results are NOT the same on each system & API. Whenever possible, do NOT use
										 this 'classic' render states, use RenderState::ZBias instead. If this state is not null, the renderer
										 will automatically manipulate the internal projection matrix to perform an 'z bias' which is more
										 predictable as the 'classic' polygon offset. */
		SlopeScaleDepthBias = 6,	/**< Slope scale bias/polygon offset factor, try to avoid using this -> see ZBias (float to PLGeneral::uint32 example PLGeneral::Tools::FloatToUInt32(-1.0f), default: 0) */
		DepthBias           = 7,	/**< Depth bias/polygon offset units, try to avoid using this -> see ZBias (float to PLGeneral::uint32 example PLGeneral::Tools::FloatToUInt32(-2.0f), default: 0) */
		// Blend
		BlendEnable         = 8,	/**< Enable/disable blending (false/true, default: false) */
		SrcBlendFunc        = 9,	/**< Source blend function (see BlendFunc, default: BlendFunc::SrcAlpha) */
		DstBlendFunc        = 10,	/**< Destination blend function (see BlendFunc, default: BlendFunc::InvSrcAlpha) */
		// Stencil
		StencilEnable       = 11,	/**< Enable/disable stencil test (false/true, default: false) */
		StencilFunc         = 12,	/**< Stencil test passes if ((ref & mask) stencilfn (stencil & mask)) is true (see Compare, default: Compare::Always) */
		StencilRef          = 13,	/**< Reference value used in stencil test (PLGeneral::uint32, default: 0) */
		StencilMask         = 14,	/**< Mask value used in stencil test (PLGeneral::uint32, default: 0xFFFFFFFF) */
		StencilFail         = 15,	/**< Operation to perform if stencil test fails (StencilOp, default: StencilOp::Keep) */
		StencilZFail        = 16,	/**< Operation to perform if stencil test passes and Z test fails (StencilOp, default: StencilOp::Keep) */
		StencilPass         = 17,	/**< Operation to perform if both stencil and Z tests pass (StencilOp, default: StencilOp::Keep) */
		TwoSidedStencilMode = 18,	/**< Enable/disable 2 sided stenciling (false/true, default: false, requires Capabilities::bTwoSidedStencils)
										 If the triangle winding order is clockwise, the Stencil* operations will be used. If the winding
										 order is counterclocwise, the CCWStencil* operations will be used. */
		CCWStencilFunc      = 19,	/**< Stencil test passes if ((ref & mask) stencilfn (stencil & mask)) is true (see Compare, default: Compare::Always, requires Capabilities::bTwoSidedStencils) */
		CCWStencilFail      = 20,	/**< Operation to perform if ccw stencil test fails (StencilOp, default: StencilOp::Keep, requires Capabilities::bTwoSidedStencils) */
		CCWStencilZFail     = 21,	/**< Operation to perform if ccw stencil test passes and Z test fails (StencilOp, default: StencilOp::Keep, requires Capabilities::bTwoSidedStencils) */
		CCWStencilPass      = 22,	/**< Operation to perform if both ccw stencil and Z tests pass (StencilOp, default: StencilOp::Keep, requires Capabilities::bTwoSidedStencils) */
		// Point and line
		PointSize           = 23,	/**< Point size when it is not specified for each vertex. (float, default: 1.0)
										 This value is in screen space units if RenderState::PointScaleEnable is false; otherwise this value is in world space units. */
		PointScaleEnable    = 24,	/**< Controls computation of size for point primitives. (false/true, default: false)
										 When true, the point size is interpreted as a camera space value and is scaled by the distance function and the frustum
										 to viewport y-axis scaling to compute the final screen-space point size. When false, the point size is interpreted as screen
										 space and used directly. */
		PointSizeMin        = 25,	/**< Minimum size of point primitives (float, default: 1.0, requires Capabilities::bPointParameters) */
		PointSizeMax        = 26,	/**< Maximum size of point primitives, must be greater than or equal to PointSizeMin (float, default: 64.0, requires Capabilities::bPointParameters) */
		PointScaleA         = 27,	/**< Controls for distance-based size attenuation for point primitives (float, default: 1.0, requires Capabilities::bPointParameters) */
		PointScaleB         = 28,	/**< Controls for distance-based size attenuation for point primitives (float, default: 0.0, requires Capabilities::bPointParameters) */
		PointScaleC         = 29,	/**< Controls for distance-based size attenuation for point primitives (float, default: 0.0, requires Capabilities::bPointParameters) */
		LineWidth			= 30,	/**< Line width (float, default: 1.0) */
		// Tessellation
		TessellationFactor  = 31,	/**< Tessellation factor (1-Capabilities::nMaxTessellationFactor inclusive, default: 1, requires Capabilities::nMaxTessellationFactor > 1) */
		TessellationMode    = 32,	/**< Tessellation mode (default: TessellationMode::Discrete, requires Capabilities::nMaxTessellationFactor > 1) */
		// Misc
		PointSpriteEnable   = 33,	/**< When true, use point texture mapping (false/true, default: false, requires Capabilities::bPointSprite) */
		DitherEnable        = 34,	/**< Enable/disable dithering (false/true, default: false) */
		ScissorTestEnable   = 35,	/**< Enable/disable the scissor test (false/true, default: false) */
		MultisampleEnable   = 36,	/**< When true, perform multisample (false/true, default: true, requires Capabilities::nMultisampleAntialiasingSamples > 1, usually set automatically by the surfaces) */
		InvCullMode         = 37,	/**< Inverse cull mode active? RenderState::CullMode isn't touched only the intern API setting
										 is inverted! (false/true, default: false) */
		FixedFillMode       = 38,	/**< General fill mode which is normally set once. If this isn't Fill::Unknown this fill mode
										 will be used instead of RenderState::FillMode (see Fill, default: Fill::Unknown) */
		// End
		Number              = 39,	/**< Number of render states */
		Unknown             = 40	/**< Unknown render state */
	};
};

/**
*  @brief
*    Primitive types
*/
class Primitive {
	public:
	enum Enum {
		PointList     = 0,	/**< Point list */
		LineList      = 1,	/**< Line list */
		LineStrip     = 2,	/**< Line strip */
		TriangleList  = 3,	/**< Triangle list */
		TriangleStrip = 4,	/**< Triangle strip */
		TriangleFan   = 5,	/**< Triangle fan */
		// End
		Number        = 7,	/**< Number of primitive types */
		Unknown       = 8	/**< Unknown primitive type */
	};
};

/**
*  @brief
*    Lock modes
*/
class Lock {
	public:
	enum Enum {
		ReadOnly  = 0,	/**< Read only */
		WriteOnly = 1,	/**< Write only */
		ReadWrite = 2,	/**< Read and write */
		// End
		Number    = 3,	/**< Number of lock modes */
		Unknown   = 4	/**< Unknown lock mode */
	};
};

/**
*  @brief
*    Usage flags
*/
class Usage {
	public:
	enum Enum {
		Static    = 0,	/**< Static memory usage */
		Dynamic   = 1,	/**< Dynamic memory usage */
		WriteOnly = 2,  /**< Informs the system that the application writes only to the buffer.
							 Using this flag enables the driver to choose the best memory location
							 for efficient write operations and rendering. */
		Software  = 3,	/**< Software memory usage (for instance temp buffers, normally no rendering possible) */
		// End
		Number    = 4,	/**< Number of usage flags */
		Unknown   = 5	/**< Unknown usage */
	};
};

/**
*  @brief
*    Texture addressing modes
*/
class TextureAddressing {
	public:
	enum Enum {
		Clamp   = 0,	/**< Texture coordinates outside the range [0.0, 1.0] are set to the texture color at 0.0 or 1.0, respectively. */
		Border  = 1,	/**< Texture coordinates outside the range [0.0, 1.0] are set to the border color. */
		Wrap    = 2,	/**< Tile the texture at every integer junction. For example, for u values between 0 and 3, the texture is repeated three times; no mirroring is performed. */
		Mirror  = 3,	/**< Similar to Wrap, except that the texture is flipped at every integer junction. For u values between 0
							 and 1, for example, the texture is addressed normally; between 1 and 2, the texture is flipped (mirrored); between 2 and 3, the texture is normal again, and so on. */
		// End
		Number  = 4,	/**< Number of texture-addressing modes */
		Unknown = 5		/**< Unknown texture-addressing mode */
	};
	pl_enum(Enum)
		pl_enum_value(Clamp,	"Texture coordinates outside the range [0.0, 1.0] are set to the texture color at 0.0 or 1.0, respectively.")
		pl_enum_value(Border,	"Texture coordinates outside the range [0.0, 1.0] are set to the border color.")
		pl_enum_value(Wrap,		"Tile the texture at every integer junction. For example, for u values between 0 and 3, the texture is repeated three times; no mirroring is performed.")
		pl_enum_value(Mirror,	"Similar to Wrap, except that the texture is flipped at every integer junction")
	pl_enum_end
};

/**
*  @brief
*    Texture filtering modes
*
*  @note
*    - Defines texture filtering modes for a texture stage
*/
class TextureFiltering {
	public:
	enum Enum {
		None        = 0,	/**< Mipmapping disabled. The rasterizer should use the magnification filter instead. */
		Point       = 1,	/**< Point filtering used as a texture magnification or minification filter. The texel
								 with coordinates nearest to the desired pixel value is used. The texture filter to
								 be used between mipmap levels is nearest-point mipmap filtering. The rasterizer uses
								 the color from the texel of the nearest mipmap texture. */
		Linear      = 2,	/**< Bilinear interpolation filtering used as a texture magnification or minification filter.
								 A weighted average of a 2x2 area of texels surrounding the desired pixel is used. The
								 texture filter to use between mipmap levels is trilinear mipmap interpolation. The
								 rasterizer linearly interpolates pixel color, using the texels of the two nearest mipmap textures. */
		Anisotropic = 3,	/**< Anisotropic texture filtering used as a texture magnification or minification filter.
								 Compensates for distortion caused by the difference in angle between the texture polygon
								 and the plane of the screen. */
		// End
		Number      = 4,	/**< Number of texture filtering modes */
		Unknown     = 5		/**< Unknown texture filtering mode */
	};
	pl_enum(Enum)
		pl_enum_value(None,			"Mipmapping disabled. The rasterizer should use the magnification filter instead.")
		pl_enum_value(Point,		"Point filtering used as a texture magnification or minification filter")
		pl_enum_value(Linear,		"Bilinear interpolation filtering used as a texture magnification or minification filter")
		pl_enum_value(Anisotropic,	"Anisotropic texture filtering used as a texture magnification or minification filter")
	pl_enum_end
};

/**
*  @brief
*    Sampler states
*/
class Sampler {
	public:
	enum Enum {
		// Address modes
		AddressU      =  0,	/**< Texture-address mode for the u/s coordinate (TextureAddressing, default: TextureAddressing::Wrap) */
		AddressV      =  1,	/**< Texture-address mode for the v/t coordinate (TextureAddressing, default: TextureAddressing::Wrap) */
		AddressW      =  2,	/**< Texture-address mode for the w/r coordinate (TextureAddressing, default: TextureAddressing::Wrap) */
		// Filter
		MagFilter     =  3,	/**< Magnification filter of type TextureFiltering (default: TextureFiltering::Linear) */
		MinFilter     =  4,	/**< Minification filter of type TextureFiltering (default: TextureFiltering::Linear) */
		MipFilter     =  5,	/**< Mipmap filter to use during minification. See TextureFiltering. (default: TextureFiltering::Linear) */
		// Misc
		MipmapLODBias =  6,	/**< Mipmap level of detail (LOD) bias (float, default: 0.0) */
		MaxMapLevel   =  7,	/**< LOD index of largest map to use. Values range from 0 to (n-1) where 0 is the largest. (PLGeneral::uint32, default: 1000) */
		MaxAnisotropy =  8,	/**< Maximum anisotropy (PLGeneral::uint32, default: 1) */
		// End
		Number        =  9,	/**< Number of sampler states */
		Unknown       = 10	/**< Unknown sampler state */
	};
};


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Display mode
*/
struct DisplayMode {
	PLMath::Vector2i  vSize;		/**< Screen resolution */
	PLGeneral::uint32 nColorBits;	/**< Number of bits for the color (for example 32) */
	PLGeneral::uint32 nFrequency;	/**< Refresh rate (for example 60) */
};

/**
*  @brief
*    Holds all hardware capabilities
*/
struct Capabilities {
	PLGeneral::uint8  nMaxColorRenderTargets;			/**< Maximum number of color render targets (multi render targets (MRT)) */
	PLGeneral::uint8  nMaxTextureUnits;					/**< Maximum number of texture units */
	PLGeneral::uint16 nMaxAnisotropy;					/**< Maximum anisotropy */
	PLGeneral::uint8  nMaxTessellationFactor;			/**< Maximum tessellation factor (inclusive) */
	PLGeneral::uint16 nMaxTextureBufferSize;			/**< Maximum texture buffer size */
	bool              bTextureBufferRectangle;			/**< Rectangle texture buffers supported? (no power of 2) */
	PLGeneral::uint16 nMaxRectangleTextureBufferSize;	/**< Maximum rectangle texture buffer size */
	bool              bTextureBuffer3D;					/**< 3D texture buffers supported? */
	PLGeneral::uint16 nMax3DTextureBufferSize;			/**< Maximum 3D texture buffer size */
	bool              bTextureBufferCube;				/**< Cube texture buffers supported? */
	PLGeneral::uint16 nMaxCubeTextureBufferSize;		/**< Maximum cube texture buffer size */
	bool              bStencilWrap;						/**< Stencil wrap supported? (for StencilOp::IncrWrap & StencilOp::DecrWrap) */
	bool              bTwoSidedStencils;				/**< Two sided stencils supported? (for RenderState::TwoSidedStencilMode, RenderState::CCWStencilFunc,
															 RenderState::CCWStencilFail, RenderState::CCWStencilZFail, RenderState::CCWStencilPass) */
	bool              bDepthBoundsTest;					/**< Depth bounds test supported? (for Renderer::SetDepthBounds()) */
	bool              bPointSprite;						/**< Point sprite supported? (for RenderState::PointSpriteEnable) */
	bool              bPointParameters;					/**< Point parameters supported? (for RenderState::PointSizeMin, RenderState::PointSizeMax,
															 RenderState::PointScaleA, RenderState::PointScaleB, RenderState::PointScaleC) */
	bool              bOcclusionQuery;					/**< Occlusion query supported? (for the OcclusionQuery class) */
	bool              bVertexBufferSecondaryColor;		/**< Vertex buffer secondary color supported? (for the second channel of VertexBuffer::Color) */
	PLGeneral::uint32 nZBufferBits;						/**< Z buffer bits (for example 24) */
	PLGeneral::uint32 nStencilBits;						/**< Stencil buffer bits (for example 8) */
	PLGeneral::uint32 nMultisampleAntialiasingSamples;	/**< Multisample antialiasing samples */
};

/**
*  @brief
*    Renderer statistics
*/
struct Statistics {
	PLGeneral::uint32 nRenderStateChanges;			/**< Number of render (internal API) state changes */
	PLGeneral::uint32 nSamplerStateChanges;			/**< Number of sampler (internal API) state changes */
	PLGeneral::uint32 nDrawPrimitivCalls;			/**< Number of draw primitiv calls */
	PLGeneral::uint32 nVertices;					/**< Number of rendered vertices */
	PLGeneral::uint32 nTriangles;					/**< Number of rendered triangles */
	PLGeneral::uint32 nTextureBuffersNum;			/**< Number of texture buffers */
	PLGeneral::uint64 nTextureBuffersMem;			/**< Memory in bytes the texture buffers require */
	PLGeneral::uint32 nTextureBufferBinds;			/**< Number of texture buffer bindings */
	PLGeneral::uint32 nVertexBufferNum;				/**< Number of vertex buffers */
	PLGeneral::uint64 nVertexBufferMem;				/**< Memory in bytes the vertex buffers require */
	PLGeneral::uint32 nVertexBuffersSetupTime;		/**< Vertex buffers setup time (mircoseconds) */
	PLGeneral::uint32 nVertexBufferLocks;			/**< Number of vertex buffer locks */
	PLGeneral::uint32 nIndexBufferNum;				/**< Number of index buffers */
	PLGeneral::uint64 nIndexBufferMem;				/**< Memory in bytes the index buffers require */
	PLGeneral::uint32 nIndexBuffersSetupTime;		/**< Index buffers setup time (microseconds) */
	PLGeneral::uint32 nIndexBufferLocks;			/**< Number of index buffer locks */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TYPES_H__
