/*********************************************************\
 *  File: DockWidgetManager.h                            *
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


#ifndef __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
#define __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QMainWindow;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class DockWidget;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight RTTI dock widget manager
*
*  @note
*    - Loosely couples together RTTI dock widgets, the RTTI dock widgets can still be destroyed individually (e.g. when the Qt dock widget is destroyed)
*/
class DockWidgetManager : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidget;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetManager, "PLFrontendQt", PLCore::Object, "PixelLight RTTI dock widget manager")
		#ifdef PLFRONTENDQT_EXPORTS	// The following is only required when compiling PLFrontendQt
			// Methods
			pl_method_2(SetDockWidgetsAttribute,		pl_ret_type(void),	const PLCore::String&,	const PLCore::String&,	"Set dock widgets attribute value (dock widget broadcast). Attribute name as first parameter, attribute value as second parameter.",															"")
			pl_method_1(SetDockWidgetsAttributeDefault,	pl_ret_type(void),	const PLCore::String&,							"Set dock widgets attribute to it's default value (dock widget broadcast). Attribute name as first parameter.",																					"")
			pl_method_2(CallDockWidgetsMethod,			pl_ret_type(void),	const PLCore::String&,	const PLCore::String&,	"Call dock widgets method (dock widget broadcast). Method name as first parameter, parameters as string (e.g. \"Param0='x' Param1='y'\") as second parameter.",									"")
			pl_method_1(SetDockWidgetsValues,			pl_ret_type(void),	const PLCore::String&,							"Set multiple dock widgets attribute values as a string at once (dock widget broadcast). String containing attributes and values as first parameter (e.g. \"Name='Bob' Position='1 2 3'\").",	"")
			pl_method_0(SetDockWidgetsDefaultValues,	pl_ret_type(void),													"Set all dock widgets attributes to default (dock widget broadcast).",																															"")
		#endif
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
		*    Pointer to Qt main window, can be a null pointer
		*
		*  @note
		*    - You're responsible for destroying this PixelLight RTTI dock widget manager instance
		*/
		PLFRONTENDQT_API DockWidgetManager(QMainWindow *pQMainWindow);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetManager();

		//[-------------------------------------------------------]
		//[ Management                                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Shows a dock widget
		*
		*  @param[in] sClassName
		*    Class name of the PixelLight RTTI class encapsulating a Qt dock widget (must be derived from "PLFrontendQt::DockWidget")
		*
		*  @return
		*    The shown dock widget, can be a null pointer (you don't need to care about destroying the dock widget instance)
		*
		*  @note
		*    - If there's already a shown dock widget of the given class name, it will get the focus
		*    - If there's already a dock widget of the given class name, it will be shown
		*    - If there's currently no dock widget of the given class name, it will be instanced and shown
		*/
		PLFRONTENDQT_API DockWidget *ShowDockWidget(const PLCore::String &sClassName);

		/**
		*  @brief
		*    Returns the first dock widget instance which is an instance of the given class
		*
		*  @param[in] sClassName
		*    Class name of the PixelLight RTTI class encapsulating a Qt dock widget (must be derived from "PLFrontendQt::DockWidget")
		*
		*  @return
		*    The first dock widget instance which is an instance of the given class, can be a null pointer
		*/
		PLFRONTENDQT_API DockWidget *GetFirstDockWidget(const PLCore::String &sClassName);

		/**
		*  @brief
		*    Hides all registered dock widgets
		*/
		PLFRONTENDQT_API void HideDockWidgets();

		/**
		*  @brief
		*    Destroys all registered dock widgets
		*/
		PLFRONTENDQT_API void DestroyDockWidgets();

		//[-------------------------------------------------------]
		//[ Communication - Direct access functions               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Set dock widgets attribute value by using a given string value (dock widget broadcast)
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] sValue
		*    Attribute value as string
		*
		*  @remarks
		*    Similar to the "PLCore::Object::SetAttribute()"-method but iterates over all registered
		*    dock widgets and calls the "SetAttribute()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void SetDockWidgetsAttribute(const PLCore::String &sName, const PLCore::String &sValue);

		/**
		*  @brief
		*    Set dock widgets attribute value by using a given dynamic variable reference (dock widget broadcast)
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] cVar
		*    Attribute value as dynamic variable reference
		*
		*  @see
		*    - "void SetDockWidgetsAttribute(const PLCore::String &sName, const PLCore::String &sValue)"
		*/
		PLFRONTENDQT_API void SetDockWidgetsAttribute(const PLCore::String &sName, const PLCore::DynVar &cVar);

		/**
		*  @brief
		*    Set dock widgets attribute value by using a given dynamic variable pointer (dock widget broadcast)
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] pVar
		*    Attribute value as dynamic variable pointer, in case of a null pointer, nothing happens at all
		*
		*  @see
		*    - "void SetDockWidgetsAttribute(const PLCore::String &sName, const PLCore::String &sValue)"
		*/
		PLFRONTENDQT_API void SetDockWidgetsAttribute(const PLCore::String &sName, const PLCore::DynVar *pVar);

		/**
		*  @brief
		*    Set dock widgets attribute to it's default value (dock widget broadcast)
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @remarks
		*    Similar to the "PLCore::Object::SetAttributeDefault()"-method but iterates over all registered
		*    dock widgets and calls the "SetAttributeDefault()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void SetDockWidgetsAttributeDefault(const PLCore::String &sName);

		/**
		*  @brief
		*    Call dock widgets method with given dynamic parameters (dock widget broadcast)
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Dynamic parameters
		*
		*  @remarks
		*    Similar to the "PLCore::Object::CallMethod()"-method but iterates over all registered
		*    dock widgets and calls the "CallMethod()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void CallDockWidgetsMethod(const PLCore::String &sName, PLCore::DynParams &cParams);

		/**
		*  @brief
		*    Call dock widgets method with given constant dynamic parameters (dock widget broadcast)
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Constant dynamic parameters
		*
		*  @see
		*    - "void CallDockWidgetsMethod(const PLCore::String &sName, PLCore::DynParams &cParams)"
		*/
		PLFRONTENDQT_API void CallDockWidgetsMethod(const PLCore::String &sName, const PLCore::DynParams &cParams);

		/**
		*  @brief
		*    Call dock widgets method with parameters given as string (dock widget broadcast)
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] sParams
		*    Parameters as string
		*
		*  @see
		*    - "void CallDockWidgetsMethod(const PLCore::String &sName, PLCore::DynParams &cParams)"
		*/
		PLFRONTENDQT_API void CallDockWidgetsMethod(const PLCore::String &sName, const PLCore::String &sParams);

		/**
		*  @brief
		*    Call dock widgets method with parameters given as XML element (dock widget broadcast)
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cElement
		*    Parameters as XML element
		*
		*  @see
		*    - "void CallDockWidgetsMethod(const PLCore::String &sName, PLCore::DynParams &cParams)"
		*/
		PLFRONTENDQT_API void CallDockWidgetsMethod(const PLCore::String &sName, const PLCore::XmlElement &cElement);

		//[-------------------------------------------------------]
		//[ Communication - Object state functions                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Set multiple dock widgets attribute values as a string at once (dock widget broadcast)
		*
		*  @param[in] sString
		*    String containing attributes and values (e.g. \"Name='Bob' Position='1 2 3'\")
		*
		*  @remarks
		*    Similar to the "PLCore::Object::SetValues()"-method but iterates over all registered
		*    dock widgets and calls the "SetValues()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void SetDockWidgetsValues(const PLCore::String &sVars);

		/**
		*  @brief
		*    Set dock widgets attribute values from XML (dock widget broadcast)
		*
		*  @param[out] cElement
		*    XML element
		*
		*  @see
		*    - "void SetDockWidgetsValues(const PLCore::String &sVars)"
		*/
		PLFRONTENDQT_API void SetDockWidgetsValuesXml(const PLCore::XmlElement &cElement);

		/**
		*  @brief
		*    Set all dock widgets attributes to default (dock widget broadcast)
		*
		*  @remarks
		*    Similar to the "PLCore::Object::SetDefaultValues()"-method but iterates over all registered
		*    dock widgets and calls the "SetDefaultValues()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void SetDockWidgetsDefaultValues();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Registers the given dock widget within this dock widget manager
		*
		*  @param[in] cDockWidget
		*    Dock widget to register
		*/
		inline void RegisterDockWidget(DockWidget &cDockWidget);

		/**
		*  @brief
		*    Unregisters the given dock widget within this dock widget manager
		*
		*  @param[in] cDockWidget
		*    Dock widget to unregister
		*/
		inline void UnregisterDockWidget(DockWidget &cDockWidget);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QMainWindow				   *m_pQMainWindow;		/**< Pointer to Qt main window, can be a null pointer */
		PLCore::Array<DockWidget*>  m_lstDockWidgets;	/**< List of registered dock widgets */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetManager.inl"


#endif // __PLFRONTENDQT_DOCKWIDGETMANAGER_H__
