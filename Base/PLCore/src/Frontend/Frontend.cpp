/*********************************************************\
 *  File: Frontend.cpp                                   *
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
#include "PLCore/Core.h"
#include "PLCore/Base/Class.h"
#include "PLCore/Frontend/FrontendImpl.h"
#include "PLCore/Frontend/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Run the frontend
*/
int Frontend::Run(const String &sFrontendClass, const String &sApplicationClass, const String &sExecutableFilename, const Array<String> &lstArguments)
{
	int nResult = 0;	// No error by default

	// [TODO] Make this optional?
	// Get PixelLight runtime directory
	const String sPLDirectory = Core::GetRuntimeDirectory();
	if (sPLDirectory.GetLength()) {
		// Scan for plugins in PixelLight runtime directory -> The script plugins are now ready to be used
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory, NonRecursive);
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory + "/Plugins/", Recursive);
	}

	// Get the RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(sFrontendClass);
	if (pClass && pClass->IsDerivedFrom("PLCore::FrontendImpl")) {
		// Create the RTTI class instance
		Object *pObject = pClass->Create();
		if (pObject) {
			// Let the frontend run
			static_cast<FrontendImpl*>(pObject)->Run(sApplicationClass, sExecutableFilename, lstArguments);

			// Destroy the frontend
			delete pObject;
		}
	} else {
		// [TODO] Fallback as test
		pClass = ClassManager::GetInstance()->GetClass("PLRenderer::RendererApplication");
		if (pClass && pClass->IsDerivedFrom("PLCore::FrontendImpl")) {
			// Create the RTTI class instance
			Object *pObject = pClass->Create();
			if (pObject) {
				// Let the frontend run
				static_cast<FrontendImpl*>(pObject)->Run(sApplicationClass, sExecutableFilename, lstArguments);

				// Destroy the frontend
				delete pObject;
			}
		}
	}

	// Done
	return nResult;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Frontend::Frontend(FrontendImpl &cImpl) :
	m_pImpl(&cImpl)
{
	// Set frontend
	m_pImpl->m_pFrontend = this;
}

/**
*  @brief
*    Destructor
*/
Frontend::~Frontend()
{
}

/**
*  @brief
*    Get native window handle
*/
handle Frontend::GetNativeWindowHandle() const
{
	// Call backend
	return m_pImpl->GetNativeWindowHandle();
}

/**
*  @brief
*    Give the frontend a chance to process OS messages
*/
void Frontend::Ping() const
{
	// Call backend
	return m_pImpl->Ping();
}

/**
*  @brief
*    Get window width
*/
uint32 Frontend::GetWidth() const
{
	// Call backend
	return m_pImpl->GetWidth();
}

/**
*  @brief
*    Get window height
*/
uint32 Frontend::GetHeight() const
{
	// Call backend
	return m_pImpl->GetHeight();
}

/**
*  @brief
*    Redraw frontend window
*/
void Frontend::Redraw()
{
	// Call backend
	m_pImpl->Redraw();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get frontend implementation
*/
FrontendImpl *Frontend::GetImpl() const
{
	// Return implementation
	return m_pImpl;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
