/*********************************************************\
 *  File: FrontendPixelLight.cpp                         *
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
#include "PLCore/Base/Class.h"
#include "PLCore/System/System.h"
#include "PLCore/Frontend/FrontendImpl.h"
#include "PLCore/Frontend/FrontendApplication.h"
#include "PLCore/Frontend/FrontendPixelLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendPixelLight::FrontendPixelLight(FrontendImpl &cImpl) : Frontend(cImpl),
	m_pFrontendApplication(nullptr),
	m_bFrontendApplicationInitialized(false)
{
}

/**
*  @brief
*    Destructor
*/
FrontendPixelLight::~FrontendPixelLight()
{
}


//[-------------------------------------------------------]
//[ Public virtual FrontendImpl functions                 ]
//[-------------------------------------------------------]
bool FrontendPixelLight::IsRunning() const
{
	return m_bFrontendApplicationInitialized;
}


//[-------------------------------------------------------]
//[ Private virtual FrontendImpl functions                ]
//[-------------------------------------------------------]
void FrontendPixelLight::OnDraw()
{
	// Let the frontend application draw into it's window
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnDraw();
}

void FrontendPixelLight::OnSize()
{
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractLifecycle functions         ]
//[-------------------------------------------------------]
void FrontendPixelLight::OnCreate()
{
	// Get the RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass("Application");	// [TODO] Class name as parameter
	if (pClass && pClass->IsDerivedFrom("PLCore::FrontendApplication")) {
		// Create the RTTI class instance
		m_pFrontendApplication = static_cast<FrontendApplication*>(pClass->Create());
		if (m_pFrontendApplication) {
			m_pFrontendApplication->m_pFrontend = this;

			// Fill application context
			ApplicationContext &cApplicationContext = const_cast<ApplicationContext&>(m_pFrontendApplication->GetApplicationContext());	// [TODO] Casting away const is not nice
			cApplicationContext.SetStartupDirectory(System::GetInstance()->GetCurrentDir());
			// [TODO]
//			cApplicationContext.SetExecutableFilename(sExecutableFilename);
//			cApplicationContext.SetArguments(lstArguments);
		}
	}
}

void FrontendPixelLight::OnRestart()
{
	// Nothing to do in here
}

bool FrontendPixelLight::OnStart()
{
	if (m_pFrontendApplication && m_pFrontendApplication->OnStart()) {
		// Call application-specific initialization routine
		m_pFrontendApplication->OnInit();

		// Frontend application successfully initialized
		m_bFrontendApplicationInitialized = true;

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

void FrontendPixelLight::OnResume()
{
	// Nothing to do in here
}

void FrontendPixelLight::OnPause()
{
	// Nothing to do in here
}

void FrontendPixelLight::OnStop()
{
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized) {
		// Call application-specific de-initialization routine
		m_pFrontendApplication->OnDeInit();

		// De-Initialize application
		m_pFrontendApplication->OnStop();

		// Frontend application is no longer initialized
		m_bFrontendApplicationInitialized = false;
	}
}

void FrontendPixelLight::OnDestroy()
{
	// Destroy the frontend application instance
	if (m_pFrontendApplication) {
		delete m_pFrontendApplication;
		m_pFrontendApplication = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
