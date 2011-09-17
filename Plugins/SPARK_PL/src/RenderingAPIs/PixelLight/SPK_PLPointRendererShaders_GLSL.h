/*********************************************************\
 *  File: SPK_PLPointRendererShaders_GLSL.h              *
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
