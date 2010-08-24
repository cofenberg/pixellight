/*********************************************************\
 *  File: SRPDeferredDOF_Cg.h                            *
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


const static char *pszDeferredDOF_DepthBlur_Cg_FS = "\n\
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
FS_OUTPUT main(VS_OUTPUT   IN			// Interpolated output from the vertex stage\n\
	 , uniform float4      DOFParams	// DOFParams coefficients\n\
										// x = near blur depth (!= y); y = focal plane depth; z = far blur depth (!= y))\n\
										// w = blurriness cutoff constant for objects behind the focal plane\n\
	 , uniform samplerRECT RGBTexture	// RGB texture\n\
	 , uniform samplerRECT NormalDepth)	// Normal depth texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch the required texel RGB data and pass it through\n\
	OUT.color.rgb = texRECT(RGBTexture, IN.texUV).rgb;\n\
\n\
	// Fetch the required texel depth data\n\
	float depth = texRECT(NormalDepth, IN.texUV).b;\n\
\n\
    // Compute depth blur\n\
    float f;\n\
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
    OUT.color.a = saturate(f*0.5f + 0.5f);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


const static char *pszDeferredDOF_Downsample_Cg_FS = "\n\
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
\n\
// Neighbor offset table\n\
const static float2 Offsets[16] = {\n\
	float2( 1.5f, -1.5f), // 0\n\
	float2( 1.5f, -0.5f), // 1\n\
	float2( 1.5f,  0.5f), // 2\n\
	float2( 1.5f,  1.5f), // 3\n\
	float2( 0.5f, -1.5f), // 4\n\
	float2( 0.5f, -0.5f), // 5\n\
	float2( 0.5f,  0.5f), // 6\n\
	float2( 0.5f,  1.5f), // 7\n\
	float2(-0.5f, -1.5f), // 8\n\
	float2(-0.5f, -0.5f), // 9\n\
	float2(-0.5f,  0.5f), // 10\n\
	float2(-0.5f,  1.5f), // 11\n\
	float2(-1.5f, -1.5f), // 12\n\
	float2(-1.5f, -0.5f), // 13\n\
	float2(-1.5f,  0.5f), // 14\n\
	float2(-1.5f,  1.5f), // 15\n\
};\n\
\n\
// Main main function\n\
FS_OUTPUT main(VS_OUTPUT  IN		// Interpolated output from the vertex stage\n\
	, uniform samplerRECT Texture)	// Texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Downsample\n\
	float4 color = 0;\n\
	for (int i=0; i<16; i++)\n\
		color += texRECT(Texture, IN.texUV + Offsets[i]);\n\
	OUT.color = color*(1.0f/16.0f);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


const static char *pszDeferredDOF_Blur_Cg_FS = "\n\
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
// Neighbor offset table\n\
const static float2 Offsets[13] = {\n\
	float2( 6,  6), // 0\n\
	float2( 5,  5), // 1\n\
	float2( 4,  4), // 2\n\
	float2( 3,  3), // 3\n\
	float2( 2,  2), // 4\n\
	float2( 1,  1), // 5\n\
	float2( 0,  0), // 6\n\
	float2(-1, -1), // 7\n\
	float2(-2, -2), // 8\n\
	float2(-3, -3), // 9\n\
	float2(-4, -4), // 10\n\
	float2(-5, -5), // 11\n\
	float2(-6, -6) // 12\n\
};\n\
const static float Weights[13] = {\n\
	0.002216, // 0\n\
	0.008764, // 1\n\
	0.026995, // 2\n\
	0.064759, // 3\n\
	0.120985, // 4\n\
	0.176033, // 5\n\
	0.199471, // 6\n\
	0.176033, // 7\n\
	0.120985, // 8\n\
	0.064759, // 9\n\
	0.026995, // 10\n\
	0.008764, // 11\n\
	0.002216  // 12\n\
};\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN		// Interpolated output from the vertex stage\n\
	 , uniform float2	   UVScale	// UV scale\n\
	 , uniform samplerRECT Texture)	// HDR texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	OUT.color = 0;\n\
	for (int i=0; i<13; i++)\n\
		OUT.color += texRECT(Texture, IN.texUV + Offsets[i]*UVScale)*Weights[i];\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


const static char *pszDeferredDOF_Result_Cg_FS = "\n\
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
#define NUM_TAPS 8				   // Number of taps the shader will use\n\
const float2 poisson[NUM_TAPS] = { // Containts poisson-distributed positions on the unit circle\n\
  { 0.7f, -0.2f},\n\
  { 0.1f, -0.9f},\n\
  { 0.3f,  0.8f},\n\
  { 0.8f,  0.3f},\n\
  {-0.7f,  0.4f},\n\
  {-0.4f,  0.6f},\n\
  {-0.8f, -0.5f},\n\
  {-0.4f,  0.6f},\n\
};\n\
\n\
const float2 maxCoC = float2(5, 10);	// Maximum circle of confusion (CoC) radius\n\
                                        // and diameter in pixels\n\
const float radiusScale = 0.4f;  // Scale factor for minimum CoC size on low res image\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT   IN				// Interpolated output from the vertex stage\n\
	 , uniform float       EffectWeight		// Effect weight\n\
	 , uniform float       BlurDownscale	// Blur downscale (never 0!)\n\
	 , uniform samplerRECT BlurTexture		// Blur texture\n\
	 , uniform samplerRECT Texture)			// Texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Fetch center tap\n\
	float4 texelColor = texRECT(Texture, IN.texUV);\n\
	OUT.color = texelColor;\n\
\n\
	// Save its depth\n\
	float centerDepth = OUT.color.a;\n\
\n\
	// Convert depth into blur radius in pixels\n\
	float discRadius = abs(OUT.color.a*maxCoC.y - maxCoC.x);\n\
\n\
	// Compute radius on low-res image\n\
	float discRadiusLow = discRadius*radiusScale*(1/BlurDownscale);\n\
\n\
	// Reusing output to accumulate samples\n\
	OUT.color = 0;\n\
	for (int i=0; i<NUM_TAPS; i++) {\n\
		// Compute tap texture coordinates\n\
		float2 coordLow  = IN.texUV/BlurDownscale + (poisson[i]*discRadiusLow);\n\
		float2 coordHigh = IN.texUV + (poisson[i]*discRadius);\n\
\n\
		// Fetch low- and high-res tap\n\
		float4 tapLow  = texRECT(BlurTexture, coordLow);\n\
		float4 tapHigh = texRECT(Texture,     coordHigh);\n\
\n\
		// Mix low- and high-res taps based on tap blurriness\n\
		float  tapBlur = abs(tapHigh.a*2 - 1); // Put blurriness into [0, 1]\n\
		float4 tap     = lerp(tapHigh, tapLow, tapBlur);\n\
\n\
		// 'smart' blur ignores taps that are closer than the center tap and in focus\n\
		tap.a = (tap.a >= centerDepth) ? 1 : abs(tap.a*2 - 1);\n\
\n\
		// Accumulate\n\
		OUT.color.rgb += tap.rgb*tap.a;\n\
		OUT.color.a   += tap.a;\n\
	}\n\
	#define FLT_MIN 1.175494351e-38F // Minimum positive value\n\
	if (OUT.color.a > FLT_MIN)\n\
		OUT.color = OUT.color/OUT.color.a;\n\
	#undef FLT_MIN\n\
\n\
	// Blend between without and with effect\n\
	OUT.color = lerp(texelColor, OUT.color, EffectWeight);\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


// Definitions:
// - DEPTH_BLUR: Show depth blur
// - BLUR:       Show blur
const static char *pszDeferredDOF_Show_Cg_FS = "\n\
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
FS_OUTPUT main(VS_OUTPUT   IN		// Interpolated output from the vertex stage\n\
	 , uniform samplerRECT Texture)	// Texture\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Show\n\
#ifdef DEPTH_BLUR\n\
	OUT.color = texRECT(Texture, IN.texUV).a;\n\
#elif defined BLUR\n\
	OUT.color = float4(texRECT(Texture, IN.texUV).rgb, 1);\n\
#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
