/*********************************************************\
 *  File: PLPluginClassInfo.h                            *
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


#ifndef __PLPLUGINCLASSINFO_H__
#define __PLPLUGINCLASSINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLCore/Container/HashMap.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class to parse an pl_class..pl_class_end block
*/
class PLPluginClassInfo {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPluginClassInfo();

		/**
		*  @brief
		*    Destructor
		*/
		~PLPluginClassInfo();

		/**
		*  @brief
		*    Appends the parsed information to the given XML element
		*
		*  @param[in] cParent
		*   XML element to append the parsed information to
		*/
		void Save(PLCore::XmlElement &cParent) const;

		/**
		*  @brief
		*    Parse the given pl_class pl_class_end block
		*
		*  @param[in] sPLClassBlock
		*    Block to parse
		*/
		void ParsePLClassBlock(const PLCore::String &sPLClassBlock);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Source to copy from
		*/
		PLPluginClassInfo(const PLPluginClassInfo &cOther);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cOther
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLPluginClassInfo &operator =(const PLPluginClassInfo &cOther);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String									m_sClassName;				/**< Name of the class */
		PLCore::String									m_sNamespace;				/**< Namespace in which the class is in */
		PLCore::String									m_sBaseClass;				/**< Name of the base class */
		PLCore::String									m_sDescription;				/**< Class description */
		bool											m_bHasConstructor;			/**< Flag which indicates whether or not the class has at least one constructor known to the RTTI */
		bool											m_bHasDefaultConstructor;	/**< Flag which indicates whether or not the class has a default constructor known to the RTTI */
		PLCore::HashMap<PLCore::String, PLCore::String> m_mapProperties;			/**< List of class properties and their value */


};


#endif // __PLPLUGINCLASSINFO_H__
