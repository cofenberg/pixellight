/*********************************************************\
 *  File: Sampler2DArray_Cg.h                            *
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


static const PLCore::String sSourceCode_Fragment_Header = STRINGIFY(
// Uniforms
uniform sampler2DARRAY VolumeTexture;		// Volume texture map
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
float FetchScalar(float3 Position)
{
	// Fetch and return the requested scalar
	// -> There's no automatic filtering between the array layers
	return tex2DARRAYlod(VolumeTexture, float4(Position.xy, Position.z*VolumeTextureDepth, VolumeTextureLOD)).r;	// z-component = array layer index, must be an integer between [0...depth-1]
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
float FetchScalarOffset(float3 Position, int3 Offset)
{
	// Fetch and return the requested scalar
	return tex2DARRAYlod(VolumeTexture, float4(Position.xy, Position.z*VolumeTextureDepth, VolumeTextureLOD), Offset).r;	// z-component = array layer index, must be an integer between [0...depth-1]
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
