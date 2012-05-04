/*********************************************************\
 *  File: SPTessellationShaders_Cg.cpp                   *
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


// [TODO] Under construction: Cg version not tested, yet (requires a NVIDIA GPU :/)
// Shaders are from: http://prideout.net/blog/?p=48 (Philip Rideout, "The Little Grasshopper - Graphics Programming Tips")
// -> Ported to Cg syntax


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
static const PLCore::String sVertexShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float3 VertexPosition : POSITION;	// Object space vertex position input
};

// Programs
VS_OUTPUT main(float3 VertexPosition : POSITION)	// Object space vertex position input
{
	VS_OUTPUT Out;

	// Pass through the object space vertex position
	Out.VertexPosition = VertexPosition;

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Tessellation control shader source code               ]
//[-------------------------------------------------------]
static const PLCore::String sTessellationControlShaderSourceCodeCg = STRINGIFY(
gp5tcp PATCH_3
void main(
		// Input
		in int				   InvocationID	: CONTROLPOINT_ID,
		in AttribArray<float3> vPosition	: POSITION,		// Vertex position input received from the vertex shader
		// Uniforms
		uniform float TessellationLevelInner,				// Inner tessellation level
		uniform float TessellationLevelOuter,				// Outer tessellation level
		// Output
		out precise float3 tcPosition		 : POSITION,	// Vertex position output
		out			float  TessLevelOuter[3] : EDGETESS,	// Outer tessellation level
		out			float  TessLevelInner[1] : INNERTESS	// Inner tessellation level
	)
{
	tcPosition = vPosition[InvocationID];
	if (InvocationID == 0) {
		TessLevelInner[0] = TessellationLevelInner;
		TessLevelOuter[0] = TessellationLevelOuter;
		TessLevelOuter[1] = TessellationLevelOuter;
		TessLevelOuter[2] = TessellationLevelOuter;
	}
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Tessellation evaluation shader source code            ]
//[-------------------------------------------------------]
static const PLCore::String sTessellationEvaluationShaderSourceCodeCg = STRINGIFY(
gp5tep TRIANGLES PATCH_3 SPACE_EQUAL ORDER_CW
void main(
		// Input
		in float3			   TessCoord  : TESSCOORD,
		in AttribArray<float3> tcPosition : POSITION,	// Vertex position input received from the tesselator
		// Uniforms
		uniform float4x4 ObjectSpaceToClipSpaceMatrix,	// Object space to clip space matrix
		// Output
		out precise float3 Position		   : POSITION,
		out precise float3 tePosition	   : ATTR0,
		out precise float3 tePatchDistance : ATTR1
	)
{
	float3 p0 = TessCoord.x*tcPosition[0];
	float3 p1 = TessCoord.y*tcPosition[1];
	float3 p2 = TessCoord.z*tcPosition[2];
	tePatchDistance = TessCoord;
	tePosition = normalize(p0 + p1 + p2);
	Position = mul(ObjectSpaceToClipSpaceMatrix, float4(tePosition, 1));
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Geometry shader source code                           ]
//[-------------------------------------------------------]
static const PLCore::String sGeometryShaderSourceCodeCg = STRINGIFY(
TRIANGLE void main(AttribArray<float3> Position		   : POSITION,	// Clip space vertex positions from tessellation evaluation shader, lower/left is (-1,-1) and upper/right is (1,1)
				   AttribArray<float3> tePosition	   : ATTR0,
				   AttribArray<float3> tePatchDistance : ATTR1,
				   uniform float3x3 NormalMatrix					// Object space to clip space rotation matrix
	)
{
	float3 A = tePosition[2] - tePosition[0];
	float3 B = tePosition[1] - tePosition[0];
	float3 gFacetNormal = mul(NormalMatrix, normalize(cross(A, B)));

	float3 gTriDistance = float3(1, 0, 0);
	emitVertex(Position[0] : POSITION, gFacetNormal : ATTR0, tePatchDistance[0] : ATTR1, gTriDistance : ATTR2);

	gTriDistance = float3(0, 1, 0);
	emitVertex(Position[1] : POSITION, gFacetNormal : ATTR0, tePatchDistance[1] : ATTR1, gTriDistance : ATTR2);

	gTriDistance = float3(0, 0, 1);
	emitVertex(Position[2] : POSITION, gFacetNormal : ATTR0, tePatchDistance[2] : ATTR1, gTriDistance : ATTR2);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
static const PLCore::String sFragmentShaderSourceCodeCg = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float3 Position		  : POSITION;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float3 gFacetNormal   : ATTR0;
	float3 gTriDistance   : ATTR1;
	float3 gPatchDistance : ATTR2;
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR0;
};

// Programs
float Amplify(float d, float scale, float offset)
{
	d = scale*d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2*d*d);
	return d;
}

FS_OUTPUT main(VS_OUTPUT	  In,	// Geometry shader output as fragment shader input
			   uniform float3 LightPosition,
			   uniform float3 DiffuseMaterial,
			   uniform float3 AmbientMaterial)
{
	FS_OUTPUT Out;

	float3 N = normalize(In.gFacetNormal);
	float3 L = LightPosition;
	float df = abs(dot(N, L));
	float3 color = AmbientMaterial + df*DiffuseMaterial;

	float d1 = min(min(In.gTriDistance.x, In.gTriDistance.y), In.gTriDistance.z);
	float d2 = min(min(In.gPatchDistance.x, In.gPatchDistance.y), In.gPatchDistance.z);
	color = Amplify(d1, 40, -0.5)*Amplify(d2, 60, -0.5)*color;

	Out.Color0 = float4(color, 1.0);

	// Done
	return Out;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
