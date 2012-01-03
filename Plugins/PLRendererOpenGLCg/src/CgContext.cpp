/*********************************************************\
 *  File: CgContext.cpp                                  *
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
#include <PLCore/Log/Log.h>
#include "PLRendererOpenGLCg/CgContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
CGcontext CgContext::m_pCgContext       = nullptr;
uint32    CgContext::m_nCgContexCounter = 0;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a Cg context reference
*/
void CgContext::AddCgContextReference()
{
	// Check Cg context
	if (!m_nCgContexCounter && !m_pCgContext) {
		PL_LOG(Info, String("Initialize Cg ") + CG_VERSION_NUM)
		m_pCgContext = cgCreateContext();
		cgSetErrorCallback(CgErrorCallback);

		// [TEST] Disable debug mode for better performance
//		cgGLSetDebugMode(CG_FALSE);

		// Delay program recompilation until the program object code is needed
		cgSetAutoCompile(m_pCgContext, CG_COMPILE_LAZY);
	}
	m_nCgContexCounter++;
}

/**
*  @brief
*    Releases a Cg context reference
*/
void CgContext::ReleaseCgContextReference()
{
	// Check Cg context
	m_nCgContexCounter--;
	if (!m_nCgContexCounter && m_pCgContext) {
		PL_LOG(Info, String("De-initialize Cg ") + CG_VERSION_NUM)
		cgSetErrorCallback(nullptr); // Just for sure :)
		cgDestroyContext(m_pCgContext);
		m_pCgContext = nullptr;
	}
}

/**
*  @brief
*    Returns the Cg context
*/
CGcontext CgContext::GetCgContext()
{
	return m_pCgContext;
}

/**
*  @brief
*    Creates a Cg program
*/
CGprogram CgContext::CreateCgProgram(CGprofile pCgProfile, const String &sSourceCode, const String &sEntry, const String &sArguments)
{
	// Set optimal profile options - this will set implicit compiler arguments chosen based on the the available compiler arguments, GPU, and driver
	cgGLSetOptimalOptions(pCgProfile);

	// Create the program
	const char *pszArguments[2] = { sArguments.GetLength() ? sArguments.GetASCII() : nullptr, nullptr };
	CGprogram pCgProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, sSourceCode.GetASCII(), pCgProfile, sEntry.GetLength() ? sEntry.GetASCII() : "main", pszArguments);
	if (!pCgProgram) {
		// Error!
		PL_LOG(Error, String("Can't create Cg program! Error: ") + cgGetErrorString(cgGetError()))
	}

	// Done
	return pCgProgram;
}


//[-------------------------------------------------------]
//[ Private static Cg callback functions                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal Cg error callback function
*/
void CgContext::CgErrorCallback()
{
	CGerror nLastError = cgGetError();
	if (nLastError) {
		const char *pszListing = cgGetLastListing(m_pCgContext);
		PL_LOG(Error, "\n---------------------------------------------------")
		PL_LOG(Error, cgGetErrorString(nLastError))
		if (pszListing)
			PL_LOG(Error, pszListing)
		PL_LOG(Error, "---------------------------------------------------\n")
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
