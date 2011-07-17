/*********************************************************\
 *  File: RenderInterfacePLShaders_Cg.h                  *
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
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 VertexTexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
	float4 VertexColor    : COLOR;		// Vertex color\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float2 VertexPosition : POSITION,	// Window space vertex position input\n\
			   float2 VertexTexCoord : TEXCOORD0,	// Vertex texture coordinate input\n\
			   float4 VertexColor    : COLOR,		// Vertex color input\n\
	   uniform float2 Translation,					// Window space translation\n\
	   uniform float2 WindowSizeInv)				// 1/(window size)\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.VertexPosition     = float4(VertexPosition + Translation, 0, 1);\n\
	Out.VertexPosition.xy *= WindowSizeInv;					// Change into 0..1 range\n\
	Out.VertexPosition.y   = 1 - Out.VertexPosition.y;		// Flip y axis\n\
	Out.VertexPosition.xy  = Out.VertexPosition.xy*2 - 1;	// Change into -1..1 range\n\
\n\
	// Pass through the vertex texture coordinate\n\
	Out.VertexTexCoord = VertexTexCoord;\n\
\n\
	// Pass through the vertex color\n\
	Out.VertexColor = VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLGeneral::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 VertexPosition : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 VertexTexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
	float4 VertexColor    : COLOR;		// Vertex color\n\
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
	// Fragment color = fetched interpolated texel color\n\
	Out.Color0 = tex2D(TextureMap, In.VertexTexCoord)*In.VertexColor;\n\
\n\
	// Perform an alpha test to discard fragments - Reject pixels with an alpha of <=0\n\
	if (Out.Color0.a <= 0)\n\
		discard; // Throw the fragment away and don't draw it!\n\
\n\
	// Done\n\
	return Out;\n\
}";
