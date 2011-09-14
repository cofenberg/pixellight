/*********************************************************\
 *  File: FrontendApplication.cpp                        *
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
#include "PLCore/System/System.h"
#include "PLCore/Tools/Localization.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Tools/LocalizationGroup.h"
#include "PLCore/Frontend/FrontendContext.h"
#include "PLCore/Frontend/FrontendApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(FrontendApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the frontend this application is running in
*/
Frontend &FrontendApplication::GetFrontend() const
{
	// Return reference to the frontend
	return *m_pFrontend;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendApplication::FrontendApplication(Frontend &cFrontend) : CoreApplication(),
	m_pFrontend(&cFrontend)
{
	// Set application name and title
	SetName(m_pFrontend->GetContext().GetName());
	SetTitle(m_pFrontend->GetContext().GetName());

	// Set running state
	m_bRunning = true;
}

/**
*  @brief
*    Destructor
*/
FrontendApplication::~FrontendApplication()
{
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractLifecycle functions         ]
//[-------------------------------------------------------]
/**
*  @brief
*    De-initialization function that is called after OnDeInit()
*/
void FrontendApplication::OnStop()
{
	// Write down display mode information
	GetConfig().SetVar("PLCore::FrontendConfig", "X",      String(GetFrontend().GetX()));
	GetConfig().SetVar("PLCore::FrontendConfig", "Y",      String(GetFrontend().GetY()));
	GetConfig().SetVar("PLCore::FrontendConfig", "Width",  String(GetFrontend().GetWidth()));
	GetConfig().SetVar("PLCore::FrontendConfig", "Height", String(GetFrontend().GetHeight()));

	// Call base implementation
	CoreApplication::OnStop();
}

//[-------------------------------------------------------]
//[ Protected virtual AbstractFrontend functions          ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the window size has been changed
*/
void FrontendApplication::OnSize()
{
	// No default implementation
}

/**
*  @brief
*    Called when the fullscreen mode was changed
*/
void FrontendApplication::OnFullscreenMode()
{
	// No default implementation
}

/**
*  @brief
*    Called to let the frontend draw into it's window
*/
void FrontendApplication::OnDraw()
{
	// No default implementation
}

/**
*  @brief
*    Called to let the frontend update it's states
*/
void FrontendApplication::OnUpdate()
{
	// No default implementation
}

/**
*  @brief
*    Called when string data has been dropped onto the frontend window
*/
void FrontendApplication::OnDrop(const Container<String> &lstFiles)
{
	// No default implementation
}


//[-------------------------------------------------------]
//[ Protected virtual CoreApplication functions           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when application should initialize it's configuration
*/
void FrontendApplication::OnInitConfig()
{
	// Call base implementation
	CoreApplication::OnInitConfig();

	// Read frontend configuration and set frontend position and size of the previous session
	GetFrontend().SetPositionSize(GetConfig().GetVarInt("PLCore::FrontendConfig", "X"),
								  GetConfig().GetVarInt("PLCore::FrontendConfig", "Y"),
								  GetConfig().GetVarInt("PLCore::FrontendConfig", "Width"),
								  GetConfig().GetVarInt("PLCore::FrontendConfig", "Height"));
}

/**
*  @brief
*    Called when application should load it's plugins
*/
void FrontendApplication::OnInitPlugins()
{
	// The "Scan PL-runtime directory for compatible plugins and load them in"-part is job of a higher being

	// Scan for plugins in the application directory, but not recursively, please. This is quite useful
	// for shipping applications and putting all plugins inside the application root directory
	// (which is necessary due to VC manifest policy)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory(), NonRecursive);

	// Scan for plugins in "Plugins" directory (recursively)
	ClassManager::GetInstance()->ScanPlugins(m_cApplicationContext.GetAppDirectory() + "/Plugins/", Recursive);
}

/**
*  @brief
*    Called when application should set it's data paths
*/
void FrontendApplication::OnInitData()
{
	// The "Scan PL-runtime directory for compatible data and register it"-part is job of a higher being

	// Is '.' (= the current directory) already a base directory? If not, add it right now...
	LoadableManager *pLoadableManager = LoadableManager::GetInstance();
	if (!pLoadableManager->IsBaseDir('.'))
		pLoadableManager->AddBaseDir('.');

	// Is the application directory already a base directory? If not, add it right now...
	if (!pLoadableManager->IsBaseDir(m_cApplicationContext.GetAppDirectory()))
		pLoadableManager->AddBaseDir(m_cApplicationContext.GetAppDirectory());

	// Scan for packages in current "Data" directory
	const String sCurrentDir = System::GetInstance()->GetCurrentDir();
	pLoadableManager->ScanPackages(sCurrentDir.GetLength() ? (sCurrentDir + "/Data") : "Data");

	// Scan for packages in application's "Data" directory
	if (sCurrentDir != m_cApplicationContext.GetAppDirectory())
		pLoadableManager->ScanPackages(m_cApplicationContext.GetAppDirectory().GetLength() ? (m_cApplicationContext.GetAppDirectory() + "/Data") : "Data");

	// Get localization language (from config or from default)
	String sLanguage = m_cConfig.GetVar("PLCore::CoreConfig", "Language");
	if (!sLanguage.GetLength()) {
		// Use always English instead of the current program locale language so that we have a known default behavior
		sLanguage = "English";
	}

	// Setup localization system
	Localization::GetInstance()->SetLanguage(sLanguage);
	if (sLanguage.GetLength()) {
		LocalizationGroup *pLocalizationGroup = Localization::GetInstance()->AddGroup(Localization::PixelLight);
		if (pLocalizationGroup)
			pLocalizationGroup->Load("Data/Misc/" + Localization::PixelLight + '_' + sLanguage + ".loc");
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
