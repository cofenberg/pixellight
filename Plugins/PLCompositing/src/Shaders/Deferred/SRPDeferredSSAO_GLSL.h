/*********************************************************\
 *  File: SRPDeferredSSAO_GLSL.h                         *
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


// GLSL vertex shader source code
static const PLCore::String sDeferredSSAO_GLSL_VS = "\
// GLSL preprocessor directives\n\
#version 110	// OpenGL 2.0\n\
\n\
// Attributes\n\
attribute vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   vec4 VertexTexCoordVS;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
									// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform ivec2 TextureSize;		// Texture size in texel\n\
uniform ivec2 InputTextureSize;	// Input size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS.xy = VertexPosition.zw*vec2(TextureSize);\n\
	VertexTexCoordVS.zw = VertexPosition.zw*vec2(InputTextureSize);\n\
}";


// GLSL vertex shader source code
static const PLCore::String sDeferredSSAO_GLSL_FS = "\
// GLSL preprocessor directives\n\
#version 110	// OpenGL 2.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec4 VertexTexCoordVS;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
								// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform float			BlurRadius;			// Blur radius\n\
uniform float			BlurFalloff;		// Blur falloff\n\
uniform float			Sharpness;			// Sharpness\n\
uniform vec2			UVScale;			// UV scale\n\
uniform sampler2DRect	InputTexture;		// Input texture\n\
uniform sampler2DRect	NormalDepthTexture;	// RG=normal vector, B=linear view space length\n\
\n\
// Programs\n\
float FetchEyeZ(sampler2DRect normalDepthTexture, vec2 uv)\n\
{\n\
	return texture2DRect(normalDepthTexture, uv).b;\n\
}\n\
\n\
float BlurFunction(sampler2DRect inputTexture, sampler2DRect normalDepthTexture, float blurFalloff, float sharpness, vec2 uv, vec2 uvInput, float r, float center_c, float center_d, inout float w_total)\n\
{\n\
	float c = texture2DRect(inputTexture, uvInput).r;\n\
	float d = FetchEyeZ(normalDepthTexture, uv);\n\
\n\
	float ddiff = d - center_d;\n\
	float w = exp(-r*r*blurFalloff - ddiff*ddiff*sharpness);\n\
	w_total += w;\n\
\n\
	return w*c;\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	float b = 0.0;\n\
	float w_total = 0.0;\n\
	float center_c = texture2DRect(InputTexture, VertexTexCoordVS.zw).r;\n\
	float center_d = FetchEyeZ(NormalDepthTexture, VertexTexCoordVS.xy);\n\
	for (float r=-BlurRadius; r<=BlurRadius; r++)\n\
		b += BlurFunction(InputTexture, NormalDepthTexture, BlurFalloff, Sharpness, VertexTexCoordVS.xy + r*UVScale, VertexTexCoordVS.zw + r*UVScale, r, center_c, center_d, w_total);\n\
	float value = b/w_total;\n\
	gl_FragColor = vec4(value, value, value, value);\n\
}";
