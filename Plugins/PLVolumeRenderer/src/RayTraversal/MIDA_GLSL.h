/*********************************************************\
 *  File: MIDA_GLSL.h                                    *
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


// "Maximum intensity differences accumulation" (MIDA) as described within the paper "Instant Volume Visualization using Maximum Intensity Difference Accumulation"

// Front-to-back compositing as described within the book "Real-Time Volume Graphics", section "7.1 Basic Structure of Ray Casting" (page 165)
// -> Early ray termination
// -> Requires opacity correction
//   -> Described in the book "Real-Time Volume Graphics", section "9.1.3 Opacity Correction" (page 219)
//   -> Also described in "GPU Gems", section "39.4.3 Rendering" ( http://http.developer.nvidia.com/GPUGems/gpugems_ch39.html )


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float Opacity;	// Opacity, usually within the interval [~0 .. 1] = [transparent .. solid]

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

	// Color accumulation variable
	vec4 destinationColor = vec4(0.0, 0.0, 0.0, 0.0);

	// Integrate front-to-back over the volume
	// -> Front-to-back traversal
	float maximumScalar = 0.0;
	for (int step=0; step<NumberOfSteps; step++) {
		// Call the clip position function
		//     bool ClipPosition(vec3 Position)
		if (!ClipPosition(currentPosition)) {
			// Call the reconstruction function
			//     float Reconstruction(vec3 Position)
			float scalar = Reconstruction(currentPosition);

			// New maximum scalar value?
			if (maximumScalar < scalar) {
				float weighting = 1.0 - (scalar - maximumScalar);
				maximumScalar = scalar;

				// Call the shading function
				//     vec4 Shading(float Scalar, vec3 Position, vec3 StepPositionDelta)
				vec4 sourceColor = Shading(scalar, currentPosition, StepPositionDelta);

				// Apply the given opacity
				sourceColor.a *= Opacity;

				// Pre-multipy color by their corresponding opacity value
				sourceColor.rgb *= sourceColor.a;

				// Front-to-back compositing
				// -> MIDA only differs from standard DVR compositing by the additional weighting
				destinationColor = (1.0 - weighting*destinationColor.a)*sourceColor + weighting*destinationColor;

				// Early ray termination: Break from the loop when alpha gets high enough
				if (destinationColor.a >= 0.95)
					break;
			}
		}

		// Update the current position inside the volume
		currentPosition += StepPositionDelta;
	}

	// Return the calculated fragment color
	return destinationColor;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
