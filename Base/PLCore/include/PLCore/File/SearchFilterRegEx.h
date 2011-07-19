/*********************************************************\
 *  File: SearchFilterRegEx.h                            *
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


#ifndef __PLCORE_FILE_SEARCHFILTERREGEX_H__
#define __PLCORE_FILE_SEARCHFILTERREGEX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/RegEx.h"
#include "PLCore/File/SearchFilter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Search filter working with a regular expression (PCRE syntax)
*
*  @see
*    - 'RegEx'-class
*/
class SearchFilterRegEx : public SearchFilter {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sExpression
		*    Regular expression
		*  @param[in] nMode
		*    Processing mode (combination of EMatch values)
		*/
		PLCORE_API SearchFilterRegEx(const String &sExpression, uint32 nMode = RegEx::MatchCaseSensitive | RegEx::MatchGreedy);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~SearchFilterRegEx();

		/**
		*  @brief
		*    Get expression
		*
		*  @return
		*    Regular expression
		*/
		PLCORE_API String GetExpression() const;


	//[-------------------------------------------------------]
	//[ Public virtual SearchFilter functions                 ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual bool CheckFile(const String &sFilename);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RegEx m_cRegEx;		/**< Regular expression */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FILE_SEARCHFILTERREGEX_H__
