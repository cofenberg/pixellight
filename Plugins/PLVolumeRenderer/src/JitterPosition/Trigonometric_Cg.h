/*********************************************************\
 *  File: Trigonometric_Cg.h                             *
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float DitherRay;	// Scale factor for dithering the ray's start position in order to avoid wooden grain effects (usually value between 0...1)

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
	return DitherRay*fract(cos(JitterPosition_FragmentCoordinate.x*11.55 + JitterPosition_FragmentCoordinate.y*42.123)*35684.525);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
