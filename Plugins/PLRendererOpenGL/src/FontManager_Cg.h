/*********************************************************\
 *  File: FontManager_Cg.h                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3 VertexPosition : POSITION,	// Object space vertex position input, lower/left is (0,0) and upper/right is (1,1)\n\
	uniform float4   GlyphSizePenPosition,			// Object space glyph size (xy) and object space pen position (zw) => scale & bias\n\
	uniform float4   TextureCoordinateMinMax,		// The normalized minimum (xy) and maximum (zw) glyph texture coordinate inside the glyph texture atlas\n\
	uniform float4x4 ObjectSpaceToClipSpaceMatrix	// Object space to clip space matrix\n\
)\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the object space vertex position\n\
	float4 position = float4(VertexPosition.xy*GlyphSizePenPosition.xy + GlyphSizePenPosition.zw, 0, 1);\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.Position = mul(ObjectSpaceToClipSpaceMatrix, position);\n\
\n\
	// Set the normalized vertex texture coordinate\n\
	if (int(VertexPosition.z) == 0)			// Vertex 0 - lower/left corner\n\
		Out.TexCoord = float2(TextureCoordinateMinMax.x, TextureCoordinateMinMax.w);\n\
	else if (int(VertexPosition.z) == 1)	// Vertex 1 - lower/right corner\n\
		Out.TexCoord = TextureCoordinateMinMax.zw;\n\
	else if (int(VertexPosition.z) == 2)	// Vertex 2 - upper/left corner\n\
		Out.TexCoord = TextureCoordinateMinMax.xy;\n\
	else if (int(VertexPosition.z) == 3)	// Vertex 3 - upper/right corner\n\
		Out.TexCoord = float2(TextureCoordinateMinMax.z, TextureCoordinateMinMax.y);\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In,	// Vertex shader or geometry shader output as fragment shader input\n\
	uniform sampler2D GlyphMap,	// Glyph atlas texture map\n\
	uniform float4	  Color		// Text color\n\
)\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
	Out.Color0 = float4(Color.r, Color.g, Color.b, tex2D(GlyphMap, In.TexCoord).a*Color.a);\n\
\n\
	// Done\n\
	return Out;\n\
}";
