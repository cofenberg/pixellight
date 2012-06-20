/*********************************************************\
 *  File: Context_GDCM.h                                 *
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


#ifndef __PLLOADERDCM_CONTEXT_H__
#define __PLLOADERDCM_CONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <sstream>
#include <PLCore/Core/AbstractContext.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLLoaderDICOM_GDCM {


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
} // PLLoaderDICOM_GDCM


#endif // __PLLOADERDCM_CONTEXT_H__
