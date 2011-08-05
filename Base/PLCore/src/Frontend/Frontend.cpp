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
#include "PLCore/Log/Log.h"
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
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sFrontendClass, const String &sApplicationClass)
{
	// Create a frontend instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendClass);
	if (pFrontendImpl) {
		// Let the frontend run
		const int nResult = pFrontendImpl->Run(sExecutableFilename, lstArguments, sApplicationClass);

		// Destroy the frontend
		delete pFrontendImpl;

		// Done
		return nResult;
	} else {
		// Error!
		return -1;
	}
}

/**
*  @brief
*    Run the frontend using traditional C-arguments
*/
int Frontend::Run(int argc, char **argv, const String &sFrontendClass, const String &sApplicationClass)
{
	// Create a frontend instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendClass);
	if (pFrontendImpl) {
		// Let the frontend run
		const int nResult = pFrontendImpl->Run(argc, argv, sApplicationClass);

		// Destroy the frontend
		delete pFrontendImpl;

		// Done
		return nResult;
	} else {
		// Error!
		return -1;
	}
}

int Frontend::Run(int argc, wchar_t **argv, const String &sFrontendClass, const String &sApplicationClass)
{
	// Create a frontend instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendClass);
	if (pFrontendImpl) {
		// Let the frontend run
		const int nResult = pFrontendImpl->Run(argc, argv, sApplicationClass);

		// Destroy the frontend
		delete pFrontendImpl;

		// Done
		return nResult;
	} else {
		// Error!
		return -1;
	}
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
*    Redraw frontend window
*/
void Frontend::Redraw()
{
	// Call backend
	m_pImpl->Redraw();
}

/**
*  @brief
*    Give the frontend a chance to process OS messages
*/
void Frontend::Ping() const
{
	// Call backend
	m_pImpl->Ping();
}

/**
*  @brief
*    Redraw frontend window and give the frontend a chance to process OS messages
*/
void Frontend:: RedrawAndPing()
{
	// Call backend methods
	m_pImpl->Redraw();
	m_pImpl->Ping();
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
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a frontend instance
*/
FrontendImpl *Frontend::CreateInstance(const String &sFrontendClass)
{
	// [TODO] Make this optional?
	// Get PixelLight runtime directory
	const String sPLDirectory = Core::GetRuntimeDirectory();
	if (sPLDirectory.GetLength()) {
		// Scan for plugins in PixelLight runtime directory -> The script plugins are now ready to be used
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory, NonRecursive);
		ClassManager::GetInstance()->ScanPlugins(sPLDirectory + "/Plugins/", Recursive);
	}

	// Get the frontend RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(sFrontendClass);
	if (pClass && pClass->IsDerivedFrom("PLCore::FrontendImpl")) {
		// Create the frontend RTTI class instance
		Object *pObject = pClass->Create();
		if (pObject) {
			// Write down a log message
			PL_LOG(Info, "Using frontend '" + pClass->GetClassName() + "': " + pClass->GetDescription())

			// Done
			return static_cast<FrontendImpl*>(pObject);
		} else {
			// Error!
			PL_LOG(Error, "Failed instancing frontend '" + pClass->GetClassName() + "': " + pClass->GetDescription())
		}
	} else {
		// Error!
		PL_LOG(Error, "Frontend '" + sFrontendClass + "' is no valid frontend RTTI class")
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
