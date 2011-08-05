/*********************************************************\
 *  File: FrontendImpl.cpp                               *
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
#include "PLCore/Frontend/Frontend.h"
#include "PLCore/Frontend/FrontendImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(FrontendImpl)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendImpl::FrontendImpl() :
	m_pFrontend(nullptr),
	m_nWidth(0),
	m_nHeight(0)
{
}

/**
*  @brief
*    Destructor
*/
FrontendImpl::~FrontendImpl()
{
}

/**
*  @brief
*    Get window width
*/
uint32 FrontendImpl::GetWidth() const
{
	// Return current width
	return m_nWidth;
}

/**
*  @brief
*    Get window height
*/
uint32 FrontendImpl::GetHeight() const
{
	// Return current height
	return m_nHeight;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called to let the frontend draw into it's window
*/
void FrontendImpl::OnDraw()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnDraw();
}

/**
*  @brief
*    Called when the window size has been changed
*/
void FrontendImpl::OnSize()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnSize();
}


//[-------------------------------------------------------]
//[ Protected virtual AbstractLifecycle functions         ]
//[-------------------------------------------------------]
void FrontendImpl::OnCreate()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnCreate();
}

void FrontendImpl::OnRestart()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnRestart();
}

bool FrontendImpl::OnStart()
{
	// Call virtual function from frontend
	return m_pFrontend ? m_pFrontend->OnStart() : true;
}

void FrontendImpl::OnResume()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnResume();
}

void FrontendImpl::OnPause()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnPause();
}

void FrontendImpl::OnStop()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnStop();
}

void FrontendImpl::OnDestroy()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnDestroy();
}


//[-------------------------------------------------------]
//[ Protected virtual FrontendImpl functions              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the frontend should run
*/
int FrontendImpl::Run(const String &sExecutableFilename, const Array<String> &lstArguments, const String &sApplicationClass)
{
	// Nothing to do in here
	return 0;
}

/**
*  @brief
*    Run the frontend using traditional C-arguments
*/
int FrontendImpl::Run(int argc, char **argv, const String &sApplicationClass)
{
	// By default, call the version of the "Run()"-method using PixelLight strings by using the same approach used in "PLMain()"
	Array<String> lstArguments;
	for (int i=1; i<argc; i++)
		lstArguments.Add(argv[i]);
	return Run(System::GetInstance()->GetExecutableFilename(), lstArguments, sApplicationClass);
}

int FrontendImpl::Run(int argc, wchar_t **argv, const String &sApplicationClass)
{
	// By default, call the version of the "Run()"-method using PixelLight strings by using the same approach used in "PLMain()"
	Array<String> lstArguments;
	for (int i=1; i<argc; i++)
		lstArguments.Add(argv[i]);
	return Run(System::GetInstance()->GetExecutableFilename(), lstArguments, sApplicationClass);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
