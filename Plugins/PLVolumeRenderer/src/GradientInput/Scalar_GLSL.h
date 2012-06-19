/*********************************************************\
 *  File: Scalar_GLSL.h                                  *
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


static const PLCore::String sSourceCode_Fragment_Part = STRINGIFY(
/**
*  @brief
*    Fetches the gradient input by using a given position inside the volume
*
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Gradient input
*/
float GradientInput(vec3 Position)
{
	// Call the fetch scalar function
	//     float FetchScalar(vec3 Position)
	return FetchScalar(Position);
}
);	// STRINGIFY

/**
*  @brief
*    Fetches the gradient input by using a given position inside the volume by using a texel offset
*
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in] Offset
*    Texel offset
*
*  @return
*    Gradient input
*/
// Call the fetch scalar function by using a texel offset
//     float FetchScalarOffset(vec3 Position, ivec3 Offset)
// When realizing this as function, I received the following GLSL compiler error:
//   "error(#30) Built-in function parameter type check fail: offset must be a constant/literal in texture functions Offset should be a constant expression"
// -> According to the GLSL specification ("The OpenGL® Shading Language - Language Version: 3.30 - Document Revision: 6 - 11-Mar-2010") this behaviour correct in general
// -> When resolving functions, the GLSL compiler was unable to detect that the given parameter was actually constant/literal
// -> So, this one in here is realized by using a macro instead of a function
// -> Used system: "ATI Mobility Radeon HD 4850" (512 MiB) using Catalyst 12.1 and Windows 7 64 bit
static const PLCore::String sSourceCode_Fragment = sSourceCode_Fragment_Part + "\n#define GradientInputOffset(Position, Offset) FetchScalarOffset(Position, Offset)\n";


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
