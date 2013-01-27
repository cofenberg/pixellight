/*********************************************************\
 *  File: SPRTTShaders_Cg.h                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
	float4 VertexPosition : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float2 VertexTextureCoordinate : TEXCOORD0;	// Vertex texture coordinate
	float4 VertexColor : COLOR;					// Vertex color
};

// Programs
VS_OUTPUT main(float3   VertexPosition : POSITION,				// Object space vertex position input
			   float2   VertexTextureCoordinate : TEXCOORD0,	// Vertex texture coordinate input
			   float4   VertexColor : COLOR,					// Vertex color input
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,			// Object space to clip space matrix
	   uniform float    ColorFactor)							// Color factor
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));

	// Pass through the texture coordinate
	Out.VertexTextureCoordinate = VertexTextureCoordinate;

	// Write out the vertex color
	Out.VertexColor = lerp(float4(1, 1, 1, 1), VertexColor, ColorFactor);

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
	float4 VertexPosition : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float2 VertexTextureCoordinate : TEXCOORD0;	// Vertex texture coordinate
	float4 VertexColor : COLOR;					// Vertex color
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;
};

// Programs
FS_OUTPUT main(VS_OUTPUT In,			// Vertex shader output as fragment shader input
	   uniform sampler2D DiffuseMap)	// Diffuse map
{
	FS_OUTPUT Out;

	// Set fragment color
	Out.Color0 = tex2D(DiffuseMap, In.VertexTextureCoordinate)*In.VertexColor;

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Scene program - Vertex shader source code             ]
//[-------------------------------------------------------]
static const PLCore::String sSceneVertexShaderSourceCodeCg = STRINGIFY(
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
//[ Scene program - Fragment shader source code           ]
//[-------------------------------------------------------]
static const PLCore::String sSceneFragmentShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float3 VertexNormal   : TEXCOORD0;	// World space vertex normal
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;	// RGBA fragment color 0
	float4 Color1 : COLOR1;	// RGBA fragment color 1
	float4 Color2 : COLOR2;	// RGBA fragment color 2
	float4 Color3 : COLOR3;	// RGBA fragment color 3
};

// Programs
FS_OUTPUT main(VS_OUTPUT In,				// Vertex shader output as fragment shader input
	   uniform float3    LightDirection)	// World space light direction
{
	FS_OUTPUT Out;

	// Set fragment color by using primitive directional lighting
	Out.Color0 = clamp(dot(LightDirection, In.VertexNormal), 0, 1);

	// Color 1 only red component
	Out.Color1 = float4(1, 0, 0, 0);

	// Color 2 only green component
	Out.Color2 = float4(0, 1, 0, 0);

	// Color 3 only blue component
	Out.Color3 = float4(0, 0, 1, 0);

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
