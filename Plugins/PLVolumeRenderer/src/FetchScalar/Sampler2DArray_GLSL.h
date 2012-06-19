/*********************************************************\
 *  File: Sampler2DArray_GLSL.h                          *
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


static const PLCore::String sSourceCode_Fragment_Header_Part = STRINGIFY(
// Uniforms
uniform sampler2DArray VolumeTexture;		// Volume texture map
uniform float          VolumeTextureDepth;	// Depth of the volume texture (z-component)
uniform float          VolumeTextureLOD;	// Volume texture level of detail (0...<number of mipmaps>-1)

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
	// Fetch and return the requested scalar
	// -> There's no automatic filtering between the array layers
	return textureLod(VolumeTexture, vec3(Position.xy, Position.z*VolumeTextureDepth), VolumeTextureLOD).r;	// z-component = array layer index, must be an integer between [0...depth-1]
}
);	// STRINGIFY

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
// When realizing this as function, I received the following GLSL compiler error:
//   "error(#30) Built-in function parameter type check fail: offset must be a constant/literal in texture functions Offset should be a constant expression"
// -> According to the GLSL specification ("The OpenGL® Shading Language - Language Version: 3.30 - Document Revision: 6 - 11-Mar-2010") this behaviour correct in general
// -> When resolving functions, the GLSL compiler was unable to detect that the given parameter was actually constant/literal
// -> So, this one in here is realized by using a macro instead of a function
// -> Used system: "ATI Mobility Radeon HD 4850" (512 MiB) using Catalyst 12.1 and Windows 7 64 bit
static const PLCore::String sSourceCode_Fragment_Header = sSourceCode_Fragment_Header_Part + "\n#define FetchScalarOffset(Position, Offset) textureLodOffset(VolumeTexture, vec3(Position.xy, Position.z*VolumeTextureDepth), VolumeTextureLOD, Offset.xy).r\n";	// z-component = array layer index, must be an integer between [0...depth-1] and we can only use xy-offset


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
