/*********************************************************\
 *  File: SNMMeshMorph.h                                 *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MESHMORPH_H__
#define __PLSCENE_SCENENODEMODIFIER_MESHMORPH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodeModifiers/SNMMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh scene node morph modifier class
*
*  @note
*    - Adds automatically a "PLScene::SNMMeshUpdate" scene node modifier (if there's not yet one) in order to frequently update the mesh
*    - If the node has no mesh with morph targets, this modifier will have no effect
*/
class SNMMeshMorph : public SNMMesh {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMeshMorph, "PLScene", PLScene::SNMMesh, "Mesh scene node morph modifier class")
		// Constructors
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		// Attributes
		pl_attribute(Name,		PLCore::String,	"",		ReadWrite,	GetSet,			"Name of the morph target",		"")
		pl_attribute(Weight,	float,			0.0f,	ReadWrite,	DirectValue,	"Morph target weight",			"")
		pl_attribute(MinWeight,	float,			0.0f,	ReadWrite,	DirectValue,	"Minimum morph target weight",	"")
		pl_attribute(MaxWeight,	float,			1.0f,	ReadWrite,	DirectValue,	"Maximum morph target weight",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetName() const;
		PLS_API void SetName(const PLCore::String &sValue);
		PLS_API float GetWeight() const;
		PLS_API void SetWeight(float fValue);
		PLS_API float GetMinWeight() const;
		PLS_API void SetMinWeight(float fValue);
		PLS_API float GetMaxWeight() const;
		PLS_API void SetMaxWeight(float fValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLS_API SNMMeshMorph(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMeshMorph();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Updates the morph target
		*/
		PLS_API void UpdateMorphTarget();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLCore::String m_sName;			/**< Name of the morph target */
		float		   m_fWeight;		/**< Morph target weight */
		float		   m_fMinWeight;	/**< Minimum morph target weight */
		float		   m_fMaxWeight;	/**< Maximum morph target weight */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MESHMORPH_H__
