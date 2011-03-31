/*********************************************************\
 *  File: SRPDiffuseOnlyShaders_GLSL.h                   *
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


// GLSL vertex shader source code (the depreciated "attribute" and "varying" instead of "in" and "out" are used because some GPU drivers produced errors when using "in"/"out", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDiffuseOnly_GLSL_VS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;		// Object space vertex position input\n\
#ifdef VS_TEXCOORD0\n\
	attribute highp vec2 VertexTexCoord0;	// Vertex texture coordinate 0 input\n\
	varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
#endif\n\
\n\
// Uniforms\n\
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;\n\
\n\
#ifdef VS_TEXCOORD0\n\
	// Pass through the vertex texture coordinate 0\n\
	VertexTexCoordVS = VertexTexCoord0;\n\
#endif\n\
}";


// GLSL fragment shader source code (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDiffuseOnly_GLSL_FS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// Attributes\n\
#ifdef FS_DIFFUSEMAP\n\
	varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
#endif\n\
\n\
// Uniforms\n\
uniform lowp vec4 DiffuseColor;	// Alpha stores the opacity\n\
#ifdef FS_DIFFUSEMAP\n\
	uniform lowp sampler2D DiffuseMap;\n\
	#ifdef FS_ALPHATEST\n\
		uniform lowp float AlphaReference;\n\
	#endif\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
#ifdef FS_DIFFUSEMAP\n\
	gl_FragColor = texture2D(DiffuseMap, VertexTexCoordVS);\n\
	#ifdef FS_ALPHATEST\n\
		// Perform an alpha test to discard fragments\n\
		if (gl_FragColor.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
	#ifdef FS_GAMMACORRECTION\n\
		gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3(2.2f, 2.2f, 2.2f));	// Perform sRGB to linear space conversion (gamma correction)\n\
	#endif\n\
	gl_FragColor *= DiffuseColor;\n\
#else\n\
	gl_FragColor = DiffuseColor;\n\
#endif\n\
}";
