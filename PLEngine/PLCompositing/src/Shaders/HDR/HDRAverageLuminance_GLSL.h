/*********************************************************\
 *  File: HDRAverageLuminance_GLSL.h                     *
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


// GLSL vertex shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;	// Texture size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*TextureSize;\n\
}";


// Downsample GLSL vertex shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_VS_Downsample = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;	// Texture size in texel\n\
uniform highp vec2  Size;			// Size [0..1]\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Convert the incoming clip space vertex position from [-1..1] to [0..1]\n\
	vec2 position = (VertexPosition.xy + vec2(1))*vec2(0.5f);\n\
\n\
	// Apply size\n\
	position *= Size;\n\
\n\
	// Write out the vertex position in clip space\n\
	gl_Position = vec4(position*vec2(2) - vec2(1), 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*TextureSize;\n\
}";


// Common GLSL fragment shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_FS_Common = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp sampler2DRect	Texture;	// HDR texture\n\
\n\
// Neighbor offset table\n\
const highp vec2 Offsets[4] = highp vec2[4](\n\
	vec2( 0,  0), // Center       0\n\
	vec2( 1,  0), // Right        1\n\
	vec2( 1,  1), // Bottom right 2\n\
	vec2( 0,  1)  // Bottom       3\n\
);\n";


// Downsample log GLSL fragment shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_FS_DownsampleLog = "\
// Uniforms\n\
uniform highp vec3	LuminanceConvert;	// Convert RGB to luminance\n\
uniform highp float	Epsilon;			// A small value to avoid undefined log(0)\n\
\n\
// Downsample log main function\n\
void main()\n\
{\n\
	// 'Photographic Tone Reproduction for Digital Images': Formula 1\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++) {\n\
		// If, for any reason, there's an invalid value it would mess up everything... so, security is really a must have in here!\n\
		float value = log(dot(texture2DRect(Texture, VertexTexCoordVS + Offsets[i]).rgb, LuminanceConvert) + Epsilon);\n\
		if (!isnan(value))\n\
			luminance += value;\n\
	}\n\
\n\
	// Write down the result\n\
	gl_FragColor = vec4(luminance*0.25f);\n\
}";


// Downsample GLSL fragment shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_FS_Downsample = "\
// Downsample main function\n\
void main()\n\
{\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++)\n\
		luminance += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]).r;\n\
	gl_FragColor = vec4(luminance*0.25f);\n\
}";


// Downsample exp GLSL fragment shader source code
static const PLGeneral::String sHDRAverageLuminance_GLSL_FS_DownsampleExp = "\
// Downsample exp main function\n\
void main()\n\
{\n\
	float luminance = 0;\n\
	for (int i=0; i<4; i++)\n\
		luminance += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]).r;\n\
	gl_FragColor = vec4(exp(luminance*0.25f));\n\
}";
