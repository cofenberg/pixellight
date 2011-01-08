/*********************************************************\
 *  File: SRPDeferredHBAO_GLSL.h                         *
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
static const PLGeneral::String sDeferredHBAO_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
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
static const PLGeneral::String sDeferredHBAO_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Definitions\n\
#define M_PI 3.14159265f\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp int			NumSteps;			// Number of steps (for example 8)\n\
uniform highp int			NumDir;				// Number of directions (for example 16)\n\
uniform highp float			Radius;				// Radius of influence (for example 1)\n\
uniform highp float			InvR;				// 1/Radius (for example 1)\n\
uniform highp float			SqrR;				// Radius*Radius (for example 1)\n\
uniform highp float			AngleBias;			// Angle bias (for example 0.523599)\n\
uniform highp float			TanAngleBias;		// Tangent of angle bias (for example 0.57735026)\n\
uniform highp float			Contrast;			// Contrast (for example 2.5)\n\
uniform highp float			Attenuation;		// Attenuation (for example 1)\n\
uniform highp vec2			FocalLen;			// Focal length (for example 1.7309455 x 2.4142134)\n\
uniform highp vec2			InvFocalLen;		// 1/FocalLen (for example: 0.57771897 x 0.4142136)\n\
uniform highp vec2			Resolution;			// Resolution of the input texture data (for example 636 x 456)\n\
uniform highp vec2			InvResolution;		// 1/Resolution (for example 0.001572327f x 0.0021929825f)\n\
uniform highp vec2			RandomUVScale;		// UV scale for the random normals texture\n\
uniform highp sampler2D		RandomNormalsMap;	// RGB texture with random normals\n\
uniform highp sampler2DRect NormalDepthMap;		// RG=normal vector, B=linear view space length\n\
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
highp vec3 fetch_eye_pos(highp sampler2DRect texture, highp vec2 textureResolution, highp vec2 uv, highp vec2 invFocalLen)\n\
{\n\
	// Fetch the linear view space depth at the given texel position\n\
	highp float eye_z = texture2DRect(texture, uv*textureResolution).b;\n\
\n\
	// Reconstructs view-space position using given parameters\n\
	return uv_to_eye(uv, eye_z, invFocalLen);\n\
}\n\
\n\
highp vec3 tangent_eye_pos(highp sampler2DRect texture, highp vec2 textureResolution, highp vec2 uv, highp vec2 invFocalLen, highp vec4 tangentPlane)\n\
{\n\
	// View vector going through the surface point at uv\n\
	highp vec3 V = fetch_eye_pos(texture, textureResolution, uv, invFocalLen);\n\
	highp float NdotV = dot(tangentPlane.xyz, V);\n\
\n\
	// Intersect with tangent plane except for silhouette edges\n\
	if (NdotV < 0.0)\n\
		V *= (tangentPlane.w / NdotV);\n\
\n\
	return V;\n\
}\n\
\n\
highp float length2(vec3 v)\n\
{\n\
	return dot(v, v);\n\
}\n\
\n\
highp vec3 min_diff(highp vec3 P, highp vec3 Pr, highp vec3 Pl)\n\
{\n\
	highp vec3 V1 = Pr - P;\n\
	highp vec3 V2 = P - Pl;\n\
	return (length2(V1) < length2(V2)) ? V1 : V2;\n\
}\n\
\n\
highp vec2 rotate_direction(highp vec2 dir, highp vec2 cosSin)\n\
{\n\
	return vec2(dir.x*cosSin.x - dir.y*cosSin.y,\n\
			    dir.x*cosSin.y + dir.y*cosSin.x);\n\
}\n\
\n\
highp vec2 snap_uv_offset(highp vec2 uv, highp vec2 resolution, highp vec2 invResolution)\n\
{\n\
	return round(uv * resolution) * invResolution;\n\
}\n\
\n\
highp float tangent(highp vec3 T)\n\
{\n\
	return -T.z / length(T.xy);\n\
}\n\
\n\
highp float tangent(highp vec3 P, highp vec3 S)\n\
{\n\
	return (P.z - S.z) / length(S.xy - P.xy);\n\
}\n\
\n\
highp float biased_tangent(highp vec3 T, highp float angleBias)\n\
{\n\
	highp float phi = atan(tangent(T)) + angleBias;\n\
	return tan(min(phi, M_PI*0.5f));\n\
}\n\
\n\
highp float falloff(highp float r, highp float attenuation)\n\
{\n\
	return 1 - attenuation*r*r;\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	highp vec4 sample = texture2DRect(NormalDepthMap, VertexTexCoordVS*Resolution);\n\
\n\
	// Reconstruct view-space position\n\
	highp vec3 P = uv_to_eye(VertexTexCoordVS, sample.b, InvFocalLen);\n\
\n\
	// Project the radius of influence Radius from view space to texture space.\n\
	// The scaling by 0.5f is to go from [-1,1] to [0,1].\n\
	highp vec2 step_size = 0.5f * Radius * FocalLen / P.z;\n\
\n\
	// Early out if the projected radius is smaller than 1 pixel.\n\
	highp float numSteps = min(NumSteps, min(step_size.x * Resolution.x, step_size.y * Resolution.y));\n\
	if (numSteps < 1) {\n\
		gl_FragColor = vec4(1);\n\
		return;\n\
	}\n\
	step_size = step_size / (numSteps + 1);\n\
\n\
	// Nearest neighbor pixels on the tangent plane\n\
	#ifdef FS_NORMAL\n\
		// Reconstruct view-space normal vector\n\
		highp vec3 N = decodeNormalVector(sample.rg);\n\
		N.z = -N.z; // If this is not done, we get wrong results\n\
\n\
		highp vec4 tangentPlane = vec4(N, dot(P, N));\n\
		highp vec3 Pr = tangent_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2( InvResolution.x,                0), InvFocalLen, tangentPlane);\n\
		highp vec3 Pl = tangent_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(-InvResolution.x,                0), InvFocalLen, tangentPlane);\n\
		highp vec3 Pt = tangent_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(               0,  InvResolution.y), InvFocalLen, tangentPlane);\n\
		highp vec3 Pb = tangent_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(               0, -InvResolution.y), InvFocalLen, tangentPlane);\n\
	#else\n\
		highp vec3 Pr = fetch_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2( InvResolution.x,                0), InvFocalLen);\n\
		highp vec3 Pl = fetch_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(-InvResolution.x,                0), InvFocalLen);\n\
		highp vec3 Pt = fetch_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(               0,  InvResolution.y), InvFocalLen);\n\
		highp vec3 Pb = fetch_eye_pos(NormalDepthMap, Resolution, VertexTexCoordVS + vec2(               0, -InvResolution.y), InvFocalLen);\n\
	#endif\n\
\n\
	// Screen-aligned basis for the tangent plane\n\
	highp vec3 dPdu = min_diff(P, Pr, Pl);\n\
	highp vec3 dPdv = min_diff(P, Pt, Pb) * (Resolution.y * InvResolution.x);\n\
\n\
	// (cos(alpha), sin(alpha), jitter)\n\
	highp vec3 rand = texture2D(RandomNormalsMap, VertexTexCoordVS*RandomUVScale).xyz;\n\
\n\
	highp float aoFinal = 0;\n\
	highp float alpha = 2 * M_PI / NumDir;\n\
\n\
	// Calculate the AO\n\
	for (highp int d=0; d<NumDir; d++) {\n\
		highp float angle = alpha * d;\n\
		highp vec2 dir = vec2(cos(angle), sin(angle));\n\
		highp vec2 deltaUV = rotate_direction(dir, rand.xy) * step_size.xy;\n\
\n\
		{ // Accumulated horizon occlusion - Normal quality\n\
			// Randomize starting point within the first sample distance\n\
			highp vec2 uv = VertexTexCoordVS + snap_uv_offset(rand.z * deltaUV, Resolution, InvResolution);\n\
\n\
			// Snap increments to pixels to avoid disparities between xy\n\
			// and z sample locations and sample along a line\n\
			deltaUV = snap_uv_offset(deltaUV, Resolution, InvResolution);\n\
\n\
			// Compute tangent vector using the tangent plane\n\
			highp vec3 T = deltaUV.x * dPdu + deltaUV.y * dPdv;\n\
			highp float tanH = biased_tangent(T, AngleBias);\n\
			highp float sinH = tanH / sqrt(1 + tanH*tanH);\n\
\n\
			highp float ao = 0;\n\
			for (highp float j=1; j<=numSteps; ++j) {\n\
				uv += deltaUV;\n\
				highp vec3 S = fetch_eye_pos(NormalDepthMap, Resolution, uv, InvFocalLen);\n\
\n\
				// Ignore any samples outside the radius of influence\n\
				highp float d2  = length2(S - P);\n\
				if (d2 < SqrR) {\n\
					highp float tanS = tangent(P, S);\n\
\n\
					if(tanS > tanH) {\n\
						// Accumulate AO between the horizon and the sample\n\
						highp float sinS = tanS / sqrt(1 + tanS*tanS);\n\
						highp float r = sqrt(d2) * InvR;\n\
						ao += falloff(r, Attenuation) * (sinS - sinH);\n\
\n\
						// Update the current horizon angle\n\
						tanH = tanS;\n\
						sinH = sinS;\n\
					}\n\
				}\n\
			}\n\
			aoFinal += ao;\n\
		}\n\
	}\n\
	gl_FragColor = vec4(1 - aoFinal/NumDir*Contrast);\n\
}";
