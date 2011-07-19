/*********************************************************\
 *  File: SRPShadowMapping_GLSL.h                        *
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


// OpenGL 2.0 ("#version 110") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sSRPShadowMapping_GLSL_VS = "\
// Attributes\n\
attribute vec4 VertexPosition;		// Object space vertex position input\n\
varying   vec3 LightVecVS;\n\
#ifdef VS_TEXCOORD0\n\
	varying vec2 VertexTexCoord0;	// Vertex texture coordinate 0 input\n\
	varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
#endif\n\
\n\
// Uniforms\n\
uniform mat4  WorldVP;		// World view projection matrix\n\
uniform mat4  WorldV;		// World view matrix\n\
uniform float InvRadius;	// World space inverse light radius\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Transform vertex to clip space, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = WorldVP*VertexPosition;\n\
\n\
	// Calculate the world space light vector (the light position is the origin)\n\
	LightVecVS = -InvRadius*(WorldV*VertexPosition).xyz;\n\
\n\
#ifdef VS_DIFFUSEMAP\n\
	// Pass through the vertex texture coordinate 0\n\
	VertexTexCoordVS = VertexTexCoord0;\n\
#endif\n\
}";


// OpenGL 2.0 ("#version 110") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sSRPShadowMapping_GLSL_FS = "\
// Attributes\n\
varying vec3 LightVecVS;\n\
#ifdef FS_ALPHATEST\n\
	varying vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
#endif\n\
\n\
// Uniforms\n\
#ifdef FS_ALPHATEST\n\
	uniform sampler2D DiffuseMap;\n\
	uniform float    AlphaReference;\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	#ifdef FS_ALPHATEST\n\
		// Fetch the required texel data\n\
		vec4 sample = texture2D(DiffuseMap, VertexTexCoordVS);\n\
\n\
		// Perform an alpha test to discard fragments\n\
		if (sample.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
\n\
	// + '0.005' => Set polygon offset to avoid nasty shadow artefacts\n\
	vec4 pack = vec4(1.0, 256.0, 65536.0, 16777216.0);\n\
	gl_FragColor = pack * (length(LightVecVS) + 0.005);\n\
}";
