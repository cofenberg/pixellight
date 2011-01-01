/*********************************************************\
 *  File: EffectLoaderFX.h                               *
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


#ifndef __PLDEFAULTFILEFORMATS_CG_EFFECTLOADER_FX_H__
#define __PLDEFAULTFILEFORMATS_CG_EFFECTLOADER_FX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Effect/EffectLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Effect;
	class EffectPass;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect loader implementation for FX (CgFX)
*/
class EffectLoaderFX : public PLRenderer::EffectLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, EffectLoaderFX, "PLDefaultFileFormats", PLRenderer::EffectLoader, "Effect loader implementation for FX (CgFX)")
		pl_properties
			pl_property("Formats",	"fx,FX")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLRenderer::Effect&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, PLRenderer::Effect&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLRenderer::Effect &cEffect, PLGeneral::File &cFile);
		bool Save(PLRenderer::Effect &cEffect, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Internal per instance data
		*/
		struct SInstance {
			PLRenderer::Effect	   *pFX;		/**< Effect to load */
			int						nTechnique;	/**< The current technique */
			PLRenderer::EffectPass *pFXPass;	/**< The current pass */
			char				   *pFileData;	/**< File data */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		EffectLoaderFX();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~EffectLoaderFX();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_CG_EFFECTLOADER_FX_H__
