/*********************************************************\
 *  File: StringBufferUTF8.h                             *
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


#ifndef __PLCORE_STRINGBUFFER_UTF8_H__
#define __PLCORE_STRINGBUFFER_UTF8_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/StringBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class that contains the buffer for a UTF8 string
*
*  @note
*    - Unlike StringBufferASCII and StringBufferUnicode, the sole purpose of this implementation is to keep a cached UTF8 version of a string
*/
class StringBufferUTF8 : public StringBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class String;
	friend class StringBufferManager;
	friend class StringBufferASCII;
	friend class StringBufferUnicode;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] szString
		*    The string (converted to UTF8)
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*/
		StringBufferUTF8(char szString[], uint32 nLength);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] szString
		*    The string (converted to UTF8)
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*/
		StringBufferUTF8(const wchar_t szString[], uint32 nLength);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~StringBufferUTF8();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		char   *m_pszString;	/**< The string itself (NEVER a null pointer!) */
		uint32  m_nNumOfBytes;	/**< Number of bytes of the string */


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
} // PLCore


#endif // __PLCORE_STRINGBUFFER_UTF8_H__
