/*********************************************************\
 *  File: PublishWin32.h                                 *
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
#include <PLGeneral/String/String.h>


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
const static PLGeneral::String sRuntimeSharedLibraries[] =
{
	"PLGeneral.dll",
	"PLCore.dll",
	"PLMath.dll",
	"PLGraphics.dll",
	"PLGui.dll",
	"PLInput.dll",
	"PLRenderer.dll",
	"PLMesh.dll",
	"PLScene.dll",
	"PLEngine.dll",
	"PLPhysics.dll",
	"PLSound.dll",
	""
};
const static PLGeneral::String sRuntimeDataFiles[] =
{
	"Standard.zip",
	""
};
static const PLGeneral::String sPLRendererPlugins[] =
{
	"PLRendererOpenGL.dll",
	"PLRendererOpenGL.plugin",
	"cg.dll",
	"cgGL.dll",
	""
};
static const PLGeneral::String sPLScenePlugins[] =
{
	"PLCompositing.dll",
	"PLCompositing.plugin",
	""
};
static const PLGeneral::String sPLPhysicsPlugins[] =
{
	"PLPhysicsNewton.dll",
	"PLPhysicsNewton.plugin",
	"newton.dll",
	""
};
static const PLGeneral::String sPLSoundPlugins[] =
{
	"PLSoundOpenAL.dll",
	"PLSoundOpenAL.plugin",
	"wrap_oal.dll",
	"OpenAL32.dll",
	""
};
static const PLGeneral::String sVC2010Redistributable[] =
{
	"msvcp100.dll",
	"msvcr100.dll",
	""
};
