/*********************************************************\
 *  File: PublishLinux.h                                  *
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
