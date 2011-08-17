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
#include "PLCore/Frontend/FrontendContext.h"
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
int Frontend::Run(const FrontendContext &cFrontendContext)
{
	int nResult = -1;	// Error by default

	// [TODO] Make this optional?
	// Scan PL-runtime directory for compatible plugins and load them in
	Core::ScanRuntimeDirectoryPlugins();

	// Create a frontend implementation instance
	FrontendImpl *pFrontendImpl = CreateFrontendImplementation(cFrontendContext);
	if (pFrontendImpl) {
		// Create a frontend instance
		Frontend *pFrontend = FrontendImpl::CreateFrontend(cFrontendContext, *pFrontendImpl);
		if (pFrontend) {
			// Do the frontend lifecycle thing - let the world know that we have been created
			pFrontend->OnCreate();

			// Let the world know that this frontend is now going to run
			pFrontend->OnRun(cFrontendContext.GetExecutableFilename(), cFrontendContext.GetArguments());

			// Let the frontend implementation run
			nResult = pFrontendImpl->Run(cFrontendContext.GetExecutableFilename(), cFrontendContext.GetArguments());

			// Do the frontend lifecycle thing - let the world know that we're going to die
			pFrontend->OnDestroy();

			// Destroy the frontend
			delete pFrontend;
		}

		// Destroy the frontend implementation
		delete pFrontendImpl;
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
Frontend::Frontend(const FrontendContext &cFrontendContext, FrontendImpl &cFrontendImpl) :
	m_cFrontendContext(cFrontendContext),
	m_pFrontendImpl(&cFrontendImpl)
{
	// Set frontend
	m_pFrontendImpl->m_pFrontend = this;
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
*    Get frontend context
*/
const FrontendContext &Frontend::GetContext() const
{
	return m_cFrontendContext;
}

/**
*  @brief
*    Get native window handle
*/
handle Frontend::GetNativeWindowHandle() const
{
	// Call backend
	return m_pFrontendImpl->GetNativeWindowHandle();
}

/**
*  @brief
*    Redraw frontend window
*/
void Frontend::Redraw()
{
	// Call backend
	m_pFrontendImpl->Redraw();
}

/**
*  @brief
*    Give the frontend a chance to process OS messages
*/
void Frontend::Ping() const
{
	// Call backend
	m_pFrontendImpl->Ping();
}

/**
*  @brief
*    Redraw frontend window and give the frontend a chance to process OS messages
*/
void Frontend::RedrawAndPing()
{
	// Call backend methods
	m_pFrontendImpl->Redraw();
	m_pFrontendImpl->Ping();
}

/**
*  @brief
*    Get window width
*/
uint32 Frontend::GetWidth() const
{
	// Call backend
	return m_pFrontendImpl->GetWidth();
}

/**
*  @brief
*    Get window height
*/
uint32 Frontend::GetHeight() const
{
	// Call backend
	return m_pFrontendImpl->GetHeight();
}

/**
*  @brief
*    Gets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
bool Frontend::GetToggleFullscreenMode() const
{
	// Call backend
	return m_pFrontendImpl->GetToggleFullscreenMode();
}

/**
*  @brief
*    Sets whether it's allowed to toggle the fullscreen mode using hotkeys
*/
void Frontend::SetToggleFullscreenMode(bool bToggleFullscreenMode)
{
	// Call backend
	m_pFrontendImpl->SetToggleFullscreenMode(bToggleFullscreenMode);
}

/**
*  @brief
*    Gets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
bool Frontend::GetFullscreenAltTab() const
{
	// Call backend
	return m_pFrontendImpl->GetFullscreenAltTab();
}

/**
*  @brief
*    Sets whether it's allowed to use Alt-Tab if fullscreen mode is used
*/
void Frontend::SetFullscreenAltTab(bool bAllowed)
{
	// Call backend
	m_pFrontendImpl->SetFullscreenAltTab(bAllowed);
}

/**
*  @brief
*    Returns whether the window is in fullscreen mode or not
*/
bool Frontend::IsFullscreen() const
{
	// Call backend
	return m_pFrontendImpl->IsFullscreen();
}

/**
*  @brief
*    Sets the window's fullscreen mode
*/
void Frontend::SetFullscreen(bool bFullscreen)
{
	// Call backend
	m_pFrontendImpl->SetFullscreen(bFullscreen);
}

/**
*  @brief
*    Check if the mouse cursor is visible
*/
bool Frontend::IsMouseVisible() const
{
	// Call backend
	return m_pFrontendImpl->IsMouseVisible();
}

/**
*  @brief
*    Set mouse cursor visibility
*/
void Frontend::SetMouseVisible(bool bVisible)
{
	// Call backend
	m_pFrontendImpl->SetMouseVisible(bVisible);
}

/**
*  @brief
*    Trap mouse inside the frontend window
*/
void Frontend::SetTrapMouse(bool bTrap)
{
	// Call backend
	m_pFrontendImpl->SetTrapMouse(bTrap);
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
	return m_pFrontendImpl;
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
*    Creates a implementation frontend instance
*/
FrontendImpl *Frontend::CreateFrontendImplementation(const FrontendContext &cFrontendContext)
{
	// Get the frontend implementation RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(cFrontendContext.GetFrontendImplementation());
	if (pClass && pClass->IsDerivedFrom("PLCore::FrontendImpl")) {
		// Create the frontend RTTI class instance
		Object *pObject = cFrontendContext.GetFrontendImplementationConstructor().GetLength() ? pClass->Create(cFrontendContext.GetFrontendImplementationConstructor(), cFrontendContext.GetFrontendImplementationConstructorParameters()) : pClass->Create();
		if (pObject) {
			// Write down a log message
			PL_LOG(Info, "Using frontend implementation '" + pClass->GetClassName() + "': " + pClass->GetDescription())

			// Set parameters for the instanced frontend implementation RTTI class
			if (cFrontendContext.GetFrontendImplementationParameters().GetLength())
				pObject->SetValues(cFrontendContext.GetFrontendImplementationParameters());

			// Done
			return static_cast<FrontendImpl*>(pObject);
		} else {
			// Error!
			PL_LOG(Error, "Failed instancing frontend implementation '" + pClass->GetClassName() + "': " + pClass->GetDescription())
		}
	} else {
		// Error!
		PL_LOG(Error, "Frontend '" + cFrontendContext.GetFrontendImplementation() + "' is no valid frontend implementation RTTI class")
	}

	// Error!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
