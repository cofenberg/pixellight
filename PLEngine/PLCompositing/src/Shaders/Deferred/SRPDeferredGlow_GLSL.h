/*********************************************************\
 *  File: SRPDeferredGlow_GLSL.h                         *
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
static const PLGeneral::String sDeferredGlow_GLSL_VS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// Attributes\n\
highp  in vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
highp out vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
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


// Downscale GLSL fragment shader source code
static const PLGeneral::String sDeferredGlow_GLSL_FS_Downscale = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
highp in vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp sampler2DRect	Texture;	// Texture\n\
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
	// Downscale\n\
	gl_FragColor = vec4(0);\n\
	for (highp int i=0; i<16; i++)\n\
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]);\n\
	gl_FragColor = gl_FragColor*(1.0f/16.0f);\n\
}";


// Blur GLSL fragment shader source code
static const PLGeneral::String sDeferredGlow_GLSL_FS_Blur = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
highp in vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec2			UVScale;	// UV scale\n\
uniform highp sampler2DRect	Texture;	// Texture\n\
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
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]*UVScale)*Weights[i];\n\
}";


// Result GLSL fragment shader source code
static const PLGeneral::String sDeferredGlow_GLSL_FS_Result = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
highp in vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp float			GlowFactor;	// Glow factor\n\
uniform highp sampler2DRect	Texture;	// Texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	highp vec4 sample = texture2DRect(Texture, VertexTexCoordVS);\n\
\n\
	// Calculate the resulting glow\n\
	highp float glowFactor = sample.a*GlowFactor;\n\
	gl_FragColor = vec4(sample.rgb*glowFactor, glowFactor != 0);\n\
\n\
	// Use discard?\n\
#ifdef FS_DISCARD\n\
	if (gl_FragColor.a == 0 || (gl_FragColor.r == 0 && gl_FragColor.g == 0 && gl_FragColor.b == 0))\n\
		discard;\n\
#endif\n\
}";
