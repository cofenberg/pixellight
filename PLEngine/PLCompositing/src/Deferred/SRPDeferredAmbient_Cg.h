/*********************************************************\
 *  File: SRPDeferredAmbient_Cg.h                        *
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
 *  - ALBEDO:           Use albedo data
 *  - AMBIENTOCCLUSION: Use ambient occlusion data
 *  - SELFILLUMINATION: Self illumination data used
\*********************************************************/


const static char *pszDeferredAmbient_Cg_FS = "\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	float2 texUV	: TEXCOORD0;	// Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 color : COLOR;\n\
};\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN						// Interpolated output from the vertex stage\n\
	 , uniform float3      AmbientColor				// Ambient color\n\
	 , uniform samplerRECT AlbedoTexture			// Albedo texture\n\
#ifdef SELFILLUMINATION\n\
	 , uniform samplerRECT SelfIlluminationTexture	// Self illumination texture\n\
#endif\n\
	 )\n\
{\n\
	FS_OUTPUT OUT;\n\
	OUT.color.a = 1;\n\
\n\
	// Fetch the required texel data\n\
	float4 sample = texRECT(AlbedoTexture, IN.texUV);\n\
\n\
	// Apply albedo and ambient color\n\
#ifdef ALBEDO\n\
	OUT.color.rgb = sample.rgb*AmbientColor;\n\
#else\n\
	OUT.color.rgb = AmbientColor;\n\
#endif\n\
\n\
	// Apply ambient occlusion\n\
#ifdef AMBIENTOCCLUSION\n\
	OUT.color.rgb *= sample.a;\n\
#endif\n\
\n\
	// Apply self illumination\n\
#ifdef SELFILLUMINATION\n\
	OUT.color.rgb += texRECT(SelfIlluminationTexture, IN.texUV).rgb;\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
