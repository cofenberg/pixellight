/*********************************************************\
 *  File: SRPEndHDR_Cg.h                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
static const PLCore::String sEndHDR_Cg_VS = "\
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


// Cg fragment shader source code
static const PLCore::String sEndHDR_Cg_FS = "\
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
// Programs\n\
FS_OUTPUT main(VS_OUTPUT   IN						// Interpolated output from the vertex stage\n\
#ifdef FS_TONE_MAPPING\n\
	 , uniform float3      LuminanceConvert			// Luminance convert\n\
	 , uniform float       Key						// Key, must be >=0\n\
	 , uniform float       WhiteLevel				// White level, must be >=0\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifndef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			, uniform sampler2D AverageLuminanceTexture	// Automatic average luminance texture\n\
		#endif\n\
	#else\n\
	 , uniform float       AverageLuminance			// User set average luminance\n\
	#endif\n\
#endif\n\
#ifdef FS_BLOOM\n\
	 , uniform float       BloomFactor				// Bloom factor\n\
	 , uniform float       BloomDownscale			// Bloom downscale\n\
	 , uniform samplerRECT BloomTexture				// Bloom texture\n\
#endif\n\
#ifdef FS_GAMMA_CORRECTION\n\
	 , uniform float       InvGamma					// Inversed gamma correction value, must be >0\n\
#endif\n\
	 , uniform samplerRECT HDRTexture)				// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel data\n\
	float4 sample = texRECT(HDRTexture, IN.TexCoord.xy);\n\
\n\
	// Perform tone mapping\n\
#ifdef FS_TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	float pixelLuminance = dot(sample.rgb, LuminanceConvert);\n\
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
	OUT.Color0 = float4(clamp(sample.rgb*scaledLuminance, 0.0f, 1.0f), sample.a);\n\
#else\n\
	// Just copy over the color\n\
	OUT.Color0 = sample;\n\
#endif\n\
\n\
	// Add bloom\n\
#ifdef FS_BLOOM\n\
	OUT.Color0 = clamp(OUT.Color0 + texRECT(BloomTexture, IN.TexCoord.xy/BloomDownscale)*BloomFactor, 0.0f, 1.0f);\n\
#endif\n\
\n\
	// Perform gamma correction (linear space -> sRGB space)\n\
#ifdef FS_GAMMA_CORRECTION\n\
	OUT.Color0.rgb = pow(OUT.Color0.rgb, InvGamma);\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}";
