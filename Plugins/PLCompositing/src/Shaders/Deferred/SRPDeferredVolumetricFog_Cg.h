/*********************************************************\
 *  File: SRPDeferredVolumetricFog_Cg.h                  *
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


// Cg vertex shader source code
static const PLCore::String sDeferredVolumetricFog_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition : POSITION)	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
													// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the vertex texture coordinate\n\
	OUT.TexCoord = VertexPosition.zw;\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg fragment shader source code
static const PLCore::String sDeferredVolumetricFog_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
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
// Programs\n\
FS_OUTPUT main(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
	 , uniform float3      FogPosition		// View space fog position\n\
	 , uniform float       FogInvRadius		// View space fog inverse radius\n\
	 , uniform float3      FogColor0\n\
	 , uniform float3      FogColor1\n\
	 , uniform float2      InvFocalLen		// 1/FocalLen (for example: 0.57771897 x 0.4142136)\n\
	 , uniform int2        Resolution		// Resolution of the input texture data (for example 636 x 456)\n\
	 , uniform samplerRECT NormalDepthMap	// Normal depth texture\n\
	 )\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Get the current view space position\n\
	float3 viewSpacePos = fetch_eye_pos(NormalDepthMap, Resolution, IN.TexCoord, InvFocalLen);\n\
	viewSpacePos.z = -viewSpacePos.z;\n\
\n\
	// Calculate the fog factor\n\
	float3 fogPosition = (FogPosition - viewSpacePos)*FogInvRadius;\n\
	viewSpacePos = -viewSpacePos*FogInvRadius;\n\
	float value = dot(viewSpacePos, viewSpacePos);\n\
	if (value == 0.0f)\n\
		value = 0.000001f;	// Do never ever divide through zero, this may lead to ugly blocks!\n\
	float  k  = clamp(dot(fogPosition, viewSpacePos)/value, 0.0f, 1.0f);\n\
	float4 pl = float4(k*viewSpacePos - fogPosition, 1.0f);\n\
	value = dot(pl, pl);\n\
	if (value == 0.0f)\n\
		value = 0.000001f;	// Do never ever divide through zero, this may lead to ugly blocks!\n\
	OUT.Color0.rgb = clamp(FogColor0/value - FogColor1, 0.0f, 1.0f);\n\
	OUT.Color0.a = 1;\n\
\n\
	// Done\n\
	return OUT;\n\
}";
