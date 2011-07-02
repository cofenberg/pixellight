/*********************************************************\
 *  File: PLDynVarColorTreeItem.cpp                      *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#include <QtGui/QRgb>
#include <QtGui/QColor>
#include <PLCore/Base/Var/DynVar.h>
#include <PLGraphics/Color/Color3.h>
#include "PLQt/QtStringAdapter.h"
#include "PLQt/DataModels/PLTreeItems/PLDynVarColorTreeItem.h"


enum { ColorRole = 33 };


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {


PLDynVarColorTreeItem::PLDynVarColorTreeItem(PLCore::DynVar *dynVar, QObject *parent) : PLDynVarStringTreeItem(dynVar, parent)
{
}

QVariant PLDynVarColorTreeItem::data(const int column, const int role)
{
	if (column == 1) {
		if (role == ColorRole) {
			PLGraphics::Color3 col;
			QString qstr(QtStringAdapter::PLToQt(m_dynVar->GetString()));
			col.FromString(m_dynVar->GetString());

			float f = col.GetR();
			f = col.GetG();
			f = col.GetB();

			QColor color(QColor::fromRgbF(col.GetR(), col.GetG(), col.GetB()));
			return color;
		}
		return QVariant();
	}

	return PLDynVarStringTreeItem::data(column, role);
}

bool PLDynVarColorTreeItem::setData(const int column, const QVariant &value, const int role)
{
	if (role != Qt::EditRole || column != 1)
		return false;

	QColor color = value.value<QColor>();
	PLGraphics::Color3 col((float)color.redF(), (float)color.greenF(), (float)color.blueF());
	m_dynVar->SetString(col.ToString());
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLQt
