/*********************************************************\
 *  File: HDRLightAdaptation_GLSL.h                      *
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


// GLSL vertex shader source code
static const PLGeneral::String sHDRLightAdaptation_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
attribute highp vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
}";


// GLSL fragment shader source code (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sHDRLightAdaptation_GLSL_FS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Uniforms\n\
uniform highp float		Factor;				// Interpolation factor\n\
uniform highp sampler2D	PreviousTexture;	// Previous average luminance\n\
uniform highp sampler2D	CurrentTexture;		// Current average luminance\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Get the previous and current average luminance\n\
	float previouAverageLuminance = texture2D(PreviousTexture, vec2(0.5f, 0.5f)).r;\n\
	float currentAverageLuminance = texture2D(CurrentTexture,  vec2(0.5f, 0.5f)).r;\n\
\n\
	// Adapt the luminance using Pattanaik's technique\n\
	gl_FragColor = vec4(mix(previouAverageLuminance, currentAverageLuminance, Factor));\n\
}";
