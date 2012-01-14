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
#include <PLCore/File/Url.h>
#include <PLCore/Tools/LoadableType.h>
#include <PLCore/Tools/LoadableManager.h>
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

/**
*  @brief
*    Returns the dock widget manager instance the application is using
*/
PLFrontendQt::DockWidgetManager *ApplicationQt::GetDockWidgetManager() const
{
	// Is there an GUI instance?
	if (m_pGui) {
		// Get the Qt main window
		PLFrontendQt::FrontendMainWindow *pFrontendMainWindow = m_pGui->GetFrontendMainWindow();
		if (pFrontendMainWindow)
			return &pFrontendMainWindow->GetDockWidgetManager();
	}

	// Error!
	return nullptr;
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
	Application::OnDeInit();
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
		}

		// Redraw & ping the frontend so the GUI stays kind-of responsive while loading
		GetFrontend().RedrawAndPing();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Application functions               ]
//[-------------------------------------------------------]
bool ApplicationQt::LoadResource(const String &sFilename, const String &sType)
{
	// The used loadable type may be changed within this method
	String sTypeToUse = sType;

	// Disable the GUI window while loading so the user can't prank around
	if (m_pGui) {
		// In case no loadable type is provided, we need to guess the loadable type...
		// which can go terrible wrong. If required, ask the user for the desired loadable type.
		if (!sTypeToUse.GetLength()) {
			// Get file extension
			const Url cUrl(sFilename);
			const String sExtension = cUrl.GetExtension();
			if (sExtension.GetLength()) {
				// Get loadable types by using the loadable extension
				Array<LoadableType*> lstTypes;
				LoadableManager::GetInstance()->GetTypesByExtension(sExtension, lstTypes);
				if (lstTypes.GetNumOfElements() > 1) {
					// Get array with type names
					Array<String> lstTypeNames;
					for (uint32 i=0; i<lstTypes.GetNumOfElements(); i++)
						lstTypeNames.Add(lstTypes[i]->GetName());

					// We have multiple candidates, ask the user for the desired loadable type
					sTypeToUse = m_pGui->InputDialog(cUrl.GetNativePath(), "Please specify the resource type", lstTypeNames);
					if (!sTypeToUse.GetLength()) {
						// Get us out of here right now!
						return false;
					}

					// It's also possible that one loadable type has multiple loaders with a same extension
					// -> For simplicity we ignore this case in here
				}
			}
		}

		// Disable the GUI
		m_pGui->SetEnabled(false);

		// Give the user a hint what's currently going on
		SetStateText("Loading resource \"" + sFilename + '\"');

		// Ping the frontend so the GUI shows the important state text as soon as possible
		// -> Resource loading may take a while and showing an updated state text after loading is done is not that helpful
		GetFrontend().Ping();
	}

	// Call base implementation
	const bool bResult = Application::LoadResource(sFilename, sTypeToUse);

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

	// We could ping the frontend via "GetFrontend().Ping()" in general so the GUI shows the
	// important state text as soon as possible, but this might have an notable influence on
	// the performance due to internal message processing
}
