/*********************************************************\
 *  File: Parameters.cpp                                 *
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
#include "PLRenderer/Renderer/Parameters.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
// For fast Parameters::DataTypeToString()
const String g_sDataTypeToString[] = {
	"String",
	"Integer",
	"Integer2",
	"Integer3",
	"Integer4",
	"Float",
	"Float2",
	"Float3",
	"Float4",
	"Double",
	"Double2",
	"Double3",
	"Double4",
	"Float3x3",
	"Float3x4",
	"Float4x4",
	"Double4x4",
	"Texture", // [TODO] Currently not 'TextureBuffer'
	"Unknown"
};
// For fast Parameters::DataTypeFromString()
HashMap<String, Parameters::EDataType> g_mapDataTypeFromString;


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a data type as string
*/
String Parameters::DataTypeToString(EDataType nDataType)
{
	return (nDataType <= UnknownDataType) ? g_sDataTypeToString[nDataType] : "";
}

/**
*  @brief
*    Returns a data type as number
*/
Parameters::EDataType Parameters::DataTypeFromString(const PLCore::String &sDataType)
{
	// Check parameter
	if (sDataType.GetLength()) {
		// Initialize the hash map?
		if (!g_mapDataTypeFromString.GetNumOfElements()) {
			g_mapDataTypeFromString.Add("String",	 String);
			g_mapDataTypeFromString.Add("Integer",	 Integer);
			g_mapDataTypeFromString.Add("Integer2",	 Integer2);
			g_mapDataTypeFromString.Add("Integer3",	 Integer3);
			g_mapDataTypeFromString.Add("Integer4",	 Integer4);
			g_mapDataTypeFromString.Add("Float",	 Float);
			g_mapDataTypeFromString.Add("Float2",	 Float2);
			g_mapDataTypeFromString.Add("Float3",	 Float3);
			g_mapDataTypeFromString.Add("Float4",	 Float4);
			g_mapDataTypeFromString.Add("Double",	 Double);
			g_mapDataTypeFromString.Add("Double2",	 Double2);
			g_mapDataTypeFromString.Add("Double3",	 Double3);
			g_mapDataTypeFromString.Add("Double4",	 Double4);
			g_mapDataTypeFromString.Add("Float3x3",	 Float3x4);
			g_mapDataTypeFromString.Add("Float3x4",	 Float3x4);
			g_mapDataTypeFromString.Add("Float4x4",	 Float4x4);
			g_mapDataTypeFromString.Add("Double4x4", Double4x4);
			g_mapDataTypeFromString.Add("Texture",   TextureBuffer); // [TODO] Currently not 'TextureBuffer'
			g_mapDataTypeFromString.Add("Unknown",	 UnknownDataType);
		}

		// Get the data type as number
		const EDataType &nDataType = g_mapDataTypeFromString.Get(sDataType);
		if (&nDataType != &HashMap<PLCore::String, EDataType>::Null)
			return nDataType;
	}

	// Error!
	return UnknownDataType;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Parameters::Parameters()
{
}

/**
*  @brief
*    Destructor
*/
Parameters::~Parameters()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Parameters::Parameters(const Parameters &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Parameters &Parameters::operator =(const Parameters &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
