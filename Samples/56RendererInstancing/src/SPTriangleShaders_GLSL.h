/*********************************************************\
 *  File: SPTriangleShaders_GLSL.cpp                     *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
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
// -> Version without hardware supported geometric primitive instancing
static const PLCore::String sVertexShaderSourceCodeGLSL = STRINGIFY(
// Attributes
attribute highp vec3 VertexPosition;	// Object space vertex position input
attribute highp vec4 VertexColor;		// Vertex color input
varying   highp vec4 VertexColorVS;		// Vertex color output

// Uniforms
uniform highp int  InstanceID;						// Integer instance ID of the primitive within the current batch
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	// -> Add an offset per geometric primitive instance
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition + vec3(InstanceID*0.1, 0.0, InstanceID*0.01), 1.0);

	// Pass through the vertex color
	VertexColorVS = VertexColor*vec4(0.2, 1.0, 1.0, 1.0);
}
);	// STRINGIFY


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
// -> Version with hardware supported geometric primitive instancing
static const PLCore::String sVertexShaderSourceCodeGLSL_Instanced = STRINGIFY(
// Attributes
attribute highp vec3 VertexPosition;	// Object space vertex position input
attribute highp vec4 VertexColor;		// Vertex color input
varying   highp vec4 VertexColorVS;		// Vertex color output

// Uniforms
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	// -> Add an offset per geometric primitive instance
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition + vec3(float(gl_InstanceID)*0.1, 0.0, float(gl_InstanceID)*0.01), 1.0);

	// Pass through the vertex color
	VertexColorVS = VertexColor*vec4(0.2, 1.0, 1.0, 1.0);
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


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
