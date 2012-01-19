/*********************************************************\
 *  File: SRPEndFXAA_GLSL.h                              *
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


// OpenGL 3.0 ("#version 130") GLSL vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sEndFXAA_GLSL_VS = "\
// Attributes\n\
attribute vec4 VertexPosition;	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
								// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 output, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Set the clip space vertex position\n\
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);\n\
\n\
	// Pass through the vertex texture coordinate\n\
	VertexTexCoordVS.xy = VertexPosition.zw;\n\
}";


// OpenGL 3.0 ("#version 130") GLSL fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sEndFXAA_GLSL_FS = "\
// Constants\n\
//const vec2 InvTextureSize;	// 1/(texture size) - set when creating the shader\n\
\n\
// GLSL extensions\n\
#extension GL_ARB_texture_rectangle : enable\n\
\n\
// Attributes\n\
varying vec2 VertexTexCoordVS;	// Vertex texture coordinate 0 input from vertex shader, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)\n\
\n\
// Uniforms\n\
uniform sampler2D Texture;	// Texture\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Call the FXAA shader, lucky us that we don't have to write an own implementation\n\
	gl_FragColor = vec4(FxaaPixelShader(VertexTexCoordVS, Texture, InvTextureSize), 1.0);\n\
}";
