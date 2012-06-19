/*********************************************************\
 *  File: Box_Cg.h                                       *
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


// Template version
static const PLCore::String sSourceCode_Fragment_Template = STRINGIFY(
// Uniforms
uniform float4x4 VolumeSpaceToClipBoxSpace_x_;	// Volume space to clip box space matrix
uniform bool     InvertClipping_x_;				// Invert clipping?

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
bool ClipPosition_x_(float3 Position)
{
	// Transform the given volume space position into clip box space
	float3 position = mul(VolumeSpaceToClipBoxSpace_x_, float4(Position, 1.0)).xyz;

	// In clip box space, the clip box is centered and has a radius of 0.5 along each axis

	// Does the given position survive the clipping operation or is it clipped away?
	bool clipPosition = (position.x > -0.5 && position.x < 0.5 && position.y > -0.5 && position.y < 0.5 && position.z > -0.5 && position.z < 0.5);
	return InvertClipping_x_ ? !clipPosition : clipPosition;
}
);	// STRINGIFY

// None-template version
static const PLCore::String sSourceCode_Fragment = sSourceCode_Fragment_Template + '\n' + STRINGIFY(
bool ClipPosition(float3 Position)
{
	// Call the function version also used by the template
	return ClipPosition_x_(Position);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
