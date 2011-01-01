/*********************************************************\
 *  File: SRPDeferredDOF_GLSL.h                          *
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
static const PLGeneral::String sDeferredDOF_GLSL_VS = "\
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


// Depth blur GLSL fragment shader source code
static const PLGeneral::String sDeferredDOF_GLSL_FS_DepthBlur = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec4			DOFParams;			// DOFParams coefficients\n\
												// x = near blur depth (!= y); y = focal plane depth; z = far blur depth (!= y))\n\
												// w = blurriness cutoff constant for objects behind the focal plane\n\
uniform highp sampler2DRect RGBTexture;			// RGB texture\n\
uniform highp sampler2DRect NormalDepthTexture;	// Normal depth texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel RGB data and pass it through\n\
	gl_FragColor.rgb = texture2DRect(RGBTexture, VertexTexCoordVS).rgb;\n\
\n\
	// Fetch the required texel depth data\n\
	highp float depth = texture2DRect(NormalDepthTexture, VertexTexCoordVS).b;\n\
\n\
	// Compute depth blur\n\
	highp float f;\n\
	if (depth < DOFParams.y) {\n\
		// Scale depth value between near blur distance and focal distance to [-1, 0] range\n\
		f = (depth - DOFParams.y)/(DOFParams.y - DOFParams.x);\n\
	} else {\n\
		// Scale depth value between focal distance and far blur distance to [0, 1] range\n\
		f = (depth - DOFParams.y)/(DOFParams.z - DOFParams.y);\n\
\n\
		// Clamp the far blur to a maximum blurriness\n\
		f = clamp(f, 0, DOFParams.w);\n\
	}\n\
\n\
	// Scale and bias into [0, 1] range\n\
	gl_FragColor.a = clamp(f*0.5f + 0.5f, 0.0f, 1.0f);\n\
}";


// Downscale GLSL fragment shader source code
static const PLGeneral::String sDeferredDOF_GLSL_FS_Downscale = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp sampler2DRect	Texture;	// Texture\n\
\n\
// Neighbor offset table\n\
const lowp vec2 Offsets[16] = lowp vec2[16](\n\
	lowp vec2( 1.5f, -1.5f), // 0\n\
	lowp vec2( 1.5f, -0.5f), // 1\n\
	lowp vec2( 1.5f,  0.5f), // 2\n\
	lowp vec2( 1.5f,  1.5f), // 3\n\
	lowp vec2( 0.5f, -1.5f), // 4\n\
	lowp vec2( 0.5f, -0.5f), // 5\n\
	lowp vec2( 0.5f,  0.5f), // 6\n\
	lowp vec2( 0.5f,  1.5f), // 7\n\
	lowp vec2(-0.5f, -1.5f), // 8\n\
	lowp vec2(-0.5f, -0.5f), // 9\n\
	lowp vec2(-0.5f,  0.5f), // 10\n\
	lowp vec2(-0.5f,  1.5f), // 11\n\
	lowp vec2(-1.5f, -1.5f), // 12\n\
	lowp vec2(-1.5f, -0.5f), // 13\n\
	lowp vec2(-1.5f,  0.5f), // 14\n\
	lowp vec2(-1.5f,  1.5f)  // 15\n\
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Downscale\n\
	gl_FragColor = vec4(0);\n\
	for (highp int i=0; i<16; i++)\n\
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]);\n\
	gl_FragColor = gl_FragColor*(1.0f/16.0f);\n\
}";


// Blur GLSL fragment shader source code
static const PLGeneral::String sDeferredDOF_GLSL_FS_Blur = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp vec2			UVScale;	// UV scale\n\
uniform highp sampler2DRect	Texture;	// Texture\n\
\n\
// Neighbor offset table\n\
const lowp vec2 Offsets[13] = lowp vec2[13](\n\
	lowp vec2( 6,  6), // 0\n\
	lowp vec2( 5,  5), // 1\n\
	lowp vec2( 4,  4), // 2\n\
	lowp vec2( 3,  3), // 3\n\
	lowp vec2( 2,  2), // 4\n\
	lowp vec2( 1,  1), // 5\n\
	lowp vec2( 0,  0), // 6\n\
	lowp vec2(-1, -1), // 7\n\
	lowp vec2(-2, -2), // 8\n\
	lowp vec2(-3, -3), // 9\n\
	lowp vec2(-4, -4), // 10\n\
	lowp vec2(-5, -5), // 11\n\
	lowp vec2(-6, -6)  // 12\n\
);\n\
const lowp float Weights[13] = lowp float[13](\n\
	0.002216f, // 0\n\
	0.008764f, // 1\n\
	0.026995f, // 2\n\
	0.064759f, // 3\n\
	0.120985f, // 4\n\
	0.176033f, // 5\n\
	0.199471f, // 6\n\
	0.176033f, // 7\n\
	0.120985f, // 8\n\
	0.064759f, // 9\n\
	0.026995f, // 10\n\
	0.008764f, // 11\n\
	0.002216f  // 12\n\
);\n\
\n\
// Programs\n\
void main()\n\
{\n\
	gl_FragColor = vec4(0);\n\
	for (highp int i=0; i<13; i++)\n\
		gl_FragColor += texture2DRect(Texture, VertexTexCoordVS + Offsets[i]*UVScale)*Weights[i];\n\
}";


// Result GLSL fragment shader source code
static const PLGeneral::String sDeferredDOF_GLSL_FS_Result = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp float			EffectWeight;	// Effect weight\n\
uniform highp float			BlurDownscale;	// Blur downscale (never 0!)\n\
uniform highp sampler2DRect BlurTexture;	// Blur texture\n\
uniform highp sampler2DRect Texture;		// Texture\n\
\n\
#define NUM_TAPS 8	// Number of taps the shader will use\n\
const lowp vec2 poisson[NUM_TAPS] = lowp vec2[NUM_TAPS]( // Containts poisson-distributed positions on the unit circle\n\
	lowp vec2( 0.7f, -0.2f),\n\
	lowp vec2( 0.1f, -0.9f),\n\
	lowp vec2( 0.3f,  0.8f),\n\
	lowp vec2( 0.8f,  0.3f),\n\
	lowp vec2(-0.7f,  0.4f),\n\
	lowp vec2(-0.4f,  0.6f),\n\
	lowp vec2(-0.8f, -0.5f),\n\
	lowp vec2(-0.4f,  0.6f)\n\
);\n\
\n\
const highp vec2 maxCoC = vec2(5, 10);	// Maximum circle of confusion (CoC) radius\n\
										// and diameter in pixels\n\
const highp float radiusScale = 0.4f;	// Scale factor for minimum CoC size on low res image\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch center tap\n\
	highp vec4 texelColor = texture2DRect(Texture, VertexTexCoordVS);\n\
	gl_FragColor = texelColor;\n\
\n\
	// Save its depth\n\
	highp float centerDepth = gl_FragColor.a;\n\
\n\
	// Convert depth into blur radius in pixels\n\
	highp float discRadius = abs(gl_FragColor.a*maxCoC.y - maxCoC.x);\n\
\n\
	// Compute radius on low-res image\n\
	highp float discRadiusLow = discRadius*radiusScale*(1/BlurDownscale);\n\
\n\
	// Reusing output to accumulate samples\n\
	gl_FragColor = vec4(0);\n\
	for (highp int i=0; i<NUM_TAPS; i++) {\n\
		// Compute tap texture coordinates\n\
		highp vec2 coordLow  = VertexTexCoordVS/BlurDownscale + (poisson[i]*discRadiusLow);\n\
		highp vec2 coordHigh = VertexTexCoordVS + (poisson[i]*discRadius);\n\
\n\
		// Fetch low- and high-res tap\n\
		highp vec4 tapLow  = texture2DRect(BlurTexture, coordLow);\n\
		highp vec4 tapHigh = texture2DRect(Texture,     coordHigh);\n\
\n\
		// Mix low- and high-res taps based on tap blurriness\n\
		highp float tapBlur = abs(tapHigh.a*2 - 1); // Put blurriness into [0, 1]\n\
		highp vec4  tap     = mix(tapHigh, tapLow, tapBlur);\n\
\n\
		// 'smart' blur ignores taps that are closer than the center tap and in focus\n\
		tap.a = (tap.a >= centerDepth) ? 1.0f : abs(tap.a*2 - 1);\n\
\n\
		// Accumulate\n\
		gl_FragColor.rgb += tap.rgb*tap.a;\n\
		gl_FragColor.a   += tap.a;\n\
	}\n\
	#define FLT_MIN 1.175494351e-38F // Minimum positive value\n\
	if (gl_FragColor.a > FLT_MIN)\n\
		gl_FragColor = gl_FragColor/gl_FragColor.a;\n\
	#undef FLT_MIN\n\
\n\
	// Blend between without and with effect\n\
	gl_FragColor = mix(texelColor, gl_FragColor, EffectWeight);\n\
}";


// Debug GLSL fragment shader source code
static const PLGeneral::String sDeferredDOF_GLSL_FS_Debug = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
varying highp vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp sampler2DRect Texture;	// Texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
#ifdef FS_DEPTH_BLUR\n\
	gl_FragColor = vec4(texture2DRect(Texture, VertexTexCoordVS).a);\n\
#elif defined FS_BLUR\n\
	gl_FragColor = vec4(texture2DRect(Texture, VertexTexCoordVS).rgb, 1.0f);\n\
#endif\n\
}";
