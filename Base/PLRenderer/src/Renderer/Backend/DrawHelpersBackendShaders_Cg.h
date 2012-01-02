/*********************************************************\
 *  File: DrawHelpersBackendShaders_Cg.cpp               *
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
static const PLCore::String sVertexShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	#ifdef VS_TEXCOORD0\n\
		float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
	#endif\n\
	#ifdef VS_VERTEXCOLOR\n\
		float4 Color : COLOR0;			// Vertex color\n\
	#endif\n\
};\n\
\n\
// Programs\n\
VS_OUTPUT main(float3 VertexPosition : POSITION			// Object space vertex position input\n\
	#ifdef VS_TEXCOORD0\n\
		, float2 VertexTextureCoordinate : TEXCOORD0	// Vertex texture coordinate input\n\
		, uniform float4x4 TextureMatrix				// Texture matrix\n\
	#endif\n\
	#ifdef VS_VERTEXCOLOR\n\
		, float4 VertexColor : COLOR0					// Vertex color input\n\
	#endif\n\
	, uniform float4x4 ObjectSpaceToClipSpaceMatrix		// Object space to clip space matrix\n\
)\n\
{\n\
	VS_OUTPUT Out;\n\
\n\
	// Calculate the clip space vertex position\n\
	Out.Position = mul(ObjectSpaceToClipSpaceMatrix, float4(VertexPosition, 1));\n\
\n\
#ifdef VS_TEXCOORD0\n\
	// Pass through the texture coordinate\n\
	Out.TexCoord = mul(TextureMatrix, float4(VertexTextureCoordinate, 1, 1)).xy;\n\
#endif\n\
\n\
#ifdef VS_VERTEXCOLOR\n\
	// Pass through the color\n\
	Out.Color = VertexColor;\n\
#endif\n\
\n\
	// Done\n\
	return Out;\n\
}";


// Cg fragment shader source code
static const PLCore::String sFragmentShaderSourceCodeCg = "\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 Position : POSITION;			// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	#ifdef FS_DIFFUSEMAP\n\
		float2 TexCoord : TEXCOORD0;	// Vertex texture coordinate\n\
	#endif\n\
	#ifdef FS_VERTEXCOLOR\n\
		float4 Color : COLOR0;			// Vertex color\n\
	#endif\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 Color0 : COLOR0;\n\
};\n\
\n\
// Programs\n\
FS_OUTPUT main(VS_OUTPUT In						// Vertex shader or geometry shader output as fragment shader input\n\
	#ifndef FS_VERTEXCOLOR\n\
		, uniform float4 Color					// Color\n\
	#endif\n\
	#ifdef FS_DIFFUSEMAP\n\
		#ifdef FS_DIFFUSEMAP2D\n\
			, uniform sampler2D DiffuseMap		// 2D diffuse map\n\
		#else\n\
			, uniform samplerRECT DiffuseMap	// Rectangle diffuse map\n\
		#endif\n\
		#ifdef FS_ALPHATEST\n\
			, uniform float AlphaReference		// Alpha reference\n\
		#endif\n\
	#endif\n\
)\n\
{\n\
	FS_OUTPUT Out;\n\
\n\
#ifdef FS_DIFFUSEMAP\n\
	#ifdef FS_DIFFUSEMAP2D\n\
		Out.Color0 = tex2D(DiffuseMap, In.TexCoord);\n\
	#else\n\
		Out.Color0 = texRECT(DiffuseMap, In.TexCoord);\n\
	#endif\n\
	#ifdef FS_ALPHATEST\n\
		// Perform an alpha test to discard fragments\n\
		if (Out.Color0.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
\n\
	// Still here? Then apply the given color...\n\
	#ifdef FS_VERTEXCOLOR\n\
		Out.Color0 *= In.Color;\n\
	#else\n\
		Out.Color0 *= Color;\n\
	#endif\n\
#else\n\
	#ifdef FS_VERTEXCOLOR\n\
		Out.Color0 = In.Color;\n\
	#else\n\
		Out.Color0 = Color;\n\
	#endif\n\
#endif\n\
\n\
	// Done\n\
	return Out;\n\
}";
