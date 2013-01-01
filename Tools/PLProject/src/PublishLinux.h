/*********************************************************\
 *  File: PublishLinux.h                                  *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
static const PLCore::String sRuntimeSharedLibraries[] =
{
	"libPLCore.so",
	"libPLMath.so",
	"PLMath.plugin",
	"libPLGraphics.so",
	"PLGraphics.plugin",
	"libPLInput.so",
	"PLInput.plugin",
	"libPLRenderer.so",
	"PLRenderer.plugin",
	"libPLMesh.so",
	"PLMesh.plugin",
	"libPLScene.so",
	"PLScene.plugin",
	"libPLEngine.so",
	"PLEngine.plugin",
	"libPLPhysics.so",
	"PLPhysics.plugin",
	"libPLSound.so",
	"PLSound.plugin",
	"libPLFrontendOS.so",
	"PLFrontendOS.plugin",
	""
};
static const PLCore::String sRuntimeDataFiles[] =
{
	"Standard.zip",
	""
};
static const PLCore::String sPLRendererPlugins[] =
{
	"libPLRendererOpenGL.so",
	"PLRendererOpenGL.plugin",
	"libPLRendererOpenGLCg.dll",
	"PLRendererOpenGLCg.plugin",
	"libCg.so",
	"libCgGL.so",
	""
};
static const PLCore::String sPLScenePlugins[] =
{
	"libPLCompositing.so",
	"PLCompositing.plugin",
	""
};
static const PLCore::String sPLPhysicsPlugins[] =
{
	"libPLPhysicsNewton.so",
	"PLPhysicsNewton.plugin",
	"libNewton.so",
	""
};
static const PLCore::String sPLSoundPlugins[] =
{
	"libPLSoundOpenAL.so",
	"PLSoundOpenAL.plugin",
	"libopenal.so",
	"libvorbis.so",
	"libvorbisfile.so",
	"libogg.so",
	""
};
