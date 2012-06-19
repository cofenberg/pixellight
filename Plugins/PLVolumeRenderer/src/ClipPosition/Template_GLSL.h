/*********************************************************\
 *  File: Template_GLSL.h                                *
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


// Shader template: We want to be able to apply multiple clip position functions at one and the same time
// -> From the outside, only one "ClipPosition()"-function should be called to keep the overal structure manageable
// -> C++ configures this shader and adds multiple "ClipPosition()"-function calls in here


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


// Template version
static const PLCore::String sSourceCode_Fragment_Template = STRINGIFY(
/**
*  @brief
*    Performs an clipping operation on the given position
*
*  @param[in] Position
*    Position inside the volume to perform clipping on, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    'true' if the given position was clipped, else 'false' if the given position survived the clipping operation
*/
bool ClipPosition(vec3 Position)
{
	_x_	// This will be replaced via C++ by real function calls

	// The given position survived the clipping operation and was not clipped away
	return false;
}
);	// STRINGIFY

// None-template version
static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// None-template version
bool ClipPosition(vec3 Position)
{
	// Nothing to do in here

	// The given position survived the clipping operation and was not clipped away
	return false;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
