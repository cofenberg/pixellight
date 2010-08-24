/*********************************************************\
 *  File: SRPEndHDR_Cg.h                                 *
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
 *  - BLOOM:                         Add bloom
 *  - GAMMA_CORRECTION:              Perform gamma correction
\*********************************************************/


const static char *pszEndHDR_Cg_FS = "\n\
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
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN						// Interpolated output from the vertex stage\n\
#ifdef TONE_MAPPING\n\
	 , uniform float3      LuminanceConvert			// Luminance convert\n\
	 , uniform float       Key						// Key, must be >=0\n\
	 , uniform float       WhiteLevel				// White level, must be >=0\n\
	#ifdef AUTOMATIC_AVERAGE_LUMINANCE\n\
	 , uniform sampler2D   AverageLuminanceTexture	// Automatic average luminance texture\n\
	#else\n\
	 , uniform float       AverageLuminance			// User set average luminance\n\
	#endif\n\
#endif\n\
#ifdef BLOOM\n\
	 , uniform float       BloomFactor				// Bloom factor\n\
	 , uniform float       BloomDownscale			// Bloom downscale\n\
	 , uniform samplerRECT BloomTexture				// Bloom texture\n\
#endif\n\
#ifdef GAMMA_CORRECTION\n\
	 , uniform float       InvGamma					// Inversed gamma correction value, must be >0\n\
#endif\n\
	 , uniform samplerRECT HDRTexture)				// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel data\n\
	float4 sample = texRECT(HDRTexture, IN.texUV);\n\
\n\
	// Perform tone mapping\n\
#ifdef TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	float pixelLuminance = dot(sample.rgb, LuminanceConvert);\n\
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
	OUT.color = float4(saturate(sample.rgb*scaledLuminance), sample.a);\n\
#else\n\
	// Just copy over the color\n\
	OUT.color = sample;\n\
#endif\n\
\n\
	// Add bloom\n\
#ifdef BLOOM\n\
	OUT.color = saturate(OUT.color + texRECT(BloomTexture, IN.texUV/BloomDownscale)*BloomFactor);\n\
#endif BLOOM\n\
\n\
	// Perform gamma correction (linear space -> sRGB space)\n\
#ifdef GAMMA_CORRECTION\n\
	OUT.color.rgb = pow(OUT.color.rgb, InvGamma);\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
