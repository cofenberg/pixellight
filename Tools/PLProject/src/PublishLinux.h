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
const static PLCore::String sRuntimeSharedLibraries[] =
{
	"libPLCore.so",
	"libPLMath.so",
	"libPLGraphics.so",
	"libPLGui.so",
	"libPLInput.so",
	"libPLRenderer.so",
	"libPLMesh.so",
	"libPLScene.so",
	"libPLEngine.so",
	"libPLPhysics.so",
	"libPLSound.so",
	""
};
const static PLCore::String sRuntimeDataFiles[] =
{
	"Standard.zip",
	""
};
static const PLCore::String sPLRendererPlugins[] =
{
	"libPLRendererOpenGL.so",
	"PLRendererOpenGL.plugin",
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
