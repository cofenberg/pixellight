/*********************************************************\
 *  File: SRPDeferredDepthFog_Cg.h                       *
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
 *  - LINEAR_MODE:       Fog effect intensifies linearly between the start and end points (f=(end-d)/(end-start))
 *  - EXPONENTIAL_MODE:  Fog effect intensifies exponentially (f=1/((e^(d*density))))
 *  - EXPONENTIAL2_MODE: Fog effect intensifies exponentially with the square of the distance (f=1/((e^((d*density)^2))))
\*********************************************************/


const static char *pszDeferredDepthFog_Cg_FS = "\n\
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
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage\n\
	 , uniform float	   FarPlane				// Far clipping plane (never 0!)\n\
	 , uniform float4	   FogColor				// Fog color\n\
	#ifdef LINEAR_MODE\n\
	 , uniform float	   FogEnd				// Fog end\n\
	 , uniform float	   FogRange				// Fog end - fog start (never 0!)\n\
	#else\n\
	 , uniform float	   FogDensity			// Fog density\n\
	#endif\n\
	 , uniform samplerRECT NormalDepthTexture)	// Normal depth texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Get the depth\n\
	float depth = texRECT(NormalDepthTexture, IN.texUV).b/FarPlane;\n\
\n\
	// Calculate the fog intensity [0...1] = [full fog...no fog]\n\
	#define E 2.71828 // Natural logarithm\n\
#ifdef LINEAR_MODE\n\
	float fogFactor = (FogEnd - depth)/FogRange;\n\
#elif defined EXPONENTIAL_MODE\n\
	// The pow parameters are safe, so no NAN can be produced in here\n\
	float fogFactor = 1/pow(E, depth*FogDensity);\n\
#elif defined EXPONENTIAL2_MODE\n\
	// The pow parameters are safe, so no NAN can be produced in here\n\
	float fogFactor = 1/pow(E, depth*depth*FogDensity*FogDensity);\n\
#else\n\
	float fogFactor = 0;\n\
#endif\n\
\n\
	// Apply the fog color\n\
	OUT.color = (1 - saturate(fogFactor))*FogColor;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
