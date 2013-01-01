/*********************************************************\
 *  File: ClassListModel.cpp                             *
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
		ClassListInfoTreeItemBase(bool isModule, const QString &name, const QString &description, TreeItemBase *parent = nullptr) : TreeItemBase(1, parent),
			m_sName(name),
			m_sDescription(description),
			m_isModule(isModule)
		{
		}

		virtual QVariant data(const int column, const int role) override
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
		ModuleInfoTreeItem(const Module &moduleItem, TreeItemBase *parent = nullptr) : ClassListInfoTreeItemBase(true, QtStringAdapter::PLToQt(moduleItem.GetName()), QtStringAdapter::PLToQt(moduleItem.GetDescription()), parent),
			m_sVendor(QtStringAdapter::PLToQt(moduleItem.GetVendor())),
			m_sLicense(QtStringAdapter::PLToQt(moduleItem.GetLicense())),
			m_sFilename(QtStringAdapter::PLToQt(moduleItem.GetFilename()))
		{
			SetTooltipText(QObject::tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Module Information</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Description: </td><td>%2</td></tr>"
							"<tr><td>Vendor: </td><td>%3</td></tr>"
							"<tr><td>License: </td><td>%4</td></tr>"
							"<tr><td>Filename: </td><td>%5</td></tr>"
							"</table>").arg(m_sName, m_sDescription, m_sVendor, m_sLicense, m_sFilename));
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column > 0)
				return QVariant();
			else if (role == ClassListModel::ModuleVendorRole)
				return m_sVendor;
			else if (role == ClassListModel::ModuleLicenseRole)
				return m_sLicense;
			else if (role == ClassListModel::ModuleFilenameRole)
				return m_sFilename;
			return ClassListInfoTreeItemBase::data(column, role);
		}


	private:
		QString m_sVendor;
		QString m_sLicense;
		QString m_sFilename;


};

class ClassInfoTreeItem : public ClassListInfoTreeItemBase {


	public:
		ClassInfoTreeItem(const Class &classItem, TreeItemBase *parent = nullptr) : ClassListInfoTreeItemBase(false, QtStringAdapter::PLToQt(classItem.GetClassName()), QtStringAdapter::PLToQt(classItem.GetDescription()), parent),
			m_sBaseClass(QtStringAdapter::PLToQt(classItem.GetBaseClassName())),
			m_sNameWithoutNameSpace(QtStringAdapter::PLToQt(classItem.GetName()))
		{
			SetTooltipText(QObject::tr("<table>"
							"<tr><td bgcolor=#00ff00 colspan=\"2\">Class Information</td></tr>"
							"<tr><td>Name: </td><td>%1</td></tr>"
							"<tr><td>Description: </td><td>%2</td></tr>"
							"<tr><td>Base class: </td><td>%3</td></tr>"
							"</table>").arg(m_sName, m_sDescription, m_sBaseClass));
		}

		virtual QVariant data(const int column, const int role) override
		{
			if (column > 0)
				return QVariant();
			else if (role == ClassListModel::ClassBaseClassRole)
				return m_sBaseClass;
			else if (role == ClassListModel::ClassNameWithoutNamespaceRole)
				return m_sNameWithoutNameSpace;
			return ClassListInfoTreeItemBase::data(column, role);
		}


	private:
		QString m_sBaseClass;
		QString m_sNameWithoutNameSpace;


};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
ClassListModel::ClassListModel(bool hierarchical, QObject *parent) : TreeModelBase(new HeaderTreeItem, parent)
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

void ClassListModel::CreateClassItemsFromModule(const Module &moduleItem, TreeItemBase *parent)
{
	const List<const Class*> classes = moduleItem.GetClasses();

	Iterator<const Class*> cIterator = classes.GetIterator();

	while (cIterator.HasNext()) {
		const Class *pElement = cIterator.Next();

		new ClassInfoTreeItem(*pElement, parent);
	}
}

void ClassListModel::CreateHierarchicalClassItems(const Class &baseClass, TreeItemBase *parent)
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
