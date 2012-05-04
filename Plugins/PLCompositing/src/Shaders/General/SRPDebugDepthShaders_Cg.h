/*********************************************************\
 *  File: SRPDebugDepthShaders_Cg.h                      *
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
static const PLCore::String sEndHDR_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float4 VertexPosition : POSITION	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
												// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
  , uniform int2	  TextureSize				// Texture size in texel\n\
	)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.TexCoord = VertexPosition.zw*TextureSize;\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg fragment shader source code
static const PLCore::String sEndHDR_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT   IN		// Interpolated output from the vertex stage\n\
	 , uniform samplerRECT Texture	// Texture\n\
#ifdef FS_LINEARIZE_DEPTH\n\
	 , uniform float2      ZNearFar	// x=Z near plane, y=Z far plane\n\
#endif\n\
	)\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel data\n\
	float sample = texRECT(Texture, IN.TexCoord).x;\n\
\n\
	// Linearize the depth\n\
	#ifdef FS_LINEARIZE_DEPTH\n\
		sample = (2.0*ZNearFar.x)/(ZNearFar.y + ZNearFar.x - sample*(ZNearFar.y - ZNearFar.x));\n\
	#endif\n\
\n\
	// Set the resulting color\n\
	OUT.Color0 = float4(sample, sample, sample, 1.0);\n\
\n\
	// Done\n\
	return OUT;\n\
}";
