/*********************************************************\
 *  File: SRPEndHDR_GLSL.h                               *
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


// OpenGL 3.0 ("#version 130") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLGeneral::String sEndHDR_GLSL_VS = "\
// Attributes\n\
in vec4 VertexPosition;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
								// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	out vec3 VertexTexCoordVS;	// Vertex texture coordinate 0 + average luminance within the z component output\n\
#else\n\
	out vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
#endif\n\
\n\
// Uniforms\n\
uniform ivec2 TextureSize;							// Texture size in texel\n\
#ifdef VS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	uniform sampler2D	AverageLuminanceTexture;	// Automatic average luminance texture\n\
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


// OpenGL 3.0 ("#version 130") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLGeneral::String sEndHDR_GLSL_FS = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
	in vec3 VertexTexCoordVS;	// Vertex texture coordinate 0 + average luminance within the z component input from vertex shader\n\
#else\n\
	in vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
#endif\n\
\n\
// Uniforms\n\
#ifdef FS_TONE_MAPPING\n\
	uniform vec3			LuminanceConvert;				// Luminance convert\n\
	uniform float			Key;							// Key, must be >=0\n\
	uniform float			WhiteLevel;						// White level, must be >=0\n\
	#ifdef FS_AUTOMATIC_AVERAGE_LUMINANCE\n\
		#ifndef FS_AUTOMATIC_AVERAGE_LUMINANCE_VTF\n\
			uniform sampler2D	AverageLuminanceTexture;	// Automatic average luminance texture\n\
		#endif\n\
	#else\n\
		uniform float		AverageLuminance;				// User set average luminance\n\
	#endif\n\
#endif\n\
#ifdef FS_BLOOM\n\
	uniform float			BloomFactor;					// Bloom factor\n\
	uniform float			BloomDownscale;					// Bloom downscale\n\
	uniform sampler2DRect	BloomTexture;					// Bloom texture\n\
#endif\n\
#ifdef FS_GAMMA_CORRECTION\n\
	uniform float			InvGamma;						// Inversed gamma correction value, must be >0\n\
#endif\n\
uniform sampler2DRect		HDRTexture;						// HDR texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	vec4 sample = texture2DRect(HDRTexture, VertexTexCoordVS.xy);\n\
\n\
	// Perform tone mapping\n\
#ifdef FS_TONE_MAPPING\n\
	// Convert RGB to luminance\n\
	float pixelLuminance = dot(sample.rgb, LuminanceConvert);\n\
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
	float keyOverLuminance = (averageLuminance > 0.0f) ? Key/averageLuminance : 0.0f;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 2\n\
	float scaledLuminance = keyOverLuminance*pixelLuminance;\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 4\n\
	scaledLuminance = (scaledLuminance*(1 + (scaledLuminance/pow(keyOverLuminance*WhiteLevel, 2)))) / (1 + scaledLuminance);\n\
\n\
	// Set LDR color\n\
	gl_FragColor = vec4(clamp(sample.rgb*scaledLuminance, 0.0f, 1.0f), sample.a);\n\
#else\n\
	// Just copy over the color\n\
	gl_FragColor = sample;\n\
#endif\n\
\n\
	// Add bloom\n\
#ifdef FS_BLOOM\n\
	gl_FragColor = clamp(gl_FragColor + texture2DRect(BloomTexture, VertexTexCoordVS.xy/BloomDownscale)*BloomFactor, 0.0f, 1.0f);\n\
#endif\n\
\n\
	// Perform gamma correction (linear space -> sRGB space)\n\
#ifdef FS_GAMMA_CORRECTION\n\
	gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3(InvGamma));\n\
#endif\n\
}";
