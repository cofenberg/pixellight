/*********************************************************\
 *  File: ShaderToolsCg.cpp                              *
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
#include <PLGeneral/Log/Log.h>
#include "PLRendererOpenGLCg/ShaderToolsCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
CGcontext ShaderToolsCg::m_pCgContext       = nullptr;
uint32    ShaderToolsCg::m_nCgContexCounter = 0;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a Cg context reference
*/
void ShaderToolsCg::AddCgContextReference()
{
	// Check Cg context
	if (!m_nCgContexCounter && !m_pCgContext) {
		PL_LOG(Info, PLGeneral::String::Format("Initialize Cg %d", CG_VERSION_NUM))
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
void ShaderToolsCg::ReleaseCgContextReference()
{
	// Check Cg context
	m_nCgContexCounter--;
	if (!m_nCgContexCounter && m_pCgContext) {
		PL_LOG(Info, String::Format("De-initialize Cg %d", CG_VERSION_NUM))
		cgSetErrorCallback(nullptr); // Just for sure :)
		cgDestroyContext(m_pCgContext);
		m_pCgContext = nullptr;
	}
}

/**
*  @brief
*    Returns the Cg context
*/
CGcontext ShaderToolsCg::GetCgContext()
{
	return m_pCgContext;
}

/**
*  @brief
*    Creates a Cg program
*/
CGprogram ShaderToolsCg::CreateCgProgram(CGprofile pCgProfile, const String &sSourceCode, const String &sEntry)
{
	// Set optimal profile options - this will set implicit compiler arguments chosen based on the the available compiler arguments, GPU, and driver
	cgGLSetOptimalOptions(pCgProfile);

	// Create the program
	CGprogram pCgProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, sSourceCode.GetASCII(), pCgProfile, sEntry.GetLength() ? sEntry.GetASCII() : "main", nullptr);
	if (!pCgProgram) {
		// Error!
		PL_LOG(Error, PLGeneral::String::Format("Can't create Cg program! Error: %s", cgGetErrorString(cgGetError())))
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
void ShaderToolsCg::CgErrorCallback()
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
} // OpenGL
