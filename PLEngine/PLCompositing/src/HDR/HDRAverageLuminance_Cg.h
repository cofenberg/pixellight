/*********************************************************\
 *  File: HDRAverageLuminance_Cg.h                       *
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


const static char *pszHDRAverageLuminance_Cg_FS = "\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 color : COLOR;\n\
};\n\
\n\
\n\
// Neighbor offset table\n\
const static float2 Offsets[4] = {\n\
	float2( 0,  0), // Center       0\n\
	float2( 1,  0), // Right        1\n\
	float2( 1,  1), // Bottom right 2\n\
	float2( 0,  1)  // Bottom       3\n\
};\n\
\n\
// Downsample log main function\n\
FS_OUTPUT DownsampleLog(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
			  , uniform float3      LuminanceConvert	// Convert RGB to luminance\n\
			  , uniform float       Epsilon				// A small value to avoid undefined log(0)\n\
			  , uniform samplerRECT Texture)			// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 1\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++) {\n\
		// If, for any reason, there's an invalid value it would mess up everything... so, security is really a must have in here!\n\
		float value = log(dot(texRECT(Texture, IN.texUV + Offsets[i]).rgb, LuminanceConvert) + Epsilon);\n\
		if (!isnan(value))\n\
			luminance += value;\n\
	}\n\
\n\
	// Write down the result\n\
	OUT.color = luminance*0.25f;\n\
\n\
	// Done\n\
	return OUT;\n\
}\n\
\n\
// Downsample main function\n\
FS_OUTPUT Downsample(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
		   , uniform samplerRECT Texture)		// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++)\n\
		luminance += texRECT(Texture, IN.texUV + Offsets[i]).r;\n\
	OUT.color = luminance*0.25f;\n\
\n\
	// Done\n\
	return OUT;\n\
}\n\
\n\
// Downsample exp main function\n\
FS_OUTPUT DownsampleExp(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
			  , uniform samplerRECT Texture)		// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++)\n\
		luminance += texRECT(Texture, IN.texUV + Offsets[i]).r;\n\
	OUT.color = exp(luminance*0.25f);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
