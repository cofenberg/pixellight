/*********************************************************\
 *  File: PublishWin32.h                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
	"PLCore.dll",
	"PLMath.dll",
	"PLMath.plugin",
	"PLGraphics.dll",
	"PLGraphics.plugin",
	"PLInput.dll",
	"PLInput.plugin",
	"PLRenderer.dll",
	"PLRenderer.plugin",
	"PLMesh.dll",
	"PLMesh.plugin",
	"PLScene.dll",
	"PLScene.plugin",
	"PLEngine.dll",
	"PLEngine.plugin",
	"PLPhysics.dll",
	"PLPhysics.plugin",
	"PLSound.dll",
	"PLSound.plugin",
	"PLFrontendOS.dll",
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
	"PLRendererOpenGL.dll",
	"PLRendererOpenGL.plugin",
	"PLRendererOpenGLCg.dll",
	"PLRendererOpenGLCg.plugin",
	"cg.dll",
	"cgGL.dll",
	""
};
static const PLCore::String sPLScenePlugins[] =
{
	"PLCompositing.dll",
	"PLCompositing.plugin",
	""
};
static const PLCore::String sPLPhysicsPlugins[] =
{
	"PLPhysicsNewton.dll",
	"PLPhysicsNewton.plugin",
	"newton.dll",
	""
};
static const PLCore::String sPLSoundPlugins[] =
{
	"PLSoundOpenAL.dll",
	"PLSoundOpenAL.plugin",
	"wrap_oal.dll",
	"OpenAL32.dll",
	""
};
static const PLCore::String sVC2010Redistributable[] =
{
	"msvcp100.dll",
	"msvcr100.dll",
	""
};
