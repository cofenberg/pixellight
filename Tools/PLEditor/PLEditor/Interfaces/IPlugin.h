/*********************************************************\
 *  File: IPlugin.h                                      *
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


#ifndef IPLUGIN_H
#define IPLUGIN_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QString>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Editor plugin interface
*/
class IPlugin {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PluginManager;


	//[-------------------------------------------------------]
	//[ Definitions                                           ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Plugin type
		*/
		enum EType {
			TypeDockWidget = 0,
		};


	//[-------------------------------------------------------]
	//[ Public virtual IPlugin methods                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the type of the plugin
		*
		*  @return
		*    The type of the plugin
		*/
		virtual EType getType() const = 0;

		/**
		*  @brief
		*    Returns the name of the plugin
		*
		*  @return
		*    The name of the plugin
		*/
		virtual QString getName() const = 0;
		
		/**
		 *  @brief
		 *    Creates a clone of this instance.
		 *
		 *  @note
		 *    The caller must destroy the clone after usage
		 * 
		 *  @return
		 *    cloned instance
		 */
		virtual IPlugin* Clone() const = 0;


	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		IPlugin() {}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~IPlugin() {}


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		IPlugin(const IPlugin &cSource) {}

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		IPlugin &operator =(const IPlugin &cSource) { return *this; }


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor


#endif // IPLUGIN_H
