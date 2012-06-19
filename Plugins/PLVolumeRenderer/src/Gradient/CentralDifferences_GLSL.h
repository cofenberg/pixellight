/*********************************************************\
 *  File: CentralDifferences_GLSL.h                      *
 *      Fragment shader source code - GLSL (OpenGL 3.3 ("#version 330")
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


// Finite differences
// On-the-fly gradient computation approximating gradient vectors using the central differences scheme
// as described within the book "Real-Time Volume Graphics", section "5.3.1 Gradient Estimation" (page 109) and section "5.6 On-the-Fly Gradients" (page 127).
// -> Also described within the book "GPU Gems", section "39.4.1 Data Representation and Processing" (http://http.developer.nvidia.com/GPUGems/gpugems_ch39.html)


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
/**
*  @brief
*    Gradient
*
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Gradient (not normalized)
*/
vec3 Gradient(vec3 Position)
{
	// Call the gradient input function by using a texel offset
	//     float GradientInputOffset(vec3 Position, ivec3 Offset)

	// 6 volume texture fetches for the gradient
	vec3 sample1;
	sample1.x = GradientInputOffset(Position, ivec3(-1,  0,  0));
	sample1.y = GradientInputOffset(Position, ivec3( 0, -1,  0));
	sample1.z = GradientInputOffset(Position, ivec3( 0,  0, -1));
	vec3 sample2;
	sample2.x = GradientInputOffset(Position, ivec3( 1,  0,  0));
	sample2.y = GradientInputOffset(Position, ivec3( 0,  1,  0));
	sample2.z = GradientInputOffset(Position, ivec3( 0,  0,  1));

	// Central difference
	return sample2 - sample1;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
