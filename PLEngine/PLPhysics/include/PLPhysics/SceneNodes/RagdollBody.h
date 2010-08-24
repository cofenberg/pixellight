/*********************************************************\
 *  File: RagdollBody.h                                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLPHYSICS_SCENENODES_RAGDOLLBODY_H__
#define __PLPHYSICS_SCENENODES_RAGDOLLBODY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLMath/Quaternion.h>
#include "PLPhysics/PLPhysics.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color4;
}
namespace PLRenderer {
	class Renderer;
}
namespace PLScene {
	class VisNode;
}
namespace PLPhysics {
	class Body;
	class SNRagdoll;
	class ElementHandler;
	class SCPhysicsWorld;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Ragdoll body
*
*  @note
*    - If you changed some of the initial settings you have to recreate
*      the physics object in order to see the changes.
*/
class RagdollBody {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent ragdoll
		*/
		PLPHYSICS_API RagdollBody(SNRagdoll *pParent);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~RagdollBody();

		/**
		*  @brief
		*    Returns the PL physics body
		*
		*  @return
		*    The PL physics body, NULL on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICS_API Body *GetBody() const;

		/**
		*  @brief
		*    Sets the name of the body
		*
		*  @param[in] sName
		*    New body name
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe this name is already used within the ragdoll?)
		*/
		PLPHYSICS_API bool SetName(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Draws the physics body
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cColor
		*    Color to use
		*  @param[in] cVisNode
		*    The current visibility node of this scene node
		*/
		PLPHYSICS_API void Draw(PLRenderer::Renderer &cRenderer, const PLGraphics::Color4 &cColor, const PLScene::VisNode &cVisNode) const;

		/**
		*  @brief
		*    Creates the physics body
		*
		*  @note
		*    - After this function the physics body is in it's initial pose
		*/
		PLPHYSICS_API void CreatePhysicsBody();

		/**
		*  @brief
		*    Destroys the physics body
		*/
		PLPHYSICS_API void DestroyPhysicsBody();

		/**
		*  @brief
		*    Returns the current rotation of the physics body
		*
		*  @param[out] qQ
		*    Will receive the current rotation of the physics body
		*/
		PLPHYSICS_API void GetRotation(PLMath::Quaternion &qQ) const;

		/**
		*  @brief
		*    Returns the current transform matrix of the physics body
		*
		*  @param[out] mTrans
		*    Will receive the current transform matrix of the physics body
		*/
		PLPHYSICS_API void GetTransformMatrix(PLMath::Matrix3x4 &mTrans) const;

		/**
		*  @brief
		*    Adds a force to the body
		*
		*  @param[in] vForce
		*    Force to add
		*/
		PLPHYSICS_API void AddForce(const PLMath::Vector3 &vForce);


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint32 nIndex;
		PLGeneral::String sName;

		PLGeneral::String sJoint;	/**< Joint this body is attached to */

		// Specified whether the body (and any possible joints its connected to) are enabled
		bool bEnabled;

		PLMath::Vector3 vSize;
		PLMath::Vector3 vPos;
		PLMath::Quaternion qRot;
		float fMass;

		SNRagdoll *m_pParentRagdoll;
		ElementHandler *m_pBodyHandler;	/**< Holds the PL physics body */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODES_RAGDOLLBODY_H__
