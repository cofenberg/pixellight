/*********************************************************\
 *  File: DVRBackToFront_Cg.h                            *
 *      Fragment shader source code - Cg
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


// Back-to-front compositing as described within the book "Real-Time Volume Graphics", section "7.1 Basic Structure of Ray Casting" (page 165)
// -> No early ray termination
// -> Requires opacity correction
//   -> Described in the book "Real-Time Volume Graphics", section "9.1.3 Opacity Correction" (page 219)
//   -> Also described in "GPU Gems", section "39.4.3 Rendering" ( http://http.developer.nvidia.com/GPUGems/gpugems_ch39.html )


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float OpacityCorrectionFactor;	// Opacity correction factor
uniform float Opacity;					// Opacity, usually within the interval [~0 .. 1] = [transparent .. solid]

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
float4 RayTraversal(float3 StartPosition, int NumberOfSteps, float3 StepPositionDelta, float MaximumTravelLength)
{
	// Current position inside the volume
	float3 currentPosition = StartPosition + NumberOfSteps*StepPositionDelta;

	// Color accumulation variable
	float4 destinationColor = float4(0.0, 0.0, 0.0, 0.0);

	// Integrate back-to-front over the volume
	// -> Back-to-front traversal
	for (int step=NumberOfSteps; step>0; step--) {
		// Call the clip position function
		//     bool ClipPosition(float3 Position)
		if (!ClipPosition(currentPosition)) {
			// Call the reconstruction function
			//     float Reconstruction(float3 Position)
			float scalar = Reconstruction(currentPosition);

			// Call the shading function
			//     vec4 Shading(float Scalar, float3 Position, float3 StepPositionDelta)
			float4 sourceColor = Shading(scalar, currentPosition, StepPositionDelta);

			// Apply opacity correction
			sourceColor.a = (1.0 - pow(1.0 - sourceColor.a, OpacityCorrectionFactor))*Opacity;

			// Back-to-front compositing
			destinationColor.rgb = (1.0 - sourceColor.a)*destinationColor.rgb + sourceColor.a*sourceColor.rgb;

			// Accumulate alpha
			destinationColor.a += sourceColor.a;
		}

		// Update the current position inside the volume
		currentPosition -= StepPositionDelta;
	}

	// Return the calculated fragment color
	return destinationColor;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
