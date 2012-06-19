/*********************************************************\
 *  File: Lighting_GLSL.h                                *
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
// Uniforms
uniform vec3 ViewingDirection;	// Viewing direction in scene node space
uniform vec3 LightDirection;	// Normalized light direction in scene node space
uniform vec3 AmbientColor;		// Ambient color

// Varying
vec3 previousNormal = vec3(0.0, 0.0, 0.0);	// Normal from the previous step

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
	//     vec4 Classification(float Scalar)
	vec4 color = Classification(Scalar);

	// Call the gradient function
	//     vec3 Gradient(vec3 Position)
	vec3 gradient = Gradient(Position);

	// Calculate the normalized normal, avoid nasty division by zero
	float gradientLength = length(gradient);
	vec3 normal = (gradientLength > 0.0) ? gradient/gradientLength : previousNormal;

	// Backup the currently used normal vector
	previousNormal = normal;

	// Call the illumination function
	//     vec3 Illumination(vec3 SurfaceColor, vec3 SurfaceNormal, vec3 ViewingDirection, vec3 LightDirection)
	color.rgb = AmbientColor + Illumination(color.rgb, normal, ViewingDirection, LightDirection);

	// Return the RGBA result of the shading
	return color;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
