/*********************************************************\
 *  File: TreeItemBase.h                                 *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLFRONTENDQT_TREEITEMBASE_H__
#define __PLFRONTENDQT_TREEITEMBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QModelIndex>
#include <PLCore/PLCore.h>	// Only needed for compilers which doesn't have nullptr as a builtin type
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {

class TreeModelBase;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tree item base
*/
class PLFRONTENDQT_API TreeItemBase {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit TreeItemBase(TreeItemBase *parent = nullptr);
		TreeItemBase(int columnCount, TreeItemBase* parent);
		virtual ~TreeItemBase();

		int columnCount() const;
		int row() const;
		virtual QVariant data(const int column, const int role) = 0;
		virtual bool setData(const int column, const QVariant &value, const int role) { return false; };
		Qt::ItemFlags flags( const int column) const;
		
		/**
		*  @brief
		*    Adds an child to this tree node
		* 
		*  @param[in] pChild
		*    the child object to be added
		* 
		*  @remarks
		*    The item takes ownership of this item so it can't be an stack object
		*/
		void AddChild(TreeItemBase* pChild);
		
		/**
		*  @brief
		*    Insert an child to this tree node
		* 
		*  @param[in] pChild
		*    the child object to be added
		* 
		*  @param[in] nPosition
		*    the position at which the child should be added
		* 
		*  @remarks
		*    The item takes ownership of this item so it can't be an stack object
		*/
		void InsertChild(TreeItemBase* pChild, int nPosition);
		
		/**
		*  @brief
		*    Remove an child from this tree node
		* 
		*  @param[in] pChild
		*    the child object to be removed
		*
		*  @param[in] bDestroy
		*    should the child be destroyed?
		*
		*  @remarks
		*    the child item gets destroyed
		*/
		void RemoveChild(TreeItemBase* pChild, bool bDestroy = true);
		
		/**
		*  @brief
		*    move an child within the child list
		*
		*  @param[in] nFromIndex
		*    The index of the child which should be moved
		*
		*  @param[in] nToIndex
		*    The index to child the item should be moved
		*
		*  @note
		*    - This methods assumes, that both index values are within 0 and child count -1
		*/
		void MoveChild(int nFromIndex, int nToIndex);
		
		/**
		*  @brief
		*    Returns the index of the child
		*
		*  @return
		*    the child index if the given item or -1 if not found
		*/
		int GetChildIndex(TreeItemBase* pChild) const;
		
		/**
		*  @brief
		*   Returns a list of child objects.
		*
		*  @return
		*    a const reference to the internal child list
		*/
		const QList<TreeItemBase*>& children() const;
		
		/**
		*  @brief
		*   Removes all child items from the internal list
		*
		*  @remarks
		*    The child items gets destroyed, after this all hold references/pointer to such a child is invalid
		*/
		void clearChildren();
		
		/**
		*  @brief
		*   Returns the parent item of this item
		*
		*  @return
		*    the parent item, can be a null pointer when this item has no parent
		*/
		TreeItemBase* parent() const;
		
		/**
		*  @brief
		*   Returns the position of this item
		*
		*  @return
		*    the position of this item as a pair (row, column)
		*/
		QPair<int, int> position();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		void SetFlags(const int column, const Qt::ItemFlags flags);
		void RemoveFlags(const int column, const Qt::ItemFlags flags);
		void SetColumnCount(const int columnCount);
		void ChangeParent(TreeItemBase* pNewParent, bool bNoAdd = false);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		QMap<int, Qt::ItemFlags>	 m_flagsMap;
		int							 m_columnCount;
		TreeItemBase				*m_pParent;
		QList<TreeItemBase*>		 m_cChildren;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_TREEITEMBASE_H__
