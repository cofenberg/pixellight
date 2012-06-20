/*********************************************************\
 *  File: Isosurface_GLSL.h                              *
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
uniform float IsosurfaceValue;	// Isosurface value
uniform float Opacity;			// Opacity, usually within the interval [~0 .. 1] = [transparent .. solid]

/**
*  @brief
*    Integrates over the volume
*
*  @param[in] StartPosition
*    Start position of the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in] NumberOfSteps
*    Number of steps along the ray (= number of samples to take), must be positive
*  @param[in] StepPositionDelta
*    Position advance per step along the ray, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in] MaximumTravelLength
*    Maximum travel length along the ray, within the interval [0 .. 1]
*
*  @return
*    RGBA result of the ray traversal
*/
vec4 RayTraversal(vec3 StartPosition, int NumberOfSteps, vec3 StepPositionDelta, float MaximumTravelLength)
{
	// Current position inside the volume
	vec3 currentPosition = StartPosition;

	// Integrate over the volume
	for (int step=0; step<NumberOfSteps; step++) {
		// Call the clip position function
		//     bool ClipPosition(vec3 Position)
		if (!ClipPosition(currentPosition)) {
			// Call the reconstruction function
			//     float Reconstruction(vec3 Position)
			float scalar = Reconstruction(currentPosition);

			// Check for isosurface value match
			if (scalar > IsosurfaceValue) {
				// Intersection refinement as mentioned within the book "Real-Time Volume Graphics", section "14.5.1 Deferred Shading Pipeline" (page 374)
				// -> Improve image quality by sacrificing a bit of the performance
				StepPositionDelta *= -0.5;
				for (int i=0; i<4; i++) {
					// Update the current position inside the volume
					currentPosition += StepPositionDelta;

					// Call the reconstruction function
					//     float Reconstruction(vec3 Position)
					scalar = Reconstruction(currentPosition);

					// Update the refine advance
					StepPositionDelta *= (scalar > IsosurfaceValue) ?  0.5 : -0.5;
				}

				// Call the shading function
				//     vec4 Shading(float Scalar, vec3 Position, vec3 StepPositionDelta)
				vec4 color = Shading(scalar, currentPosition, StepPositionDelta);

				// Ignore calculated opacity, this is a solid surface
				return vec4(color.rgb, Opacity);
			}
		}

		// Update the current position inside the volume
		currentPosition += StepPositionDelta;
	}

	// No isosurface hit
	return vec4(0.0, 0.0, 0.0, 0.0);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
