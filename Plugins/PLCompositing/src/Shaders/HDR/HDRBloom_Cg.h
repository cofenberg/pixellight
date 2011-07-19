/*********************************************************\
 *  File: HDRBloom_Cg.h                                  *
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


// Downscale and bloom Cg vertex shader source code
static const PLCore::String sHDRBloom_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
		float3 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>) + average luminance within the z component\n\
	#else\n\
		float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
	#endif\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition : POSITION	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
												// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
  , uniform int2	  TextureSize				// Texture size in texel\n\
	#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
  , uniform sampler2D AverageLuminanceTexture	// Automatic average luminance texture\n\
	#endif\n\
	)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.TexCoord.xy = VertexPosition.zw*TextureSize;\n\
\n\
	// Get the average luminance by using vertex texture fetch so we have just 4 instead of xxxx average luminance texture accesses when doing this within the fragment shader\n\
	#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
		OUT.TexCoord.z = tex2D(AverageLuminanceTexture, float2(0.5f, 0.5f)).r;\n\
	#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Downscale Cg fragment shader source code
static const PLCore::String sHDRBloom_Cg_FS_Downscale = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
		float3 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>) + average luminance within the z component\n\
	#else\n\
		float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
	#endif\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
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
	float2(-1.5f,  1.5f), // 15\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
#ifdef FS_TONE_MAPPING\n\
	 , uniform float3      LuminanceConvert		// Luminance convert\n\
	 , uniform float       Key					// Key, must be >=0\n\
	 , uniform float       WhiteLevel			// White level, must be >=0\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifndef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			, uniform sampler2D AverageLuminanceTexture	// Automatic average luminance texture\n\
		#endif\n\
	#else\n\
	 , uniform float       AverageLuminance		// User set average luminance\n\
	#endif\n\
#endif\n\
	 , uniform float	   BrightThreshold		// Bright threshold\n\
	 , uniform samplerRECT HDRTexture)			// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Downscale\n\
	float4 color = 0;\n\
	for (int i=0; i<16; i++)\n\
		color += texRECT(HDRTexture, IN.TexCoord.xy + Offsets[i]);\n\
	OUT.Color0 = color*(1.0f/16.0f);\n\
\n\
    // The rest is for tone mapping - nearly same code as in 'SRPEndHDR_Cg'\n\
\n\
	// Perform tone mapping\n\
#ifdef FS_TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	float pixelLuminance = dot(OUT.Color0.rgb, LuminanceConvert);\n\
\n\
	// Get the average luminance\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			#define averageLuminance IN.TexCoord.z\n\
		#else\n\
			float averageLuminance = tex2D(AverageLuminanceTexture, float2(0.5f, 0.5f)).r;\n\
		#endif\n\
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
	OUT.Color0 = float4(clamp(OUT.Color0.rgb*scaledLuminance, 0.0f, 1.0f), OUT.Color0.a);\n\
#endif\n\
\n\
	// Bright pass - do this 'after' tone mapping, just looks better\n\
	OUT.Color0 = max(float4(0, 0, 0, 0), OUT.Color0 - BrightThreshold);\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Bloom Cg vertex shader source code
static const PLCore::String sHDRBloom_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
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
	0.002216f, // 0\n\
	0.008764f, // 1\n\
	0.026995f, // 2\n\
	0.064759f, // 3\n\
	0.120985f, // 4\n\
	0.176033f, // 5\n\
	0.199471f, // 6\n\
	0.176033f, // 7\n\
	0.120985f, // 8\n\
	0.064759f, // 9\n\
	0.026995f, // 10\n\
	0.008764f, // 11\n\
	0.002216f  // 12\n\
};\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN			// Interpolated output from the vertex stage\n\
	 , uniform float2	   UVScale		// UV scale\n\
	 , uniform samplerRECT HDRTexture)	// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	OUT.Color0 = 0;\n\
	for (int i=0; i<13; i++)\n\
		OUT.Color0 += texRECT(HDRTexture, IN.TexCoord + Offsets[i]*UVScale)*Weights[i];\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
