/*********************************************************\
 *  File: SRPDeferredVolumetricFog_GLSL.h                *
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


// OpenGL 3.0 ("#version 130") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLGeneral::String sDeferredVolumetricFog_GLSL_VS = "\
// Attributes\n\
in  vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
							// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
out vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw;\n\
}";


// OpenGL 3.0 ("#version 130") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLGeneral::String sDeferredVolumetricFog_GLSL_FS = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
in vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Uniforms\n\
uniform vec3           FogPosition;		// View space fog position\n\
uniform float          FogInvRadius;	// View space fog inverse radius\n\
uniform vec3           FogColor0;\n\
uniform vec3           FogColor1;\n\
uniform vec2           InvFocalLen;		// 1/FocalLen (for example: 0.57771897 x 0.4142136)\n\
uniform ivec2          Resolution;		// Resolution of the input texture data (for example 636 x 456)\n\
uniform sampler2DRect  NormalDepthMap;	// Normal depth texture\n\
\n\
// Programs\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
vec3 decodeNormalVector(vec2 normal)\n\
{\n\
	vec2 fenc = normal*4 - 2;\n\
	float f = dot(fenc, fenc);\n\
	float g = sqrt(1 - f/4);\n\
	vec3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using given parameters\n\
vec3 uv_to_eye(vec2 uv, float eye_z, vec2 invFocalLen)\n\
{\n\
	// Convert from texture space [0,1] range into [-1,1] clip space\n\
	uv = uv*2 - 1;\n\
\n\
	// Reconstructs view-space position\n\
	return vec3(uv * invFocalLen * eye_z, eye_z);\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using a given texel\n\
vec3 fetch_eye_pos(sampler2DRect texture, ivec2 textureResolution, vec2 uv, vec2 invFocalLen)\n\
{\n\
	// Fetch the linear view space depth at the given texel position\n\
	float eye_z = texture2DRect(texture, uv*textureResolution).b;\n\
\n\
	// Reconstructs view-space position using given parameters\n\
	return uv_to_eye(uv, eye_z, invFocalLen);\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	// Get the current view space position\n\
	vec3 viewSpacePos = fetch_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS, InvFocalLen);\n\
	viewSpacePos.z = -viewSpacePos.z;\n\
\n\
	// Calculate the fog factor\n\
	vec3 fogPosition = (FogPosition - viewSpacePos)*FogInvRadius;\n\
	viewSpacePos = -viewSpacePos*FogInvRadius;\n\
	float k  = clamp(dot(fogPosition, viewSpacePos)/dot(viewSpacePos, viewSpacePos), 0.0f, 1.0f);\n\
	vec4  pl = vec4(k*viewSpacePos - fogPosition, 1.0f);\n\
	gl_FragColor.rgb = clamp(FogColor0/dot(pl, pl) - FogColor1, 0.0f, 1.0f);\n\
	gl_FragColor.a = 1.0f;\n\
}";
