/*********************************************************\
 *  File: SRPDeferredSSAO_Cg.h                           *
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
 *
 *  Definitions:
 *  - XBLUR: X blur, if not defined => y blur
\*********************************************************/


// Blur
const static char *pszDeferredSSAO_Cg_VS = "\n\
// Vertex input\n\
struct VS_INPUT {\n\
	float4 position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
};\n\
\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position   : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	  : TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
	float2 texInputUV : TEXCOORD1;	// Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Main function\n\
VS_OUTPUT main(VS_INPUT IN					// Vertex input\n\
	 , uniform int2		TextureSize			// Texture size\n\
	 , uniform int2		InputTextureSize)	// Input texture size\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.position = IN.position;\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.texUV      = IN.texUV*TextureSize;\n\
	OUT.texInputUV = IN.texUV*InputTextureSize;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


// Blur
const static char *pszDeferredSSAO_Cg_FS = "\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position   : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	  : TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
	float2 texInputUV : TEXCOORD1;	// Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 color : COLOR;\n\
};\n\
\n\
float fetch_eye_z(samplerRECT normalDepthTexture, float2 uv)\n\
{\n\
	return texRECT(normalDepthTexture, uv).b;\n\
}\n\
\n\
float BlurFunction(samplerRECT inputTexture, samplerRECT normalDepthTexture, float g_BlurFalloff, float g_Sharpness, float2 uv, float2 uvInput, float r, float center_c, float center_d, inout float w_total)\n\
{\n\
	float c = texRECT(inputTexture, uvInput);\n\
	float d = fetch_eye_z(normalDepthTexture, uv);\n\
\n\
	float ddiff = d - center_d;\n\
	float w = exp(-r*r*g_BlurFalloff - ddiff*ddiff*g_Sharpness);\n\
	w_total += w;\n\
\n\
	return w*c;\n\
}\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
	 , uniform float	   g_BlurRadius\n\
	 , uniform float	   g_BlurFalloff\n\
	 , uniform float	   g_Sharpness\n\
	 , uniform samplerRECT InputTexture			// Input texture\n\
	 , uniform samplerRECT NormalDepthTexture)	// RG=normal vector, B=linear view space length\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	float b = 0;\n\
	float w_total = 0;\n\
	float center_c = texRECT(InputTexture, IN.texInputUV);\n\
	float center_d = fetch_eye_z(NormalDepthTexture, IN.texUV);\n\
\n\
	for (float r=-g_BlurRadius; r<=g_BlurRadius; ++r) {\n\
		#ifdef XBLUR\n\
			float2 uvOffset = float2(r, 0);\n\
		#else\n\
			float2 uvOffset = float2(0, r);\n\
		#endif\n\
		b += BlurFunction(InputTexture, NormalDepthTexture, g_BlurFalloff, g_Sharpness, IN.texUV + uvOffset, IN.texInputUV + uvOffset, r, center_c, center_d, w_total);\n\
	}\n\
	OUT.color = b/w_total;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
