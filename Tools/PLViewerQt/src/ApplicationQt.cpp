/*********************************************************\
 *  File: ApplicationQt.cpp                              *
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
#include <PLMath/Math.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include "Gui.h"
#include "ApplicationQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ApplicationQt)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ApplicationQt::ApplicationQt(Frontend &cFrontend) : Application(cFrontend),
	m_pGui(nullptr),
	m_fLoadProgress(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
ApplicationQt::~ApplicationQt()
{
	// GUI instance has to be destroyed in "ApplicationQt::OnDeInit()" which is guaranteed to be called
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::AbstractFrontend functions  ]
//[-------------------------------------------------------]
void ApplicationQt::OnUpdate()
{
	// Update the GUI
	if (m_pGui)
		m_pGui->Update();

	// Call base implementation
	Application::OnUpdate();
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::CoreApplication functions     ]
//[-------------------------------------------------------]
void ApplicationQt::OnInit()
{
	// Initialize the GUI (no "m_pGui" security checks required, the application lifecycle is guaranteed)
	m_pGui = new Gui(*this);
	m_pGui->SetEnabled(true);

	// Call base implementation
	Application::OnInit();
}

void ApplicationQt::OnDeInit()
{
	// De-initialize the GUI (no "m_pGui" security checks required, the application lifecycle is guaranteed)
	delete m_pGui;
	m_pGui = nullptr;

	// Call base implementation
	Application::OnInit();
}


//[-------------------------------------------------------]
//[ Public virtual EngineApplication functions            ]
//[-------------------------------------------------------]
bool ApplicationQt::LoadScene(const String &sFilename)
{
	// It's possible that someone is calling "LoadScene()" directly, so disabling the GUI just in "LoadResource()" is not sufficient
	// -> Within the viewer, usually it's "LoadResource()" -> "LoadScene()"
	// -> Disabling/enabling the GUI twice is no problem, "Gui::SetEnabled()" can handle it

	// Disable the GUI window while loading so the user can't prank around
	if (m_pGui)
		m_pGui->SetEnabled(false);

	// Reset the current load progress and ensure everything is up-to-date when we start to load
	m_fLoadProgress = -0.42f;	// So "OnLoadProgress()" is forced to update
	OnLoadProgress(0.0f);

	// Call base implementation
	const bool bResult = Application::LoadScene(sFilename);

	// Enable the Qt main window when loading is done
	if (m_pGui)
		m_pGui->SetEnabled(true);

	// Done
	return bResult;
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::EngineApplication functions ]
//[-------------------------------------------------------]
void ApplicationQt::OnLoadProgress(float fLoadProgress)
{
	// Time for an update? (we don't want to redraw & ping the frontend each time a single tiny scene node was loaded *performance*)
	if ((fLoadProgress - m_fLoadProgress) >= 0.01f) {
		// Update the current load progress
		m_fLoadProgress = fLoadProgress;

		// Is there an GUI instance?
		if (m_pGui) {
			// Ensure the loading process looks always reasonable to the user
			fLoadProgress = PLMath::Math::ClampToInterval(fLoadProgress, 0.0f, 1.0f);

			// Let the GUI handle the information presentation of the current load progress (in percentage)
			// -> When zero percentage, present another text because for instance loading a XML document may take a moment
			SetStateText(fLoadProgress ? String::Format("Loading... %.0f%%", fLoadProgress*100.0f) : "Prepare loading...");

			// Redraw the frontend so the GUI stays kind-of responsive while loading, the "Ping" is done within "SetStateText()" above
			GetFrontend().Redraw();
		} else {
			// Redraw & ping the frontend so the GUI stays kind-of responsive while loading
			GetFrontend().RedrawAndPing();
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Application functions               ]
//[-------------------------------------------------------]
bool ApplicationQt::LoadResource(const String &sFilename, const String &sType)
{
	// Disable the GUI window while loading so the user can't prank around
	if (m_pGui) {
		m_pGui->SetEnabled(false);

		// Give the user a hint what's currently going on
		SetStateText("Loading resource \"" + sFilename + '\"');
	}

	// Call base implementation
	const bool bResult = Application::LoadResource(sFilename, sType);

	// Enable the Qt main window when loading is done
	if (m_pGui)
		m_pGui->SetEnabled(true);

	// Done
	return bResult;
}

void ApplicationQt::SetStateText(const String &sText)
{
	// Is there an GUI instance?
	if (m_pGui) {
		// Let the GUI handle the information presentation
		m_pGui->SetStateText(sText);
	} else {
		// Call base implementation
		Application::SetStateText(sText);
	}

	// Ping the frontend so the GUI shows the important state text as soon as possible
	GetFrontend().Ping();
}
