/*********************************************************\
 *  File: Loader.cpp                                     *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Class.h"
#include "PLCore/String/Tokenizer.h"
#include "PLCore/Tools/LoaderImpl.h"
#include "PLCore/Tools/Loader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the loader implementation
*/
LoaderImpl *Loader::GetImpl()
{
	// Create the loader implementation class instance if required right now
	if (!m_pLoaderImpl)
		m_pLoaderImpl = reinterpret_cast<LoaderImpl*>(m_pClass->Create());

	// Return the loader implementation class instance
	return m_pLoaderImpl;
}

/**
*  @brief
*    Returns the name of the loadable type
*/
String Loader::GetTypeName() const
{
	const Class *pClass = m_pClass;
	return pClass ? pClass->GetProperties().Get("Type") : "";
}

/**
*  @brief
*    Checks if a format is supported in a list of extensions
*/
bool Loader::IsFormatSupported(const String &sExtension)
{
	// Check all supported formats
	InitFormatsList();
	for (uint32 i=0; i<m_lstFormats.GetNumOfElements(); i++) {
		if (m_lstFormats[i] == sExtension)
			return true; // Format found
	}

	// The format is not supported
	return false;
}

/**
*  @brief
*    Returns the formats string
*/
String Loader::GetFormats() const
{
	const Class *pClass = m_pClass;
	return pClass ? pClass->GetProperties().Get("Formats") : "";
}

/**
*  @brief
*    Returns the description string
*/
String Loader::GetDescription() const
{
	const Class *pClass = m_pClass;
	return pClass ? pClass->GetDescription() : "";
}

/**
*  @brief
*    Returns the whether loading is supported
*/
bool Loader::CanLoad() const
{
	const Class *pClass = m_pClass;
	return pClass ? pClass->GetProperties().Get("Load").GetBool() : false;
}

/**
*  @brief
*    Returns the whether saving is supported
*/
bool Loader::CanSave() const
{
	const Class *pClass = m_pClass;
	return pClass ? pClass->GetProperties().Get("Save").GetBool() : false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Loader::Loader() :
	m_pClass(nullptr),
	m_pLoaderImpl(nullptr),
	m_pLoadableType(nullptr)
{
	// No implementation because the copy operator is never used
}

/**
*  @brief
*    Constructor
*/
Loader::Loader(const Class &cClass) :
	m_pClass(&cClass),
	m_pLoaderImpl(nullptr),
	m_pLoadableType(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
Loader::~Loader()
{
	// Destroy the loader implementation class instance
	if (m_pLoaderImpl)
		delete m_pLoaderImpl;
}

/**
*  @brief
*    Copy operator
*/
Loader &Loader::operator =(const Loader &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Initializes the formats list
*/
void Loader::InitFormatsList()
{
	// Is the list already initialized?
	if (!m_lstFormats.GetNumOfElements()) {
		// Parse formats all supported formats
		const String sFormats = GetFormats();
		if (sFormats.GetLength()) {
			// Setup the tokenizer
			Tokenizer cTokenizer;
			cTokenizer.Start(sFormats);
			cTokenizer.SetDelimiters(" ,\t\r\n");
			cTokenizer.SetSingleChars("");

			// Register the filename extensions of this loader
			String sToken = cTokenizer.GetNextToken();
			while (sToken.GetLength()) {
				m_lstFormats.Add(sToken);
				sToken = cTokenizer.GetNextToken();
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
