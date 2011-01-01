/*********************************************************\
 *  File: StringBufferUnicode.h                          *
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


#ifndef __PLGENERAL_STRINGBUFFER_UNICODE_H__
#define __PLGENERAL_STRINGBUFFER_UNICODE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/StringBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class that contains the buffer for a Unicode string
*/
class StringBufferUnicode : public StringBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class String;
	friend class StringBufferManager;
	friend class StringBufferASCII;
	friend class StringBufferUTF8;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] szString
		*    The string (this string buffer takes over the control)
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*  @param[in] nMaxLength
		*    Maximum available length of the string buffer (excluding the terminating zero)
		*/
		StringBufferUnicode(wchar_t szString[], uint32 nLength, uint32 nMaxLength);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] szString
		*    The string (converted to Unicode)
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*  @param[in] nMaxLength
		*    Maximum available length of the string buffer (excluding the terminating zero)
		*/
		StringBufferUnicode(const char szString[], uint32 nLength, uint32 nMaxLength);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~StringBufferUnicode();

		/**
		*  @brief
		*    Sets the string
		*
		*  @param[in] szString
		*    The string
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*
		*  @note
		*    - Makes the buffered ASCII/UTF8 versions invalid
		*/
		void SetString(wchar_t szString[], uint32 nLength);

		/**
		*  @brief
		*    Sets the new string length
		*
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*
		*  @note
		*    - Makes the buffered ASCII/UTF8 versions invalid
		*/
		void SetNewStringLength(uint32 nLength);

		/**
		*  @brief
		*    Sets a character
		*
		*  @param[in] nCharacter
		*    Character to set
		*/
		void SetCharacter(wchar_t nCharacter);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		wchar_t			  *m_pszString;	/**< The string itself (NEVER NULL!) */
		StringBufferASCII *m_pASCII;	/**< ASCII string buffer version of the current string (can be NULL) */
		StringBufferUTF8  *m_pUTF8;		/**< UTF8 string buffer version of the current string (can be NULL) */


	//[-------------------------------------------------------]
	//[ Public virtual StringBuffer functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual String::EFormat GetFormat() const;
		virtual StringBufferASCII *GetASCII();
		virtual StringBufferUnicode *GetUnicode();
		virtual StringBufferUTF8 *GetUTF8();
		virtual uint32 GetNumOfBytes() const;
		virtual StringBuffer *Clone() const;
		virtual StringBuffer *Duplicate();
		virtual bool IsLessThan(const char szString[], uint32 nLength) const;
		virtual bool IsLessThan(const wchar_t szString[], uint32 nLength) const;
		virtual bool IsGreaterThan(const char szString[], uint32 nLength) const;
		virtual bool IsGreaterThan(const wchar_t szString[], uint32 nLength) const;
		virtual bool Compare(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const;
		virtual bool Compare(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const;
		virtual bool CompareNoCase(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const;
		virtual bool CompareNoCase(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const;
		virtual bool IsAlphabetic() const;
		virtual bool IsAlphaNumeric() const;
		virtual bool IsNumeric() const;
		virtual bool IsSubstring(const char szString[], uint32 nLength) const;
		virtual bool IsSubstring(const wchar_t szString[], uint32 nLength) const;
		virtual int IndexOf(const char szString[], uint32 nPos, uint32 nLength) const;
		virtual int IndexOf(const wchar_t szString[], uint32 nPos, uint32 nLength) const;
		virtual int LastIndexOf(const char szString[], int nPos, uint32 nLength) const;
		virtual int LastIndexOf(const wchar_t szString[], int nPos, uint32 nLength) const;
		virtual StringBuffer *GetSubstring(uint32 nPos, uint32 nCount) const;
		virtual StringBuffer *ToLower();
		virtual StringBuffer *ToUpper();
		virtual StringBuffer *Delete(uint32 nPos, uint32 nCount);
		virtual StringBuffer *Append(const char szString[], uint32 nCount);
		virtual StringBuffer *Append(const wchar_t szString[], uint32 nCount);
		virtual StringBuffer *Insert(const char szString[], uint32 nPos, uint32 nCount);
		virtual StringBuffer *Insert(const wchar_t szString[], uint32 nPos, uint32 nCount);
		virtual StringBuffer *Replace(char nOld, char nNew, uint32 &nReplaced);
		virtual StringBuffer *Replace(wchar_t nOld, wchar_t nNew, uint32 &nReplaced);
		virtual StringBuffer *Replace(const char szOld[], uint32 nOldLength, const char szNew[], uint32 nNewLength, uint32 &nReplaced);
		virtual StringBuffer *Replace(const wchar_t szOld[], uint32 nOldLength, const wchar_t szNew[], uint32 nNewLength, uint32 &nReplaced);
		virtual StringBuffer *SetCharacter(uint32 nIndex, char nCharacter);
		virtual StringBuffer *SetCharacter(uint32 nIndex, wchar_t nCharacter);
		virtual StringBuffer *TrimLeading();
		virtual StringBuffer *TrimTrailing();
		virtual StringBuffer *RemoveLineEndings();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_STRINGBUFFER_UNICODE_H__
