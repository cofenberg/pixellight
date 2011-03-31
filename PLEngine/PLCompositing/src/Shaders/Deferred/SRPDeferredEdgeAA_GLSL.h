/*********************************************************\
 *  File: SRPDeferredEdgeAA_GLSL.h                       *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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


// GLSL vertex shader source code
static const PLGeneral::String sDeferredEdgeAA_GLSL_VS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// Attributes\n\
highp in  vec4 VertexPosition;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
									// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
highp out vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output\n\
\n\
// Uniforms\n\
uniform highp ivec2 TextureSize;	// Texture size in texel\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0f, 1.0f);\n\
\n\
	// Pass through the scaled vertex texture coordinate\n\
	VertexTexCoordVS = VertexPosition.zw*TextureSize;\n\
}";


// GLSL fragment shader source code
static const PLGeneral::String sDeferredEdgeAA_GLSL_FS = "\
// GLSL preprocessor directives\n\
#version 130	// OpenGL 3.0\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
highp in vec2 VertexTexCoordVS;	// Vertex texture coordinate input from vertex shader\n\
\n\
// Uniforms\n\
uniform highp float	MinGradient;			// Minumum gradient\n\
uniform highp float	WeightScale;			// Weight scale\n\
#ifdef FS_SHOW_EDGES\n\
	uniform lowp vec3 EdgeColor;			// Edge color\n\
#endif\n\
uniform highp sampler2DRect FrontMap;		// Front texture\n\
uniform highp sampler2DRect NormalDepthMap;	// Normal depth texture\n\
\n\
// Neighbor offset table\n\
const lowp vec2 Offsets[9] = lowp vec2[9](\n\
	lowp vec2( 0,  0), // Center       0\n\
	lowp vec2(-1, -1), // Top left     1\n\
	lowp vec2( 0, -1), // Top          2\n\
	lowp vec2( 1, -1), // Top right    3\n\
	lowp vec2( 1,  0), // Right        4\n\
	lowp vec2( 1,  1), // Bottom right 5\n\
	lowp vec2( 0,  1), // Bottom       6\n\
	lowp vec2(-1,  1), // Bottom left  7\n\
	lowp vec2(-1,  0)  // Left         8\n\
);\n\
\n\
// Programs\n\
// Decodes a 2 component normal vector to a 3 component normal vector\n\
highp vec3 decodeNormalVector(highp vec2 normal)\n\
{\n\
	highp vec2 fenc = normal*4 - 2;\n\
	highp float f = dot(fenc, fenc);\n\
	highp float g = sqrt(1 - f/4);\n\
	highp vec3 n;\n\
	n.xy = fenc*g;\n\
	n.z = 1 - f/2;\n\
	return n;\n\
}\n\
\n\
// Program entry point\n\
void main()\n\
{\n\
	// Retrieve normal and depth data for all neighbors\n\
	highp float depth[9];\n\
	highp vec3  normal[9];\n\
	for (lowp int i=0; i<9; i++) {\n\
		// Retrieve sample at new location\n\
		highp vec3 sample = texture2DRect(NormalDepthMap, VertexTexCoordVS + Offsets[i]).xyz;\n\
\n\
		// Get depth and normal\n\
		depth[i]  = sample.b;\n\
		normal[i] = decodeNormalVector(sample.rg);\n\
	}\n\
\n\
	// Compute deltas in depth\n\
	highp vec4 deltas1;\n\
	highp vec4 deltas2;\n\
	deltas1.x = depth[1];\n\
	deltas1.y = depth[2];\n\
	deltas1.z = depth[3];\n\
	deltas1.w = depth[4];\n\
	deltas2.x = depth[5];\n\
	deltas2.y = depth[6];\n\
	deltas2.z = depth[7];\n\
	deltas2.w = depth[8];\n\
\n\
	// Compute absolute gradients from center\n\
	deltas1 = abs(deltas1 - depth[0]);\n\
	deltas2 = abs(depth[0] - deltas2);\n\
\n\
	// Find min and max gradient, ensuring min != 0\n\
	highp vec4 maxDeltas = max(deltas1, deltas2);\n\
	highp vec4 minDeltas = max(min(deltas1, deltas2), MinGradient);\n\
\n\
	// Compare change in gradients, flagging ones that change significantly.\n\
	// How severe the change must be to get flagged is a function of the\n\
	// minimum gradient. It is not resolution dependent. The constant\n\
	// number here would change based on how the depth values are stored\n\
	// and how sensitive the edge detection should be.\n\
	highp vec4 depthResults = step(minDeltas*25.0f, maxDeltas);\n\
\n\
	// Compute change in the cosine of the angle between normals\n\
	deltas1.x = dot(normal[1], normal[0]);\n\
	deltas1.y = dot(normal[2], normal[0]);\n\
	deltas1.z = dot(normal[3], normal[0]);\n\
	deltas1.w = dot(normal[4], normal[0]);\n\
	deltas2.x = dot(normal[5], normal[0]);\n\
	deltas2.y = dot(normal[6], normal[0]);\n\
	deltas2.z = dot(normal[7], normal[0]);\n\
	deltas2.w = dot(normal[8], normal[0]);\n\
	deltas1 = abs(deltas1 - deltas2);\n\
\n\
	// Compare change in the cosine of the angles, flagging changes\n\
	// above some constant threshold. The cosine of the angle is not a\n\
	// linear function of the angle, so to have the flagging be\n\
	// independent of the angles involved, an arccos function would be\n\
	// required.\n\
	highp vec4 normalResults = step(0.4f, deltas1);\n\
	normalResults = max(normalResults, depthResults);\n\
	highp float w = (normalResults.x + normalResults.y + normalResults.z + normalResults.w)*0.25f; // 0=no aa, 1=full aa\n\
	if (w <= 0) {\n\
		// Early escape: No anti-aliasing required\n\
		#ifdef FS_SHOW_EDGESONLY\n\
			gl_FragColor = 0;\n\
		#else\n\
			gl_FragColor = texture2DRect(FrontMap, VertexTexCoordVS);\n\
		#endif\n\
		return;\n\
	}\n\
\n\
	// Scale the weight\n\
	w *= WeightScale;\n\
\n\
	// Perform anti-aliasing\n\
	#ifdef FS_SHOW_EDGES\n\
		gl_FragColor = vec4(EdgeColor, 1);\n\
	#else\n\
		// Smoothed color\n\
		#ifdef FS_MORE_SAMPLES\n\
			gl_FragColor = 0;\n\
			for (int i=0; i<9; i++)\n\
				gl_FragColor += texture2DRect(FrontMap, VertexTexCoordVS + Offsets[i]*w);\n\
			gl_FragColor /= 9;\n\
		#else\n\
			highp vec4 s0 = texture2DRect(FrontMap, VertexTexCoordVS + Offsets[2]*w);\n\
			highp vec4 s1 = texture2DRect(FrontMap, VertexTexCoordVS + Offsets[4]*w);\n\
			highp vec4 s2 = texture2DRect(FrontMap, VertexTexCoordVS + Offsets[6]*w);\n\
			highp vec4 s3 = texture2DRect(FrontMap, VertexTexCoordVS + Offsets[8]*w);\n\
			gl_FragColor = (s0 + s1 + s2 + s3)/4.0f;\n\
		#endif\n\
	#endif\n\
}";
