/*********************************************************\
 *  File: SPTriangleShaders_Cg.cpp                       *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
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
	float4 VertexColor    : COLOR;		// Vertex color
};

// Programs
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input
			   float4   VertexColor    : COLOR,			// Vertex color input
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,	// Object space to clip space matrix
	   uniform float4   Color)							// Object color
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));

	// Pass through the vertex color
	Out.VertexColor = VertexColor*Color;

	// Done
	return Out;
}
);	// STRINGIFY


// Cg vertex shader source code - uniform buffer version
static const PLCore::String sVertexShaderSourceCodeCg_UniformBuffer = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float4 VertexColor    : COLOR;		// Vertex color
};

// Uniforms
typedef struct {
	float4x4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix
	float4   Color;							// Object color
} UniformBlockStruct;

// Programs
VS_OUTPUT main(float3             VertexPosition : POSITION,	// Object space vertex position input
			   float4             VertexColor    : COLOR,		// Vertex color input
	   uniform UniformBlockStruct UniformBlock   : BUFFER[0])	// Uniform block
{
	VS_OUTPUT Out;

	// Calculate the clip space vertex position... Lookout! We need to transpose the matrix for Cg, I just swap the parameters in here for this!
	Out.VertexPosition = mul(float4(VertexPosition, 1), UniformBlock.ObjectSpaceToClipSpaceMatrix);

	// Pass through the vertex color
	Out.VertexColor = VertexColor*UniformBlock.Color;

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Geometry shader source code                           ]
//[-------------------------------------------------------]
static const PLCore::String sGeometryShaderSourceCodeCg = STRINGIFY(
TRIANGLE void main(AttribArray<float4> VertexPosition : POSITION,	// Clip space vertex positions from vertex shader, lower/left is (-1,-1) and upper/right is (1,1)
				   AttribArray<float4> VertexColor    : COLOR)		// Vertex colors from vertex shader
{
	// Pass-thru
	for (int i=0; i<VertexPosition.length; i++)
		emitVertex(VertexPosition[i] : POSITION, VertexColor[i] : COLOR);
	restartStrip();

	// Create a clone of the triangle with a shifted position and evil inverted colors
	for (int i=0; i<VertexPosition.length; i++) {
		float4 position = VertexPosition[i] + float4(3, 2, 0, 0);
		float4 color    = 1 - VertexColor[i];
		emitVertex(position : POSITION, color : COLOR);
	}
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
FS_OUTPUT main(VS_OUTPUT In)	// Vertex shader or geometry shader output as fragment shader input
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
