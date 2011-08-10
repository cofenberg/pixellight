/*********************************************************\
 *  File: PluginFactory.cpp                              *
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
#include "IPluginDockWidget/Inspector.h"
#include "PluginFactory.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditorPluginBase {


//[-------------------------------------------------------]
//[ Public virtual PLEditor::IPluginFactory methods       ]
//[-------------------------------------------------------]
QString PluginFactory::getName() const
{
	return "Base";
}

QString PluginFactory::getVendor() const
{
	return "Copyright (C) 2002-2011 by The PixelLight Team";
}

QString PluginFactory::getLicense() const
{
	return "GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version";
}

QString PluginFactory::getDescription() const
{
	return "PixelLight base plugin";
}

unsigned int PluginFactory::getNumOfClasses() const
{
	return 0;
}

QObject *PluginFactory::createInstance(unsigned int nClass) const
{
	switch (nClass) {
		case 0:
			return new Inspector();

		default:
			return nullptr;
	}
}


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PluginFactory::PluginFactory()
{
}

/**
*  @brief
*    Destructor
*/
PluginFactory::~PluginFactory()
{
}


//[-------------------------------------------------------]
//[ Qt definitions                                        ]
//[-------------------------------------------------------]
Q_EXPORT_PLUGIN2(BasePlugin, PluginFactory)


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditorPluginBase
