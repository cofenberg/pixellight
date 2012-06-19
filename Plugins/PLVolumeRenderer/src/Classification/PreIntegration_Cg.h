/*********************************************************\
 *  File: PreIntegration_Cg.h                            *
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


// "Pre-Integration" as described within the book "Real-Time Volume Graphics", section "4.5 Pre-Integrated Transfer Functions" (page 92) and section "7.2 Single-Pass GPU Ray Casting for Uniform Grids" (page 167).
// -> "Pre-integrated transfer functions allow us to use much lower sampling rates than post-interpolative transfer functions when using transfer functions that contain high frequencies." (quote from page 102)


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform sampler2D PreintegrationTableTexture;	// Preintegration table texture map

// Global variables
float2 previousCurrentScalar = float2(0.0, 0.0);	// x = Previous scalar, y = Current scalar

/**
*  @brief
*    Scalar classification
*
*  @param[in] Scalar
*    Scalar to perform a classification on
*
*  @return
*    RGBA result of the classification
*/
float4 Classification(float Scalar)
{
	// Set the current scalar
	previousCurrentScalar.y = Scalar;

	// Lookup in pre-integration table
	float4 sample = tex1Dlod(PreintegrationTableTexture, float4(previousCurrentScalar, 0.0, 0.0, 0.0));

	// [TODO] Only required for HDR rendering with gamma correction -> Add a trigger
	// [TODO] For better performance, put this directly within the 1D texture
	// Perform sRGB to linear space conversion (gamma correction)
	sample.rgb = pow(sample.rgb, float3(2.2, 2.2, 2.2));

	// Save the previous scalar
	previousCurrentScalar.x = Scalar;

	// Return the result of the scalar classification
	return sample;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
