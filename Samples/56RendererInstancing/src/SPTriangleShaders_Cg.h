/*********************************************************\
 *  File: SPTriangleShaders_Cg.cpp                       *
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
// Version without hardware supported geometric primitive instancing
static const PLCore::String sVertexShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float4 VertexColor    : COLOR;		// Vertex color
};

// Programs
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input
			   float4   VertexColor    : COLOR,			// Vertex color input
	   uniform int      InstanceID,						// Integer instance ID of the primitive within the current batch
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix)	// Object space to clip space matrix
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	// -> Add an offset per geometric primitive instance
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition + float3(InstanceID*0.1, 0.0, InstanceID*0.01), 1));

	// Pass through the vertex color
	Out.VertexColor = VertexColor*float4(0.2, 1.0, 1.0, 1.0);

	// Done
	return Out;
}
);	// STRINGIFY

// Version with hardware supported geometric primitive instancing
static const PLCore::String sVertexShaderSourceCodeCg_Instanced = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float4 VertexColor    : COLOR;		// Vertex color
};

// Programs
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input
			   float4   VertexColor    : COLOR,			// Vertex color input
			   int      InstanceID     : INSTANCEID,	// Integer instance ID of the primitive within the current batch
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix)	// Object space to clip space matrix
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	// -> Add an offset per geometric primitive instance
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition + float3(InstanceID*0.1, 0.0, InstanceID*0.01), 1));

	// Pass through the vertex color
	Out.VertexColor = VertexColor*float4(0.2, 1.0, 1.0, 1.0);

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
	float4 VertexColor    : COLOR;		// Vertex color
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;
};

// Programs
FS_OUTPUT main(VS_OUTPUT In)	// Vertex shader output as fragment shader input
{
	FS_OUTPUT Out;

	// Fragment color = interpolated vertex color
	Out.Color0 = In.VertexColor;

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
