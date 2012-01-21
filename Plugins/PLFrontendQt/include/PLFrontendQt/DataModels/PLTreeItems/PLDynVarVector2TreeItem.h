/*********************************************************\
 *  File: PLDynVarVector2TreeItem.h                      *
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


#ifndef __PLFRONTENDQT_PLDYNVARVECTOR2TREEITEM_H__
#define __PLFRONTENDQT_PLDYNVARVECTOR2TREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
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
*    Dynamic variable tree item: Vector2
*/
class PLFRONTENDQT_API PLDynVarVector2TreeItem : public PLDynVarStringTreeItem {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLDynVarVector2TreeItem(PLCore::DynVar *dynVar, QObject *parent = nullptr);
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
		PLMath::Vector2 m_Vector2;


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		class Vector2ValueBaseTreeItem: public TreeItemBase {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2ValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector2TreeItem *parentItem);
				virtual QVariant data(const int column, const int role) override;
				bool setData(const int column, const QVariant &value, const int role);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector2 &vector) = 0;
				virtual void SetVectorData(PLMath::Vector2 &vector, float newValue) = 0;


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				QString					 m_Name;
				PLDynVarVector2TreeItem *m_parentItem;


		};

		class Vector2XValueTreeItem : public Vector2ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2XValueTreeItem(QObject *parent, PLDynVarVector2TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector2 &vector) override;
				virtual void SetVectorData(PLMath::Vector2 &vector, float newValue) override;


		};

		class Vector2YValueTreeItem : public Vector2ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector2YValueTreeItem(QObject *parent, PLDynVarVector2TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector2ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector2 &vector) override;
				virtual void SetVectorData(PLMath::Vector2 &vector, float newValue) override;


		};
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLDYNVARVECTOR2TREEITEM_H__
