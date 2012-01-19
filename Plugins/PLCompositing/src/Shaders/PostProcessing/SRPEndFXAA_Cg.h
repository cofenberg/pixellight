/*********************************************************\
 *  File: SRPEndFXAA_Cg.h                                *
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
static const PLCore::String sEndFXAA_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition : POSITION	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
												// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
	)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the vertex texture coordinate\n\
	OUT.TexCoord.xy = VertexPosition.zw;\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg fragment shader source code
static const PLCore::String sEndFXAA_Cg_FS = "\
// Constants\n\
//const float2 InvTextureSize;	// 1/(texture size) - set when creating the shader\n\
\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT IN			// Interpolated output from the vertex stage\n\
	 , uniform sampler2D Texture)	// Texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Call the FXAA shader, lucky us that we don't have to write an own implementation\n\
	OUT.Color0 = float4(FxaaPixelShader(IN.TexCoord, Texture, InvTextureSize), 1.0);\n\
\n\
	// Done\n\
	return OUT;\n\
}";
