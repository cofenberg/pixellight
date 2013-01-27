/*********************************************************\
 *  File: QtStringAdapter.h                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLFRONTENDQT_QTSTRINGADAPTER_H__
#define __PLFRONTENDQT_QTSTRINGADAPTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <QtCore/QString>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static adapter class for mapping Qt strings to PixelLight strings and vice versa
*
*  @remarks
*    We provide this string adapter class because it's nice to be able to use PixelLight within Qt as comfortable as possible. Please note
*    that the existence of this adapter class doesn't mean that PixelLight depends on Qt - inside PixelLight, neither this class nor Qt are used!
*    (that's the reason why there's just a header file for this class, and no C++ file)
*/
class QtStringAdapter {


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a PLCore::String version from the given QString
		*
		*  @param[in] sString
		*    QString to convert
		*
		*  @return
		*    A PLCore::String version from the given QString
		*/
		static PLCore::String QtToPL(const QString &sString)
		{
			// While PixelLight is build with "wchar_t is treated as built-in type", Qt is not - therefore we pass
			// over the string by using UTF8 to avoid the need to recompile PixelLight/Qt with other compiler settings
			return PLCore::String::FromUTF8(sString.toUtf8().constData());
		}

		/**
		*  @brief
		*    Returns a QString version from the given PLCore::String
		*
		*  @param[in] sString
		*    PLCore::String to convert
		*
		*  @return
		*    A QString version from the given PLCore::String
		*/
		static QString PLToQt(const PLCore::String &sString)
		{
			// Check the internal PixelLight string format
			switch (sString.GetFormat()) {
				case PLCore::String::ASCII:
					return QString::fromAscii(sString.GetASCII());

				case PLCore::String::Unicode:
					// While PixelLight is build with "wchar_t is treated as built-in type", Qt is not - therefore we pass
					// over the string by using UTF8 to avoid the need to recompile PixelLight/Qt with other compiler settings
					return QString::fromUtf8(sString.GetUTF8());
			}

			// Error!
			return "";
		}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QTSTRINGADAPTER_H__
