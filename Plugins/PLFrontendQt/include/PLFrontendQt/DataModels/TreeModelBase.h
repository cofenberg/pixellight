/*********************************************************\
 *  File: TreeModelBase.h                                *
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


#ifndef __PLFRONTENDQT_TREEMODELBASE_H__
#define __PLFRONTENDQT_TREEMODELBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QAbstractItemModel>
#include <PLCore/PLCore.h>	// Only needed for compilers which doesn't have nullptr as a builtin type
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TreeItemBase;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Base class for a tree model
*
*  @note
*    - This class implements an model which is static regarding its elements -> no user interaction to change the model structure
*/
class PLFRONTENDQT_API TreeModelBase : public QAbstractItemModel {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor for the TreeModel
		*
		*  @param[in] rootItem (must be valid)
		*    root Item for the tree. This item is used for getting the data for the header row.
		*    Note: The model takes ownership of the root item
		*    -> if the model gets destroyed the root item will also be destroyed (if not someone else has taken the ownership after the model was constructed)
		*  @param[in] parent
		*    Optional parent item to which the model instance belongs
		*   (this instance gets automatically deleted if parent gets destroyed)
		*/
		explicit TreeModelBase(TreeItemBase *rootItem, QObject *parent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TreeModelBase();

		/**
		*  @brief
		*    Returns the index of the item in the model specified by the given row, column and parent index
		*/
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

		/**
		*  @brief
		*    Returns the parent of the model item with the given index. If the item has no parent, an invalid QModelIndex is returned.
		*/
		QModelIndex parent(const QModelIndex &index) const;

		/**
		*  @brief
		*    Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
		*
		*  @note
		*    - Only the first column can have children in this model so if parent has column >0 then 0 is returned
		*/
		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/**
		*  @brief
		*    Returns the number of columns for the children of the given parent.
		*
		*  @note
		*    - In most subclasses, the number of columns is independent of the parent
		*/
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		/**
		*  @brief
		*    Returns the data stored under the given role for the item referred to by the index.
		*
		*  @note
		*    - If you do not have a value to return, return an invalid QVariant instead of returning 0
		*
		*  @see
		*    - Qt::ItemDataRole for available roles
		*/
		QVariant data(const QModelIndex &index, int role) const;

		/**
		*  @brief
		*    Returns the data for the given role and section in the header with the specified orientation.
		*    For horizontal headers, the section number corresponds to the column number. Similarly, for vertical headers, the section number corresponds to the row number.
		*/
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		/**
		*  @brief
		*    Returns the item flags for the given index
		*/
		virtual Qt::ItemFlags flags(const QModelIndex &index) const;

		/**
		*  @brief
		*    Sets the role data for the item at index to value.
		*
		*  @returns
		*    true if successful; otherwise false
		*
		*  @note
		*    - If setting the data was successful the signal dataChanged gets emitted to notify the views about the change
		*/
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		/**
		*  @brief
		*    Returns the model index of the given item
		*
		*  @returns
		*    the model index of the given item or an invalid model index when the item doesn't belong to this model instance
		*/
		QModelIndex GetIndexForTreeItem(TreeItemBase *item) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		TreeItemBase *GetTreeItemFromIndex(const QModelIndex &parent) const;
		TreeItemBase *GetRootItem() { return m_rootItem; }


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		TreeItemBase *m_rootItem;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_TREEMODELBASE_H__
