/*********************************************************\
 *  File: HDRBloom_GLSL.h                                *
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


// Downsample and bloom OpenGL 3.0 ("#version 130") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator" or by hand
static const PLGeneral::String sHDRBloom_GLSL_VS = "\
// Attributes\n\
in highp vec4 VertexPosition;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	out highp vec3 VertexTexCoordVS;	// Vertex texture coordinate 0 + average luminance within the z component output\n\
#else\n\
	out highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
#endif\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;						// Texture size in texel\n\
#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	uniform highp sampler2D	AverageLuminanceTexture;	// Automatic average luminance texture\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS.xy = VertexPosition.zw*TextureSize;\n\
\n\
	// Get the average luminance by using vertex texture fetch so we have just 4 instead of xxxx average luminance texture accesses when doing this within the fragment shader\n\
	#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
		VertexTexCoordVS.z = texture2D(AverageLuminanceTexture, vec2(0.5f, 0.5f)).r;\n\
	#endif\n\
}";


// Downsample OpenGL 3.0 ("#version 130") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLGeneral::String sHDRBloom_GLSL_FS_Downscale = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	in highp vec3 VertexTexCoordVS;	// Vertex texture coordinate 0 + average luminance within the z component input from vertex shader\n\
#else\n\
	in highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
#endif\n\
\n\
// Uniforms\n\
#ifdef FS_TONE_MAPPING\n\
	uniform highp vec3			LuminanceConvert;	// Luminance convert\n\
	uniform highp float			Key;				// Key, must be >=0\n\
	uniform highp float			WhiteLevel;			// White level, must be >=0\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifndef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			uniform highp sampler2D	AverageLuminanceTexture;	// Automatic average luminance texture\n\
		#endif\n\
	#else\n\
		uniform highp float		AverageLuminance;	// User set average luminance\n\
	#endif\n\
#endif\n\
uniform highp float			BrightThreshold;		// Bright threshold\n\
uniform highp sampler2DRect	HDRTexture;				// HDR texture\n\
\n\
// Neighbor offset table\n\
const lowp vec2 Offsets[16] = lowp vec2[16](\n\
	lowp vec2( 1.5f, -1.5f), // 0\n\
	lowp vec2( 1.5f, -0.5f), // 1\n\
	lowp vec2( 1.5f,  0.5f), // 2\n\
	lowp vec2( 1.5f,  1.5f), // 3\n\
	lowp vec2( 0.5f, -1.5f), // 4\n\
	lowp vec2( 0.5f, -0.5f), // 5\n\
	lowp vec2( 0.5f,  0.5f), // 6\n\
	lowp vec2( 0.5f,  1.5f), // 7\n\
	lowp vec2(-0.5f, -1.5f), // 8\n\
	lowp vec2(-0.5f, -0.5f), // 9\n\
	lowp vec2(-0.5f,  0.5f), // 10\n\
	lowp vec2(-0.5f,  1.5f), // 11\n\
	lowp vec2(-1.5f, -1.5f), // 12\n\
	lowp vec2(-1.5f, -0.5f), // 13\n\
	lowp vec2(-1.5f,  0.5f), // 14\n\
	lowp vec2(-1.5f,  1.5f)  // 15\n\
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Downsample\n\
	highp vec4 color = vec4(0);\n\
	for (highp int i=0; i<16; i++)\n\
		color += texture2DRect(HDRTexture, VertexTexCoordVS.xy + Offsets[i]);\n\
	gl_FragColor = color*(1.0f/16.0f);\n\
\n\
    // The rest is for tone mapping - nearly same code as in 'SRPEndHDR_GLSL'\n\
\n\
	// Perform tone mapping\n\
#ifdef FS_TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	highp float pixelLuminance = dot(gl_FragColor.rgb, LuminanceConvert);\n\
\n\
	// Get the average luminance\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			#define averageLuminance VertexTexCoordVS.z\n\
		#else\n\
			float averageLuminance = texture2D(AverageLuminanceTexture, vec2(0.5f, 0.5f)).r;\n\
		#endif\n\
	#else\n\
		#define averageLuminance AverageLuminance\n\
	#endif\n\
\n\
	// Use the Reinhard global tone map operator to compute the scaled luminance\n\
	highp float keyOverLuminance = (averageLuminance > 0.0f) ? Key/averageLuminance : 0.0f;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 2\n\
	highp float scaledLuminance = keyOverLuminance*pixelLuminance;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 4\n\
	scaledLuminance = (scaledLuminance*(1 + (scaledLuminance/pow(keyOverLuminance*WhiteLevel, 2)))) / (1 + scaledLuminance);\n\
\n\
	// Set LDR color\n\
	gl_FragColor = vec4(clamp(gl_FragColor.rgb*scaledLuminance, 0.0f, 1.0f), gl_FragColor.a);\n\
#endif\n\
\n\
	// Bright pass - do this 'after' tone mapping, just looks better\n\
	gl_FragColor = max(vec4(0), gl_FragColor - vec4(BrightThreshold));\n\
}";


// Bloom GLSL vertex shader source code
static const PLGeneral::String sHDRBloom_GLSL_FS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
in highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec2			UVScale;	// UV scale\n\
uniform highp sampler2DRect	HDRTexture;	// HDR texture\n\
\n\
// Neighbor offset table\n\
const lowp vec2 Offsets[13] = lowp vec2[13](\n\
	lowp vec2( 6,  6), // 0\n\
	lowp vec2( 5,  5), // 1\n\
	lowp vec2( 4,  4), // 2\n\
	lowp vec2( 3,  3), // 3\n\
	lowp vec2( 2,  2), // 4\n\
	lowp vec2( 1,  1), // 5\n\
	lowp vec2( 0,  0), // 6\n\
	lowp vec2(-1, -1), // 7\n\
	lowp vec2(-2, -2), // 8\n\
	lowp vec2(-3, -3), // 9\n\
	lowp vec2(-4, -4), // 10\n\
	lowp vec2(-5, -5), // 11\n\
	lowp vec2(-6, -6)  // 12\n\
);\n\
const lowp float Weights[13] = lowp float[13](\n\
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
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	gl_FragColor = vec4(0);\n\
	for (highp int i=0; i<13; i++)\n\
		gl_FragColor += texture2DRect(HDRTexture, VertexTexCoordVS + Offsets[i]*UVScale)*Weights[i];\n\
}";
