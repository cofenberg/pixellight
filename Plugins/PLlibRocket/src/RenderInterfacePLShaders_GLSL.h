/*********************************************************\
 *  File: RenderInterfacePLShaders_GLSL.h                *
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


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLCore::String sVertexShaderSourceCodeGLSL = "\
// Attributes\n\
attribute mediump vec2 VertexPosition;		// Window space vertex position input\n\
attribute lowp    vec2 VertexTexCoord;		// Vertex texture coordinate input\n\
varying   lowp    vec2 VertexTexCoordVS;	// Vertex texture coordinate output\n\
attribute lowp    vec4 VertexColor;			// Vertex color input\n\
varying   lowp    vec4 VertexColorVS;		// Vertex color output\n\
\n\
// Uniforms\n\
uniform mediump vec2 Translation;	// Window space translation\n\
uniform mediump vec2 WindowSizeInv;	// 1/(window size)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position    = vec4(VertexPosition + Translation, 0.0, 1.0);\n\
	gl_Position.xy *= WindowSizeInv;		// Change into 0..1 range\n\
	gl_Position.y   = 1.0 - gl_Position.y;	// Flip y axis\n\
	gl_Position.xy  = gl_Position.xy*2.0 - 1.0;	// Change into -1..1 range\n\
\n\
	// Pass through the vertex texture coordinate\n\
	VertexTexCoordVS = VertexTexCoord;\n\
\n\
	// Pass through the vertex color\n\
	VertexColorVS = VertexColor;\n\
}";


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand (the depreciated "attribute" and "varying" instead of "in" and "out" are used because we want to stay compatible to OpenGL ES 2.0)
static const PLCore::String sFragmentShaderSourceCodeGLSL = "\
// Attributes\n\
varying lowp vec2 VertexTexCoordVS;	// Interpolated vertex texture coordinate input from vertex shader\n\
varying lowp vec4 VertexColorVS;	// Interpolated vertex color input from vertex shader\n\
\n\
// Uniforms\n\
uniform lowp sampler2D TextureMap;	// Texture map\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fragment color = fetched interpolated texel color\n\
	gl_FragColor = texture2D(TextureMap, VertexTexCoordVS)*VertexColorVS;\n\
\n\
	// Perform an alpha test to discard fragments - Reject pixels with an alpha of <=0\n\
	if (gl_FragColor.a <= 0.0)\n\
		discard; // Throw the fragment away and don't draw it!\n\
}";
