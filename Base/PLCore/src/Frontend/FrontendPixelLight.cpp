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
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(FrontendPixelLight)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendPixelLight::FrontendPixelLight(FrontendImpl &cFrontendImpl) : Frontend(cFrontendImpl),
	ApplicationClass(this),
	ApplicationConstructor(this),
	ApplicationConstructorParameters(this),
	ApplicationParameters(this),
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
//[ Public virtual Frontend functions                     ]
//[-------------------------------------------------------]
bool FrontendPixelLight::IsRunning() const
{
	return (m_pFrontendApplication && m_bFrontendApplicationInitialized && m_pFrontendApplication && m_pFrontendApplication->IsRunning());
}


//[-------------------------------------------------------]
//[ Protected virtual Frontend functions                  ]
//[-------------------------------------------------------]
void FrontendPixelLight::OnRun(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Fill application context
	if (m_pFrontendApplication) {
		ApplicationContext &cApplicationContext = m_pFrontendApplication->m_cApplicationContext;
		cApplicationContext.SetStartupDirectory(System::GetInstance()->GetCurrentDir());
		cApplicationContext.SetExecutableFilename(sExecutableFilename);
		cApplicationContext.SetArguments(lstArguments);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractLifecycle functions         ]
//[-------------------------------------------------------]
void FrontendPixelLight::OnCreate()
{
	// Get the frontend application RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(ApplicationClass.GetString());
	if (pClass && pClass->IsDerivedFrom("PLCore::FrontendApplication")) {
		// Create the frontend application RTTI class instance
		if (ApplicationConstructor.GetString().GetLength())
			m_pFrontendApplication = static_cast<FrontendApplication*>(pClass->Create(ApplicationConstructor.GetString(), "Frontend=\"" + Type<Frontend&>::ConvertToString(*this) + "\" " + ApplicationConstructorParameters.GetString()));
		else
			m_pFrontendApplication = static_cast<FrontendApplication*>(pClass->Create(Params<Object*, Frontend&>(*this)));
		if (m_pFrontendApplication) {
			// Set parameters for the instanced frontend application RTTI class
			if (ApplicationParameters.GetString().GetLength())
				m_pFrontendApplication->SetValues(ApplicationParameters.GetString());

			// Do the frontend lifecycle thing - let the world know that we have been created
			m_pFrontendApplication->OnCreate();
		}
	}
}

void FrontendPixelLight::OnRestart()
{
	// Do the frontend lifecycle thing
	if (m_pFrontendApplication)
		m_pFrontendApplication->OnRestart();
}

bool FrontendPixelLight::OnStart()
{
	// Do the frontend lifecycle thing
	if (m_pFrontendApplication && m_pFrontendApplication->OnStart()) {
		// Frontend application successfully initialized (the following "OnInit()" is just application-specific, not framework specific)
		m_bFrontendApplicationInitialized = true;

		// Call application-specific initialization routine
		m_pFrontendApplication->OnInit();

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

void FrontendPixelLight::OnResume()
{
	// Do the frontend lifecycle thing
	if (m_pFrontendApplication)
		m_pFrontendApplication->OnResume();
}

void FrontendPixelLight::OnPause()
{
	// Do the frontend lifecycle thing
	if (m_pFrontendApplication)
		m_pFrontendApplication->OnPause();
}

void FrontendPixelLight::OnStop()
{
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized) {
		// Call application-specific de-initialization routine
		m_pFrontendApplication->OnDeInit();

		// Do the frontend lifecycle thing
		m_pFrontendApplication->OnStop();

		// Frontend application is no longer initialized
		m_bFrontendApplicationInitialized = false;
	}
}

void FrontendPixelLight::OnDestroy()
{
	// Destroy the frontend application instance
	if (m_pFrontendApplication) {
		// Do the frontend lifecycle thing - let the world know that we're going to die
		m_pFrontendApplication->OnDestroy();

		// Destroy the frontend application instance
		delete m_pFrontendApplication;
		m_pFrontendApplication = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractFrontend functions          ]
//[-------------------------------------------------------]
void FrontendPixelLight::OnSize()
{
	// Call virtual function from application
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnSize();
}

void FrontendPixelLight::OnDisplayMode()
{
	// Call virtual function from application
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnDisplayMode();
}

void FrontendPixelLight::OnFullscreenMode()
{
	// Call virtual function from application
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnFullscreenMode();
}

void FrontendPixelLight::OnDraw()
{
	// Call virtual function from application
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnDraw();
}

void FrontendPixelLight::OnUpdate()
{
	// Call virtual function from application
	if (m_pFrontendApplication && m_bFrontendApplicationInitialized)
		m_pFrontendApplication->OnUpdate();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
