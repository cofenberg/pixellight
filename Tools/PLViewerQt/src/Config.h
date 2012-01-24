/*********************************************************\
 *  File: Config.h                                       *
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


#ifndef __CONFIG_H__
#define __CONFIG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Config/Config.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PLViewerQt configuration classes
*/
class PLViewerQtConfig : public PLCore::ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, PLViewerQtConfig, "", PLCore::ConfigGroup, "PLViewerQt general configuration classes")
		// Attributes
		pl_attribute(DefaultFilename,				PLCore::String,	"",		ReadWrite,	DirectValue,	"Default resource (e.g. scene or script)",																	"")
		pl_attribute(ShowColorGradientBackground,	bool,			true,	ReadWrite,	GetSet,			"Show color gradient background? (whether or not this has an effect depends on the used scene renderer)",	"")
		pl_attribute(ShowBackfacesAndSilhouettes,	bool,			true,	ReadWrite,	GetSet,			"Show backfaces and silhouettes? (whether or not this has an effect depends on the used scene renderer)",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		bool GetShowColorGradientBackground() const;
		void SetShowColorGradientBackground(bool bValue);
		bool GetShowBackfacesAndSilhouettes() const;
		void SetShowBackfacesAndSilhouettes(bool bValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLViewerQtConfig();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLViewerQtConfig();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bShowColorGradientBackground;	/**< Show color gradient background? (whether or not this has an effect depends on the used scene renderer) */
		bool m_bShowBackfacesAndSilhouettes;	/**< Show backfaces and silhouettes? (whether or not this has an effect depends on the used scene renderer) */


};


#endif // __CONFIG_H__
