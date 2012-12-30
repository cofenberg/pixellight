/*********************************************************\
 *  File: QTableViewWithCopy.cpp                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
