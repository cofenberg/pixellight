/*********************************************************\
 *  File: SRPDeferredSPAAO_GLSL.h                        *
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


// OpenGL 2.1 ("#version 120") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sDeferredSPAAO_GLSL_VS = "\
// Attributes\n\
attribute vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw;\n\
}";


// OpenGL 2.1 ("#version 120") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sDeferredSPAAO_GLSL_FS = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Uniforms\n\
uniform float			SampleRadius;		// The sampling radius\n\
uniform float			Intensity;			// The ambient occlusion intensity\n\
uniform float			Scale;				// Scales distance between occludes and occludee\n\
uniform float			Bias;				// Controls the width of the occlusion cone considered by the occludee\n\
uniform vec2			InvFocalLen;		// 1/FocalLen (for example: 0.57771897 x 0.4142136)\n\
uniform int				RandomSize;			// Resolution of the input random data (for example 64)\n\
uniform sampler2D		RandomNormalsMap;	// RG=normal vector, B=linear view space length\n\
uniform ivec2			Resolution;			// Resolution of the input texture data (for example 636 x 456)\n\
uniform sampler2DRect	NormalDepthMap;		// RG=normal vector, B=linear view space length\n\
\n\
// Programs\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
vec3 decodeNormalVector(vec2 normal)\n\
{\n\
	vec2 fenc = normal*4.0 - 2.0;\n\
	float f = dot(fenc, fenc);\n\
	float g = sqrt(1.0 - f/4.0);\n\
	vec3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1.0 - f/2.0;\n\
	return n;\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using given parameters\n\
vec3 uv_to_eye(vec2 uv, float eye_z, vec2 invFocalLen)\n\
{\n\
	// Convert from texture space [0,1] range into [-1,1] clip space\n\
	uv = uv*2.0 - 1.0;\n\
\n\
	// Reconstructs view-space position\n\
	return vec3(uv * invFocalLen * eye_z, eye_z);\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using a given texel\n\
vec3 fetch_eye_pos(sampler2DRect texture, ivec2 textureResolution, vec2 uv, vec2 invFocalLen)\n\
{\n\
	// Fetch the linear view space depth at the given texel position\n\
	float eye_z = texture2DRect(texture, uv*vec2(textureResolution)).b;\n\
\n\
	// Reconstructs view-space position using given parameters\n\
	return uv_to_eye(uv, eye_z, invFocalLen);\n\
}\n\
\n\
// AO calculation\n\
float doAmbientOcclusion(vec2 tcoord, vec2 uv, vec3 p, vec3 cnorm)\n\
{\n\
	vec3 diff = fetch_eye_pos(NormalDepthMap, Resolution, tcoord + uv, InvFocalLen) - p;\n\
	vec3 v = normalize(diff);\n\
	float d = length(diff)*Scale;\n\
	return max(0.0, dot(cnorm, v) - Bias)*(1.0/(1.0 + d))*Intensity;\n\
}\n\
\n\
\n\
const vec2 vec[4] = vec2[4](\n\
	vec2( 1.0,  0.0),\n\
	vec2(-1.0,  0.0),\n\
	vec2( 0.0,  1.0),\n\
	vec2( 0.0, -1.0)\n\
);\n\
\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	vec4 sample = texture2DRect(NormalDepthMap, VertexTexCoordVS*vec2(Resolution));\n\
\n\
	// Reconstruct view-space position\n\
	vec3 p = uv_to_eye(VertexTexCoordVS, sample.b, InvFocalLen);\n\
\n\
	// Reconstruct view-space normal vector\n\
	vec3 n = decodeNormalVector(sample.rg);\n\
	n.z = -n.z; // If this is not done, we get wrong results\n\
\n\
	// Locals\n\
	vec2 rand = normalize(texture2D(RandomNormalsMap, vec2(Resolution)*VertexTexCoordVS/float(RandomSize)).xy*2.0 - 1.0);	// Returns a random normal vector\n\
	float ao = 0.0;\n\
	float rad = SampleRadius/p.z;\n\
\n\
	// SSAO calculation\n\
	int iterations = 4;\n\
	for (int j=0; j<iterations; j++) {\n\
		vec2 coord1 = reflect(vec[j], rand)*rad;\n\
		vec2 coord2 = vec2(coord1.x*0.707 - coord1.y*0.707, coord1.x*0.707 + coord1.y*0.707);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord1*0.25, p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord2*0.5,  p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord1*0.75, p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord2,      p, n);\n\
	}\n\
	ao /= float(iterations)*4.0;\n\
	ao = 1.0 - clamp(ao, 0.0, 1.0);\n\
	gl_FragColor = vec4(ao, ao, ao, ao);\n\
}";
