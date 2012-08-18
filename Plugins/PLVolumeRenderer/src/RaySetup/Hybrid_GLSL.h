/*********************************************************\
 *  File: Hybrid_GLSL.h                                  *
 *      Vertex and fragment shader source code - GLSL (OpenGL 3.3 ("#version 330")
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


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
static const PLCore::String sSourceCode_Vertex = STRINGIFY(
// Attributes
in  vec3 VertexPosition;	// Object space vertex position input
in  vec3 VertexTexCoord;	// Vertex texture coordinate input
out vec3 VertexTexCoordVS;	// Vertex texture coordinate output

// Uniforms
uniform mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

// Programs
void main()
{
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1.0);

	// Pass through the vertex texture coordinate
	VertexTexCoordVS = VertexTexCoord;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
static const PLCore::String sSourceCode_Fragment_Header = STRINGIFY(
// Attributes
					 in  vec3 VertexTexCoordVS;	// Interpolated vertex texture coordinate input from vertex shader, the position (volume object space) the ray leaves the volume
layout(location = 0) out vec4 OutFragmentColor;	// Resulting fragment color

// Uniforms
uniform vec3  RayOrigin;	// Ray origin in volume object space
uniform float StepSize;		// Step size
);	// STRINGIFY

static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Programs
void main()
{
	// The position (volume object space) the ray leaves the volume is provided by the vertex shader
	vec3 rayEndPosition = VertexTexCoordVS;

	// Get normalized ray direction in volume object space
	vec3 rayDirection = normalize(rayEndPosition - RayOrigin);

	// Calculate the distance our ray travels through the volume
	float maximumTravelLength;
	{ // Intersect ray with a cube (http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm)
		// Compute intersection of ray with all six bbox planes
		// (due overhead we don't test for division by zero)
		vec3 tbot = (vec3(0.0, 0.0, 0.0) - RayOrigin) / rayDirection;
		vec3 ttop = (vec3(1.0, 1.0, 1.0) - RayOrigin) / rayDirection;

		// Re-order intersections to find smallest and largest on each axis
		vec3 tmin = min(ttop, tbot);
		vec3 tmax = max(ttop, tbot);

		// Find the largest tmin and the smallest tmax
		float near = max(max(tmin.x, tmin.y), max(tmin.x, tmin.z));
		float far  = min(min(tmax.x, tmax.y), min(tmax.x, tmax.z));

		// Clamp near
		if (near < 0.0)
			near = 0.0;

		// [DEBUG] Fragment color = [0, 1] -> 1 (white) if there was an intersection, else 0 (black) -> result should always be white because we're drawing a cube in order to generate the rays
		// OutFragmentColor = (far > near) ? vec4(1.0, 1.0, 1.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0); return;

		// Calculate the distance our ray travels through the volume
		maximumTravelLength = far - near;
	}

	// Calculate the position (volume object space) the ray enters the volume
	vec3 rayStartPosition = rayEndPosition - rayDirection*maximumTravelLength;

	// Calculate the position advance per step along the ray
	vec3 stepPositionDelta = rayDirection*StepSize;

	// Call the clip ray function
	//     void ClipRay(inout vec3 RayOrigin, vec3 RayDirection, inout float MaximumTravelLength)
	ClipRay(rayStartPosition, rayDirection, maximumTravelLength);

	// Call the jitter position function to add jittering to the start position of the ray in order to reduce wooden grain effect
	//     float JitterPosition(vec3 Position)
	rayStartPosition += stepPositionDelta*JitterPosition(rayStartPosition);

	// Call the ray traversal function
	//     vec4 RayTraversal(vec3 StartPosition, int NumberOfSteps, vec3 StepPositionDelta, float MaximumTravelLength)
	// -> Clamp the result to [0, 1] interval, else the image might flicker ugly on NVIDIA GPU's while working fine on AMD GPU'S (HDR only issue)
	OutFragmentColor = (maximumTravelLength > 0.0) ? clamp(RayTraversal(rayStartPosition, int(maximumTravelLength/StepSize), stepPositionDelta, maximumTravelLength), vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0)) : vec4(0.0, 0.0, 0.0, 0.0);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
