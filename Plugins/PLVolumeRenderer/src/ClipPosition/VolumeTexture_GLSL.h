/*********************************************************\
 *  File: VolumeTexture_GLSL.h                           *
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


// Template version
static const PLCore::String sSourceCode_Fragment_Template = STRINGIFY(
// Uniforms
uniform mat4      VolumeSpaceToClipVolumeTextureSpace_x_;	// Volume space to clip volume texture space matrix
uniform bool      InvertClipping_x_;						// Invert clipping?
uniform sampler3D ClipVolumeTexture_x_;						// Clip volume texture map
uniform float     ClipThreshold_x_;							// Clip threshold, everything above will be clipped

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
bool ClipPosition_x_(vec3 Position)
{
	// Transform the given volume space position into clip volume texture space
	vec3 position = (VolumeSpaceToClipVolumeTextureSpace_x_*vec4(Position, 1.0)).xyz + vec3(0.5, 0.5, 0.5);

	// In clip volume texture space, the interval is [(0, 0, 0) .. (1, 1, 1)]

	// Does the given position survive the clipping operation or is it clipped away?
	bool clipPosition = (position.x > 0.0 && position.x < 1.0 && position.y > 0.0 && position.y < 1.0 && position.z > 0.0 && position.z < 1.0);
	if (clipPosition)
		clipPosition = (textureLod(ClipVolumeTexture_x_, position, 0.0).r > ClipThreshold_x_);
	return InvertClipping_x_ ? !clipPosition : clipPosition;
}
);	// STRINGIFY

// None-template version
static const PLCore::String sSourceCode_Fragment = sSourceCode_Fragment_Template + '\n' + STRINGIFY(
bool ClipPosition(vec3 Position)
{
	// Call the function version also used by the template
	return ClipPosition_x_(Position);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
