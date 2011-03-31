/*********************************************************\
 *  File: SRPDeferredDepthFog_GLSL.h                     *
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
static const PLGeneral::String sDeferredDepthFog_GLSL_VS = "\
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


// GLSL fragment shader source code
static const PLGeneral::String sDeferredDepthFog_GLSL_FS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
highp in vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp float FarPlane;				// Far clipping plane (never 0!)\n\
uniform lowp  vec4  FogColor;				// Fog color\n\
#ifdef FS_LINEAR_MODE\n\
	uniform highp float	FogEnd;				// Fog end\n\
	uniform highp float	FogRange;			// Fog end - fog start (never 0!)\n\
#else\n\
	uniform highp float FogDensity;			// Fog density\n\
#endif\n\
uniform highp sampler2DRect NormalDepthMap;	// Normal depth texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Get the depth\n\
	highp float depth = texture2DRect(NormalDepthMap, VertexTexCoordVS).b/FarPlane;\n\
\n\
	// Calculate the fog intensity [0...1] = [full fog...no fog]\n\
	#define E 2.71828 // Natural logarithm\n\
#ifdef FS_LINEAR_MODE\n\
	highp float fogFactor = (FogEnd - depth)/FogRange;\n\
#elif defined FS_EXPONENTIAL_MODE\n\
	// The pow parameters are safe, so no NAN can be produced in here\n\
	highp float fogFactor = 1/pow(E, depth*FogDensity);\n\
#elif defined FS_EXPONENTIAL2_MODE\n\
	// The pow parameters are safe, so no NAN can be produced in here\n\
	highp float fogFactor = 1/pow(E, depth*depth*FogDensity*FogDensity);\n\
#else\n\
	highp float fogFactor = 0;\n\
#endif\n\
\n\
	// Apply the fog color\n\
	gl_FragColor = (1 - clamp(fogFactor, 0.0f, 1.0f))*FogColor;\n\
}";
