/*********************************************************\
 *  File: DockWidgetVolumeTransferFunction.h             *
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


#ifndef __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_H__
#define __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeGui/DockWidgetVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QLabel;
	class QMainWindow;
QT_END_NAMESPACE
namespace PLVolumeGui {
	class TransferFunctionWidget;
	class DockWidgetVolumeTransferFunctionQObject;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume transfer function Qt dock widget class
*/
class DockWidgetVolumeTransferFunction : public DockWidgetVolume {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetVolumeTransferFunctionQObject;
	friend class TransferFunctionWidget;	// [TODO] Remove this


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMEGUI_RTTI_EXPORT, DockWidgetVolumeTransferFunction, "PLVolumeGui", PLVolumeGui::DockWidgetVolume, "Volume transfer function Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Transfer Function")
		pl_properties_end
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	PLFrontendQt::DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQMainWindow
		*    Pointer to Qt main window, can be a null pointer (in this case you're responsible for destroying this instance)
		*  @param[in] pDockWidgetManager
		*    Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer
		*/
		DockWidgetVolumeTransferFunction(QMainWindow *pQMainWindow, PLFrontendQt::DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetVolumeTransferFunction();


	//[-------------------------------------------------------]
	//[ Public virtual DockWidgetVolume functions             ]
	//[-------------------------------------------------------]
	public:
		PLVOLUMEGUI_API virtual void SelectObject(PLCore::Object *pObject) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Updates the transfer function
		*
		*  @param[in] pObject
		*    Selected object can be a null pointer (which frees the internal data)
		*/
		void UpdateObject(PLCore::Object *pObject);

		/**
		*  @brief
		*    Updates the transfer function result
		*/
		void UpdateTransferFunctionResult();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DockWidgetVolumeTransferFunctionQObject *m_pDockWidgetVolumeTransferFunctionQObject;	/**< QObject instance for Qt's signal/slot mechanisms, always valid */
		TransferFunctionWidget					*m_pTransferFunctionWidget;						/**< Transfer function Qt widget instance, can be a null pointer */
		QLabel									*m_pTransferFunctionResultWidget;				/**< Transfer function result Qt widget instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui


#endif // __PLVOLUMEGUI_DOCKWIDGET_VOLUME_TRANSFERFUNCTION_H__
