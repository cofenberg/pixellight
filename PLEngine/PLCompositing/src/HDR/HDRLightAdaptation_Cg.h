/*********************************************************\
 *  File: HDRLightAdaptation_Cg.h                        *
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
\*********************************************************/


const static char *pszHDRLightAdaptation_Cg_FS = "\n\
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
FS_OUTPUT main(VS_OUTPUT		 IN					// Interpolated output from the vertex stage\n\
			 , uniform float	 Factor				// Interpolation factor\n\
			 , uniform sampler2D PreviousTexture	// Previous average luminance\n\
			 , uniform sampler2D CurrentTexture)	// Current average luminance\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Get the previous and current average luminance\n\
	float previouAverageLuminance = tex2D(PreviousTexture, float2(0.5f, 0.5f)).r;\n\
	float currentAverageLuminance = tex2D(CurrentTexture,  float2(0.5f, 0.5f)).r;\n\
\n\
	// Adapt the luminance using Pattanaik's technique\n\
	OUT.color = lerp(previouAverageLuminance, currentAverageLuminance, Factor);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
