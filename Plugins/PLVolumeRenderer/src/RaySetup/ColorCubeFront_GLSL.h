/*********************************************************\
 *  File: ColorCubeFront_GLSL.h                          *
 *      Vertex and fragment shader source code - GLSL
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


//[-------------------------------------------------------]
//[ Vertex shader source code                             ]
//[-------------------------------------------------------]
// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) vertex shader source code, "#version" is added by hand
static const PLCore::String sSourceCode_Vertex = STRINGIFY(
// Attributes
attribute highp   vec3 VertexPosition;		// Object space vertex position input
attribute mediump vec3 VertexTexCoord;		// Vertex texture coordinate input
varying   mediump vec3 VertexTexCoordVS;	// Vertex texture coordinate output

// Uniforms
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;	// Object space to clip space matrix

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
// GLSL (OpenGL 2.0 ("#version 110") and OpenGL ES 2.0 ("#version 100")) fragment shader source code, "#version" is added by hand
static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Attributes
varying mediump vec3 VertexTexCoordVS;	// Interpolated vertex texture coordinate input from vertex shader, the position (volume object space) the ray enters the volume

// Programs
void main()
{
	// The position (volume object space) the ray enters the volume is provided by the vertex shader
	mediump vec3 rayPosition = VertexTexCoordVS;

	// Fragment color = The position the ray enters the volume = Color cube
	gl_FragColor = vec4(rayPosition.x, rayPosition.y, rayPosition.z, 1.0);
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY