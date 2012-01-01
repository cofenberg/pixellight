/*********************************************************\
 *  File: SPMultiViewShaders_Cg.h                        *
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
static const PLCore::String sVertexShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal
};

// Programs
VS_OUTPUT main(float4   VertexPosition : POSITION,		// Object space vertex position input
			   float3   VertexNormal   : COLOR,			// Object space vertex normal input
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,	// Object space to clip space matrix
	   uniform float4x4 ObjectSpaceToWorldSpaceMatrix)	// Object space to world space matrix
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, VertexPosition);

	// Calculate the world space vertex normal
	Out.VertexNormal = mul((float3x3)ObjectSpaceToWorldSpaceMatrix, VertexNormal);

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
static const PLCore::String sFragmentShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;
};

// Programs
FS_OUTPUT main(VS_OUTPUT In,				// Vertex shader output as fragment shader input
	   uniform float3    LightDirection)	// World space light direction
{
	FS_OUTPUT Out;

	// Set fragment color by using primitive directional lighting
	Out.Color0 = clamp(dot(LightDirection, In.VertexNormal), 0, 1);

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
