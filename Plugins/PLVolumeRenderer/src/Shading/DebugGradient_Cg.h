/*********************************************************\
 *  File: DebugGradient_Cg.h                             *
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
/**
*  @brief
*    Shading
*
*  @param[in] Scalar
*    Current voxel scalar
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in] StepPositionDelta
*    Position advance per step along the ray, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    RGBA result of the shading
*/
float4 Shading(float Scalar, float3 Position, float3 StepPositionDelta)
{
	// Call the classification function
	//     float4 Classification(float Scalar)
	float4 color = Classification(Scalar);

	// Call the gradient function
	//     float3 Gradient(float3 Position)
	float3 gradient = Gradient(Position);

	// Show gradient, only normalized if length is greater than one
	// Calculate the normalized normal, avoid nasty division by zero
	// -> We can't visualize negative values, so only positive values, please
	float gradientLength = length(gradient);
	if (gradientLength > 0.0)
		return (gradientLength > 1.0) ? float4(abs(gradient/gradientLength), color.a) : float4(abs(gradient), color.a);
	else
		return float4(0.0, 0.0, 0.0, color.a);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
