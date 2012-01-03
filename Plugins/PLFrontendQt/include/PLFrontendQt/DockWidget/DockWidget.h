/*********************************************************\
 *  File: DockWidget.h                                   *
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_H__
#define __PLFRONTENDQT_DOCKWIDGET_H__
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
class QWidget;
class QDockWidget;
QT_END_NAMESPACE
namespace PLFrontendQt {
	class DockWidgetManager;
	class InternalQDockWidget;
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
*    Abstract PixelLight RTTI class encapsulating a Qt dock widget
*
*  @remarks
*  @verbatim
*    Usage example:
*        "
*        const PLCore::Class *pClass = PLCore::ClassManager::GetInstance()->GetClass("PLFrontendQt::DockWidgetSceneGraph");
*        if (pClass)
*            pClass->Create(PLCore::Params<PLCore::Object*, QWidget*>(pQtMainWindow)));
*        "
*    The destruction of the created RTTI class instance is automatically handled by the Qt main window, see notes below.
*  @endverbatim
*
*    Each RTTI dock widget should have the following properties:
*    - "Title": Human readable title, may be shown e.g. within a menu and is used by default as the encapsulated Qt dock widget title
*
*  @note
*    - When a RTTI dock widget is instanced, it automatically creates the Qt dock widget it's encapsulating, access it by using "GetQDockWidget()"
*    - Derived RTTI dock widgets must implement a decent default behaviour to make it possible to use them out-of-the-box
*    - When a RTTI dock widget instance gets destroyed, it automatically destroys the Qt dock widget it's encapsulating
*    - When the encapsulated Qt dock widget gets destroyed, it automatically destroys the encapsulating RTTI dock widget
*    - This behaviour results in a Qt similar behaviour, when a RTTI dock widget is instanced it's parent takes over the control
*    - By convention, one should only derive new RTTI dock widgets from abstract RTTI dock widgets
*/
class DockWidget : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetManager;
	friend class InternalQDockWidget;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidget, "PLFrontendQt", PLCore::Object, "Abstract PixelLight RTTI class encapsulating a Qt dock widget")
		// Properties
		pl_properties
			pl_property("Title", "")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidget();

		/**
		*  @brief
		*    Returns the pointer to the dock widget manager this dock widget is registered to
		*
		*  @return
		*    The pointer to the dock widget manager this dock widget is registered to, can be a null pointer
		*/
		inline DockWidgetManager *GetDockWidgetManager() const;

		/**
		*  @brief
		*    Returns the encapsulated Qt dock widget
		*
		*  @return
		*    The encapsulated Qt dock widget, can be a null pointer
		*/
		inline QDockWidget *GetQDockWidget() const;

		/**
		*  @brief
		*    Returns whether or not the encapsulated Qt dock widget is currently visible
		*
		*  @return
		*    'true' if the encapsulated Qt dock widget is currently visible, else 'false'
		*
		*  @note
		*    - Comfort method, you can also use the "QDockWidget"-instance directly
		*/
		PLFRONTENDQT_API bool IsQDockWidgetVisible() const;


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
		PLFRONTENDQT_API DockWidget(QWidget *pQWidgetParent, DockWidgetManager *pDockWidgetManager = nullptr);

		//[-------------------------------------------------------]
		//[ Communication - Direct access functions               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Set dock widgets attribute value by using a given string value (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set dock widgets attribute value by using a given dynamic variable reference (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set dock widgets attribute value by using a given dynamic variable pointer (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set dock widgets attribute to it's default value (dock widget broadcast, excludes the emitting dock widget)
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
		*    Call dock widgets method with given dynamic parameters (dock widget broadcast, excludes the emitting dock widget)
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
		*    Call dock widgets method with given constant dynamic parameters (dock widget broadcast, excludes the emitting dock widget)
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
		*    Call dock widgets method with parameters given as string (dock widget broadcast, excludes the emitting dock widget)
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
		*    Call dock widgets method with parameters given as XML element (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set multiple dock widgets attribute values as a string at once (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set dock widgets attribute values from XML (dock widget broadcast, excludes the emitting dock widget)
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
		*    Set all dock widgets attributes to default (dock widget broadcast, excludes the emitting dock widget)
		*
		*  @remarks
		*    Similar to the "PLCore::Object::SetDefaultValues()"-method but iterates over all registered
		*    dock widgets and calls the "SetDefaultValues()"-method of each RTTI dock widget class instance.
		*/
		PLFRONTENDQT_API void SetDockWidgetsDefaultValues();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		InternalQDockWidget	*m_pQDockWidget;		/**< Qt dock widget, can be a null pointer */
		DockWidgetManager   *m_pDockWidgetManager;	/**< Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidget.inl"


#endif // __PLFRONTENDQT_DOCKWIDGET_H__
