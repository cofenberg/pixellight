/*********************************************************\
 *  File: SPRTTShaders_GLSL.h                            *
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
static const PLCore::String sVertexShaderSourceCodeGLSL = STRINGIFY(
// Attributes
attribute highp vec3 VertexPosition;			// Object space vertex position input
attribute highp vec2 VertexTextureCoordinate;	// Vertex texture coordinate input
varying   highp vec2 VertexTextureCoordinateVS;	// Vertex texture coordinate output
attribute lowp  vec4 VertexColor;				// Vertex color input
varying   lowp  vec4 VertexColorVS;				// Vertex color output

// Uniforms
uniform highp mat4  ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix
uniform highp float ColorFactor;					// Color factor

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1.0);

	// Pass through the texture coordinate
	VertexTextureCoordinateVS = VertexTextureCoordinate;

	// Write out the vertex color
	VertexColorVS = mix(vec4(1.0, 1.0, 1.0, 1.0), VertexColor, ColorFactor);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sFragmentShaderSourceCodeGLSL = STRINGIFY(
// Attributes
varying highp vec2 VertexTextureCoordinateVS;	// Vertex texture coordinate input from vertex shader
varying lowp  vec4 VertexColorVS;				// Vertex color input from vertex shader

// Uniforms
uniform lowp sampler2D DiffuseMap;	// Diffuse map

// Programs
void main()
{
	// Set fragment color
	gl_FragColor = texture2D(DiffuseMap, VertexTextureCoordinateVS)*VertexColorVS;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Scene program - Vertex shader source code             ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sSceneVertexShaderSourceCodeGLSL = STRINGIFY(
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
//[ Scene program - Fragment shader source code           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sSceneFragmentShaderSourceCodeGLSL = "\
// Attributes\n\
varying highp vec3 VertexNormalVS;	// World space vertex normal input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec3 LightDirection;	// World space light direction\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set fragment color by using primitive directional lighting\n\
	lowp float intensity = clamp(dot(LightDirection, VertexNormalVS), 0.0, 1.0);\n\
	gl_FragData[0] = vec4(intensity, intensity, intensity, intensity);\n\
\n\
	// Color 1 only red component\n\
	#ifdef MRT_1\n\
		gl_FragData[1] = vec4(1.0, 0.0, 0.0, 0.0);\n\
	#endif\n\
\n\
	// Color 2 only green component\n\
	#ifdef MRT_2\n\
		gl_FragData[2] = vec4(0.0, 1.0, 0.0, 0.0);\n\
	#endif\n\
\n\
	// Color 3 only blue component\n\
	#ifdef MRT_3\n\
		gl_FragData[3] = vec4(0.0, 0.0, 1.0, 0.0);\n\
	#endif\n\
}";


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
