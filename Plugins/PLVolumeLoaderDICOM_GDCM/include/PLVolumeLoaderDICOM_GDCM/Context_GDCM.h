/*********************************************************\
 *  File: Context_GDCM.h                                 *
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


#ifndef __PLVOLUMELOADERDCM_CONTEXT_H__
#define __PLVOLUMELOADERDCM_CONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <sstream>
#include <PLCore/Core/AbstractContext.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeLoaderDICOM_GDCM {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GDCM context - Static class with some useful GDCM tool methods
*/
class Context_GDCM : public PLCore::AbstractContext {


	//[-------------------------------------------------------]
	//[ Public static methods                                 ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Adds a context reference
		*
		*  @note
		*    - Should be done when creating for example a loader instance
		*    - If this is the first reference, the internal GDCM context is created automatically
		*/
		static void AddReference();

		/**
		*  @brief
		*    Releases a context reference
		*
		*  @note
		*    - Should be done when destroying for example a loader instance
		*    - If this is the last reference, the internal GDCM context is destroyed automatically
		*/
		static void ReleaseReference();

		/**
		*  @brief
		*    Flush the GDCM trace into the PixelLight log
		*/
		static void FlushTraceToLog();


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static PLCore::uint32	  m_nContextCounter;	/**< Context counter */
		static std::ostringstream m_stdOStringStream;	/**< Standard string output stream */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeLoaderDICOM_GDCM


#endif // __PLVOLUMELOADERDCM_CONTEXT_H__
