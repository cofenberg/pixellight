/*********************************************************\
 *  File: SRPDeferredGodRays_GLSL.h                      *
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


// OpenGL 2.0 ("#version 110") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sDeferredGodRays_GLSL_VS = "\
// Attributes\n\
attribute vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying   vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform ivec2 TextureSize;	// Texture size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*vec2(TextureSize);\n\
}";


// OpenGL 2.0 ("#version 110") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sDeferredGodRays_GLSL_FS = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform float			NumberOfSamples;	// Number of samples, must be >0 (should be of integer type, but that's causing troubles on some GPU drivers, see PLCompositing diary entry 02.06.2011 for more details)\n\
uniform float			Density;			// Density, must be >0\n\
uniform float			Weight;				// Weight\n\
uniform float			Decay;				// Decay\n\
uniform vec2			LightPosition;		// Screen space light position, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
uniform vec3			Color;				// Color\n\
uniform sampler2DRect	Map;				// Map\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate vector from pixel to light source in screen space\n\
	vec2 texUV = VertexTexCoordVS;\n\
	vec2 deltaTexUV = texUV - LightPosition;\n\
\n\
	// Divide by number of samples and scale by control factor\n\
	deltaTexUV *= 1.0/NumberOfSamples*Density;\n\
\n\
	// Store initial sample\n\
	vec3 color = texture2DRect(Map, VertexTexCoordVS).rgb;\n\
\n\
	// Set up illumination decay factor\n\
	float illuminationDecay = 1.0;\n\
\n\
	// Evaluate summation\n\
	for (int i=0; i<int(NumberOfSamples); i++) {\n\
		// Step sample location along ray\n\
		texUV -= deltaTexUV;\n\
\n\
		// Retrieve sample at new location\n\
		vec3 sample = texture2DRect(Map, texUV).rgb;\n\
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
	vec3 resultingColor = color*Color;\n\
\n\
	// Use discard?\n\
#ifdef FS_DISCARD\n\
	if (resultingColor.r == 0.0 && resultingColor.g == 0.0 && resultingColor.b == 0.0)\n\
		discard;\n\
#endif\n\
\n\
	// Set fragment color\n\
	gl_FragColor = vec4(resultingColor, 1.0);\n\
}";
