/*********************************************************\
 *  File: SRPShadowMapping_Cg.h                          *
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


// Cg vertex shader source code
static const PLCore::String sSRPShadowMapping_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 LightVec : TEXCOORD0;\n\
#ifdef VS_TEXCOORD0\n\
	float2 TexCoord	: TEXCOORD1;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
#endif\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition  : POSITION	// Object space vertex position\n\
			#ifdef VS_TEXCOORD0\n\
			 , float2 VertexTexCoord0 : TEXCOORD0	// Vertex texture coordinate\n\
			#endif\n\
	, uniform float4x4 WorldVP		// World view projection matrix\n\
	, uniform float4x4 WorldV		// World view matrix\n\
	, uniform float    InvRadius)	// World space inverse light radius\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Transform vertex to clip space\n\
	OUT.Position = mul(WorldVP, VertexPosition);\n\
\n\
	// Calculate the world space light vector (the light position is the origin)\n\
	OUT.LightVec = -InvRadius*mul(WorldV, VertexPosition).xyz;\n\
\n\
#ifdef VS_TEXCOORD0\n\
	// Pass through the texture coordinate\n\
	OUT.TexCoord = VertexTexCoord0;\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg fragment shader source code
static const PLCore::String sSRPShadowMapping_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 LightVec : TEXCOORD0;\n\
#ifdef FS_ALPHATEST\n\
	float2 TexCoord	: TEXCOORD1;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
#endif\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT IN\n\
#ifdef FS_ALPHATEST\n\
	 , uniform sampler2D DiffuseMap\n\
	 , uniform float     AlphaReference\n\
#endif\n\
	)\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	#ifdef FS_ALPHATEST\n\
		// Fetch the required texel data\n\
		float4 sample = tex2D(DiffuseMap, IN.TexCoord);\n\
\n\
		// Perform an alpha test to discard fragments\n\
		if (sample.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
\n\
	// + '0.005' => Set polygon offset to avoid nasty shadow artefacts\n\
	float4 pack = {1.0f, 256.0f, 65536.0f, 16777216.0f};\n\
	OUT.Color0 = pack * (length(IN.LightVec) + 0.005f);\n\
\n\
	return OUT;\n\
}";
