/*********************************************************\
 *  File: SPTriangleShaders_GLSL.cpp                     *
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


// GLSL vertex shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sVertexShaderSourceCodeGLSL = "\
// Attributes\n\
attribute highp vec3 VertexPosition;	// Object space vertex position input\n\
attribute lowp  vec4 VertexColor;		// Vertex color input\n\
varying   lowp  vec4 VertexColorVS;		// Vertex color output\n\
\n\
// Uniforms\n\
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1);\n\
\n\
	// Pass through the vertex color\n\
	VertexColorVS = VertexColor;\n\
}";


// GLSL geometry shader source code
static const PLGeneral::String sGeometryShaderSourceCodeGLSL = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_EXT_geometry_shader4 : enable\n\
\n\
// Attributes\n\
in  vec4 VertexColorVS[];	// Interpolated vertex color input from vertex shader\n\
out vec4 VertexColorGS;		// Interpolated vertex color output\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Pass-thru\n\
	for (int i=0; i<gl_VerticesIn; i++) {\n\
		gl_Position = gl_PositionIn[i];\n\
		VertexColorGS = VertexColorVS[i];\n\
		EmitVertex();\n\
	}\n\
	EndPrimitive();\n\
\n\
	// Create a clone of the triangle with a shifted position and evil inverted colors\n\
	for (int i=0; i<gl_VerticesIn; i++) {\n\
		gl_Position = gl_PositionIn[i] + vec4(3, 2, 0, 0);\n\
		VertexColorGS = 1 - VertexColorVS[i];\n\
		EmitVertex();\n\
	}\n\
}";


// GLSL fragment shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sFragmentShaderSourceCodeGLSL = "\
// Attributes\n\
varying lowp vec4 VertexColorVS;	// Interpolated vertex color input from vertex shader\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fragment color = interpolated vertex color\n\
	gl_FragColor = VertexColorVS;\n\
}";
static const PLGeneral::String sFragmentShaderSourceCodeGLSL_GS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// Attributes\n\
in vec4 VertexColorGS;	// Interpolated vertex color input from geometry shader\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fragment color = interpolated vertex color\n\
	gl_FragColor = VertexColorGS;\n\
}";
