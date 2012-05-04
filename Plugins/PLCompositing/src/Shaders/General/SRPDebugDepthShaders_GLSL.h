/*********************************************************\
 *  File: SRPDebugDepthShaders_GLSL.h                     *
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


// OpenGL 2.0 ("#version 110") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sEndHDR_GLSL_VS = STRINGIFY(
// Attributes
attribute vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
								// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)

// Uniforms
uniform ivec2 TextureSize;		// Texture size in texel

// Programs
void main()
{
	// Set the clip space vertex position
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);

	// Pass through the scaled vertex texture coordinate
	VertexTexCoordVS = VertexPosition.zw*vec2(TextureSize);
}
);	// STRINGIFY


// OpenGL 2.0 ("#version 110") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sEndHDR_GLSL_FS = "\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform sampler2DRect Texture;	// Texture\n\
#ifdef FS_LINEARIZE_DEPTH\n\
	uniform vec2 ZNearFar;		// x=Z near plane, y=Z far plane\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Fetch the required texel data\n\
	float sample = texture2DRect(Texture, VertexTexCoordVS).x;\n\
\n\
	// Linearize the depth\n\
	#ifdef FS_LINEARIZE_DEPTH\n\
		sample = (2.0*ZNearFar.x)/(ZNearFar.y + ZNearFar.x - sample*(ZNearFar.y - ZNearFar.x));\n\
	#endif\n\
\n\
	// Set the resulting color\n\
	gl_FragColor = vec4(sample, sample, sample, 1.0);\n\
}";


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
