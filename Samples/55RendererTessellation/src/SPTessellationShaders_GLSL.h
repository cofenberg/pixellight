/*********************************************************\
 *  File: SPTessellationShaders_GLSL.cpp                 *
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


// Shaders are from: http://prideout.net/blog/?p=48 (Philip Rideout, "The Little Grasshopper - Graphics Programming Tips")


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
// GLSL (OpenGL 4.0 ("#version 400")) vertex shader source code, "#version" is added by hand
static const PLCore::String sVertexShaderSourceCodeGLSL = STRINGIFY(
// Attributes
in  vec3 VertexPosition;	// Object space vertex position input
out vec3 vPosition;			// Vertex position output

// Programs
void main()
{
	// Pass through the vertex position
	vPosition = VertexPosition;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Tessellation control shader source code               ]
//[-------------------------------------------------------]
// GLSL (OpenGL 4.0 ("#version 400")) tessellation control shader source code, "#version" is added by hand
static const PLCore::String sTessellationControlShaderSourceCodeGLSL = STRINGIFY(
// Attributes
layout(vertices = 3) out;
in  vec3 vPosition[];	// Vertex position input received from the vertex shader
out vec3 tcPosition[];	// Vertex position output

// Uniforms
uniform float TessellationLevelInner;	// Inner tessellation level
uniform float TessellationLevelOuter;	// Outer tessellation level

// Programs
void main()
{
	tcPosition[gl_InvocationID] = vPosition[gl_InvocationID];
	if (gl_InvocationID == 0) {
		gl_TessLevelInner[0] = TessellationLevelInner;
		gl_TessLevelOuter[0] = TessellationLevelOuter;
		gl_TessLevelOuter[1] = TessellationLevelOuter;
		gl_TessLevelOuter[2] = TessellationLevelOuter;
	}
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Tessellation evaluation shader source code            ]
//[-------------------------------------------------------]
// GLSL (OpenGL 4.0 ("#version 400")) tessellation evaluation shader source code, "#version" is added by hand
static const PLCore::String sTessellationEvaluationShaderSourceCodeGLSL = STRINGIFY(
// Attributes
layout(triangles, equal_spacing, cw) in;
in  vec3 tcPosition[];	// Vertex position input received from the tesselator
out vec3 tePosition;
out vec3 tePatchDistance;

// Uniforms
uniform mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

// Programs
void main()
{
	vec3 p0 = gl_TessCoord.x*tcPosition[0];
	vec3 p1 = gl_TessCoord.y*tcPosition[1];
	vec3 p2 = gl_TessCoord.z*tcPosition[2];
	tePatchDistance = gl_TessCoord;
	tePosition = normalize(p0 + p1 + p2);
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(tePosition, 1);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Geometry shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 4.0 ("#version 400")) geometry shader source code, "#version" is added by hand
static const PLCore::String sGeometryShaderSourceCodeGLSL = STRINGIFY(
// Attributes
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in  vec3 tePosition[3];
in  vec3 tePatchDistance[3];
out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;

// Uniforms
uniform mat3 NormalMatrix;	// Object space to clip space rotation matrix

// Programs
void main()
{
	vec3 A = tePosition[2] - tePosition[0];
	vec3 B = tePosition[1] - tePosition[0];
	gFacetNormal = NormalMatrix * normalize(cross(A, B));

	gPatchDistance = tePatchDistance[0];
	gTriDistance = vec3(1, 0, 0);
	gl_Position = gl_in[0].gl_Position; EmitVertex();

	gPatchDistance = tePatchDistance[1];
	gTriDistance = vec3(0, 1, 0);
	gl_Position = gl_in[1].gl_Position; EmitVertex();

	gPatchDistance = tePatchDistance[2];
	gTriDistance = vec3(0, 0, 1);
	gl_Position = gl_in[2].gl_Position; EmitVertex();

	EndPrimitive();
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Fragment shader source code                           ]
//[-------------------------------------------------------]
// GLSL (OpenGL 4.0 ("#version 400")) fragment shader source code, "#version" is added by hand
static const PLCore::String sFragmentShaderSourceCodeGLSL = STRINGIFY(
// Attributes
layout(location = 0) out vec4 OutFragmentColor;
in vec3  gFacetNormal;
in vec3  gTriDistance;
in vec3  gPatchDistance;
in float gPrimitive;

// Uniforms
uniform vec3 LightPosition;
uniform vec3 DiffuseMaterial;
uniform vec3 AmbientMaterial;

// Programs
float Amplify(float d, float scale, float offset)
{
	d = scale*d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2*d*d);
	return d;
}

void main()
{
	vec3 N = normalize(gFacetNormal);
	vec3 L = LightPosition;
	float df = abs(dot(N, L));
	vec3 color = AmbientMaterial + df*DiffuseMaterial;

	float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
	float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
	color = Amplify(d1, 40, -0.5)*Amplify(d2, 60, -0.5)*color;

	OutFragmentColor = vec4(color, 1.0);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
