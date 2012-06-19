/*********************************************************\
 *  File: DockWidgetVolumeInformation.h                  *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUMEGUI_DOCKWIDGET_VOLUME_INFORMATION_H__
#define __PLVOLUMEGUI_DOCKWIDGET_VOLUME_INFORMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolumeGui/DockWidgetVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QTableView;
	class QMainWindow;
	class QStandardItemModel;
QT_END_NAMESPACE
namespace PLGraphics {
	class ImageBuffer;
}
namespace PLVolume {
	class SNVolume;
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
*    Volume information Qt dock widget class
*/
class DockWidgetVolumeInformation : public DockWidgetVolume {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMEGUI_RTTI_EXPORT, DockWidgetVolumeInformation, "PLVolumeGui", PLVolumeGui::DockWidgetVolume, "Volume information Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Volume Information")
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
		DockWidgetVolumeInformation(QMainWindow *pQMainWindow, PLFrontendQt::DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~DockWidgetVolumeInformation();


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
		*    Updates the volume information
		*
		*  @param[in] pObject
		*    Selected object can be a null pointer
		*/
		void UpdateObject(PLCore::Object *pObject);

		/**
		*  @brief
		*    Fills the given Qt standard item model
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cSNVolume
		*    Currently selected volume scene node
		*/
		void FillStandardItemModel(QStandardItemModel &cQStandardItemModel, const PLVolume::SNVolume &cSNVolume) const;

		/**
		*  @brief
		*    Fills the given Qt standard item model, image buffer part
		*
		*  @param[in] cQStandardItemModel
		*    Qt standard item model to fill
		*  @param[in] cImageBuffer
		*    Currently selected image buffer
		*/
		void FillStandardItemModelImageBuffer(QStandardItemModel &cQStandardItemModel, PLGraphics::ImageBuffer &cImageBuffer) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QTableView *m_pQTableView;	/**< Qt table view instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui


#endif // __PLVOLUMEGUI_DOCKWIDGET_VOLUME_INFORMATION_H__
