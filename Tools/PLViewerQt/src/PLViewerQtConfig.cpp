/*********************************************************\
 *  File: Config.cpp                                     *
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
#include "ApplicationQt.h"
#include "PLViewerQtConfig.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(PLViewerQtConfig)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
bool PLViewerQtConfig::GetShowColorGradientBackground() const
{
	return m_bShowColorGradientBackground;
}

void PLViewerQtConfig::SetShowColorGradientBackground(bool bValue)
{
	m_bShowColorGradientBackground = bValue;

	// Update color gradient background according to the configuration
	CoreApplication *pCoreApplication = CoreApplication::GetApplication();
	if (pCoreApplication && pCoreApplication->IsInstanceOf("ApplicationQt"))
		static_cast<ApplicationQt*>(pCoreApplication)->UpdateColorGradientBackground();
}

bool PLViewerQtConfig::GetShowBackfacesAndSilhouettes() const
{
	return m_bShowBackfacesAndSilhouettes;
}

void PLViewerQtConfig::SetShowBackfacesAndSilhouettes(bool bValue)
{
	m_bShowBackfacesAndSilhouettes = bValue;

	// Update backfaces and silhouettes visualization according to the configuration
	CoreApplication *pCoreApplication = CoreApplication::GetApplication();
	if (pCoreApplication && pCoreApplication->IsInstanceOf("ApplicationQt"))
		static_cast<ApplicationQt*>(pCoreApplication)->UpdateBackfacesAndSilhouettes();
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PLViewerQtConfig::PLViewerQtConfig() :
	ShowColorGradientBackground(this),
	ShowBackfacesAndSilhouettes(this),
	m_bShowColorGradientBackground(true),
	m_bShowBackfacesAndSilhouettes(true)

{
}

/**
*  @brief
*    Destructor
*/
PLViewerQtConfig::~PLViewerQtConfig()
{
}
