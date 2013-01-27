/*********************************************************\
 *  File: GuiPickingQObject.h                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLVIEWERQT_PICKING_QOBJECT_H__
#define __PLVIEWERQT_PICKING_QOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/qobject.h>
#include <PLMath/Vector4.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SNMTransformGizmo;
}
class GuiPicking;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI picking Qt dock widget class, QObject instance for Qt's signal/slot mechanisms
*
*  @remarks
*    Sadly, it appears that Qt's signal/slot mechanisms can't be used without QObject/Q_OBJECT. But we don't want to do a multiple inheritance
*    like "class GuiPicking : public QObject, public PLFrontendQt::DockWidget" either because this can cause serious casting issues.
*    So, we need to add another class just to be able to use Qt's signal/slot mechanisms. We can't use an embedded class for this either because
*    Qt's MOC doesn't like this. :/
*/
class GuiPickingQObject : public QObject {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GuiPicking;


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGuiPicking
		*    GUI picking owner instance
		*/
		GuiPickingQObject(GuiPicking &cGuiPicking);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GuiPickingQObject();

		/**
		*  @brief
		*    Starts the clone mode when all preconditions for it are satisfied and we're not already in clone mode
		*/
		void StartCloneMode();

		/**
		*  @brief
		*    Ends the clone mode and starts the clone action, but only if we're in fact in clone mode
		*/
		void EndCloneMode();

		/**
		*  @brief
		*    Asks the user for the number of desired clones (with a decent limited number)
		*
		*  @return
		*    The number of desired clones
		*/
		PLCore::uint32 GetNumOfClones() const;


	//[-------------------------------------------------------]
	//[ Public virtual QObject methods                        ]
	//[-------------------------------------------------------]
	public:
		virtual bool eventFilter(QObject *pQObject, QEvent *pQEvent) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		GuiPicking				   *m_pGuiPicking;		/**< GUI picking owner instance, always valid */
		PLScene::SNMTransformGizmo *m_pTransformGizmo;	/**< Currently used transform gizmo, can be a null pointer */
		bool						m_bCloneMode;		/**< Are we currently in clone mode? */
		PLMath::Vector4				m_vOriginalValue;	/**< Original value when the clone mode was started */


};


#endif // __PLVIEWERQT_PICKING_QOBJECT_H__
