/*********************************************************\
 *  File: CentralDifferences9_Cg.h                       *
 *      Fragment shader source code - Cg
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


// Finite differences
// On-the-fly gradient computation approximating gradient vectors using the central differences scheme
// as described within the book "Real-Time Volume Graphics", section "5.3.1 Gradient Estimation" (page 109) and section "5.6 On-the-Fly Gradients" (page 127).
// -> Also described within the book "GPU Gems", section "39.4.1 Data Representation and Processing" (http://http.developer.nvidia.com/GPUGems/gpugems_ch39.html)


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform float3 GradientInvVolumeTextureSize;	// 1/<Volume texture size>

/**
*  @brief
*    Gradient via central difference
*
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Gradient (not normalized)
*/
float3 CentralDifference(float3 Position)
{
	// Call the gradient input function by using a texel offset
	//     float GradientInputOffset(float3 Position, int3 Offset)

	// 6 volume texture fetches for the gradient
	float3 sample1;
	sample1.x = GradientInputOffset(Position, int3(-1,  0,  0));
	sample1.y = GradientInputOffset(Position, int3( 0, -1,  0));
	sample1.z = GradientInputOffset(Position, int3( 0,  0, -1));
	float3 sample2;
	sample2.x = GradientInputOffset(Position, int3( 1,  0,  0));
	sample2.y = GradientInputOffset(Position, int3( 0,  1,  0));
	sample2.z = GradientInputOffset(Position, int3( 0,  0,  1));

	// Central difference
	return sample2 - sample1;
}

/**
*  @brief
*    Gradient
*
*  @param[in] Position
*    Current position along the ray inside the volume, within the interval [(0, 0, 0) .. (1, 1, 1)]
*
*  @return
*    Gradient (not normalized)
*/
vec3 Gradient(vec3 Position)
{
	float3 g0 = CentralDifference(Position);
	float3 g1 = CentralDifference(Position + float3(-GradientInvVolumeTextureSize.x, -GradientInvVolumeTextureSize.y, -GradientInvVolumeTextureSize.z));
	float3 g2 = CentralDifference(Position + float3( GradientInvVolumeTextureSize.x,  GradientInvVolumeTextureSize.y,  GradientInvVolumeTextureSize.z));
	float3 g3 = CentralDifference(Position + float3(-GradientInvVolumeTextureSize.x,  GradientInvVolumeTextureSize.y, -GradientInvVolumeTextureSize.z));
	float3 g4 = CentralDifference(Position + float3( GradientInvVolumeTextureSize.x, -GradientInvVolumeTextureSize.y,  GradientInvVolumeTextureSize.z));
	float3 g5 = CentralDifference(Position + float3(-GradientInvVolumeTextureSize.x, -GradientInvVolumeTextureSize.y,  GradientInvVolumeTextureSize.z));
	float3 g6 = CentralDifference(Position + float3( GradientInvVolumeTextureSize.x,  GradientInvVolumeTextureSize.y, -GradientInvVolumeTextureSize.z));
	float3 g7 = CentralDifference(Position + float3(-GradientInvVolumeTextureSize.x,  GradientInvVolumeTextureSize.y,  GradientInvVolumeTextureSize.z));
	float3 g8 = CentralDifference(Position + float3( GradientInvVolumeTextureSize.x, -GradientInvVolumeTextureSize.y, -GradientInvVolumeTextureSize.z));
	float3 mix0 = lerp(lerp(g1, g2, 0.5), lerp(g3, g4, 0.5), 0.5);
	float3 mix1 = lerp(lerp(g5, g6, 0.5), lerp(g7, g8, 0.5), 0.5);
	return lerp(g0, lerp(mix0, mix1, 0.5), 0.75);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
