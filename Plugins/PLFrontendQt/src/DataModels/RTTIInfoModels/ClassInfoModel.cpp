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
#include <QtCore/QStringList>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Var/VarDesc.h>
#include <PLCore/Base/Event/EventDesc.h>
#include <PLCore/Base/Event/EventHandlerDesc.h>
#include <PLCore/Base/Func/FuncDesc.h>
#include <PLCore/Base/Func/ConstructorDesc.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/TreeItemBase.h"
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
//[ Classes                                               ]
//[-------------------------------------------------------]
class ClassInfoPropertyTreeItem : public TreeItemBase {


	public:
		ClassInfoPropertyTreeItem(const QString &propertyName, const QString &propertyValue, TreeItemBase *parent = nullptr) : TreeItemBase(1, parent), m_sPropertyName(propertyName), m_sPropertyValue(propertyValue)
		{
			m_sToolTipText = QObject::tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Property Information</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Value: </td><td>%2</td></tr>"
							"</table>").arg(m_sPropertyName, m_sPropertyValue);
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column > 0)
				return QVariant();
			
			if (role == Qt::DisplayRole) {
				return m_sPropertyName;
			}
			else if (role == Qt::ToolTipRole) {
				return m_sToolTipText;
			}

			return QVariant();
		}


	private:
		QString m_sPropertyName;
		QString m_sPropertyValue;
		QString m_sToolTipText;


};

class ClassListItem : public TreeItemBase {


	public:
		explicit ClassListItem(const Class *pClass, ClassInfoModel::ClassInfoItemRoles displayRole = ClassInfoModel::NameRole, TreeItemBase *parent = nullptr) : TreeItemBase(1, parent) , m_pClass(pClass), m_cDisplayRole(displayRole)
		{
			QString tooltipTemplate = QObject::tr("<table>"
									"<tr><td bgcolor=#00ff00 colspan=\"2\">Class Information</td></tr>"
									"<tr><td>Name:</td><td><ClassName></td></tr>"
									"<tr><td>Description:</td><td><ClassDesc></td></tr>"
									"</table>");

			m_sTooltip = tooltipTemplate.replace("<ClassName>", QtStringAdapter::PLToQt(pClass->GetClassName())).replace("<ClassDesc>", QtStringAdapter::PLToQt(pClass->GetDescription())).replace("<FullClassName>", QtStringAdapter::PLToQt(pClass->GetClassName()));
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column != 0 || !m_pClass)
				return QVariant();

			if (role == Qt::ToolTipRole)
				return m_sTooltip;
			ClassInfoModel::ClassInfoItemRoles itemRole = static_cast<ClassInfoModel::ClassInfoItemRoles>(role);
			if (role == Qt::DisplayRole)
				itemRole = m_cDisplayRole;
			else if (role == Qt::ToolTipRole)
				itemRole = ClassInfoModel::DescriptionRole;

			return GetDataForClassListItemRole(itemRole);
		}

		const Class *GetObject()
		{
			return m_pClass;
		}


	private:
		QVariant GetDataForClassListItemRole(ClassInfoModel::ClassInfoItemRoles role)
		{
			switch (role) {
				case ClassInfoModel::NameRole:
					return "Name: " + QtStringAdapter::PLToQt(m_pClass->GetClassName());

				case ClassInfoModel::NamespaceRole:
					return "Namespace: " + QtStringAdapter::PLToQt(m_pClass->GetNamespace());

				case ClassInfoModel::DescriptionRole:
					return "Description: " + QtStringAdapter::PLToQt(m_pClass->GetDescription());

				default:
					return QVariant();
			}
		}


	private:
		const Class *m_pClass;
		const ClassInfoModel::ClassInfoItemRoles m_cDisplayRole;
		QString m_sTooltip;


};

class ClassInfoCategoryTreeItem : public TreeItemBase {


	public:
		ClassInfoCategoryTreeItem(const QString name, TreeItemBase *parent = nullptr) : TreeItemBase(1, parent), m_name(name)
		{
		}

		virtual QVariant data(const int column, const int role) override
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

template<class T>
class ClassInfoTreeItemBase : public TreeItemBase {


	public:
		ClassInfoTreeItemBase(const T &cVarDesc, TreeItemBase *parent = nullptr) : TreeItemBase(1, parent),
			m_sName(QtStringAdapter::PLToQt(cVarDesc.GetName())),
			m_sDescription(QtStringAdapter::PLToQt(cVarDesc.GetDescription()))
		{
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column > 0)
				return QVariant();
			
			if (role == Qt::DisplayRole) {
				return m_sName;
			}
			else if( role == Qt::ToolTipRole) {
				return m_sToolTip;
			}

			return QVariant();
		}

	protected:
		void SetToolTipText(const QString &toolTipText)
		{
			m_sToolTip = toolTipText;
		}

