/*********************************************************\
 *  File: PLPluginClassInfo.h                            *
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

#ifndef PLPLUGINCLASSINFO_H
#define PLPLUGINCLASSINFO_H
#pragma once

//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/HashMap.h>

//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}

//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    class to parse an pl_class..pl_class_end block
*/
class PLPLuginClassInfo {

	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPLuginClassInfo();

		/**
		*  @brief
		*    Destructor
		*/
		~PLPLuginClassInfo();

		/**
		*  @brief
		*    Appends the parsed information to the given xml element
		*/
		void Save(PLGeneral::XmlElement &pParent);

		/**
		*  @brief
		*    Parse the given pl_class pl_class_end block
		*/
		void ParsePlClassBlock(const PLGeneral::String &sPLClassBlock);

	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    copy constructor
		*/
		PLPLuginClassInfo(const PLPLuginClassInfo& other);

		/**
		*  @brief
		*    assignment operator
		*/
		PLPLuginClassInfo& operator=(const PLPLuginClassInfo& other);

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sClassName;											/** Name of the class */
		PLGeneral::String m_sNamespace;											/** Namespace in which the class is */
		PLGeneral::String m_sBaseClass;											/** Name of the base class */
		PLGeneral::String m_sDescription;										/** Class description */
		bool m_bHasConstructor;													/** Flag which indicates if the class has at least one constructor known by the RTTI */
		bool m_bHasDefaultConstructor;											/** Flag which indicates if the class has andefault constructor known by the RTTI */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapProperties;	/** List of class properties and theire value*/
};

#endif // PLPLUGINCLASSINFO_H
