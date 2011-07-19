/*********************************************************\
 *  File: SPRTTShaders_Cg.h                              *
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
	float4 VertexPosition : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 VertexTextureCoordinate : TEXCOORD0;	// Vertex texture coordinate\n\
	float4 VertexColor : COLOR;					// Vertex color\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3   VertexPosition : POSITION,				// Object space vertex position input\n\
			   float2   VertexTextureCoordinate : TEXCOORD0,	// Vertex texture coordinate input\n\
			   float4   VertexColor : COLOR,					// Vertex color input\n\
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,			// Object space to clip space matrix\n\
	   uniform float    ColorFactor)							// Color factor\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));\n\
\n\
	// Pass through the texture coordinate\n\
	Out.VertexTextureCoordinate = VertexTextureCoordinate;\n\
\n\
	// Write out the vertex color\n\
	Out.VertexColor = lerp(float4(1, 1, 1, 1), VertexColor, ColorFactor);\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 VertexTextureCoordinate : TEXCOORD0;	// Vertex texture coordinate\n\
	float4 VertexColor : COLOR;					// Vertex color\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In,			// Vertex shader output as fragment shader input\n\
	   uniform sampler2D DiffuseMap)	// Diffuse map\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Set fragment color\n\
	Out.Color0 = tex2D(DiffuseMap, In.VertexTextureCoordinate)*In.VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


//[-------------------------------------------------------]
//[ Scene program                                         ]
//[-------------------------------------------------------]
// Cg vertex shader source code
static const PLCore::String sSceneVertexShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4   VertexPosition : POSITION,		// Object space vertex position input\n\
			   float3   VertexNormal   : COLOR,			// Object space vertex normal input\n\
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
static const PLCore::String sSceneFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;	// RGBA fragment color 0\n\
	float4 Color1 : COLOR1;	// RGBA fragment color 1\n\
	float4 Color2 : COLOR2;	// RGBA fragment color 2\n\
	float4 Color3 : COLOR3;	// RGBA fragment color 3\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In,				// Vertex shader output as fragment shader input\n\
	   uniform float3    LightDirection)	// World space light direction\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Set fragment color by using primitiv directional lighting\n\
	Out.Color0 = clamp(dot(LightDirection, In.VertexNormal), 0, 1);\n\
\n\
	// Color 1 only red component\n\
	Out.Color1 = float4(1, 0, 0, 0);\n\
\n\
	// Color 2 only green component\n\
	Out.Color2 = float4(0, 1, 0, 0);\n\
\n\
	// Color 3 only blue component\n\
	Out.Color3 = float4(0, 0, 1, 0);\n\
\n\
	// Done\n\
	return Out;\n\
}";
