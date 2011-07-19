/*********************************************************\
 *  File: PostProcessManager.cpp                         *
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
#include <PLCore/Tools/Loader.h>
#include "PLCompositing/Shaders/PostProcessing/PostProcess.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessLoader.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PostProcessManager::PostProcessManager(RendererContext &cRendererContext) :
	m_pRendererContext(&cRendererContext),
	m_nTextureFormat(TextureBuffer::R8G8B8A8)
{
}

/**
*  @brief
*    Destructor
*/
PostProcessManager::~PostProcessManager()
{
}

/**
*  @brief
*    Returns the used renderer context
*/
RendererContext &PostProcessManager::GetRendererContext() const
{
	return *m_pRendererContext;
}

/**
*  @brief
*    Returns the texture format
*/
TextureBuffer::EPixelFormat PostProcessManager::GetTextureFormat() const
{
	return m_nTextureFormat;
}

/**
*  @brief
*    Sets the texture format
*/
void PostProcessManager::SetTextureFormat(TextureBuffer::EPixelFormat nFormat)
{
	m_nTextureFormat = nFormat;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool PostProcessManager::Unload()
{
	// Remove all post processes
	Clear();

	// Reset texture format
	m_nTextureFormat = TextureBuffer::R8G8B8A8;

	// Call base implementation
	return Loadable::Unload();
}

String PostProcessManager::GetLoadableTypeName() const
{
	static const String sString = "PostProcess";
	return sString;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::Loadable functions            ]
//[-------------------------------------------------------]
bool PostProcessManager::CallLoadable(File &cFile, Loader &cLoader, const String &sMethod, const String &sParams)
{
	// Get the loader implementation
	LoaderImpl *pLoaderImpl = cLoader.GetImpl();
	if (pLoaderImpl) {
		// Load
		if (sParams.GetLength()) {
			pLoaderImpl->CallMethod(sMethod, "Param0=\"" + Type<PostProcessManager&>::ConvertToString(*this) + "\" Param1=\"" + Type<File&>::ConvertToString(cFile) + "\" " + sParams);
			return true;
		} else {
			Params<bool, PostProcessManager&, File&> cParams(*this, cFile);
			pLoaderImpl->CallMethod(sMethod, cParams);
			return cParams.Return;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::ElementManager functions      ]
//[-------------------------------------------------------]
PostProcess *PostProcessManager::CreateElement(const String &sName)
{
	return new PostProcess(sName, *this);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
