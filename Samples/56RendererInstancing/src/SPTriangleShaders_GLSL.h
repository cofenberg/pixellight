/*********************************************************\
 *  File: SPTriangleShaders_GLSL.cpp                     *
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
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition + vec3(gl_InstanceID*0.1, 0.0, gl_InstanceID*0.01), 1.0);

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
