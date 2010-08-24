/*********************************************************\
 *  File: Application.cpp                                *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Console.h>
#include <PLCore/Tools/Localization.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() : PLCore::ConsoleApplication()
{
	// Set application name and title
	SetName("02CommandLine");
	SetTitle(PLT("PLSample 02 - CommandLine"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));

	// Register commandline options:
	//   02CommandLine [-u/--uppercase] [-p/--prefix <prefix>] <text> [postfix]
	m_cCommandLine.AddParameter	("Prefix",    "-p", "--prefix",		"Text prefix",						"",	false);
	m_cCommandLine.AddFlag		("Uppercase", "-u", "--uppercase",	"Convert the text to upper case",		false);
	m_cCommandLine.AddArgument	("Text",							"Text string",						"",	true);
	m_cCommandLine.AddArgument	("Postfix",							"Text postfix",						"",	false);
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}


//[-------------------------------------------------------]
//[ Private virtual ConsoleApplication functions          ]
//[-------------------------------------------------------]
void Application::Main()
{
	// Get text, prefix and postfix
	String sText    = m_cCommandLine.GetValue("Text");
	String sPrefix  = m_cCommandLine.GetValue("Prefix");
	String sPostfix = m_cCommandLine.GetValue("Postfix");
	if (sPrefix .GetLength() > 0) sText = sPrefix + " " + sText;
	if (sPostfix.GetLength() > 0) sText = sText   + " " + sPostfix;

	// Get uppercase option
	if (m_cCommandLine.IsValueSet("-u")) sText.ToUpper();

	// Print text
	System::GetInstance()->GetConsole().Print("Text: '" + sText + "'\n");

	// Print additional arguments
	for (uint32 i=0; i<m_cCommandLine.GetNumOfAdditionalArguments(); i++) {
		if (i == 0) {
		System::GetInstance()->GetConsole().Print("\nAddition arguments:\n");
		}
		System::GetInstance()->GetConsole().Print("- '" + m_cCommandLine.GetAdditionalArgument(i) + "'\n");
	}
}
