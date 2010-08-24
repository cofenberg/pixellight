/*********************************************************\
 *  File: HDRBloom_Cg.h                                  *
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
 *  - TONE_MAPPING:                  Perform tone mapping
 *    - AUTOMATIC_AVERAGE_LUMINANCE: Perform light adaptation (TONE_MAPPING must be set, too)
\*********************************************************/


const static char *pszHDRBloom_Downsample_Cg_FS = "\n\
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
	float2(-1.5f,  1.5f), // 15\n\
};\n\
\n\
// Downsample main function\n\
FS_OUTPUT Downsample(VS_OUTPUT   IN							// Interpolated output from the vertex stage\n\
#ifdef TONE_MAPPING\n\
		   , uniform float3      LuminanceConvert			// Luminance convert\n\
		   , uniform float       Key						// Key, must be >=0\n\
		   , uniform float       WhiteLevel					// White level, must be >=0\n\
	#ifdef AUTOMATIC_AVERAGE_LUMINANCE\n\
		   , uniform sampler2D   AverageLuminanceTexture	// Automatic average luminance texture\n\
	#else\n\
		   , uniform float       AverageLuminance			// User set average luminance\n\
	#endif\n\
#endif\n\
		   , uniform float		 BrightThreshold			// Bright threshold\n\
		   , uniform samplerRECT Texture)					// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Downsample\n\
	float4 color = 0;\n\
	for (int i=0; i<16; i++)\n\
		color += texRECT(Texture, IN.texUV + Offsets[i]);\n\
	OUT.color = color*(1.0f/16.0f);\n\
\n\
    // The rest is for tone mapping - same code as in 'SRPEndHDR_Cg'\n\
\n\
	// Perform tone mapping\n\
#ifdef TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	float pixelLuminance = dot(OUT.color.rgb, LuminanceConvert);\n\
\n\
	// Get the average luminance\n\
	#ifdef AUTOMATIC_AVERAGE_LUMINANCE\n\
		float averageLuminance = tex2D(AverageLuminanceTexture, float2(0.5f, 0.5f)).r;\n\
	#else\n\
		#define averageLuminance AverageLuminance\n\
	#endif\n\
\n\
	// Use the Reinhard global tone map operator to compute the scaled luminance\n\
	float keyOverLuminance = (averageLuminance > 0.0f) ? Key/averageLuminance : 0.0f;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 2\n\
	float scaledLuminance = keyOverLuminance*pixelLuminance;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 4\n\
	scaledLuminance = (scaledLuminance*(1 + (scaledLuminance/pow(keyOverLuminance*WhiteLevel, 2)))) / (1 + scaledLuminance);\n\
\n\
	// Set LDR color\n\
	OUT.color = float4(saturate(OUT.color.rgb*scaledLuminance), OUT.color.a);\n\
#endif\n\
\n\
	// Bright pass - do this 'after' tone mapping, just looks better\n\
	OUT.color = max(float4(0, 0, 0, 0), OUT.color - BrightThreshold);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


const static char *pszHDRBloom_Cg_FS = "\n\
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
	 , uniform samplerRECT Texture)	// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	OUT.color = 0;\n\
	for (int i=0; i<13; i++)\n\
		OUT.color += texRECT(Texture, IN.texUV + Offsets[i]*UVScale)*Weights[i];\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
