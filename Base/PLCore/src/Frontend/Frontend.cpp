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
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Frontend)


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Run the frontend
*/
int Frontend::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sFrontendImplClass, const String &sApplicationClass)
{
	// Create a frontend implementation instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendImplClass);
	if (pFrontendImpl) {
		// Let the world know that this frontend is now going to run
		pFrontendImpl->GetFrontend().OnRun(sExecutableFilename, lstArguments);

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
int Frontend::Run(int argc, char **argv, const String &sFrontendImplClass, const String &sApplicationClass)
{
	// Create a frontend implementation instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendImplClass);
	if (pFrontendImpl) {
		{ // Let the world know that this frontend is now going to run
			Array<String> lstArguments;
			for (int i=1; i<argc; i++)
				lstArguments.Add(argv[i]);
			pFrontendImpl->GetFrontend().OnRun(lstArguments[0], lstArguments);
		}

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

int Frontend::Run(int argc, wchar_t **argv, const String &sFrontendImplClass, const String &sApplicationClass)
{
	// Create a frontend implementation instance
	FrontendImpl *pFrontendImpl = CreateInstance(sFrontendImplClass);
	if (pFrontendImpl) {
		{ // Let the world know that this frontend is now going to run
			Array<String> lstArguments;
			for (int i=1; i<argc; i++)
				lstArguments.Add(argv[i]);
			pFrontendImpl->GetFrontend().OnRun(lstArguments[0], lstArguments);
		}

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
void Frontend::RedrawAndPing()
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

/**
*  @brief
*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
bool Frontend::GetToggleFullscreenMode() const
{
	// Call backend
	return m_pImpl->GetToggleFullscreenMode();
}

/**
*  @brief
*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Call backend
	m_pImpl->SetToggleFullscreenMode(bToggleFullscreenMode);
}

/**
*  @brief
*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
bool Frontend::GetFullscreenAltTab() const
{
	// Call backend
	return m_pImpl->GetFullscreenAltTab();
}

/**
*  @brief
*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Call backend
	m_pImpl->SetFullscreenAltTab(bAllowed);
}

/**
*  @brief
*    Returns whether the window is in fullscreen mode or not
*/
bool Frontend::IsFullscreen() const
{
	// Call backend
	return m_pImpl->IsFullscreen();
}

/**
*  @brief
*    Sets the window's fullscreen mode
*/
void Frontend::SetFullscreen(bool bFullscreen)
{
	// Call backend
	m_pImpl->SetFullscreen(bFullscreen);
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
//[ Protected virtual Frontend functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the frontend is run
*/
void Frontend::OnRun(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// No default implementation
}


//[-------------------------------------------------------]
//[ Private static functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a frontend instance
*/
FrontendImpl *Frontend::CreateInstance(const String &sFrontendImplClass)
{
	// [TODO] Make this optional?
	// Scan PL-runtime directory for compatible plugins and load them in
	Core::ScanRuntimeDirectoryPlugins();

	// Get the frontend implementation RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(sFrontendImplClass);
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
		PL_LOG(Error, "Frontend '" + sFrontendImplClass + "' is no valid frontend implementation RTTI class")
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
