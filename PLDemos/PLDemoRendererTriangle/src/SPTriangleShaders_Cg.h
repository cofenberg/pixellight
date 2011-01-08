/*********************************************************\
 *  File: SPTriangleShaders_Cg.cpp                       *
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
static const PLGeneral::String sVertexShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position\n\
	float4 VertexColor    : COLOR;		// Vertex color\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input\n\
			   float4   VertexColor    : COLOR,			// Vertex color input\n\
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix)	// Object space to clip space matrix\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.VertexPosition = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));\n\
\n\
	// Pass through the vertex color\n\
	Out.VertexColor = VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg geometry shader source code
static const PLGeneral::String sGeometryShaderSourceCodeCg = "\
TRIANGLE void main(AttribArray<float4> VertexPosition : POSITION,	// Clip space vertex positions from vertex shader\n\
				   AttribArray<float4> VertexColor    : COLOR)		// Vertex colors from vertex shader\n\
{\n\
	// Pass-thru\n\
	for (int i=0; i<VertexPosition.length; i++)\n\
		emitVertex(VertexPosition[i] : POSITION, VertexColor[i] : COLOR);\n\
	restartStrip();\n\
\n\
	// Create a clone of the triangle with a shifted position and evil inverted colors\n\
	for (int i=0; i<VertexPosition.length; i++) {\n\
		float4 position = VertexPosition[i] + float4(3, 2, 0, 0);\n\
		float4 color    = 1 - VertexColor[i];\n\
		emitVertex(position : POSITION, color : COLOR);\n\
	}\n\
}";


// Cg fragment shader source code
static const PLGeneral::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position\n\
	float4 VertexColor    : COLOR;		// Vertex color\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In)	// Vertex shader or geometry shader output as fragment shader input\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Fragment color = interpolated vertex color\n\
	Out.Color0 = In.VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";
