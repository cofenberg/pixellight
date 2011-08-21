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
#include "PLCore/Log/Log.h"
#include "PLCore/Base/Class.h"
#include "PLCore/System/System.h"
#include "PLCore/Frontend/Frontend.h"
#include "PLCore/Frontend/FrontendContext.h"
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
	m_pFrontend(nullptr)
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
*    Returns the frontend instance
*/
Frontend *FrontendImpl::GetFrontend() const
{
	return m_pFrontend;
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
//[ Protected virtual AbstractFrontend functions          ]
//[-------------------------------------------------------]
void FrontendImpl::OnSize()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnSize();
}

void FrontendImpl::OnFullscreenMode()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnFullscreenMode();
}

void FrontendImpl::OnDraw()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnDraw();
}

void FrontendImpl::OnUpdate()
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnUpdate();
}

void FrontendImpl::OnDrop(const Container<String> &lstFiles)
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnDrop(lstFiles);
}


//[-------------------------------------------------------]
//[ Protected virtual FrontendImpl functions              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the frontend is run
*/
void FrontendImpl::OnRun(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Call virtual function from frontend
	if (m_pFrontend)
		m_pFrontend->OnRun(sExecutableFilename, lstArguments);
}

/**
*  @brief
*    Called when the frontend should run
*/
int FrontendImpl::Run(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Nothing to do in here
	return 0;
}


//[-------------------------------------------------------]
//[ Protected static functions                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    Creates a frontend instance
*/
Frontend *FrontendImpl::CreateFrontend(const FrontendContext &cFrontendContext, FrontendImpl &cFrontendImpl)
{
	// Get the frontend RTTI class
	const Class *pClass = ClassManager::GetInstance()->GetClass(cFrontendContext.GetFrontend());
	if (pClass && pClass->IsDerivedFrom("PLCore::Frontend")) {
		// Create the frontend RTTI class instance
		Object *pObject = nullptr;
		if (cFrontendContext.GetFrontendConstructor().GetLength())
			pObject = pClass->Create(cFrontendContext.GetFrontendConstructor(), "FrontendContext=\"" + Type<const FrontendContext&>::ConvertToString(cFrontendContext) + "\" FrontendImpl=\"" + Type<FrontendImpl&>::ConvertToString(cFrontendImpl) + "\" " + cFrontendContext.GetFrontendConstructorParameters());
		else
			pObject = pClass->Create(Params<Object*, const FrontendContext&, FrontendImpl&>(cFrontendContext, cFrontendImpl));

		// Do we now have an instance?
		if (pObject) {
			// Cast the pointer to a frontend pointer
			Frontend *pFrontend = static_cast<Frontend*>(pObject);

			// Write down a log message
			PL_LOG(Info, "Using frontend '" + pClass->GetClassName() + "': " + pClass->GetDescription())

			// Set parameters for the instanced frontend RTTI class
			if (cFrontendContext.GetFrontendParameters().GetLength())
				pObject->SetValues(cFrontendContext.GetFrontendParameters());

			// Done
			return pFrontend;
		} else {
			// Error!
			PL_LOG(Error, "Failed instancing frontend '" + pClass->GetClassName() + "': " + pClass->GetDescription())
		}
	} else {
		// Error!
		PL_LOG(Error, "Frontend '" + cFrontendContext.GetFrontend() + "' is no valid frontend RTTI class")
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Correct frontend position and size settings
*/
void FrontendImpl::CorrectPositionSize(int &nX, int &nY, uint32 &nWidth, uint32 &nHeight, uint32 nScreenWidth, uint32 nScreenHeight, uint32 nMinWidth, uint32 nMinHeight)
{
	// The frontend position shouldn't be negative
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;

	// The frontend position shouldn't be outside the visible screen
	if (nX > nScreenWidth-nMinHeight)
		nX = nScreenWidth-nMinHeight;
	if (nY > nScreenHeight-nMinHeight)
		nY = nScreenHeight-nMinHeight;

	// The width of the frontend shouldn't leave the visible screen
	int nDelta = (nX + nWidth) - nScreenWidth;
	if (nDelta > 0)
		nWidth = (nWidth-nDelta > 0) ? (nWidth-nDelta) : nMinHeight;

	// The height of the frontend shouldn't leave the visible screen
	nDelta = (nY + nHeight) - nScreenHeight;
	if (nDelta > 0)
		nHeight = (nHeight-nDelta > 0) ? (nHeight-nDelta) : nMinHeight;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
