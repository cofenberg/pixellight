/*********************************************************\
 *  File: Stochastic_Cg.h                                *
 *      Fragment shader source code - Cg
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


// "Stochastic Jittering" as described within the book "Real-Time Volume Graphics", section "9.1.4 Stochastic Jittering" (page 220)


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float     DitherRay;		// Scale factor for dithering the ray's start position in order to avoid wooden grain effects (usually value between 0...1)
uniform sampler2D RandomTexture;	// Random texture map
uniform float2    InvTileSize;		// 1/<tile size> (avoid expensive division within the fragment shader)

// Varying
float2 JitterPosition_FragmentCoordinate : WPOS;

/**
*  @brief
*    Jitter the start position of the ray in order to reduce wooden grain effect
*
*  @param[in] Position
*    Position inside the volume to perform jitter on, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Jitter factor, usually in the interval [0 .. 1]
*/
float JitterPosition(float3 Position)
{
	return DitherRay*tex2Dlod(RandomTexture, float4(JitterPosition_FragmentCoordinate*InvTileSize, 0.0, 0.0)).r;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
