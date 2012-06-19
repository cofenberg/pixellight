/*********************************************************\
 *  File: DebugGradient_GLSL.h                           *
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
vec4 Shading(float Scalar, vec3 Position, vec3 StepPositionDelta)
{
	// Call the classification function
	//     float4 Classification(float Scalar)
	vec4 color = Classification(Scalar);

	// Call the gradient function
	//     vec3 Gradient(vec3 Position)
	vec3 gradient = Gradient(Position);

	// Show gradient, only normalized if length is greater than one
	// Calculate the normalized normal, avoid nasty division by zero
	// -> We can't visualize negative values, so only positive values, please
	float gradientLength = length(gradient);
	if (gradientLength > 0.0)
		return (gradientLength > 1.0) ? vec4(abs(gradient/gradientLength), color.a) : vec4(abs(gradient), color.a);
	else
		return vec4(0.0, 0.0, 0.0, color.a);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
