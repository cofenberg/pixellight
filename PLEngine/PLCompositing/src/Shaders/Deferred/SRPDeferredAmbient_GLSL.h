/*********************************************************\
 *  File: SRPDeferredAmbient_GLSL.h                      *
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
\*********************************************************/


// GLSL vertex shader source code (the depreciated "attribute" and "varying" instead of "in" and "out" are used because some GPU drivers produced errors when using "in"/"out", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDeferredAmbient_GLSL_VS = "\
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


// GLSL fragment shader source code (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDeferredAmbient_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform lowp vec3		   AmbientColor;	// Ambient color\n\
uniform lowp sampler2DRect AlbedoMap;		// Albedo texture\n\
#ifdef FS_SELFILLUMINATION\n\
	uniform lowp sampler2DRect SelfIlluminationMap;	// Self illumination texture\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	lowp vec4 sample = texture2DRect(AlbedoMap, VertexTexCoordVS);\n\
\n\
	// Apply albedo and ambient color\n\
#ifdef FS_ALBEDO\n\
	gl_FragColor.rgb = sample.rgb*AmbientColor;\n\
#else\n\
	gl_FragColor.rgb = AmbientColor;\n\
#endif\n\
\n\
	// Apply ambient occlusion\n\
#ifdef FS_AMBIENTOCCLUSION\n\
	gl_FragColor.rgb *= sample.a;\n\
#endif\n\
\n\
	// Apply self illumination\n\
#ifdef FS_SELFILLUMINATION\n\
	gl_FragColor.rgb += texture2DRect(SelfIlluminationMap, VertexTexCoordVS).rgb;\n\
#endif\n\
\n\
	// Alpha is always 1\n\
	gl_FragColor.a = 1;\n\
}";
