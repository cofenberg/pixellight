/*********************************************************\
 *  File: QtStringAdapter.h                              *
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


#ifndef __PLQT_QTSTRINGADAPTER_H__
#define __PLQT_QTSTRINGADAPTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <QtCore/QString>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {


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
*    (that's the reason why there's just a header file for this class, and no c++ file)
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
		static PLGeneral::String QtToPL(const QString &sString)
		{
			// While PixelLight is build with "wchar_t is treated as built-in type", Qt is not - therefore we pass
			// over the string by using UTF8 to avoid the need to recompile PixelLight/Qt with other compiler settings
			return PLGeneral::String::FromUTF8(sString.toUtf8().constData());
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
		static QString PLToQt(const PLGeneral::String &sString)
		{
			// Check the internal PixelLight string format
			switch (sString.GetFormat()) {
				case PLGeneral::String::ASCII:
					return QString::fromAscii(sString.GetASCII());

				case PLGeneral::String::Unicode:
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
} // PLQt


#endif // __PLQT_QTSTRINGADAPTER_H__
