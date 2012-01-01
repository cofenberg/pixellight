/*********************************************************\
 *  File: PublishWin32.h                                 *
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
