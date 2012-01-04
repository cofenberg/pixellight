/*********************************************************\
 *  File: ClassListModel.cpp                             *
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
#include <PLCore/Container/List.h>
#include <PLCore/Base/Class.h>
#include <PLCore/Base/Module.h>
#include <PLCore/Base/ClassManager.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/HeaderTreeItem.h"
#include "PLFrontendQt/DataModels/RTTIInfoModels/ClassListModel.h"


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
class ClassListInfoTreeItemBase : public TreeItemBase {


	public:
		ClassListInfoTreeItemBase(bool isModule, const QString &name, const QString &description, QObject *parent = nullptr) : TreeItemBase(1, parent),
			m_sName(name),
			m_sDescription(description),
			m_isModule(isModule)
		{
		}

		virtual QVariant data(const int column, const int role)
		{
			if (column > 0)
				return QVariant();
			if (role == Qt::ToolTipRole)
				return m_sTooltip;
			else if (role == Qt::DisplayRole || (role == ClassListModel::ClassListNameRole))
				return m_sName;
			else if (role == ClassListModel::ClassListDescriptionRole)
				return m_sDescription;
			else if (role == ClassListModel::ClassListItemType)
				return m_isModule;
			return QVariant();
		}


	protected:
		void SetTooltipText(const QString &tooltipText)
		{
			m_sTooltip = tooltipText;
		}


	protected:
		QString m_sName;
		QString m_sDescription;
		QString m_sTooltip;
		bool m_isModule;


};

class ModuleInfoTreeItem : public ClassListInfoTreeItemBase {


	public:
		ModuleInfoTreeItem(const Module &moduleItem, QObject *parent = nullptr) : ClassListInfoTreeItemBase(true, QtStringAdapter::PLToQt(moduleItem.GetName()), QtStringAdapter::PLToQt(moduleItem.GetDescription()), parent),
			m_sVendor(QtStringAdapter::PLToQt(moduleItem.GetVendor())),
			m_sLicense(QtStringAdapter::PLToQt(moduleItem.GetLicense()))
		{
			SetTooltipText(tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Module Info</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Description: </td><td>%2</td></tr>"
							"<tr><td>Vendor: </td><td>%3</td></tr>"
							"<tr><td>License: </td><td>%4</td></tr>"
							"</table>").arg(m_sName, m_sDescription, m_sVendor, m_sLicense));
		}

		virtual QVariant data(const int column, const int role)
		{
			if (column > 0)
				return QVariant();
			else if (role == ClassListModel::ModuleVendorRole)
				return m_sVendor;
			else if (role == ClassListModel::ModuleLicenseRole)
				return m_sLicense;
			return ClassListInfoTreeItemBase::data(column, role);
		}


	private:
		QString m_sVendor;
		QString m_sLicense;


};

class ClassInfoTreeItem : public ClassListInfoTreeItemBase {


	public:
		ClassInfoTreeItem(const Class &classItem, QObject *parent = nullptr) : ClassListInfoTreeItemBase(false, QtStringAdapter::PLToQt(classItem.GetName()), QtStringAdapter::PLToQt(classItem.GetDescription()), parent),
			m_sBaseClass(QtStringAdapter::PLToQt(classItem.GetBaseClassName())),
			m_sFulleName(QtStringAdapter::PLToQt(classItem.GetClassName())),
			m_sNamespace(QtStringAdapter::PLToQt(classItem.GetNamespace()))
		{
			SetTooltipText(tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Class Info</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Fullname: </td><td>%2</td></tr>"
							"<tr><td>Description: </td><td>%3</td></tr>"
							"<tr><td>Base class: </td><td>%4</td></tr>"
							"</table>").arg(m_sName, m_sFulleName, m_sDescription, m_sBaseClass));
		}

		virtual QVariant data(const int column, const int role)
		{
			if (column > 0)
				return QVariant();
			else if (role == ClassListModel::ClassBaseClassRole)
				return m_sBaseClass;
			else if (role == ClassListModel::ClassFullNameRole)
				return m_sFulleName;
			else if (role == ClassListModel::ClassNamespaceRole)
				return m_sNamespace;
			return ClassListInfoTreeItemBase::data(column, role);
		}


	private:
		QString m_sBaseClass;
		QString m_sFulleName;
		QString m_sNamespace;


};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassListModel::ClassListModel(bool hierarchical, QObject *parent) : TreeModelBase(new HeaderTreeItem(parent), parent)
{
	QStringList headerItems;
	headerItems << "Element";

	HeaderTreeItem *header = static_cast<HeaderTreeItem*>(GetRootItem());
	header->setHeaderItems(headerItems);

	SetupModel(hierarchical);
}

ClassListModel::~ClassListModel()
{
}

void ClassListModel::SetupModel(bool hierarchical)
{
	beginResetModel();

	ClassManager *manager = ClassManager::GetInstance();

	if (hierarchical) {
		const Class *coreObject = manager->GetClass("PLCore::Object");

		ClassInfoTreeItem *classInfoItem = new ClassInfoTreeItem(*coreObject, GetRootItem());

		CreateHierarchicalClassItems(*coreObject, classInfoItem);
	} else {
		const List<const Module*> modules = manager->GetModules();

		Iterator<const Module*> cIterator = modules.GetIterator();

		while (cIterator.HasNext()) {
			const Module *pElement = cIterator.Next();

			ModuleInfoTreeItem *moduleItem = new ModuleInfoTreeItem(*pElement, GetRootItem());
			CreateClassItemsFromModule(*pElement, moduleItem);
		}
	}

	endResetModel();
}

void ClassListModel::CreateClassItemsFromModule(const Module &moduleItem, QObject *parent)
{
	const List<const Class*> classes = moduleItem.GetClasses();

	Iterator<const Class*> cIterator = classes.GetIterator();

	while (cIterator.HasNext()) {
		const Class *pElement = cIterator.Next();

		new ClassInfoTreeItem(*pElement, parent);
	}
}

void ClassListModel::CreateHierarchicalClassItems(const Class &baseClass, QObject *parent)
{
	List<const Class*> classes;
	baseClass.GetDerivedClasses(classes);

	Iterator<const Class*> cIterator = classes.GetIterator();

	while (cIterator.HasNext()) {
		const Class *pElement = cIterator.Next();
		CreateHierarchicalClassItems(*pElement, new ClassInfoTreeItem(*pElement, parent));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLFrontendQt
