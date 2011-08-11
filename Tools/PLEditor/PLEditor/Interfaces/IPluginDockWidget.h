/*********************************************************\
 *  File: IPluginDockWidget.h                            *
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


#ifndef IPLUGINDOCKWIDGET_H
#define IPLUGINDOCKWIDGET_H
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "IPlugin.h"

class QDockWidget;

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Editor dock widget plugin interface
*/
class IPluginDockWidget : public IPlugin {


	//[-------------------------------------------------------]
	//[ Public virtual IPluginDockWidget methods              ]
	//[-------------------------------------------------------]
	public:
		virtual Qt::DockWidgetArea InitialArea() = 0;
		virtual QDockWidget* GetWidget() = 0;
		
	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		IPluginDockWidget() {}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~IPluginDockWidget() {}


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor


#endif // IPLUGINDOCKWIDGET_H
