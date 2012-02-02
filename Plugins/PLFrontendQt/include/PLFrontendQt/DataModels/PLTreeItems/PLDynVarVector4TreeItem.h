/*********************************************************\
 *  File: PLDynVarVector4TreeItem.h                      *
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


#ifndef __PLFRONTENDQT_PLDYNVARVECTOR4TREEITEM_H__
#define __PLFRONTENDQT_PLDYNVARVECTOR4TREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector4.h>
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
*    Dynamic variable tree item: Vector4
*/
class PLFRONTENDQT_API PLDynVarVector4TreeItem : public PLDynVarStringTreeItem {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLDynVarVector4TreeItem(PLCore::DynVar *dynVar, TreeItemBase *parent = nullptr);
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
		PLMath::Vector4 m_Vector4;


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		class Vector4ValueBaseTreeItem: public TreeItemBase {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector4ValueBaseTreeItem(const QString &name, TreeItemBase *parent, PLDynVarVector4TreeItem *parentItem);
				virtual QVariant data(const int column, const int role) override;
				bool setData(const int column, const QVariant &value, const int role);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector4ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector4 &vector) = 0;
				virtual void SetVectorData(PLMath::Vector4 &vector, float newValue) = 0;


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				QString					 m_Name;
				PLDynVarVector4TreeItem *m_parentItem;


		};

		class Vector4XValueTreeItem : public Vector4ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector4XValueTreeItem(TreeItemBase *parent, PLDynVarVector4TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector4ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				float GetVectorData(const PLMath::Vector4 &vector);
				void SetVectorData(PLMath::Vector4 &vector, float newValue);


		};

		class Vector4YValueTreeItem : public Vector4ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector4YValueTreeItem(TreeItemBase *parent, PLDynVarVector4TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector4ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector4 &vector) override;
				virtual void SetVectorData(PLMath::Vector4 &vector, float newValue) override;


		};

		class Vector4ZValueTreeItem : public Vector4ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector4ZValueTreeItem(TreeItemBase *parent, PLDynVarVector4TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector4ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector4 &vector) override;
				virtual void SetVectorData(PLMath::Vector4 &vector, float newValue) override;


		};

		class Vector4WValueTreeItem : public Vector4ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector4WValueTreeItem(TreeItemBase *parent, PLDynVarVector4TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector4ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector4 &vector) override;
				virtual void SetVectorData(PLMath::Vector4 &vector, float newValue) override;


		};


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLDYNVARVECTOR4TREEITEM_H__
