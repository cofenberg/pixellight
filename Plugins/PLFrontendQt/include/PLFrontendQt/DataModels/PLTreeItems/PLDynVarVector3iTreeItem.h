/*********************************************************\
 *  File: PLDynVarVector3iTreeItem.h                     *
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


#ifndef __PLFRONTENDQT_PLDYNVARVECTOR3ITREEITEM_H__
#define __PLFRONTENDQT_PLDYNVARVECTOR3ITREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3i.h>
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
*    Dynamic variable tree item: Vector3i
*/
class PLFRONTENDQT_API PLDynVarVector3iTreeItem : public PLDynVarStringTreeItem {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLDynVarVector3iTreeItem(PLCore::DynVar *dynVar, QObject *parent = nullptr);
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
		PLMath::Vector3i m_Vector3i;


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		class Vector3iValueBaseTreeItem: public TreeItemBase {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3iValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector3iTreeItem *parentItem);
				virtual QVariant data(const int column, const int role) override;
				bool setData(const int column, const QVariant &value, const int role);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector3i& vector) = 0;
				virtual void SetVectorData(PLMath::Vector3i &vector, int newValue) = 0;


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				QString					 m_Name;
				PLDynVarVector3iTreeItem *m_parentItem;


		};

		class Vector3iXValueTreeItem : public Vector3iValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3iXValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				int GetVectorData(const PLMath::Vector3i &vector);
				void SetVectorData(PLMath::Vector3i &vector, int newValue);


		};

		class Vector3iYValueTreeItem : public Vector3iValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3iYValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector3i &vector) override;
				virtual void SetVectorData(PLMath::Vector3i &vector, int newValue) override;


		};

		class Vector3iZValueTreeItem : public Vector3iValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3iZValueTreeItem(QObject *parent, PLDynVarVector3iTreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3iValueBaseTreeItem functions ]
			//[-------------------------------------------------------]
			protected:
				virtual int GetVectorData(const PLMath::Vector3i &vector) override;
				virtual void SetVectorData(PLMath::Vector3i &vector, int newValue) override;


		};


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_PLDYNVARVECTOR3ITREEITEM_H__
