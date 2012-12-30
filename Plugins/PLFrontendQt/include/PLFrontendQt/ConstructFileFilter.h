/*********************************************************\
 *  File: ConstructFileFilter.h                          *
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


#ifndef __PLFRONTENDQT_CONSTRUCTFILEFILTER_H__
#define __PLFRONTENDQT_CONSTRUCTFILEFILTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static helper class for constructing file filters for "QFileDialog"
*/
class ConstructFileFilter {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructs a file filter for "QFileDialog" by using the given loadable type
		*
		*  @param[in] sFilterName
		*    Filter name, e.g. "Scene", usually translated into the used language by using e.g. Qt's "tr()"-macro
		*  @param[in] sLoadableType
		*    Name of the loadable type to construct the file filter for, e.g. "Scene"
		*
		*  @return
		*    The constructed file filter, e.g. "Scene (*.scene *.SCENE)"
		*
		*  @see
		*    - "PLCore::LoadableManager"
		*/
		static PLFRONTENDQT_API PLCore::String ByLoadableType(const PLCore::String &sFilterName, const PLCore::String &sLoadableType);

		/**
		*  @brief
		*    Constructs a file filter for "QFileDialog" by using the supported script languages
		*
		*  @param[in] sFilterName
		*    Filter name, e.g. "Scene", usually translated into the used language by using e.g. Qt's "tr()"-macro
		*
		*  @return
		*    The constructed file filter, e.g. "Script (*.lua *.LUA)"
		*
		*  @see
		*    - "PLCore::ScriptManager"
		*/
		static PLFRONTENDQT_API PLCore::String ByScriptLanguages(const PLCore::String &sFilterName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_CONSTRUCTFILEFILTER_H__
