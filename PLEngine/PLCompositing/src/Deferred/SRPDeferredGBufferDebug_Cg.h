/*********************************************************\
 *  File: SRPDeferredGBufferDebug_Cg.h                   *
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
 *  - SHOW_ALBEDO:            Show albedo
 *  - SHOW_AMBIENTOCCLUSION:  Show ambient occlusion
 *  - SHOW_NORMALS:           Show normals
 *  - SHOW_DEPTH:             Show depth
 *  - SHOW_SPECULAR_COLOR:    Show specular color
 *  - SHOW_SPECULAR_EXPONENT: Show specular exponent
 *  - SHOW_SELFILLUMINATION:  Show self illumination
 *  - SHOW_GLOW:              Show glow
\*********************************************************/


const static char *pszDeferredGBufferDebug_Cg_FS = "\n\
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
// Decodes a 2 component normal vector to a 3 component normal vector\n\
float3 decodeNormalVector(float2 normal)\n\
{\n\
	float2 fenc = normal*4 - 2;\n\
	float f = dot(fenc, fenc);\n\
	float g = sqrt(1 - f/4);\n\
	float3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
	 , uniform float	   CameraNarPlane	// Camera far plane distance\n\
	 , uniform float	   CameraRange		// Distance between camera far and new plane (never 0!)\n\
	 , uniform samplerRECT Texture)			// Input texture containing the data to visualize\n\
{\n\
	FS_OUTPUT OUT;\n\
	OUT.color.a = 1;\n\
\n\
	// Fetch the required texel data and set the RGB output color\n\
#ifdef SHOW_BLACK\n\
	OUT.color.rgb = 0;\n\
#elif defined SHOW_ALBEDO\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).rgb;\n\
#elif defined SHOW_AMBIENTOCCLUSION\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).a;\n\
#elif defined SHOW_NORMALS\n\
	OUT.color.rgb = decodeNormalVector(texRECT(Texture, IN.texUV).rg);\n\
#elif defined SHOW_DEPTH\n\
	// Normalized the linear view space depth, else we can't inspect the depth properly\n\
	OUT.color.rgb = (texRECT(Texture, IN.texUV).b - CameraNarPlane)/CameraRange;\n\
#elif defined SHOW_SPECULAR_COLOR\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).rgb;\n\
#elif defined SHOW_SPECULAR_EXPONENT\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).a/128;\n\
#elif defined SHOW_SELFILLUMINATION\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).rgb;\n\
#elif defined SHOW_GLOW\n\
	OUT.color.rgb = texRECT(Texture, IN.texUV).a;\n\
#else\n\
	// Invalid state, should never ever happen!\n\
	OUT.color.rgb = 0;\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
