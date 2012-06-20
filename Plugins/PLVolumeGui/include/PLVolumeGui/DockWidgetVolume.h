/*********************************************************\
 *  File: DockWidgetVolume.h                             *
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


#ifndef __PLVOLUMEGUI_DOCKWIDGET_VOLUME_H__
#define __PLVOLUMEGUI_DOCKWIDGET_VOLUME_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLFrontendQt/DockWidget/DockWidget.h>
#include "PLVolumeGui/PLVolumeGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract volume Qt dock widget base class
*/
class DockWidgetVolume : public PLFrontendQt::DockWidget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMEGUI_RTTI_EXPORT, DockWidgetVolume, "PLVolumeGui", PLFrontendQt::DockWidget, "Abstract volume Qt dock widget base class")
		// Properties
		pl_properties
			pl_property("Title", "Volume")
		pl_properties_end
		#ifdef PLVOLUMEGUI_EXPORTS	// The following is only required when compiling PLVolumeGui
			// Methods
			pl_method_0(GetSelectedObject,	pl_ret_type(PLCore::Object*),						"Returns the currently selected object, can be a null pointer.",	"")
			pl_method_1(SelectObject,		pl_ret_type(void),				PLCore::Object*,	"Selects the given object. Object to select as first parameter.",	"")
		#endif
		// Slots
		pl_slot_0(OnDestroyed,	"Called when the object assigned with this dock widget was destroyed",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the currently selected object
		*
		*  @return
		*    The currently selected object, can be a null pointer
		*/
		PLVOLUMEGUI_API PLCore::Object *GetSelectedObject() const;


	//[-------------------------------------------------------]
	//[ Public virtual DockWidgetVolume functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Selects the given object
		*
		*  @param[in] pObject
		*    Object to select, can be a null pointer
		*/
		PLVOLUMEGUI_API virtual void SelectObject(PLCore::Object *pObject);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQWidgetParent
		*    Pointer to parent Qt widget, can be a null pointer (in this case you're responsible for destroying this instance)
		*  @param[in] pDockWidgetManager
		*    Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer
		*/
		DockWidgetVolume(QWidget *pQWidgetParent, PLFrontendQt::DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetVolume();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the object assigned with this dock widget was destroyed
		*/
		void OnDestroyed();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Object *m_pObject;	/**< Object assigned with this dock widget, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui


#endif // __PLVOLUMEGUI_DOCKWIDGET_VOLUME_H__