	protected:
		QString m_sName;
		QString m_sDescription;
		QString m_sToolTip;
};

class ClassInfoAttributeTreeItem : public ClassInfoTreeItemBase<VarDesc> {


	public:
		ClassInfoAttributeTreeItem(const VarDesc &cVarDesc, TreeItemBase *parent = nullptr) : ClassInfoTreeItemBase(cVarDesc, parent),
			m_sType(QtStringAdapter::PLToQt(cVarDesc.GetTypeName())),
			m_sDefault(QtStringAdapter::PLToQt(cVarDesc.GetDefault()))
		{
			SetToolTipText(QObject::tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Attribute Information</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Type: </td><td>%2</td></tr>"
							"<tr><td>Default: </td><td>%3</td></tr>"
							"<tr><td>Description: </td><td>%4</td></tr>"
							"</table>").arg(m_sName, m_sType, m_sDefault, m_sDescription));
		}

	protected:
		QString m_sType;
		QString m_sDefault;
};

template<class T>
class ClassInfoMemberWithSignatureDescTreeItem : public ClassInfoTreeItemBase<MemberDesc> {


	public:
		ClassInfoMemberWithSignatureDescTreeItem(const QString tooltipTitle, const T &cMemberDesc, TreeItemBase *parent = nullptr) :
			ClassInfoTreeItemBase(cMemberDesc, parent),
			m_sSignature(QtStringAdapter::PLToQt(cMemberDesc.GetSignature()))
		{
			SetToolTipText(QObject::tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">%1 Information</td></tr>"
							"<tr><td>Name: </td><td>%2</td></tr>"
							"<tr><td>Description: </td><td>%3</td></tr>"
							"<tr><td>Signature: </td><td>%4</td></tr>"
							"</table>").arg(tooltipTitle, m_sName, m_sDescription, m_sSignature));
		}

	private:
		QString m_sSignature;


};

//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassInfoModel::ClassInfoModel(QObject *parent): TreeModelBase(new HeaderTreeItem, parent),
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
	new ClassListItem(pClass, NameRole, m_pCommonCategory);
	new ClassListItem(pClass, DescriptionRole, m_pCommonCategory);

	// Add attributes
	const List<VarDesc*> &attr = cClass.GetAttributes();
	for (uint32 i=0; i<attr.GetNumOfElements(); ++i) {
		VarDesc *pVarDesc = attr[i];
		new ClassInfoAttributeTreeItem(*pVarDesc, m_pAttributeCategory);
	}

	// Add slots
	const List<EventHandlerDesc*> &cSlots = cClass.GetSlots();
	for (uint32 i=0; i<cSlots.GetNumOfElements(); ++i) {
		EventHandlerDesc *pVarDesc = cSlots[i];
		new ClassInfoMemberWithSignatureDescTreeItem<EventHandlerDesc>(tr("Slot"), *pVarDesc, m_pSlotsCategory);
	}

	// Add signals
	const List<EventDesc*> &cSignals = cClass.GetSignals();
	for (uint32 i=0; i<cSignals.GetNumOfElements(); ++i) {
		EventDesc *pVarDesc = cSignals[i];
		new ClassInfoMemberWithSignatureDescTreeItem<EventDesc>(tr("Signal"), *pVarDesc, m_pSignalsCategory);
	}

	// Add properties
	const HashMap<String, String> &cProps = cClass.GetProperties();
	Iterator<String> cIterator = cProps.GetKeyIterator();
	while (cIterator.HasNext()) {
		const String sName  = cIterator.Next();
		const String sValue = cProps.Get(sName);
		new ClassInfoPropertyTreeItem(QtStringAdapter::PLToQt(sName), QtStringAdapter::PLToQt(sValue), m_pPropertiesCategory);
	}

	// Add constructors
	const List<ConstructorDesc*> &cConstructors = cClass.GetConstructors();
	for (uint32 i=0; i<cConstructors.GetNumOfElements(); ++i) {
		ConstructorDesc *pVarDesc = cConstructors[i];
		new ClassInfoMemberWithSignatureDescTreeItem<ConstructorDesc>(tr("Constructor"), *pVarDesc, m_pConstructorsCategory);
	}

	// Add methods
	const List<FuncDesc*> &cMethods = cClass.GetMethods();
	for (uint32 i=0; i<cMethods.GetNumOfElements(); ++i) {
		FuncDesc *pVarDesc = cMethods[i];
		new ClassInfoMemberWithSignatureDescTreeItem<FuncDesc>(tr("Method"), *pVarDesc, m_pMethodsCategory);
	}

	endResetModel();
}

void ClassInfoModel::DeleteChilds(ClassInfoCategoryTreeItem *pCategoryItem)
{
	if (pCategoryItem) {
		pCategoryItem->clearChildren();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
