/*********************************************************\
 *  File: SPTriangleShaders_GLSL.cpp                     *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sVertexShaderSourceCodeGLSL = STRINGIFY(
// Attributes
attribute highp vec3 VertexPosition;	// Object space vertex position input
attribute highp vec4 VertexColor;		// Vertex color input
varying   highp vec4 VertexColorVS;		// Vertex color output

// Uniforms
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix
uniform highp vec4 Color;							// Object color

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1.0);

	// Pass through the vertex color
	VertexColorVS = VertexColor*Color;
}
);	// STRINGIFY


// GLSL (OpenGL 2.0 ("#version 110")) vertex shader source code, "#version" is added by hand - uniform buffer version
static const PLCore::String sVertexShaderSourceCodeGLSL_UniformBuffer =
// GLSL extensions
"#extension GL_ARB_uniform_buffer_object : enable\n"

STRINGIFY(
// Attributes
attribute highp vec3 VertexPosition;	// Object space vertex position input
attribute highp vec4 VertexColor;		// Vertex color input
varying   highp vec4 VertexColorVS;		// Vertex color output

// Uniforms
layout(std140) uniform UniformBlock
{
	highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix
	highp vec4 Color;							// Object color
};

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1.0);

	// Pass through the vertex color
	VertexColorVS = VertexColor*Color;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Geometry shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.0 ("#version 110")) geometry shader source code
static const PLCore::String sGeometryShaderSourceCodeGLSL =
// GLSL preprocessor directives
"#version 110\n"	// OpenGL 2.0

// GLSL extensions
"#extension GL_EXT_geometry_shader4 : enable\n"

STRINGIFY(
// Attributes
varying in  highp vec4 VertexColorVS[3];	// Interpolated vertex color input from vertex shader
varying out highp vec4 VertexColorGS;		// Interpolated vertex color output

// Programs
void main()
{
	// Pass-thru
	for (int i=0; i<gl_VerticesIn; i++) {
		gl_Position = gl_PositionIn[i];
		VertexColorGS = VertexColorVS[i];
		EmitVertex();
	}
	EndPrimitive();

	// Create a clone of the triangle with a shifted position and evil inverted colors
	for (int i=0; i<gl_VerticesIn; i++) {
		gl_Position = gl_PositionIn[i] + vec4(3.0, 2.0, 0.0, 0.0);
		VertexColorGS = 1.0 - VertexColorVS[i];
		EmitVertex();
	}
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sFragmentShaderSourceCodeGLSL = STRINGIFY(
// Attributes
varying highp vec4 VertexColorVS;	// Interpolated vertex color input from vertex shader

// Programs
void main()
{
	// Fragment color = interpolated vertex color
	gl_FragColor = VertexColorVS;
}
);	// STRINGIFY


// GLSL (OpenGL 2.0 ("#version 110")) fragment shader source code, "#version" is added by hand
static const PLCore::String sFragmentShaderSourceCodeGLSL_GS = STRINGIFY(
// Attributes
varying highp vec4 VertexColorGS;	// Interpolated vertex color input from geometry shader

// Programs
void main()
{
	// Fragment color = interpolated vertex color
	gl_FragColor = VertexColorGS;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
