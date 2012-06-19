/*********************************************************\
 *  File: Context_GDCM.h                                 *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
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
