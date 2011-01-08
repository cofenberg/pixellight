/*********************************************************\
 *  File: SRPDeferredSSAO_Cg.h                           *
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
static const PLGeneral::String sDeferredSSAO_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float4 TexCoord	: TEXCOORD0;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
									// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Main function\n\
VS_OUTPUT main(float4 VertexPosition : POSITION,	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
													// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
	   uniform int2	  TextureSize,					// xy = Texture size\n\
	   uniform int2	  InputTextureSize)				// Input texture size\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	OUT.TexCoord.xy = VertexPosition.zw*TextureSize;\n\
	OUT.TexCoord.zw = VertexPosition.zw*InputTextureSize;\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg vertex shader source code
static const PLGeneral::String sDeferredSSAO_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float4 TexCoord	: TEXCOORD0;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
									// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR;\n\
};\n\
\n\
float FetchEyeZ(samplerRECT normalDepthTexture, float2 uv)\n\
{\n\
	return texRECT(normalDepthTexture, uv).b;\n\
}\n\
\n\
float BlurFunction(samplerRECT inputTexture, samplerRECT normalDepthTexture, float blurFalloff, float sharpness, float2 uv, float2 uvInput, float r, float center_c, float center_d, inout float w_total)\n\
{\n\
	float c = texRECT(inputTexture, uvInput).r;\n\
	float d = FetchEyeZ(normalDepthTexture, uv);\n\
\n\
	float ddiff = d - center_d;\n\
	float w = exp(-r*r*blurFalloff - ddiff*ddiff*sharpness);\n\
	w_total += w;\n\
\n\
	return w*c;\n\
}\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
	 , uniform float	   BlurRadius			// Blur radius\n\
	 , uniform float	   BlurFalloff			// Blur falloff\n\
	 , uniform float	   Sharpness			// Sharpness\n\
	 , uniform float2	   UVScale				// UV scale\n\
	 , uniform samplerRECT InputTexture			// Input texture\n\
	 , uniform samplerRECT NormalDepthTexture)	// RG=normal vector, B=linear view space length\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	float b = 0;\n\
	float w_total = 0;\n\
	float center_c = texRECT(InputTexture, IN.TexCoord.zw).r;\n\
	float center_d = FetchEyeZ(NormalDepthTexture, IN.TexCoord.xy);\n\
	for (float r=-BlurRadius; r<=BlurRadius; r++)\n\
		b += BlurFunction(InputTexture, NormalDepthTexture, BlurFalloff, Sharpness, IN.TexCoord.xy + r*UVScale, IN.TexCoord.zw + r*UVScale, r, center_c, center_d, w_total);\n\
	OUT.Color0 = b/w_total;\n\
\n\
	// Done\n\
	return OUT;\n\
}";
