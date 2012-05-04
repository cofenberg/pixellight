/*********************************************************\
 *  File: SRPDebugWireframesShaders_GLSL.h               *
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


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sDebugWireframes_GLSL_VS = STRINGIFY(
// Attributes
attribute highp vec4 VertexPosition;	// Object space vertex position input

// Uniforms
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;
}
);	// STRINGIFY


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sDebugWireframes_GLSL_FS = STRINGIFY(
// Uniforms
uniform lowp vec4 Color;	// Color

// Programs
void main()
{
	// Just set the output color
	gl_FragColor = Color;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
