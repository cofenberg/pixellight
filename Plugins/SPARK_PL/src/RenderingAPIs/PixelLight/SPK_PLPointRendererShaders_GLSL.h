/*********************************************************\
 *  File: SPK_PLPointRendererShaders_GLSL.h              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sSPK_PLPointRendererShaders_GLSL_VS = "\
// Attributes\n\
attribute mediump vec3 VertexPosition;	// Object space vertex position input\n\
attribute lowp    vec4 VertexColor;		// Vertex color input\n\
varying   lowp    vec4 VertexColorVS;	// Vertex color output\n\
\n\
// Uniforms\n\
uniform mediump mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix\n\
uniform mediump vec4 PointParameters;				// Point parameters: point size, point scale a, point scale b, point scale c \n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1.0);\n\
\n\
	// Calculate the point size (formulas from http://www.opengl.org/registry/specs/ARB/point_parameters.txt)\n\
	mediump float distance = -gl_Position.z;\n\
	//            dist_atten = 1  /(a                 + b*distance                 + c*distance*distance)\n\
	mediump float dist_atten = 1.0/(PointParameters.y + PointParameters.z*distance + PointParameters.w*distance*distance);\n\
	// derived_size = Clamp(size * sqrt(dist_atten(dist)))\n\
	gl_PointSize    = clamp(PointParameters.x*sqrt(dist_atten), 1.0, 1024.0);\n\
\n\
	// Pass through the vertex color\n\
	VertexColorVS = VertexColor;\n\
}";


// GLSL (OpenGL 2.1 ("#version 120") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sSPK_PLPointRendererShaders_GLSL_FS = "\
// Attributes\n\
varying lowp vec4 VertexColorVS;	// Interpolated vertex color input from vertex shader\n\
\n\
// Uniforms\n\
uniform lowp sampler2D TextureMap;	// Texture map\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fragment color = fetched interpolated texel color multiplicated with the per vertex color\n\
	gl_FragColor = texture2D(TextureMap, gl_PointCoord)*VertexColorVS;\n\
}";
