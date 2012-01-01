/*********************************************************\
 *  File: StringBufferASCII.h                            *
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


#ifndef __PLCORE_STRINGBUFFER_ASCII_H__
#define __PLCORE_STRINGBUFFER_ASCII_H__
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
*    Class that contains the buffer for a ASCII string
*/
class StringBufferASCII : public StringBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class String;
	friend class StringBufferManager;
	friend class StringBufferUnicode;
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
		StringBufferASCII(char szString[], uint32 nLength, uint32 nMaxLength);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] szString
		*    The string (converted to ASCII)
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*  @param[in] nMaxLength
		*    Maximum available length of the string buffer (excluding the terminating zero)
		*/
		StringBufferASCII(const wchar_t szString[], uint32 nLength, uint32 nMaxLength);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~StringBufferASCII();

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
		*    - Makes the buffered unicode/UTF8 versions invalid
		*/
		void SetString(char szString[], uint32 nLength);

		/**
		*  @brief
		*    Sets the new string length
		*
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero)
		*
		*  @note
		*    - Makes the buffered unicode/UTF8 versions invalid
		*/
		void SetNewStringLength(uint32 nLength);

		/**
		*  @brief
		*    Sets a character
		*
		*  @param[in] nCharacter
		*    Character to set
		*/
		void SetCharacter(char nCharacter);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		char				*m_pszString;	/**< The string itself (NEVER a null pointer!) */
		StringBufferUnicode *m_pUnicode;	/**< Unicode string buffer version of the current string (can be a null pointer) */
		StringBufferUTF8	*m_pUTF8;		/**< UTF8 string buffer version of the current string (can be a null pointer) */


	//[-------------------------------------------------------]
	//[ Public virtual StringBuffer functions                 ]
	//[-------------------------------------------------------]
	public:
		virtual uint32 GetFormat() const override;
		virtual StringBufferASCII *GetASCII() override;
		virtual StringBufferUnicode *GetUnicode() override;
		virtual StringBufferUTF8 *GetUTF8() override;
		virtual uint32 GetNumOfBytes() const override;
		virtual StringBuffer *Clone() const override;
		virtual StringBuffer *Duplicate() override;
		virtual bool IsLessThan(const char szString[], uint32 nLength) const override;
		virtual bool IsLessThan(const wchar_t szString[], uint32 nLength) const override;
		virtual bool IsGreaterThan(const char szString[], uint32 nLength) const override;
		virtual bool IsGreaterThan(const wchar_t szString[], uint32 nLength) const override;
		virtual bool Compare(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const override;
		virtual bool Compare(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const override;
		virtual bool CompareNoCase(const char szString[], uint32 nLength, uint32 nPos, uint32 nCount) const override;
		virtual bool CompareNoCase(const wchar_t szString[], uint32 nLength, uint32 nPos, uint32 nCount) const override;
		virtual bool IsAlphabetic() const override;
		virtual bool IsAlphaNumeric() const override;
		virtual bool IsNumeric() const override;
		virtual bool IsSubstring(const char szString[], uint32 nLength) const override;
		virtual bool IsSubstring(const wchar_t szString[], uint32 nLength) const override;
		virtual int IndexOf(const char szString[], uint32 nPos, uint32 nLength) const override;
		virtual int IndexOf(const wchar_t szString[], uint32 nPos, uint32 nLength) const override;
		virtual int LastIndexOf(const char szString[], int nPos, uint32 nLength) const override;
		virtual int LastIndexOf(const wchar_t szString[], int nPos, uint32 nLength) const override;
		virtual StringBuffer *GetSubstring(uint32 nPos, uint32 nCount) const override;
		virtual StringBuffer *ToLower() override;
		virtual StringBuffer *ToUpper() override;
		virtual StringBuffer *Delete(uint32 nPos, uint32 nCount) override;
		virtual StringBuffer *Append(const char szString[], uint32 nCount) override;
		virtual StringBuffer *Append(const wchar_t szString[], uint32 nCount) override;
		virtual StringBuffer *Insert(const char szString[], uint32 nPos, uint32 nCount) override;
		virtual StringBuffer *Insert(const wchar_t szString[], uint32 nPos, uint32 nCount) override;
		virtual StringBuffer *Replace(char nOld, char nNew, uint32 &nReplaced) override;
		virtual StringBuffer *Replace(wchar_t nOld, wchar_t nNew, uint32 &nReplaced) override;
		virtual StringBuffer *Replace(const char szOld[], uint32 nOldLength, const char szNew[], uint32 nNewLength, uint32 &nReplaced) override;
		virtual StringBuffer *Replace(const wchar_t szOld[], uint32 nOldLength, const wchar_t szNew[], uint32 nNewLength, uint32 &nReplaced) override;
		virtual StringBuffer *SetCharacter(uint32 nIndex, char nCharacter) override;
		virtual StringBuffer *SetCharacter(uint32 nIndex, wchar_t nCharacter) override;
		virtual StringBuffer *TrimLeading() override;
		virtual StringBuffer *TrimTrailing() override;
		virtual StringBuffer *RemoveLineEndings() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_STRINGBUFFER_ASCII_H__
