/*********************************************************\
 *  File: LogFormatterHtml.inl                           *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    This text gets printed to the log when the log is opened
*/
inline void LogFormatterHtml::SetHeader(const String &sHeader)
{
	m_sHeader = sHeader;
}

/**
*  @brief
*    Sets the title of the log
*/
inline void LogFormatterHtml::SetTitle(const String &sTitle)
{
	m_sTitle = sTitle;
}

/**
*  @brief
*    Sets the Background for the HTML document either a color or a image
*/
inline void LogFormatterHtml::SetBackground(const String &sBackground)
{
	m_sBackground = sBackground;
}

/**
*  @brief
*    Sets the default text color
*/
inline void LogFormatterHtml::SetDefaultTextColor(const String &sColor)
{
	if (sColor.GetLength() > 0)
		m_sDefaultTextColor = sColor;
}

/**
*  @brief
*    Sets the default text format string
*/
inline void LogFormatterHtml::SetDefaultTextFormat(const String &sFormat)
{
	if (sFormat.GetLength() > 0)
		m_sDefaultTextFormat = sFormat;
}

/**
*  @brief
*    This text gets printed to the log before the log gets closed
*/
inline void LogFormatterHtml::SetFooter(const String &sFooter)
{
	m_sFooter = sFooter;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
