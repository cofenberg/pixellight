/*********************************************************\
 *  File: SPTexturingShaders_Cg.cpp                      *
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
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float2 VertexTexCoord : TEXCOORD0;	// Vertex texture coordinate
};

// Programs
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input
			   float2   VertexTexCoord : TEXCOORD0,		// Vertex texture coordinate input
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix)	// Object space to clip space matrix
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));

	// In case you want to have a fullscreen quad in here, replace the line above by
//	Out.VertexPosition = float4(VertexPosition, 1);

	// Pass through the vertex texture coordinate
	Out.VertexTexCoord = VertexTexCoord;

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
	float2 VertexTexCoord : TEXCOORD0;	// Vertex texture coordinate
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;
};

// Programs
FS_OUTPUT main(VS_OUTPUT In,			// Vertex shader output as fragment shader input
	   uniform sampler2D TextureMap)	// Texture map
{
	FS_OUTPUT Out;

	// Fragment color = fetched interpolated texel color
	Out.Color0 = tex2D(TextureMap, In.VertexTexCoord);

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
