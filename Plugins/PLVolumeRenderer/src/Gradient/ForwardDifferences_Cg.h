/*********************************************************\
 *  File: ForwardDifferences_Cg.h                        *
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


// Finite differences
// On-the-fly gradient computation approximating gradient vectors using the forward differences scheme
// as described within the book "Real-Time Volume Graphics", section "5.3.1 Gradient Estimation" (page 109).
// -> Also described within "ACM SIGGRAPH Asia 2008 - Course : Advanced Illumination Techniques for GPU Volume Raycasting" (http://www.voreen.org/files/sa08-coursenotes_1.pdf), section "3.2 Gradient Computation"


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
float3 Gradient(float3 Position)
{
	// Call the gradient input function by using a texel offset
	//     float GradientInputOffset(vec3 Position, int3 Offset)

	// 4 volume texture fetches for the gradient
	float value  = GradientInput(Position);
	float valueX = GradientInputOffset(Position, int3(1, 0, 0));
	float valueY = GradientInputOffset(Position, int3(0, 1, 0));
	float valueZ = GradientInputOffset(Position, int3(0, 0, 1));

	// Forward differences
	return float3(valueX - value, valueY - value, valueZ - value);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
