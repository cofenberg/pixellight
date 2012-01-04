/*********************************************************\
 *  File: ClassInfoModel.cpp                             *
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
#include <QtCore//QStringList>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Var/VarDesc.h>
#include <PLCore/Base/Event/EventDesc.h>
#include <PLCore/Base/Event/EventHandlerDesc.h>
#include <PLCore/Base/Func/FuncDesc.h>
#include <PLCore/Base/Func/ConstructorDesc.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include <PLFrontendQt/DataModels/TreeItemBase.h>
#include "PLFrontendQt/DataModels/HeaderTreeItem.h"
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassInfoModel.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontendQt {
namespace DataModels {
namespace RTTIInfoModels {


//[-------------------------------------------------------]
//[ Global definitions                                    ]
//[-------------------------------------------------------]
enum ClassInfoItemRoles {
	NameRole = Qt::UserRole+1,
	NamespaceRole,
	DescriptionRole,
	FullNameRole,
	BaseClassRole
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class ClassInfoStringTreeItem : public TreeItemBase {


	public:
		ClassInfoStringTreeItem(const QString &displayText, QObject *parent = nullptr) : TreeItemBase(1, parent), m_displayText(displayText)
		{
		}

		virtual QVariant data(const int column, const int role)
		{
			if (role == Qt::DisplayRole) {
				if (column == 0)
					return m_displayText;
			}

			return QVariant();
		}


	private:
		QString m_displayText;


};

class ClassListItem : public TreeItemBase {


	public:
		explicit ClassListItem(const Class *pClass, ClassInfoItemRoles displayRole = ClassInfoItemRoles::NameRole, QObject *parent = nullptr) : TreeItemBase(1, parent) , m_pClass(pClass), m_cDisplayRole(displayRole)
		{
			QString tooltipTemplate = tr("<table>"
									"<tr><td bgcolor=#00ff00 colspan=\"2\">Class Info</td></tr>"
									"<tr><td>Name:</td><td><ClassName></td></tr>"
									"<tr><td>Fullname:</td><td><FullClassName></td></tr>"
									"<tr><td>Description:</td><td><ClassDesc></td></tr>"
									"</table>");

			m_sTooltip = tooltipTemplate.replace("<ClassName>", QtStringAdapter::PLToQt(pClass->GetName())).replace("<ClassDesc>", QtStringAdapter::PLToQt(pClass->GetDescription())).replace("<FullClassName>", QtStringAdapter::PLToQt(pClass->GetClassName()));
		}

		virtual QVariant data(const int column, const int role)
		{
			if (column != 0 || !m_pClass)
				return QVariant();

			if (role == Qt::ToolTipRole)
				return m_sTooltip;
			ClassInfoItemRoles itemRole = static_cast<ClassInfoItemRoles>(role);
			if (role == Qt::DisplayRole)
				itemRole = m_cDisplayRole;
			else if (role == Qt::ToolTipRole)
				itemRole = ClassInfoItemRoles::DescriptionRole;

			return GetDataForClassListItemRole(itemRole);
		}

		const Class *GetObject()
		{
			return m_pClass;
		}


	private:
		QVariant GetDataForClassListItemRole(ClassInfoItemRoles role)
		{
			switch (role) {
				case ClassInfoItemRoles::FullNameRole:
					return "FullName: " + QtStringAdapter::PLToQt(m_pClass->GetClassName());

				case ClassInfoItemRoles::NameRole:
					return "Name: " + QtStringAdapter::PLToQt(m_pClass->GetName());

				case ClassInfoItemRoles::NamespaceRole:
					return "Namespace: " + QtStringAdapter::PLToQt(m_pClass->GetNamespace());

				case ClassInfoItemRoles::DescriptionRole:
					return "Description: " + QtStringAdapter::PLToQt(m_pClass->GetDescription());

				default:
					return QVariant();
			}
		}


	private:
		const Class *m_pClass;
		const ClassInfoItemRoles m_cDisplayRole;
		QString m_sTooltip;


};

class ClassInfoCategoryTreeItem : public TreeItemBase {


	public:
		ClassInfoCategoryTreeItem(const QString name, QObject *parent = nullptr) : TreeItemBase(1, parent), m_name(name)
		{
		}

		virtual QVariant data(const int column, const int role)
		{
			if (role == Qt::DisplayRole) {
				if (column == 0)
					return m_name;
			}

			return QVariant();
		}


	private:
		QString m_name;


};

class ClassInfoAttributeTreeItem : public TreeItemBase {


	public:
		ClassInfoAttributeTreeItem(const VarDesc &cVarDesc, QObject *parent = nullptr) : TreeItemBase(3, parent),
			m_sName(QtStringAdapter::PLToQt(cVarDesc.GetName())),
			m_sTypeName(QtStringAdapter::PLToQt(cVarDesc.GetTypeName())),
			m_sDescription(QtStringAdapter::PLToQt(cVarDesc.GetDescription()))
		{
		}

		virtual QVariant data(const int column, const int role)
		{
			if (role == Qt::DisplayRole || role == Qt::ToolTipRole) {
				if (column == 0)
					return m_sName;
				else if (column == 1)
					return m_sTypeName;
				else if (column == 2)
					return m_sDescription;
			}

			return QVariant();
		}


	private:
		QString m_sName;
		QString m_sTypeName;
		QString m_sDescription;


};

class ClassInfoMemberDescTreeItem : public TreeItemBase {


	public:
		ClassInfoMemberDescTreeItem(const MemberDesc &cMemberDesc, QObject *parent = nullptr) : TreeItemBase(2, parent),
			m_sName(QtStringAdapter::PLToQt(cMemberDesc.GetName())),
			m_sDescription(QtStringAdapter::PLToQt(cMemberDesc.GetDescription())),
			m_sMemberType(GetMemberTypeString(cMemberDesc.GetMemberType()))
		{
		}

		virtual QVariant data(const int column, const int role)
		{
			if (role == Qt::DisplayRole || role == Qt::ToolTipRole) {
				if (column == 0)
					return m_sName;
				else if (column == 1)
					return m_sDescription;
			}
			
			return QVariant();
		}


	private:
		QString GetMemberTypeString(EMemberType memberType)
		{
			switch (memberType) {
				case EMemberType::MemberAttribute:
					return tr("Attribute");

				case EMemberType::MemberConstructor:
					return tr("Constructor");

				case EMemberType::MemberEvent:
					return tr("Signal");

				case EMemberType::MemberEventHandler:
					return tr("Slot");

				case EMemberType::MemberMethod:
					return tr("Method");

				default:
					return QString();
			}
		}


	private:
		QString m_sName;
		QString m_sDescription;
		QString m_sMemberType;


};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassInfoModel::ClassInfoModel(QObject *parent): TreeModelBase(new HeaderTreeItem(parent), parent),
	m_pCommonCategory(nullptr),
	m_pAttributeCategory(nullptr),
	m_pSlotsCategory(nullptr),
	m_pSignalsCategory(nullptr),
	m_pPropertiesCategory(nullptr),
	m_pConstructorsCategory(nullptr),
	m_pMethodsCategory(nullptr)
{
	QStringList headerItems;
	headerItems << "Category";

	HeaderTreeItem *header = static_cast<HeaderTreeItem*>(GetRootItem());
	header->setHeaderItems(headerItems);

	m_pCommonCategory = new ClassInfoCategoryTreeItem("Common", GetRootItem());
	m_pAttributeCategory = new ClassInfoCategoryTreeItem("Attributes", GetRootItem());
	m_pSlotsCategory = new ClassInfoCategoryTreeItem("Slots", GetRootItem());
	m_pSignalsCategory = new ClassInfoCategoryTreeItem("Signals", GetRootItem());
	m_pPropertiesCategory = new ClassInfoCategoryTreeItem("Properties", GetRootItem());
	m_pConstructorsCategory = new ClassInfoCategoryTreeItem("Constructors", GetRootItem());
	m_pMethodsCategory = new ClassInfoCategoryTreeItem("Methods", GetRootItem());
}

ClassInfoModel::~ClassInfoModel()
{
}

void ClassInfoModel::SetClassItem(const Class &cClass)
{
	const Class *pClass = &cClass;

	beginResetModel();

	DeleteChilds(m_pCommonCategory);
	DeleteChilds(m_pAttributeCategory);
	DeleteChilds(m_pSlotsCategory);
	DeleteChilds(m_pSignalsCategory);
	DeleteChilds(m_pPropertiesCategory);
	DeleteChilds(m_pConstructorsCategory);
	DeleteChilds(m_pMethodsCategory);

	// Add common information items
	new ClassListItem(pClass, ClassInfoItemRoles::NameRole, m_pCommonCategory);
	new ClassListItem(pClass, ClassInfoItemRoles::DescriptionRole, m_pCommonCategory);

	// Add attributes
	const List<VarDesc*> &attr = cClass.GetAttributes();
	for (uint32 i=0; i<attr.GetNumOfElements(); ++i) {
		VarDesc *pVarDesc = attr[i];
		new ClassInfoAttributeTreeItem(*pVarDesc, m_pAttributeCategory);
	}

	// Add slots
	const List<EventHandlerDesc*> &cSignals = cClass.GetSlots();
	for (uint32 i=0; i<cSignals.GetNumOfElements(); ++i) {
		MemberDesc *pVarDesc = cSignals[i];
		new ClassInfoMemberDescTreeItem(*pVarDesc, m_pSignalsCategory);
	}

	// Add signals
	const List<EventDesc*> &cSlots = cClass.GetSignals();
	for (uint32 i=0; i<cSlots.GetNumOfElements(); ++i) {
		MemberDesc *pVarDesc = cSlots[i];
		new ClassInfoMemberDescTreeItem(*pVarDesc, m_pSignalsCategory);
	}

	// Add properties
	const HashMap<String, String> &cProps = cClass.GetProperties();
	Iterator<String> cIterator = cProps.GetKeyIterator();
	while (cIterator.HasNext()) {
		const String sName  = cIterator.Next();
		ClassInfoStringTreeItem(QtStringAdapter::PLToQt(sName), m_pPropertiesCategory);
	}

	// Add constructors
	const List<ConstructorDesc*> &cConstructors = cClass.GetConstructors();
	for (uint32 i=0; i<cConstructors.GetNumOfElements(); ++i) {
		ConstructorDesc *pVarDesc = cConstructors[i];
		new ClassInfoMemberDescTreeItem(*pVarDesc, m_pConstructorsCategory);
	}

	// Add methods
	const List<FuncDesc*> &cMethods = cClass.GetMethods();
	for (uint32 i=0; i<cMethods.GetNumOfElements(); ++i) {
		FuncDesc *pVarDesc = cMethods[i];
		new ClassInfoMemberDescTreeItem(*pVarDesc, m_pMethodsCategory);
	}

	endResetModel();
}

void ClassInfoModel::DeleteChilds(ClassInfoCategoryTreeItem *pCategoryItem)
{
	if (pCategoryItem) {
		const QObjectList &childs = pCategoryItem->children();
		qDeleteAll(childs.begin(), childs.end());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
