/*********************************************************\
 *  File: FullscreenQuad_VertexShader.h                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
 *
 *  Definitions:
 *  - SIZE_CONTROL: Size control
\*********************************************************/

const static char *pszFullscreenQuad_VertexShader = "\n\
// Vertex input\n\
struct VS_INPUT {\n\
	float4 position : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
								// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
};\n\
\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Main function\n\
VS_OUTPUT main(VS_INPUT IN				// Vertex input\n\
#ifdef SIZE_CONTROL\n\
	 , uniform float2	Size			// Size [0..1]\n\
#endif\n\
	 , uniform int2		TextureSize)	// Texture size in texel\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Vertex position\n\
#ifdef SIZE_CONTROL\n\
	// Convert the incoming clip space vertex position from [-1..1] to [0..1]\n\
	float2 position = (IN.position.xy + 1)*0.5f;\n\
\n\
	// Apply size\n\
	position *= Size;\n\
\n\
	// Write out the vertex position in clip space\n\
	OUT.position = float4(position*2 - 1, 0, 1);\n\
#else\n\
	// Pass through the vertex position\n\
	OUT.position = float4(IN.position.xy, 0, 1);\n\
#endif\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.texUV = IN.position.zw*TextureSize;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
