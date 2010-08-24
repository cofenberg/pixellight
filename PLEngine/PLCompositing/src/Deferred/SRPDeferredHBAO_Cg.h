/*********************************************************\
 *  File: SRPDeferredHBAO_Cg.h                           *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
 *
 *  Definitions:
 *  - USE_NORMAL:  Use per fragment normal vector
\*********************************************************/


const static char *pszDeferredHBAO_Cg_FS = "\n\
#define M_PI 3.14159265f\n\
\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV    : TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 color : COLOR;\n\
};\n\
\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
float3 decodeNormalVector(float2 normal)\n\
{\n\
	float2 fenc = normal*4 - 2;\n\
	float f = dot(fenc, fenc);\n\
	float g = sqrt(1 - f/4);\n\
	float3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using given parameters\n\
float3 uv_to_eye(float2 uv, float eye_z, float2 invFocalLen)\n\
{\n\
	// Convert from texture space [0,1] range into [-1,1] clip space\n\
	uv = uv*2 - 1;\n\
\n\
	// Reconstructs view-space position\n\
	return float3(uv * invFocalLen * eye_z, eye_z);\n\
}\n\
\n\
// Reconstructs view-space position (current surface point) using a given texel\n\
float3 fetch_eye_pos(samplerRECT texture, float2 textureResolution, float2 uv, float2 invFocalLen)\n\
{\n\
	// Fetch the linear view space depth at the given texel position\n\
	float eye_z = texRECT(texture, uv*textureResolution).b;\n\
\n\
	// Reconstructs view-space position using given parameters\n\
	return uv_to_eye(uv, eye_z, invFocalLen);\n\
}\n\
\n\
float3 tangent_eye_pos(samplerRECT texture, float2 textureResolution, float2 uv, float2 invFocalLen, float4 tangentPlane)\n\
{\n\
	// View vector going through the surface point at uv\n\
	float3 V = fetch_eye_pos(texture, textureResolution, uv, invFocalLen);\n\
	float NdotV = dot(tangentPlane.xyz, V);\n\
\n\
	// Intersect with tangent plane except for silhouette edges\n\
	if (NdotV < 0.0)\n\
		V *= (tangentPlane.w / NdotV);\n\
\n\
	return V;\n\
}\n\
\n\
float length2(float3 v)\n\
{\n\
	return dot(v, v);\n\
}\n\
\n\
float3 min_diff(float3 P, float3 Pr, float3 Pl)\n\
{\n\
	float3 V1 = Pr - P;\n\
	float3 V2 = P - Pl;\n\
	return (length2(V1) < length2(V2)) ? V1 : V2;\n\
}\n\
\n\
float2 rotate_direction(float2 dir, float2 cosSin)\n\
{\n\
	return float2(dir.x*cosSin.x - dir.y*cosSin.y,\n\
				  dir.x*cosSin.y + dir.y*cosSin.x);\n\
}\n\
\n\
float2 snap_uv_offset(float2 uv, float2	resolution, float2 invResolution)\n\
{\n\
	return round(uv * resolution) * invResolution;\n\
}\n\
\n\
float tangent(float3 T)\n\
{\n\
	return -T.z / length(T.xy);\n\
}\n\
\n\
float tangent(float3 P, float3 S)\n\
{\n\
	return (P.z - S.z) / length(S.xy - P.xy);\n\
}\n\
\n\
float biased_tangent(float3 T, float angleBias)\n\
{\n\
	float phi = atan(tangent(T)) + angleBias;\n\
	return tan(min(phi, M_PI*0.5f));\n\
}\n\
\n\
float falloff(float r, float attenuation)\n\
{\n\
	return 1 - attenuation*r*r;\n\
}\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
	 , uniform int		   g_NumSteps			// Number of steps (for example 8)\n\
	 , uniform int		   g_NumDir				// Number of directions (for example 16)\n\
	 , uniform float	   g_R					// Radius of influence (for example 1)\n\
	 , uniform float	   g_inv_R				// 1/g_R (for example 1)\n\
	 , uniform float	   g_sqr_R				// g_R*g_R (for example 1)\n\
	 , uniform float	   g_AngleBias			// Angle bias (for example 0.523599)\n\
	 , uniform float	   g_TanAngleBias		// Tangent of angle bias (for example 0.57735026)\n\
	 , uniform float	   g_Contrast			// Contrast (for example 2.5)\n\
	 , uniform float	   g_Attenuation		// Attenuation (for example 1)\n\
	 , uniform float2	   g_FocalLen			// Focal length (for example 1.7309455 x 2.4142134)\n\
	 , uniform float2	   g_InvFocalLen		// 1/g_FocalLen (for example: 0.57771897 x 0.4142136)\n\
	 , uniform float2	   g_Resolution			// Resolution of the input texture data (for example 636 x 456)\n\
	 , uniform float2	   g_InvResolution		// 1/g_Resolution (for example 0.001572327f x 0.0021929825f)\n\
	 , uniform float2	   RandomUVScale		// UV scale for the random normals texture\n\
	 , uniform sampler2D   RandomNormalsTexture	// RGB texture with random normals\n\
	 , uniform samplerRECT NormalDepthTexture)	// RG=normal vector, B=linear view space length\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel data\n\
	float4 sample = texRECT(NormalDepthTexture, IN.texUV*g_Resolution);\n\
