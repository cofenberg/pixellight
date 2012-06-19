/*********************************************************\
 *  File: Null_GLSL.h                                    *
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


static const PLCore::String sSourceCode_Fragment_Header = STRINGIFY(
/**
*  @brief
*    Fetches a scalar by using a given position inside the volume
*
*  @param[in] Position
*    Position inside the volume to fetch the scalar from, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Scalar, usually in the interval [0 .. 1]
*/
float FetchScalar(vec3 Position)
{
	// Nothing to do in here
	return 0.0;
}

/**
*  @brief
*    Fetches a scalar by using a given position inside the volume by using a texel offset
*
*  @param[in] Position
*    Position inside the volume to fetch the scalar from, within the interval [(0, 0, 0) .. (1, 1, 1)]
*  @param[in] Offset
*    Texel offset
*
*  @return
*    Scalar, usually in the interval [0 .. 1]
*/
float FetchScalarOffset(vec3 Position, ivec3 Offset)
{
	// Nothing to do in here
	return 0.0;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
