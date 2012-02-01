/*********************************************************\
 *  File: TreeItemBase.h                                 *
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
		*  @param[in] cPosition
		*    the position at which the child should be added
		* 
		*  @remarks
		*    The item takes ownership of this item so it can't be an stack object
		*/
		void InsertChild(TreeItemBase* pChild, int cPosition);
		
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
