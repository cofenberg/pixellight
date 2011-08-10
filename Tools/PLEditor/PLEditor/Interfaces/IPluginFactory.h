/*********************************************************\
 *  File: IPluginFactory.h                               *
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


#ifndef IPLUGINFACTORY_H
#define IPLUGINFACTORY_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QString>
#include <QtPlugin>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Editor plugin factory interface
*/
class IPluginFactory {


	//[-------------------------------------------------------]
	//[ Public virtual methods                                ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the plugin factory
		*
		*  @return
		*    The name of the plugin
		*/
		virtual QString getName() const = 0;

		/**
		*  @brief
		*    Returns the name of the plugin vendor factory
		*
		*  @return
		*    The name of the plugin vendor
		*/
		virtual QString getVendor() const = 0;

		/**
		*  @brief
		*    Returns the plugin license factory
		*
		*  @return
		*    The plugin license
		*/
		virtual QString getLicense() const = 0;

		/**
		*  @brief
		*    Returns the plugin description factory
		*
		*  @return
		*    The plugin description
		*/
		virtual QString getDescription() const = 0;

		/**
		*  @brief
		*    Returns the number of classes
		*
		*  @return
		*    The number of classes
		*/
		virtual unsigned int getNumOfClasses() const = 0;

		/**
		*  @brief
		*    Returns the number of classes
		*
		*  @param[nClass]
		*    Index of the class to create an instance from
		*
		*  @return
		*    The class instance (destroy the instance if you no longer need it), null pointer on error
		*/
		virtual QObject *createInstance(unsigned int nClass) const = 0;


	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		IPluginFactory() {}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~IPluginFactory() {}


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
		IPluginFactory(const IPluginFactory &cSource) {}

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
		IPluginFactory &operator =(const IPluginFactory &cSource) { return *this; }


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor


//[-------------------------------------------------------]
//[ Qt definitions                                        ]
//[-------------------------------------------------------]
Q_DECLARE_INTERFACE(PLEditor::IPluginFactory, "PLEditor/IPluginFactory/1.0")


#endif // IPLUGINFACTORY_H
