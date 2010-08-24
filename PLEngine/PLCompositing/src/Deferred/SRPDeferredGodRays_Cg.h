/*********************************************************\
 *  File: SRPDeferredGodRays_Cg.h                        *
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
 *  - DISCARD: Use discard
\*********************************************************/


const static char *pszDeferredGodRays_Cg_FS = "\n\
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
FS_OUTPUT main(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
	 , uniform int         NumerOfSamples	// Number of samples, must be >0\n\
	 , uniform float       Density		    // Density, must be >0\n\
	 , uniform float       Weight		    // Weight\n\
	 , uniform float       Decay		    // Decay\n\
	 , uniform float2      LightPosition	// Screen space light position, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
	 , uniform float3      Color			// Color\n\
	 , uniform samplerRECT Texture)			// Texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Calculate vector from pixel to light source in screen space\n\
	float2 texUV = IN.texUV;\n\
	float2 deltaTexUV = texUV - LightPosition;\n\
\n\
	// Divide by number of samples and scale by control factor\n\
	deltaTexUV *= 1.0f/NumerOfSamples*Density;\n\
\n\
	// Store initial sample\n\
	float3 color = texRECT(Texture, IN.texUV).rgb;\n\
\n\
	// Set up illumination decay factor\n\
	float illuminationDecay = 1;\n\
\n\
	// Evaluate summation\n\
	for (int i=0; i<NumerOfSamples; i++) {\n\
		// Step sample location along ray\n\
		texUV -= deltaTexUV;\n\
\n\
		// Retrieve sample at new location\n\
		float3 sample = texRECT(Texture, texUV).rgb;\n\
\n\
		// Apply sample attenuation scale/decay factors\n\
		sample *= illuminationDecay*Weight;\n\
\n\
		// Accumulate combined color\n\
		color += sample;\n\
\n\
		// Update exponential decay factor\n\
		illuminationDecay *= Decay;\n\
	}\n\
\n\
	// Output final color with a further scale control factor\n\
	float3 resultingColor = color*Color;\n\
\n\
	// Use discard?\n\
#ifdef DISCARD\n\
	if (resultingColor.r == 0 && resultingColor.g == 0 && resultingColor.b == 0)\n\
		discard;\n\
#else\n\
	OUT.color = float4(resultingColor, 1);\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
