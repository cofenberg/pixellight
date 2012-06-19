/*********************************************************\
 *  File: Lighting_Cg.h                                  *
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
uniform float3 ViewingDirection;	// Viewing direction in scene node space
uniform float3 LightDirection;		// Normalized light direction in scene node space
uniform float3 AmbientColor;		// Ambient color

// Varying
float3 previousNormal = float3(0.0, 0.0, 0.0);	// Normal from the previous step

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

	// Calculate the normalized normal, avoid nasty division by zero
	float gradientLength = length(gradient);
	float3 normal = (gradientLength > 0.0) ? gradient/gradientLength : previousNormal;

	// Backup the currently used normal vector
	previousNormal = normal;

	// Call the illumination function
	//     float3 Illumination(float3 SurfaceColor, float3 SurfaceNormal, float3 ViewingDirection, float3 LightDirection)
	color.rgb = AmbientColor + Illumination(color.rgb, normal, ViewingDirection, LightDirection);

	// Return the RGBA result of the shading
	return color;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
