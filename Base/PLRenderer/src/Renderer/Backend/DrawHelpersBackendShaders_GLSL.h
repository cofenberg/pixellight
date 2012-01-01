/*********************************************************\
 *  File: DrawHelpersBackendShaders_GLSL.cpp             *
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


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sVertexShaderSourceCodeGLSL = "\
// Attributes\n\
attribute mediump vec3 VertexPosition;					// Object space vertex position input\n\
#ifdef VS_TEXCOORD0\n\
	attribute mediump vec2 VertexTextureCoordinate;		// Vertex texture coordinate input\n\
	varying   mediump vec2 VertexTextureCoordinateVS;	// Vertex texture coordinate output\n\
#endif\n\
\n\
// Uniforms\n\
uniform mediump mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix\n\
#ifdef VS_TEXCOORD0\n\
	uniform mediump mat4 TextureMatrix;				// Texture matrix\n\
#endif\n\
#ifdef VS_POINTSIZE\n\
	uniform mediump float PointSize;				// Point size\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*vec4(VertexPosition, 1);\n\
\n\
	#ifdef VS_TEXCOORD0\n\
		// Pass through the texture coordinate\n\
		VertexTextureCoordinateVS = (TextureMatrix*vec4(VertexTextureCoordinate, 1, 1)).xy;\n\
	#endif\n\
\n\
	#ifdef VS_POINTSIZE\n\
		// Write the point size\n\
		gl_PointSize = PointSize;\n\
	#endif\n\
}";


// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by "PLRenderer::ProgramGenerator"
static const PLCore::String sFragmentShaderSourceCodeGLSL = "\
// Attributes\n\
#ifdef FS_DIFFUSEMAP\n\
	varying mediump vec2 VertexTextureCoordinateVS;	// Vertex texture coordinate input from vertex shader\n\
#endif\n\
\n\
// Uniforms\n\
uniform lowp vec4 Color;						// Color\n\
#ifdef FS_DIFFUSEMAP\n\
	#ifdef FS_DIFFUSEMAP2D\n\
		uniform lowp sampler2D DiffuseMap;		// 2D diffuse map\n\
	#else\n\
		uniform lowp sampler2DRect DiffuseMap;	// Rectangle diffuse map\n\
	#endif\n\
	#ifdef FS_ALPHATEST\n\
		uniform mediump float AlphaReference;	// Alpha reference\n\
	#endif\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
#ifdef FS_DIFFUSEMAP\n\
	#ifdef FS_DIFFUSEMAP2D\n\
		lowp vec4 diffuseColor = texture2D(DiffuseMap, VertexTextureCoordinateVS);\n\
	#else\n\
		lowp vec4 diffuseColor = texture2DRect(DiffuseMap, VertexTextureCoordinateVS);\n\
	#endif\n\
	#ifdef FS_ALPHATEST\n\
		// Perform an alpha test to discard fragments\n\
		if (diffuseColor.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
\n\
	// Still here? Then apply the given color...\n\
	gl_FragColor = diffuseColor*Color;\n\
#else\n\
	gl_FragColor = Color;\n\
#endif\n\
}";
