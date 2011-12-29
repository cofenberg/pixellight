/*********************************************************\
 *  File: ConstructFileFilter.h                          *
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
