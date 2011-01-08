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
static const PLGeneral::String sDeferredSSAO_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec4 VertexTexCoordVS;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
										// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;		// Texture size in texel\n\
uniform highp ivec2 InputTextureSize;	// Input size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS.xy = VertexPosition.zw*TextureSize;\n\
	VertexTexCoordVS.zw = VertexPosition.zw*InputTextureSize;\n\
}";


// GLSL vertex shader source code
static const PLGeneral::String sDeferredSSAO_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec4 VertexTexCoordVS;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
										// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform highp float			BlurRadius;			// Blur radius\n\
uniform highp float			BlurFalloff;		// Blur falloff\n\
uniform highp float			Sharpness;			// Sharpness\n\
uniform highp vec2			UVScale;			// UV scale\n\
uniform highp sampler2DRect	InputTexture;		// Input texture\n\
uniform highp sampler2DRect	NormalDepthTexture;	// RG=normal vector, B=linear view space length\n\
\n\
// Programs\n\
highp float FetchEyeZ(highp sampler2DRect normalDepthTexture, highp vec2 uv)\n\
{\n\
	return texture2DRect(normalDepthTexture, uv).b;\n\
}\n\
\n\
highp float BlurFunction(highp sampler2DRect inputTexture, highp sampler2DRect normalDepthTexture, highp float blurFalloff, highp float sharpness, highp vec2 uv, highp vec2 uvInput, highp float r, highp float center_c, highp float center_d, inout highp float w_total)\n\
{\n\
	highp float c = texture2DRect(inputTexture, uvInput).r;\n\
	highp float d = FetchEyeZ(normalDepthTexture, uv);\n\
\n\
	highp float ddiff = d - center_d;\n\
	highp float w = exp(-r*r*blurFalloff - ddiff*ddiff*sharpness);\n\
	w_total += w;\n\
\n\
	return w*c;\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	highp float b = 0.0f;\n\
	highp float w_total = 0.0f;\n\
	highp float center_c = texture2DRect(InputTexture, VertexTexCoordVS.zw).r;\n\
	highp float center_d = FetchEyeZ(NormalDepthTexture, VertexTexCoordVS.xy);\n\
	for (highp float r=-BlurRadius; r<=BlurRadius; r++)\n\
		b += BlurFunction(InputTexture, NormalDepthTexture, BlurFalloff, Sharpness, VertexTexCoordVS.xy + r*UVScale, VertexTexCoordVS.zw + r*UVScale, r, center_c, center_d, w_total);\n\
	gl_FragColor = vec4(b/w_total);\n\
}";
