/*********************************************************\
 *  File: SPMeshShaders_Cg.h                             *
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


// Cg vertex shader source code
static const PLCore::String sVertexShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4   VertexPosition : POSITION,		// Object space vertex position input\n\
			   float3   VertexNormal   : NORMAL,		// Object space vertex normal input\n\
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,	// Object space to clip space matrix\n\
	   uniform float4x4 ObjectSpaceToWorldSpaceMatrix)	// Object space to world space matrix\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, VertexPosition);\n\
\n\
	// Calculate the world space vertex normal\n\
	Out.VertexNormal = mul((float3x3)ObjectSpaceToWorldSpaceMatrix, VertexNormal);\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In,				// Vertex shader output as fragment shader input\n\
	   uniform float3    LightDirection)	// World space light direction\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Set fragment color by using primitive directional lighting\n\
	Out.Color0 = clamp(dot(LightDirection, In.VertexNormal), 0, 1);\n\
\n\
	// Done\n\
	return Out;\n\
}";
