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


// GLSL vertex shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sVertexShaderSourceCodeGLSL = "\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Object space vertex position input\n\
attribute highp vec3 VertexNormal;		// Object space vertex normal input\n\
varying   highp vec3 VertexNormalVS;	// World space vertex normal output\n\
\n\
// Uniforms\n\
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix\n\
uniform highp mat4 ObjectSpaceToWorldSpaceMatrix;	// Object space to world space matrix\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;\n\
\n\
	// Calculate the world space vertex normal\n\
	VertexNormalVS = mat3(ObjectSpaceToWorldSpaceMatrix)*VertexNormal;\n\
}";


// GLSL fragment shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sFragmentShaderSourceCodeGLSL = "\
// Attributes\n\
varying highp vec3 VertexNormalVS;	// World space vertex normal input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec3 LightDirection;	// World space light direction\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set fragment color by using primitiv directional lighting\n\
	lowp float intensity = clamp(dot(LightDirection, VertexNormalVS), 0.0f, 1.0f);\n\
	gl_FragColor = vec4(intensity, intensity, intensity, intensity);\n\
}";
