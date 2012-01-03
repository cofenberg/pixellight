/*********************************************************\
 *  File: SRPDeferredGlow_GLSL.h                         *
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


// GLSL vertex shader source code
static const PLCore::String sDeferredGlow_GLSL_VS = "\
// GLSL preprocessor directives\n\
#version 120	// OpenGL 2.1\n\
\n\
// Attributes\n\
attribute vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform ivec2 TextureSize;	// Texture size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*vec2(TextureSize);\n\
}";


// Downscale GLSL fragment shader source code
static const PLCore::String sDeferredGlow_GLSL_FS_Downscale = "\
// GLSL preprocessor directives\n\
#version 120	// OpenGL 2.1\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform sampler2DRect	Texture;	// Texture\n\
\n\
// Neighbor offset table\n\
const vec2 Offsets[16] = vec2[16](\n\
	vec2( 1.5, -1.5), // 0\n\
	vec2( 1.5, -0.5), // 1\n\
	vec2( 1.5,  0.5), // 2\n\
	vec2( 1.5,  1.5), // 3\n\
	vec2( 0.5, -1.5), // 4\n\
	vec2( 0.5, -0.5), // 5\n\
	vec2( 0.5,  0.5), // 6\n\
	vec2( 0.5,  1.5), // 7\n\
	vec2(-0.5, -1.5), // 8\n\
	vec2(-0.5, -0.5), // 9\n\
	vec2(-0.5,  0.5), // 10\n\
	vec2(-0.5,  1.5), // 11\n\
	vec2(-1.5, -1.5), // 12\n\
	vec2(-1.5, -0.5), // 13\n\
	vec2(-1.5,  0.5), // 14\n\
	vec2(-1.5,  1.5)  // 15\n\
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Downscale\n\
	gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n\
	for (int i=0; i<16; i++)\n\
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]);\n\
	gl_FragColor = gl_FragColor*(1.0/16.0);\n\
}";


// Blur GLSL fragment shader source code
static const PLCore::String sDeferredGlow_GLSL_FS_Blur = "\
// GLSL preprocessor directives\n\
#version 120	// OpenGL 2.1\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform vec2			UVScale;	// UV scale\n\
uniform sampler2DRect	Texture;	// Texture\n\
\n\
// Neighbor offset table\n\
const vec2 Offsets[13] = vec2[13](\n\
	vec2( 6.0,  6.0), // 0\n\
	vec2( 5.0,  5.0), // 1\n\
	vec2( 4.0,  4.0), // 2\n\
	vec2( 3.0,  3.0), // 3\n\
	vec2( 2.0,  2.0), // 4\n\
	vec2( 1.0,  1.0), // 5\n\
	vec2( 0.0,  0.0), // 6\n\
	vec2(-1.0, -1.0), // 7\n\
	vec2(-2.0, -2.0), // 8\n\
	vec2(-3.0, -3.0), // 9\n\
	vec2(-4.0, -4.0), // 10\n\
	vec2(-5.0, -5.0), // 11\n\
	vec2(-6.0, -6.0)  // 12\n\
);\n\
const float Weights[13] = float[13](\n\
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
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n\
	for (int i=0; i<13; i++)\n\
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]*UVScale)*Weights[i];\n\
}";


// Result GLSL fragment shader source code, "#version" is added by hand
static const PLCore::String sDeferredGlow_GLSL_FS_Result = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform float			GlowFactor;	// Glow factor\n\
uniform sampler2DRect	Texture;	// Texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	vec4 sample = texture2DRect(Texture, VertexTexCoordVS);\n\
\n\
	// Calculate the resulting glow\n\
	float glowFactor = sample.a*GlowFactor;\n\
	gl_FragColor = vec4(sample.rgb*glowFactor, glowFactor != 0.0);\n\
\n\
	// Use discard?\n\
#ifdef FS_DISCARD\n\
	if (gl_FragColor.a == 0.0 || (gl_FragColor.r == 0.0 && gl_FragColor.g == 0.0 && gl_FragColor.b == 0.0))\n\
		discard;\n\
#endif\n\
}";
