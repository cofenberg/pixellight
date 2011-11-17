/*********************************************************\
 *  File: SPMultiViewShaders_GLSL.h                      *
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sVertexShaderSourceCodeGLSL = STRINGIFY(
// Attributes
attribute highp vec4 VertexPosition;	// Object space vertex position input
attribute highp vec3 VertexNormal;		// Object space vertex normal input
varying   highp vec3 VertexNormalVS;	// World space vertex normal output

// Uniforms
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix
uniform highp mat4 ObjectSpaceToWorldSpaceMatrix;	// Object space to world space matrix

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;

	// Calculate the world space vertex normal
	VertexNormalVS = mat3(ObjectSpaceToWorldSpaceMatrix)*VertexNormal;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sFragmentShaderSourceCodeGLSL = STRINGIFY(
// Attributes
varying highp vec3 VertexNormalVS;	// World space vertex normal input from vertex shader

// Uniforms
uniform highp vec3 LightDirection;	// World space light direction

// Programs
void main()
{
	// Set fragment color by using primitive directional lighting
	lowp float intensity = clamp(dot(LightDirection, VertexNormalVS), 0.0, 1.0);
	gl_FragColor = vec4(intensity, intensity, intensity, intensity);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
