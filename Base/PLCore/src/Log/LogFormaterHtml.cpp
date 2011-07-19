/*********************************************************\
 *  File: LogFormaterHtml.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/File.h"
#include "PLCore/Log/Log.h"
#include "PLCore/Log/LogFormaterHtml.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
LogFormaterHtml::LogFormaterHtml() :
	m_sTitle("PL-Log"),
	m_sDefaultTextColor("black"),
	m_sDefaultTextFormat("|<br>"),
	m_mapTextFormats(new HashMap<uint8, String>(257))
{
}

/**
*  @brief
*    Destructor
*/
LogFormaterHtml::~LogFormaterHtml()
{
	if (m_mapTextFormats)
		delete m_mapTextFormats;
}

/**
*  @brief
*    Sets the text format string for the specified log level
*/
void LogFormaterHtml::SetTextFormat(uint8 nLogLevel, const String &sFormat)
{
	if (sFormat.GetLength() > 0) {
		if (&m_mapTextFormats->Get(nLogLevel) != &HashMap<uint8, String>::Null)
			m_mapTextFormats->Replace(nLogLevel, sFormat);
		else
			m_mapTextFormats->Add(nLogLevel, sFormat);
	}
}

/**
*  @brief
*    This text gets printed to the log when the log is opened
*/
void LogFormaterHtml::SetHeader(const String &sHeader)
{
	m_sHeader = sHeader;
}

/**
*  @brief
*    Sets the title of the log
*/
void LogFormaterHtml::SetTitle(const String &sTitle)
{
	m_sTitle = sTitle;
}

/**
*  @brief
*    Sets the Background for the HTML document either a color or a image
*/
void LogFormaterHtml::SetBackground(const String &sBackground)
{
	m_sBackground = sBackground;
}

/**
*  @brief
*    Sets the default text color
*/
void LogFormaterHtml::SetDefaultTextColor(const String &sColor)
{
	if (sColor.GetLength() > 0)
		m_sDefaultTextColor = sColor;
}

/**
*  @brief
*    Sets the default text format string
*/
void LogFormaterHtml::SetDefaultTextFormat(const String &sFormat)
{
	if (sFormat.GetLength() > 0)
		m_sDefaultTextFormat = sFormat;
}

/**
*  @brief
*    This text gets printed to the log before the log gets closed
*/
void LogFormaterHtml::SetFooter(const String &sFooter)
{
	m_sFooter = sFooter;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
LogFormaterHtml::LogFormaterHtml(const LogFormaterHtml &cSource) :
	m_sTitle("PL-Log"),
	m_sDefaultTextColor("black"),
	m_sDefaultTextFormat("|<br>"),
	m_mapTextFormats(new HashMap<uint8, String>(257))
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
LogFormaterHtml &LogFormaterHtml::operator =(const LogFormaterHtml &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Returns the HTML formated text the given log level
*/
String LogFormaterHtml::GetHtmlFormatedText(uint8 nLogLevel, const String &sText) const
{
	String sLogMessage;
	if (nLogLevel >= Log::Quiet && m_bShowLogLevelPrefix) {
		sLogMessage += "[";
		sLogMessage += Log::GetInstance()->LogLevelToString(nLogLevel);
		sLogMessage += "]: ";
	}
	sLogMessage += sText;

	const String &sValue = m_mapTextFormats->Get(nLogLevel);
	String sTemp = (&sValue != &HashMap<uint8, String>::Null) ? sValue : m_sDefaultTextFormat;
	sTemp.Replace('|', sLogMessage);
	return sTemp;
}


//[-------------------------------------------------------]
//[ Private virtual LogFormater functions                 ]
//[-------------------------------------------------------]
bool LogFormaterHtml::Open(const String &sFilename)
{
	// Open the log file via the helper function of the base class
	m_pFile = OpenFile(sFilename);

	// Error?
	if (m_pFile) {
		// Write the <html> tag
		if (m_pFile->PrintLn("<html>")) {
			// Write the title
			if (m_sTitle.GetLength() > 0) {
				String sTitle = "<head><title>";
				sTitle += m_sTitle;
				sTitle += "</title></head>";
				if (!m_pFile->PrintLn(sTitle))
					return false; // Error!
			}

			// Write the <body> tag
			String sBody = "<body";
			if (m_sBackground.GetLength() > 0) {
				sBody += ' ';
				sBody += m_sBackground;
			}
			if (m_sDefaultTextColor.GetLength() > 0) {
				sBody += " Text=\"";
				sBody += m_sDefaultTextColor;
				sBody += '\"';
			}
			sBody += '>';

			if (m_pFile->PrintLn(sBody)) {
				// Write header text if given
				if (m_sHeader.GetLength() > 0) {
					if (!m_pFile->PrintLn(m_sHeader))
						return false; // Error!
				}

				// Done
				return true;
			}
		}
	}

	// Error!
	return false;
}

bool LogFormaterHtml::Close()
{
	// Is the file open?
	if (m_pFile) {
		// Write footer
		if (m_sFooter.GetLength() > 0)
			m_pFile->PrintLn(m_sFooter);

		// Write </body> and </html> tag
		m_pFile->PrintLn("</body></html>");

		// Close file
		m_pFile->Close();

		// Reset data
		delete m_pFile;
		m_pFile = nullptr;

		// Done
		return true;
	}

	// Error, the log was not even open!
	return false;
}

bool LogFormaterHtml::Output(uint8 nLogLevel, const String &sText)
{
	if (m_pFile) {
		// Write the text and a newline
		if (m_pFile->PrintLn(GetHtmlFormatedText(nLogLevel, sText)))
			return true; // Done
	}

	// Error!
	return false;
}

bool LogFormaterHtml::Flush()
{
	return m_pFile && m_pFile->Flush();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
