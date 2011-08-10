/*********************************************************\
 *  File: PluginFactory.h                               *
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


#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLEditor/Interfaces/IPluginFactory.h>
#include "PLEditorPluginBase_global.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditorPluginBase {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Editor plugin factory implementation
*/
class PLEDITORPLUGINBASESHARED_EXPORT PluginFactory : public QObject, public PLEditor::IPluginFactory {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT
	Q_INTERFACES(PLEditor::IPluginFactory)


	//[-------------------------------------------------------]
	//[ Public virtual PLEditor::IPluginFactory methods       ]
	//[-------------------------------------------------------]
	public:
		virtual QString getName() const;
		virtual QString getVendor() const;
		virtual QString getLicense() const;
		virtual QString getDescription() const;
		virtual unsigned int getNumOfClasses() const;
		virtual QObject *createInstance(unsigned int nClass) const;


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PluginFactory();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PluginFactory();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditorPluginBase


#endif // PLUGINFACTORY_H