\n\
	// Reconstruct view-space position\n\
	float3 P = uv_to_eye(IN.texUV, sample.b, g_InvFocalLen);\n\
\n\
	// Project the radius of influence g_R from view space to texture space.\n\
	// The scaling by 0.5f is to go from [-1,1] to [0,1].\n\
	float2 step_size = 0.5f * g_R * g_FocalLen / P.z;\n\
\n\
	// Early out if the projected radius is smaller than 1 pixel.\n\
	float numSteps = min(g_NumSteps, min(step_size.x * g_Resolution.x, step_size.y * g_Resolution.y));\n\
	if (numSteps < 1) {\n\
		OUT.color = 1;\n\
		return OUT;\n\
	}\n\
	step_size = step_size / (numSteps + 1);\n\
\n\
	// Nearest neighbor pixels on the tangent plane\n\
	#ifdef USE_NORMAL\n\
		// Reconstruct view-space normal vector\n\
		float3 N = decodeNormalVector(sample.rg);\n\
		N.z = -N.z; // If this is not done, we get wrong results\n\
\n\
		float4 tangentPlane = float4(N, dot(P, N));\n\
		float3 Pr = tangent_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2( g_InvResolution.x,                  0), g_InvFocalLen, tangentPlane);\n\
		float3 Pl = tangent_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(-g_InvResolution.x,                  0), g_InvFocalLen, tangentPlane);\n\
		float3 Pt = tangent_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(                 0,  g_InvResolution.y), g_InvFocalLen, tangentPlane);\n\
		float3 Pb = tangent_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(                 0, -g_InvResolution.y), g_InvFocalLen, tangentPlane);\n\
	#else\n\
		float3 Pr = fetch_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2( g_InvResolution.x,                  0), g_InvFocalLen);\n\
		float3 Pl = fetch_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(-g_InvResolution.x,                  0), g_InvFocalLen);\n\
		float3 Pt = fetch_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(                 0,  g_InvResolution.y), g_InvFocalLen);\n\
		float3 Pb = fetch_eye_pos(NormalDepthTexture, g_Resolution, IN.texUV + float2(                 0, -g_InvResolution.y), g_InvFocalLen);\n\
	#endif\n\
\n\
	// Screen-aligned basis for the tangent plane\n\
	float3 dPdu = min_diff(P, Pr, Pl);\n\
	float3 dPdv = min_diff(P, Pt, Pb) * (g_Resolution.y * g_InvResolution.x);\n\
\n\
	// (cos(alpha), sin(alpha), jitter)\n\
	float3 rand = tex2D(RandomNormalsTexture, IN.texUV*RandomUVScale).xyz;\n\
\n\
	float aoFinal = 0;\n\
	float alpha = 2 * M_PI / g_NumDir;\n\
\n\
	// Calculate the AO\n\
	for (int d=0; d<g_NumDir; d++) {\n\
		float angle = alpha * d;\n\
		float2 dir = float2(cos(angle), sin(angle));\n\
		float2 deltaUV = rotate_direction(dir, rand.xy) * step_size.xy;\n\
\n\
		{ // Accumulated horizon occlusion - Normal quality\n\
			// Randomize starting point within the first sample distance\n\
			float2 uv = IN.texUV + snap_uv_offset(rand.z * deltaUV, g_Resolution, g_InvResolution);\n\
\n\
			// Snap increments to pixels to avoid disparities between xy\n\
			// and z sample locations and sample along a line\n\
			deltaUV = snap_uv_offset(deltaUV, g_Resolution, g_InvResolution);\n\
\n\
			// Compute tangent vector using the tangent plane\n\
			float3 T = deltaUV.x * dPdu + deltaUV.y * dPdv;\n\
			float tanH = biased_tangent(T, g_AngleBias);\n\
			float sinH = tanH / sqrt(1 + tanH*tanH);\n\
\n\
			float ao = 0;\n\
			for (float j=1; j<=numSteps; ++j) {\n\
				uv += deltaUV;\n\
				float3 S = fetch_eye_pos(NormalDepthTexture, g_Resolution, uv, g_InvFocalLen);\n\
\n\
				// Ignore any samples outside the radius of influence\n\
				float d2  = length2(S - P);\n\
				if (d2 < g_sqr_R) {\n\
					float tanS = tangent(P, S);\n\
\n\
					if(tanS > tanH) {\n\
						// Accumulate AO between the horizon and the sample\n\
						float sinS = tanS / sqrt(1 + tanS*tanS);\n\
						float r = sqrt(d2) * g_inv_R;\n\
						ao += falloff(r, g_Attenuation) * (sinS - sinH);\n\
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
	OUT.color = 1 - aoFinal/g_NumDir*g_Contrast;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
