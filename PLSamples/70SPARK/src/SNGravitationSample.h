/*********************************************************\
 *  File: SNGravitationSample.h                          *
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


#ifndef __PLSAMPLE_70_SNGRAVITATIONSAMPLE_H__
#define __PLSAMPLE_70_SNGRAVITATIONSAMPLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <SPARK_PL/PLSceneNodes/SNSystem.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace SPK {
	class Group;
	class Model;
	class PointMass;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Gravitation SPARK particle system sample scene node
*
*  @note
*    - Basing on "SPARK Gravitation Demo" from SPARK
*/
class SNGravitationSample : public SPARK_PL::SNSystem {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNGravitationSample, "", SPARK_PL::SNSystem, "Gravitation SPARK particle system sample scene node")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNGravitationSample();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNGravitationSample();


	//[-------------------------------------------------------]
	//[ Protected virtual SNSystem functions                  ]
	//[-------------------------------------------------------]
	protected:
		virtual void Update();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		// The number of point masses
		static const PLGeneral::uint32 NumOfPointMasses = 2;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SPK::Group		*m_pParticleGroup;	/**< SPARK particle group, can be a null pointer */
		SPK::Group		*m_pMassGroup;		/**< SPARK mass group, can be a null pointer */
		SPK::Model		*m_pParticleModel;
		SPK::PointMass	*m_pPointMasses[NumOfPointMasses];
		float			 m_fStep;


};


#endif // __PLSAMPLE_70_SNGRAVITATIONSAMPLE_H__
