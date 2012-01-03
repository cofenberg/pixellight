/*********************************************************\
 *  File: Inspector.cpp                                  *
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
#include "IPluginDockWidget/Inspector.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditorPluginBase {


//[-------------------------------------------------------]
//[ Public virtual PLEditor::IPluginDockWidget methods    ]
//[-------------------------------------------------------]
Inspector::EType Inspector::getType() const
{
	return TypeDockWidget;
}

QString Inspector::getName() const
{
	return "Inspector";
}

Qt::DockWidgetArea Inspector::InitialArea()
{
	return Qt::DockWidgetArea::RightDockWidgetArea;
}

PLEditor::IPlugin* Inspector::Clone() const
{
	return new Inspector();
}

//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Inspector::Inspector()
{
	m_cTreeView.setModel(&m_cModel);
	this->setWidget(&m_cTreeView);
	
	setWindowTitle(getName());
}

/**
*  @brief
*    Destructor
*/
Inspector::~Inspector()
{
}

void Inspector::SetObject(PLCore::Object *Obj)
{
	m_cModel.SetObject(Obj);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditorPluginBase
