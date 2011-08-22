/*********************************************************\
 *  File: MorphTargetAni.h                               *
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


#ifndef __PLMESH_MORPHTARGETANI_H__
#define __PLMESH_MORPHTARGETANI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Element.h>
#include <PLCore/Container/ElementManager.h>
#include <PLCore/Container/ElementHandler.h>
#include <PLRenderer/Animation/AnimationBase.h>
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Mesh;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Morph target animation class
*/
class MorphTargetAni : public PLRenderer::AnimationBase, public PLCore::Element<MorphTargetAni> {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Animation morph target
		*/
		class AniMorphTarget {


			//[-------------------------------------------------------]
			//[ Public data                                           ]
			//[-------------------------------------------------------]
			public:
				PLCore::String sName; /**< Morph target name */


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				PLMESH_API AniMorphTarget()
				{
				}

				PLMESH_API ~AniMorphTarget()
				{
				}

				PLMESH_API bool operator ==(const AniMorphTarget &cAniMorphTarget) const
				{
					return sName == cAniMorphTarget.sName;
				}


		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Name
		*  @param[in] pManager
		*    Element manager using this element, can be a null pointer
		*
		*  @note
		*    - If you provide the pointer to the owner manager the morph target animation
		*      will check in the owner morph target animation manager name list
		*    - If the desired name is already in use inside the owner manager an alternative
		*      name is set
		*/
		PLMESH_API MorphTargetAni(const PLCore::String &sName, PLCore::ElementManager<MorphTargetAni> *pManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MorphTargetAni();

		/**
		*  @brief
		*    Returns the morph target animation morph targets
		*
		*  @return
		*    Morph target animation morph targets
		*/
		PLMESH_API PLCore::Array<AniMorphTarget> &GetMorphTargets();

		/**
		*  @brief
		*    Applies the morph target weight from the given morph target frame
		*    to the given morph target weights
		*
		*  @param[out] lstMorphTargetWeights
		*    Morph target weights to manipulate
		*  @param[in]  nFrame
		*    Morph target animation frame
		*  @param[in]  fWeight
		*    Weight (0.0-1.0)
		*  @param[in]  pMesh
		*    Mesh of the given morph target weights array, can be a null pointer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If pMesh is not a null pointer lstMorphTargetWeights is a list of ALL morph target influences
		*      of the given mesh, else lstMorphTargetWeights is only a list of the morph target
		*      weights of THIS animation!
		*/
		PLMESH_API bool ApplyMorphTargetWeight(PLCore::Array<float> &lstMorphTargetWeights,
											   PLCore::uint32 nFrame, float fWeight = 1.0f, const Mesh *pMesh = nullptr) const;

		/**
		*  @brief
		*    Applies the blended morph target weight from the given morph target frames
		*    to the given morph target weights
		*
		*  @param[out] lstMorphTargetWeights
		*    Morph target weights to manipulate
		*  @param[in]  nFrame1
		*    Morph target animation frame 1
		*  @param[in]  nFrame2
		*    Morph target animation frame 2
		*  @param[in]  fTime
		*    Morph target animation time (0.0-1.0)
		*  @param[in]  fWeight
		*    Weight (0.0-1.0)
		*  @param[in]  pMesh
		*    Mesh of the given morph target weights array, can be a null pointer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - ApplyMorphTargetWeight() above
		*/
		PLMESH_API bool ApplyMorphTargetWeight(PLCore::Array<float> &lstMorphTargetWeights,
											   PLCore::uint32 nFrame1, PLCore::uint32 nFrame2, float fTime,
											   float fWeight = 1.0f, const Mesh *pMesh = nullptr) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<AniMorphTarget> m_lstAniMorphTargets;


	//[-------------------------------------------------------]
	//[ Public virtual AnimationInfo functions                ]
	//[-------------------------------------------------------]
	public:
		PLMESH_API virtual MorphTargetAni &operator =(const MorphTargetAni &cSource);
		PLMESH_API virtual PLCore::String GetSourceName() const override;


};


/**
*  @brief
*    Morph target animation manager
*/
class MorphTargetAniManager : public PLCore::ElementManager<MorphTargetAni> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API MorphTargetAniManager();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MorphTargetAniManager();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ElementManager functions      ]
	//[-------------------------------------------------------]
	private:
		virtual MorphTargetAni *CreateElement(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MORPHTARGETANI_H__
