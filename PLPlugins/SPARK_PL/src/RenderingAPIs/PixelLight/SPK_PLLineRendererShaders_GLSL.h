/*********************************************************\
 *  File: SPK_PLLineRendererShaders_GLSL.h               *
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


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLGeneral::String sSPK_PLLineRendererShaders_GLSL_VS = "\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Object space vertex position input\n\
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
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;\n\
\n\
	// Pass through the vertex color\n\
	VertexColorVS = VertexColor;\n\
}";


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLGeneral::String sSPK_PLLineRendererShaders_GLSL_FS = "\
// Attributes\n\
varying vec4 VertexColorVS;	// Interpolated vertex color input from vertex shader\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Just set the output color\n\
	gl_FragColor = VertexColorVS;\n\
}";
