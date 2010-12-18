/*********************************************************\
 *  File: QtStringAdapter.h                              *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_QTSTRINGADAPTER_H__
#define __PLGENERAL_QTSTRINGADAPTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <QtCore/QString>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static adapter class for mapping Qt strings to PixelLight strings and vice versa
*
*  @remarks
*    We provide this string adapter class because it's nice to be able to use PixelLight within Qt as comfortable as possible. Please note
*    that the existence of this adapter class doesn't mean that PixelLight depends on Qt - inside PixelLight, neither this class nor Qt are NOT used!
*    (that's the reason why there's just a header file for this class, and no c++ file)
*
*    Please note that there's a perfidy when using wchar_t in combination with PixelLight & Qt...
*
*    When using the default settings within e.g. Visual Studio 2008, wchar_t is treated as built-in type, so third party unicode
*    shared libraries usually use it. So, this is also the default setting for PixelLight projects. On the other hand, if you
*    want to use PixelLight within Qt and write something like "PLGeneral::String sString = L"Test";", the linker will give you an error
*    message like
*      "error:  unresolved external symbol "__declspec(dllimport) public: __thiscall PLGeneral::String::String(unsigned short const *,bool,int)" (__imp_??0String@PLGeneral@@QAE@PBG_NH@Z) referenced in function _main"
*    because within Qt, wchar_t is defined as "unsigned short" and not as build in type "wchar_t".
*
*    One solution is to remove "-Zc:wchar_t-" from "QMAKE_CFLAGS" within "qmake.conf" of Qt, and then recompiling Qt.
*
*    Another solution, one that we don't recommend, is to recompile PixelLight with a set "-Zc:wchar_t-"... which means that
*    it might be necessary to modify external dependencies as well!
*/
class QtStringAdapter {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a PLGeneral::String version from the given QString
		*
		*  @param[in] sString
		*    QString to convert
		*
		*  @return
		*    A PLGeneral::String version from the given QString
		*/
		static String QtToPL(const QString &sString)
		{
			// We could just use ASCII by writing
			//    return sString.toAscii().constData();
			// Or UTF8 by writing
			//    return (const PLGeneral::utf8*)sString.toUtf8().constData();
			// But PixelLight works best with wchar_t, so we use wchar_t...

			// Get the number of characters in this string (excluding the terminating zero)
			const int nLength = sString.length();
			if (nLength) {
				// Allocate enough space for the string
				wchar_t *pszString = new wchar_t[nLength + 1];	// +1 for the terminating zero
				pszString[nLength] = '\0';	// Set the terminating zero

				// Ask Qt for a wchar_t version of it's string
				if (sString.toWCharArray(pszString) == nLength) {
					// All went fine :D
					return String(pszString, false, nLength); // Do not copy, please - the PLGeneral::String takes over the control of the memory
				} else {
					// Error!

					// Cleanup
					delete [] pszString;
				}
			}

			// Empty string
			return "";
		}

		/**
		*  @brief
		*    Returns a QString version from the given PLGeneral::String
		*
		*  @param[in] sString
		*    PLGeneral::String to convert
		*
		*  @return
		*    A QString version from the given PLGeneral::String
		*/
		static QString PLToQt(const String &sString)
		{
			// Check the internal PixelLight string format
			switch (sString.GetFormat()) {
				case String::ASCII:
					return QString::fromAscii(sString.GetASCII());

				case String::Unicode:
					return QString::fromWCharArray(sString.GetUnicode());

				case String::UTF8:
					return QString::fromUtf8((const char*)sString.GetUTF8());
			}

			// Error!
			return "";
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_QTSTRINGADAPTER_H__
