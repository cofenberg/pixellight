/*********************************************************\
 *  File: ClassInfoModel.h                               *
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


#ifndef __PLFRONTENDQT_CLASSINFOMODEL_H__
#define __PLFRONTENDQT_CLASSINFOMODEL_H__


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/List.h>
#include "PLFrontendQt/DataModels/TreeModelBase.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Class;
	class MemberDesc;
}
namespace PLFrontendQt {
	namespace DataModels {
		namespace RTTIInfoModels {
			class ClassInfoCategoryTreeItem;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {
namespace DataModels {
namespace RTTIInfoModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    RTTI class info data model
*/
class PLFRONTENDQT_API ClassInfoModel : public TreeModelBase {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		enum ClassInfoItemRoles {
			NameRole = Qt::UserRole+1,
			NamespaceRole,
			DescriptionRole,
			BaseClassRole
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit ClassInfoModel(QObject *parent = nullptr);
		virtual ~ClassInfoModel();
		void SetClassItem(const PLCore::Class &cClass);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void DeleteChilds(ClassInfoCategoryTreeItem *pCategoryItem);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ClassInfoCategoryTreeItem *m_pCommonCategory;
		ClassInfoCategoryTreeItem *m_pAttributeCategory;
		ClassInfoCategoryTreeItem *m_pSlotsCategory;
		ClassInfoCategoryTreeItem *m_pSignalsCategory;
		ClassInfoCategoryTreeItem *m_pPropertiesCategory;
		ClassInfoCategoryTreeItem *m_pConstructorsCategory;
		ClassInfoCategoryTreeItem *m_pMethodsCategory;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt


#endif // __PLFRONTENDQT_CLASSINFOMODEL_H__
