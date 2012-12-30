/*********************************************************\
 *  File: Context_GDCM.cpp                               *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Log/Log.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4530)	// "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <gdcm/Common/gdcmTypes.h>
PL_WARNING_POP
#include "PLVolumeLoaderDICOM_GDCM/Context_GDCM.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLVolumeLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ Private static data                                   ]
//[-------------------------------------------------------]
uint32			   Context_GDCM::m_nContextCounter = 0;
std::ostringstream Context_GDCM::m_stdOStringStream;


//[-------------------------------------------------------]
//[ Public static methods                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a context reference
*/
void Context_GDCM::AddReference()
{
	// Check context
	if (!m_nContextCounter) {
		PL_LOG(Info, String("Initialize GDCM ") + GDCM_VERSION)

		// Ensure GDCM debug, warning and error trace is enabled
		gdcm::Trace::DebugOff();	// By default, disable the debug output or else GDCM will spam the log with more or less useless information
		gdcm::Trace::WarningOn();
		gdcm::Trace::ErrorOn();
		gdcm::Trace::SetStream(m_stdOStringStream);
	}
	m_nContextCounter++;
}

/**
*  @brief
*    Releases a context reference
*/
void Context_GDCM::ReleaseReference()
{
	// Check context
	m_nContextCounter--;
	if (!m_nContextCounter)
		PL_LOG(Info, String("De-initialize GDCM ") + GDCM_VERSION)
}

/**
*  @brief
*    Flush the GDCM trace into the PixelLight log
*/
void Context_GDCM::FlushTraceToLog()
{
	PL_LOG(Warning, m_stdOStringStream.str().c_str())
	m_stdOStringStream.clear();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeLoaderDICOM_GDCM
