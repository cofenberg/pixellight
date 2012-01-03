/*********************************************************\
 *  File: PluginManager.cpp                              *
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
#include <QDir>
#include <QPluginLoader>
#include "Interfaces/IPlugin.h"
#include "Interfaces/IPluginFactory.h"
#include "PluginManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEditor {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads in all plugins
*/
void PluginManager::loadPlugins()
{
	// Open the current directory
	QDir cQDir("");
	QString str;
	// Iterate through all found filenames
	foreach (QString sFilename, cQDir.entryList(QDir::Filter::NoSymLinks | QDir::Filter::Files)) {
		// Load the plugin
		bool debug_lib = sFilename.contains("D.");
#ifdef _DEBUG
		if (!debug_lib)
			continue;
#else
		if (debug_lib)
			continue;
#endif
		QPluginLoader cQPluginLoader(cQDir.absoluteFilePath(sFilename));
		QObject *pQObject = cQPluginLoader.instance();
		if (pQObject) {
			// Is this a IPluginFactory implementation?
			IPluginFactory *pIPluginFactory = qobject_cast<IPluginFactory*>(pQObject);
			if (pIPluginFactory) {
				// Create all possible class instances
				for (unsigned int i=0; i<pIPluginFactory->getNumOfClasses(); i++)
					m_lstPlugins.append(pIPluginFactory->createInstance(i));
			}
		}
	}
}

/**
*  @brief
*    Returns a list of currently loaded plugins
*/
const QList<const IPlugin*> &PluginManager::getPlugins() const
{
	return m_lstPlugins;
}


//[-------------------------------------------------------]
//[ Protected methods                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PluginManager::PluginManager()
{
}

/**
*  @brief
*    Destructor
*/
PluginManager::~PluginManager()
{
	foreach (const IPlugin *pIPlugin, m_lstPlugins)
		delete pIPlugin;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
PluginManager::PluginManager(const PluginManager &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
PluginManager &PluginManager::operator =(const PluginManager &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEditor
