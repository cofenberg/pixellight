/*********************************************************\
 *  File: TransferFunction_GLSL.h                        *
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


// Standard post-interpolative transfer function


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform sampler1D TransferFunctionTexture;	// Transfer function texture map

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
vec4 Classification(float Scalar)
{
	// Apply 1D transfer function
	vec4 sample = textureLod(TransferFunctionTexture, Scalar, 0.0);

	// [TODO] Only required for HDR rendering with gamma correction -> Add a trigger
	// [TODO] For better performance, put this directly within the 1D texture
	// Perform sRGB to linear space conversion (gamma correction)
	sample.rgb = pow(sample.rgb, vec3(2.2, 2.2, 2.2));

	// Return the result of the scalar classification
	return sample;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
