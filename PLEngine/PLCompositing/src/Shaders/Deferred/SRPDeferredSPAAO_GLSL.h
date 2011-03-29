/*********************************************************\
 *  File: SRPDeferredSPAAO_GLSL.h                        *
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


// GLSL vertex shader source code
static const PLGeneral::String sDeferredSPAAO_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw;\n\
}";


// GLSL fragment shader source code (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDeferredSPAAO_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader, lower/left is (0,0) and upper/right is (1,1)\n\
\n\
// Uniforms\n\
uniform highp float			SampleRadius;		// The sampling radius\n\
uniform highp float			Intensity;			// The ambient occlusion intensity\n\
uniform highp float			Scale;				// Scales distance between occluders and occludee\n\
uniform highp float			Bias;				// Controls the width of the occlusion cone considered by the occludee\n\
uniform highp vec2			InvFocalLen;		// 1/FocalLen (for example: 0.57771897 x 0.4142136)\n\
uniform highp int			RandomSize;			// Resolution of the input random data (for example 64)\n\
uniform highp sampler2D		RandomNormalsMap;	// RG=normal vector, B=linear view space length\n\
uniform highp ivec2			Resolution;			// Resolution of the input texture data (for example 636 x 456)\n\
uniform highp sampler2DRect	NormalDepthMap;		// RG=normal vector, B=linear view space length\n\
\n\
// Programs\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
highp vec3 decodeNormalVector(highp vec2 normal)\n\
{\n\
	highp vec2 fenc = normal*4 - 2;\n\
	highp float f = dot(fenc, fenc);\n\
	highp float g = sqrt(1 - f/4);\n\
	highp vec3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using given parameters\n\
highp vec3 uv_to_eye(highp vec2 uv, highp float eye_z, highp vec2 invFocalLen)\n\
{\n\
	// Convert from texture space [0,1] range into [-1,1] clip space\n\
	uv = uv*2 - 1;\n\
\n\
	// Reconstructs view-space position\n\
	return vec3(uv * invFocalLen * eye_z, eye_z);\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using a given texel\n\
highp vec3 fetch_eye_pos(highp sampler2DRect texture, highp ivec2 textureResolution, highp vec2 uv, highp vec2 invFocalLen)\n\
{\n\
	// Fetch the linear view space depth at the given texel position\n\
	highp float eye_z = texture2DRect(texture, uv*textureResolution).b;\n\
\n\
	// Reconstructs view-space position using given parameters\n\
	return uv_to_eye(uv, eye_z, invFocalLen);\n\
}\n\
\n\
// AO calculation\n\
highp float doAmbientOcclusion(highp vec2 tcoord, highp vec2 uv, highp vec3 p, highp vec3 cnorm)\n\
{\n\
	highp vec3 diff = fetch_eye_pos(NormalDepthMap, Resolution, tcoord + uv, InvFocalLen) - p;\n\
	const highp vec3 v = normalize(diff);\n\
	const highp float d = length(diff)*Scale;\n\
	return max(0.0f, dot(cnorm, v) - Bias)*(1.0f/(1.0f + d))*Intensity;\n\
}\n\
\n\
\n\
const highp vec2 vec[4] = highp vec2[4](\n\
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
	highp vec4 sample = texture2DRect(NormalDepthMap, VertexTexCoordVS*Resolution);\n\
\n\
	// Reconstruct view-space position\n\
	highp vec3 p = uv_to_eye(VertexTexCoordVS, sample.b, InvFocalLen);\n\
\n\
	// Reconstruct view-space normal vector\n\
	highp vec3 n = decodeNormalVector(sample.rg);\n\
	n.z = -n.z; // If this is not done, we get wrong results\n\
\n\
	// Locals\n\
	highp vec2 rand = normalize(texture2D(RandomNormalsMap, Resolution*VertexTexCoordVS/RandomSize).xy*2.0f - 1.0f);	// Returns a random normal vector\n\
	float ao = 0.0f;\n\
	float rad = SampleRadius/p.z;\n\
\n\
	// SSAO calculation\n\
	int iterations = 4;\n\
	for (int j=0; j<iterations; j++) {\n\
		highp vec2 coord1 = reflect(vec[j], rand)*rad;\n\
		highp vec2 coord2 = highp vec2(coord1.x*0.707f - coord1.y*0.707f, coord1.x*0.707f + coord1.y*0.707f);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord1*0.25f, p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord2*0.5f,  p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord1*0.75f, p, n);\n\
		ao += doAmbientOcclusion(VertexTexCoordVS, coord2,       p, n);\n\
	}\n\
	ao /= iterations*4.0;\n\
	gl_FragColor = vec4(1 - clamp(ao, 0.0f, 1.0f));\n\
}";
