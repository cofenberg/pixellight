/*********************************************************\
 *  File: SPK_PLQuadRendererShaders_Cg.h                 *
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
static const PLCore::String sSPK_PLQuadRendererShaders_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate 0\n\
	float4 Color    : COLOR;		// Vertex color\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3   VertexPosition : POSITION,		// Object space vertex position input\n\
			   float2   VertexTexCoord : TEXCOORD0,		// Vertex texture coordinate input\n\
			   float4   VertexColor    : COLOR,			// Vertex color input\n\
	   uniform float4x4 ObjectSpaceToClipSpaceMatrix)	// Object space to clip space matrix\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.Position = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1.0f));\n\
\n\
	// Pass through the vertex texture coordinate\n\
	Out.TexCoord = VertexTexCoord;\n\
\n\
	// Pass through the vertex color\n\
	Out.Color = VertexColor;\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sSPK_PLQuadRendererShaders_Cg_FS = "\
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
