/*********************************************************\
 *  File: SRPDeferredGodRays_GLSL.h                      *
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
static const PLGeneral::String sDeferredGodRays_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
										// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;	// Texture size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*TextureSize;\n\
}";


// GLSL fragment shader source code (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDeferredGodRays_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp int			NumberOfSamples;	// Number of samples, must be >0\n\
uniform highp float			Density;			// Density, must be >0\n\
uniform highp float			Weight;				// Weight\n\
uniform highp float			Decay;				// Decay\n\
uniform highp vec2			LightPosition;		// Screen space light position, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
uniform lowp  vec3			Color;				// Color\n\
uniform lowp  sampler2DRect	Map;				// Map\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate vector from pixel to light source in screen space\n\
	highp vec2 texUV = VertexTexCoordVS;\n\
	highp vec2 deltaTexUV = texUV - LightPosition;\n\
\n\
	// Divide by number of samples and scale by control factor\n\
	deltaTexUV *= 1.0f/NumberOfSamples*Density;\n\
\n\
	// Store initial sample\n\
	lowp vec3 color = texture2DRect(Map, VertexTexCoordVS).rgb;\n\
\n\
	// Set up illumination decay factor\n\
	highp float illuminationDecay = 1;\n\
\n\
	// Evaluate summation\n\
	for (highp int i=0; i<NumberOfSamples; i++) {\n\
		// Step sample location along ray\n\
		texUV -= deltaTexUV;\n\
\n\
		// Retrieve sample at new location\n\
		lowp vec3 sample = texture2DRect(Map, texUV).rgb;\n\
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
	lowp vec3 resultingColor = color*Color;\n\
\n\
	// Use discard?\n\
#ifdef FS_DISCARD\n\
	if (resultingColor.r == 0 && resultingColor.g == 0 && resultingColor.b == 0)\n\
		discard;\n\
#endif\n\
\n\
	// Set fragment color\n\
	gl_FragColor = vec4(resultingColor, 1.0f);\n\
}";
