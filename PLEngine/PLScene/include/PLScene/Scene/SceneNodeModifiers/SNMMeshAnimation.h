/*********************************************************\
 *  File: SNMMeshAnimation.h                             *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MESHANIMATION_H__
#define __PLSCENE_SCENENODEMODIFIER_MESHANIMATION_H__
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
*    Mesh scene node animation modifier class
*
*  @note
*    - Adds automatically a "PLScene::SNMMeshUpdate" scene node modifier (if there's not yet one) in order to frequently update the mesh
*    - If the node has no mesh with animations, this modifier will have no effect
*/
class SNMMeshAnimation : public SNMMesh {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMeshAnimation, "PLScene", PLScene::SNMMesh, "Mesh scene node animation modifier class")
		// Attributes
		pl_attribute(Name,		PLGeneral::String,	"",		ReadWrite,	GetSet,	"Name of the animation",										"")
		pl_attribute(Frame,		float,				0.0f,	ReadWrite,	GetSet,	"Current animation frame",										"")
		pl_attribute(Speed,		float,				1.0f,	ReadWrite,	GetSet,	"Animation playback speed (multiplied with original speed)",	"")
		pl_attribute(Weight,	float,				1.0f,	ReadWrite,	GetSet,	"Animation weight",												"")
		pl_attribute(MinWeight,	float,				0.0f,	ReadWrite,	GetSet,	"Minimum animation weight",										"")
		pl_attribute(MaxWeight,	float,				1.0f,	ReadWrite,	GetSet,	"Maximum animation weight",										"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetName() const;
		PLS_API void SetName(const PLGeneral::String &sValue);
		PLS_API float GetFrame() const;
		PLS_API void SetFrame(float fValue);
		PLS_API float GetSpeed() const;
		PLS_API void SetSpeed(float fValue);
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
		PLS_API SNMMeshAnimation(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMeshAnimation();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Updates the mesh
		*/
		void UpdateMesh();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sName;
		float			  m_fFrame;
		float			  m_fSpeed;
		float			  m_fWeight;
		float			  m_fMinWeight;
		float			  m_fMaxWeight;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MESHANIMATION_H__
