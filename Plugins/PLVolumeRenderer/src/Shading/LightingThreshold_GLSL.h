/*********************************************************\
 *  File: LightingThreshold_GLSL.h                       *
 *      Fragment shader source code - GLSL (OpenGL 3.3 ("#version 330")
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float IlluminationThreshold;	// Illumination threshold, usually within the interval [0 .. 1], illumination only if opacity >= this value
uniform vec3  ViewingDirection;			// Viewing direction in scene node space
uniform vec3  LightDirection;			// Normalized light direction in scene node space
uniform vec3  AmbientColor;				// Ambient color

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

	// Do the expensive lighting only were it really matters
	if (color.a >= IlluminationThreshold) {
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
		color.rgb = Illumination(color.rgb, normal, ViewingDirection, LightDirection);
	}

	// Add ambient
	color.rgb += AmbientColor;

	// Return the RGBA result of the shading
	return color;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
