/*********************************************************\
 *  File: QTableViewWithCopy.h                           *
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


#ifndef __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
#define __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	PL_WARNING_DISABLE(4251)	// "'QPainterPath::d_ptr' : class 'QScopedPointer<T,Cleanup>' needs to have dll-interface to be used by clients of class 'QPainterPath'"
	PL_WARNING_DISABLE(4800)	// "'const quint32' : forcing value to bool 'true' or 'false' (performance warning)"
	PL_WARNING_DISABLE(4512)	// "'QForeachContainer<T>' : assignment operator could not be generated with"
	PL_WARNING_DISABLE(4530)	// "C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <QtGui/qtableview.h>
PL_WARNING_POP
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    QTableView with support for copy
*/
class PLFRONTENDQT_API QTableViewWithCopy : public QTableView {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		QTableViewWithCopy();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~QTableViewWithCopy();


	//[-------------------------------------------------------]
	//[ Protected virtual QWidget functions                   ]
	//[-------------------------------------------------------]
	protected:
		virtual void keyPressEvent(QKeyEvent *) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QTABLEVIEWWTHCOPY_H__
