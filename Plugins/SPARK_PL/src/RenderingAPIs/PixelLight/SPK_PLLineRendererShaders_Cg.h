/*********************************************************\
 *  File: SPK_PLLineRendererShaders_Cg.h                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


// Cg vertex shader source code
static const PLCore::String sSPK_PLLineRendererShaders_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float4 Color    : COLOR;	// Vertex color\n\
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
	Out.Position = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1.0f));\n\
\n\
	// Pass through the vertex color\n\
	Out.Color = VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sSPK_PLLineRendererShaders_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float4 Color    : COLOR;	// Vertex color\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In)	// Vertex shader output as fragment shader input\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Just set the output color\n\
	Out.Color0 = In.Color;\n\
\n\
	// Done\n\
	return Out;\n\
}";
