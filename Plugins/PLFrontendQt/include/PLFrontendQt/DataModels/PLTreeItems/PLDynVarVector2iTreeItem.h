/*********************************************************\
 *  File: PLDynVarVector2iTreeItem.h                     *
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


#ifndef __PLFRONTENDQT_PLDYNVARVECTOR2ITREEITEM_H__
#define __PLFRONTENDQT_PLDYNVARVECTOR2ITREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLFrontendQt/DataModels//PLTreeItems/PLDynVarStringTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Dynamic variable tree item: Vector2i
*/
class PLFRONTENDQT_API PLDynVarVector2iTreeItem : public PLDynVarStringTreeItem {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLDynVarVector2iTreeItem(PLCore::DynVar *dynVar, TreeItemBase *parent = nullptr);
		virtual QVariant data(const int column, const int role) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void UpdateData();
		void UpdateDataToVar();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector2i m_Vector2i;


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		class Vector2iValueBaseTreeItem: public TreeItemBase {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2iValueBaseTreeItem(const QString &name, TreeItemBase *parent, PLDynVarVector2iTreeItem *parentItem);
				virtual QVariant data(const int column, const int role) override;
				bool setData(const int column, const QVariant &value, const int role);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector2i &vector) = 0;
				virtual void SetVectorData(PLMath::Vector2i &vector, int newValue) = 0;


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				QString					 m_Name;
				PLDynVarVector2iTreeItem *m_parentItem;


		};

		class Vector2iXValueTreeItem : public Vector2iValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2iXValueTreeItem(TreeItemBase *parent, PLDynVarVector2iTreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector2i &vector) override;
				virtual void SetVectorData(PLMath::Vector2i &vector, int newValue) override;


		};

		class Vector2iYValueTreeItem : public Vector2iValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2iYValueTreeItem(TreeItemBase *parent, PLDynVarVector2iTreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector2i &vector) override;
				virtual void SetVectorData(PLMath::Vector2i &vector, int newValue) override;


		};
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLDYNVARVECTOR2ITREEITEM_H__
