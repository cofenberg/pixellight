/*********************************************************\
 *  File: SRPDeferredGBufferDebug_GLSL.h                 *
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
static const PLGeneral::String sDeferredGBufferDebug_GLSL_VS = "\
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
static const PLGeneral::String sDeferredGBufferDebug_GLSL_FS = "\
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
uniform highp float			NearPlane;	// Camera near plane distance\n\
uniform highp float			Range;		// Distance between camera far and new plane (never 0!)\n\
uniform highp sampler2DRect Map;		// Input texture containing the data to visualize\n\
\n\
// Programs\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
highp vec3 decodeNormalVector(highp vec2 normal)\n\
{\n\
	highp vec2 fenc = normal*4 - 2;\n\
	highp float f = dot(fenc, fenc);\n\
	highp float g = sqrt(1 - f/4);\n\
	highp vec3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	// Fetch the required texel data and set the RGB output color\n\
#ifdef FS_SHOW_BLACK\n\
	gl_FragColor.rgb = 0;\n\
#elif defined FS_SHOW_ALBEDO\n\
	gl_FragColor.rgb = texture2DRect(Map, VertexTexCoordVS).rgb;\n\
#elif defined FS_SHOW_AMBIENTOCCLUSION\n\
	gl_FragColor.rgb = texture2DRect(Map, VertexTexCoordVS).aaa;\n\
#elif defined FS_SHOW_NORMALS\n\
	gl_FragColor.rgb = decodeNormalVector(texture2DRect(Map, VertexTexCoordVS).rg);\n\
#elif defined FS_SHOW_DEPTH\n\
	// Normalized the linear view space depth, else we can't inspect the depth properly\n\
	gl_FragColor.rgb = vec3((texture2DRect(Map, VertexTexCoordVS).b - NearPlane)/Range);\n\
#elif defined FS_SHOW_SPECULAR_COLOR\n\
	gl_FragColor.rgb = texture2DRect(Map, VertexTexCoordVS).rgb;\n\
#elif defined FS_SHOW_SPECULAR_EXPONENT\n\
	gl_FragColor.rgb = vec3(texture2DRect(Map, VertexTexCoordVS).a/128);\n\
#elif defined FS_SHOW_SELFILLUMINATION\n\
	gl_FragColor.rgb = texture2DRect(Map, VertexTexCoordVS).rgb;\n\
#elif defined FS_SHOW_GLOW\n\
	gl_FragColor.rgb = texture2DRect(Map, VertexTexCoordVS).aaa;\n\
#else\n\
	// Invalid state, should never ever happen!\n\
	gl_FragColor.rgb = 0;\n\
#endif\n\
\n\
	// Alpha is always 1\n\
	gl_FragColor.a = 1;\n\
}";
