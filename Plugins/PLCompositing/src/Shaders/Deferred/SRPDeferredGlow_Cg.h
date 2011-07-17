/*********************************************************\
 *  File: SRPDeferredGlow_Cg.h                           *
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
static const PLGeneral::String sDeferredGlow_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition : POSITION,	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
													// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
	   uniform int2	  TextureSize)					// Texture size in texel\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.TexCoord = VertexPosition.zw*TextureSize;\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Downscale Cg fragment shader source code
static const PLGeneral::String sDeferredGlow_Cg_FS_Downscale = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR;\n\
};\n\
\n\
// Neighbor offset table\n\
const static float2 Offsets[16] = {\n\
	float2( 1.5f, -1.5f), // 0\n\
	float2( 1.5f, -0.5f), // 1\n\
	float2( 1.5f,  0.5f), // 2\n\
	float2( 1.5f,  1.5f), // 3\n\
	float2( 0.5f, -1.5f), // 4\n\
	float2( 0.5f, -0.5f), // 5\n\
	float2( 0.5f,  0.5f), // 6\n\
	float2( 0.5f,  1.5f), // 7\n\
	float2(-0.5f, -1.5f), // 8\n\
	float2(-0.5f, -0.5f), // 9\n\
	float2(-0.5f,  0.5f), // 10\n\
	float2(-0.5f,  1.5f), // 11\n\
	float2(-1.5f, -1.5f), // 12\n\
	float2(-1.5f, -0.5f), // 13\n\
	float2(-1.5f,  0.5f), // 14\n\
	float2(-1.5f,  1.5f)  // 15\n\
};\n\
\n\
// Main main function\n\
FS_OUTPUT main(VS_OUTPUT  IN		// Interpolated output from the vertex stage\n\
	, uniform samplerRECT Texture)	// Emissive/glow texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Downscale\n\
	float4 color = 0;\n\
	for (int i=0; i<16; i++)\n\
		color += texRECT(Texture, IN.TexCoord + Offsets[i]);\n\
	OUT.Color0 = color*(1.0f/16.0f);\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Blur Cg fragment shader source code
static const PLGeneral::String sDeferredGlow_Cg_FS_Blur = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR;\n\
};\n\
\n\
// Neighbor offset table\n\
const static float2 Offsets[13] = {\n\
	float2( 6,  6), // 0\n\
	float2( 5,  5), // 1\n\
	float2( 4,  4), // 2\n\
	float2( 3,  3), // 3\n\
	float2( 2,  2), // 4\n\
	float2( 1,  1), // 5\n\
	float2( 0,  0), // 6\n\
	float2(-1, -1), // 7\n\
	float2(-2, -2), // 8\n\
	float2(-3, -3), // 9\n\
	float2(-4, -4), // 10\n\
	float2(-5, -5), // 11\n\
	float2(-6, -6) // 12\n\
};\n\
const static float Weights[13] = {\n\
	0.002216, // 0\n\
	0.008764, // 1\n\
	0.026995, // 2\n\
	0.064759, // 3\n\
	0.120985, // 4\n\
	0.176033, // 5\n\
	0.199471, // 6\n\
	0.176033, // 7\n\
	0.120985, // 8\n\
	0.064759, // 9\n\
	0.026995, // 10\n\
	0.008764, // 11\n\
	0.002216  // 12\n\
};\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN		// Interpolated output from the vertex stage\n\
	 , uniform float2	   UVScale	// UV scale\n\
	 , uniform samplerRECT Texture)	// texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	OUT.Color0 = 0;\n\
	for (int i=0; i<13; i++)\n\
		OUT.Color0 += texRECT(Texture, IN.TexCoord + Offsets[i]*UVScale)*Weights[i];\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Result Cg fragment shader source code
static const PLGeneral::String sDeferredGlow_Cg_FS_Result = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR;\n\
};\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN			// Interpolated output from the vertex stage\n\
	 , uniform float	   GlowFactor	// Glow factor\n\
	 , uniform samplerRECT Texture)		// Glow texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel data\n\
	float4 sample = texRECT(Texture, IN.TexCoord);\n\
\n\
	// Calculate the resulting glow\n\
	float glowFactor = sample.a*GlowFactor;\n\
	OUT.Color0 = float4(sample.rgb*glowFactor, glowFactor != 0);\n\
\n\
	// Use discard?\n\
#ifdef FS_DISCARD\n\
	if (OUT.Color0.a == 0 || (OUT.Color0.r == 0 && OUT.Color0.g == 0 && OUT.Color0.b == 0))\n\
		discard;\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}";
