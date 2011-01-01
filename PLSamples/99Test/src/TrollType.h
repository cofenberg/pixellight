/*********************************************************\
 *  File: TrollType.h                                    *
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


#ifndef __PLSAMPLE_TROLLTYPE_H__
#define __PLSAMPLE_TROLLTYPE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Type/Type.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Troll type which is able to remeber a complete number, as long as it's 0, 1 or 2 - in short: a completely useless example data type
*/
class TrollType {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		TrollType();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nValue
		*    Value
		*/
		TrollType(int nValue);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Other value
		*/
		TrollType(const TrollType &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		~TrollType();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cOther
		*    Other value
		*
		*  @return
		*    Reference to this value
		*/
		TrollType &operator =(const TrollType &cOther);

		/**
		*  @brief
		*    comparison operator
		*
		*  @param[in] cOther
		*    Other value
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		bool operator ==(const TrollType &cOther) const;

		/**
		*  @brief
		*    Get value
		*
		*  @return
		*    Value
		*/
		int GetValue() const;

		/**
		*  @brief
		*    Set value
		*
		*  @param[in] nValue
		*    Value
		*/
		void SetValue(int nValue);

		/**
		*  @brief
		*    Get comment from troll
		*
		*  @return
		*    Troll's comment
		*/
		PLGeneral::String GetComment() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int m_nValue;


};


//[-------------------------------------------------------]
//[ Include type implementation                           ]
//[-------------------------------------------------------]
#include "TrollType.inl"


#endif // __PLSAMPLE_TROLLTYPE_H__
