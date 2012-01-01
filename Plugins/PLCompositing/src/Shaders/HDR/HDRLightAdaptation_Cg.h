/*********************************************************\
 *  File: HDRLightAdaptation_Cg.h                        *
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
static const PLCore::String sHDRLightAdaptation_Cg_VS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float2 VertexPosition : POSITION)	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
	// Pass through the vertex position\n\
	OUT.Position = float4(VertexPosition.xy, 0, 1);\n\
\n\
	// Done\n\
	return OUT;\n\
}";


// Cg fragment shader source code
static const PLCore::String sHDRLightAdaptation_Cg_FS = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
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
	OUT.Color0 = lerp(previouAverageLuminance, currentAverageLuminance, Factor);\n\
\n\
	// Done\n\
	return OUT;\n\
}";
