/*********************************************************\
 *  File: TrollType.h                                    *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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
*    Troll type which is able to remember a complete number, as long as it's 0, 1 or 2 - in short: a completely useless example data type
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
		PLCore::String GetComment() const;


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
