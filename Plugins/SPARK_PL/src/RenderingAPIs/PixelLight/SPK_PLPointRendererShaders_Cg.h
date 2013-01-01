/*********************************************************\
 *  File: SPK_PLPointRendererShaders_Cg.h                *
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


// Cg vertex shader source code
static const PLCore::String sSPK_PLPointRendererShaders_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position  : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float4 Color     : COLOR;		// Vertex color\n\
	float  PointSize : PSIZE;		// Calculated point size\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input\n\
			   float4   VertexColor    : COLOR,			// Vertex color input\n\
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix,	// Object space to clip space matrix\n\
	   uniform float4   PointParameters)				// Point parameters: point size, point scale a, point scale b, point scale c \n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.Position = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1.0f));\n\
\n\
	// Calculate the point size (formulas from http://www.opengl.org/registry/specs/ARB/point_parameters.txt)\n\
	float distance = -Out.Position.z;\n\
	//    dist_atten = 1   /(a                 + b*distance                 + c*distance*distance)\n\
	float dist_atten = 1.0f/(PointParameters.y + PointParameters.z*distance + PointParameters.w*distance*distance);\n\
	// derived_size = Clamp(size * sqrt(dist_atten(dist)))\n\
	Out.PointSize   = clamp(PointParameters.x*sqrt(dist_atten), 1.0f, 1024.0f);\n\
\n\
	// Pass through the vertex color\n\
	Out.Color = VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sSPK_PLPointRendererShaders_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate 0\n\
	float4 Color    : COLOR;		// Vertex color\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In,			// Vertex shader output as fragment shader input\n\
	   uniform sampler2D TextureMap)	// Texture map\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	// Fragment color = fetched interpolated texel color multiplicated with the per vertex color\n\
	Out.Color0 = tex2D(TextureMap, In.TexCoord)*In.Color;\n\
\n\
	// Done\n\
	return Out;\n\
}";
