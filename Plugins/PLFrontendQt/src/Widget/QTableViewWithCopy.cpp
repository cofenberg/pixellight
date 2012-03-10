/*********************************************************\
 *  File: QTableViewWithCopy.cpp                         *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <algorithm>
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	PL_WARNING_DISABLE(4512)	// "'QForeachContainer<T>' : assignment operator could not be generated with"
	#include <QtGui/qevent.h>
	#include <QtGui/qclipboard.h>
	#include <QtGui/qapplication.h>
PL_WARNING_POP
#include "PLFrontendQt/Widget//QTableViewWithCopy.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
QTableViewWithCopy::QTableViewWithCopy()
{
}

/**
*  @brief
*    Destructor
*/
QTableViewWithCopy::~QTableViewWithCopy()
{
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void QTableViewWithCopy::keyPressEvent(QKeyEvent *pQKeyEvent)
{
	// Copy key?
	if (pQKeyEvent->matches(QKeySequence::Copy)) {
		// Get selected model index list
		QModelIndexList cQModelIndexList = selectionModel()->selectedIndexes();
		if (cQModelIndexList.size() > 0) {
			// Source: stackoverflow.com/questions/1230222/selected-rows-line-in-qtableview-copy-to-qclipboard

			// QModelIndex::operator < sorts first by row, then by column, this is what we need
			std::sort(cQModelIndexList.begin(), cQModelIndexList.end());

			// You need a pair of cQModelIndexList to find the row changes
			QModelIndex cQModelIndexPrevious = cQModelIndexList.first();
			cQModelIndexList.removeFirst();
			QString cQStringSelectedText;
			QModelIndex cQModelIndexCurrent;
			Q_FOREACH(cQModelIndexCurrent, cQModelIndexList) {
				QString cQStringText = model()->data(cQModelIndexPrevious).toString();

				// At this point `text` contains the text in one cell
				cQStringSelectedText.append(cQStringText);

				// If you are at the start of the row the row number of the previous index
				// isn't the same.  Text is followed by a row separator, which is a newline.
				if (cQModelIndexCurrent.row() != cQModelIndexPrevious.row()) {
					cQStringSelectedText.append(QLatin1Char('\n'));

				// Otherwise it's the same row, so append a column separator, which is a tab.
				} else {
					cQStringSelectedText.append(QLatin1Char('\t'));
				}
				cQModelIndexPrevious = cQModelIndexCurrent;
			}

			// Add last element
			cQStringSelectedText.append(model()->data(cQModelIndexCurrent).toString());
			cQStringSelectedText.append(QLatin1Char('\n'));
			qApp->clipboard()->setText(cQStringSelectedText);
		}
	} else {
		// Call the base implementation
		QTableView::keyPressEvent(pQKeyEvent);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
