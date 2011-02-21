/*********************************************************\
 *  File: SNBasicDemo.h                                  *
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


#ifndef __SPARK_PL_SNBASICDEMO_H__
#define __SPARK_PL_SNBASICDEMO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPARK_PL/SNSystem.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace SPK {
	class Group;
	class Model;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Basic SPARK particle system demo scene node
*
*  @note
*    - Basing on "SPARK Basic Demo"
*/
class SNBasicDemo : public SNSystem {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(SPARK_PL_RTTI_EXPORT, SNBasicDemo, "SPARK_PL", SPARK_PL::SNSystem, "Basic SPARK particle system demo scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SPARK_PL_API SNBasicDemo();

		/**
		*  @brief
		*    Destructor
		*/
		SPARK_PL_API virtual ~SNBasicDemo();


	//[-------------------------------------------------------]
	//[ Protected virtual SNSystem functions                  ]
	//[-------------------------------------------------------]
	protected:
		SPARK_PL_API virtual void Update();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SPK::Group *m_pParticleGroup;	/**< SPARK particle group, can be a null pointer */
		SPK::Model *m_pParticleModel;
		float		m_fStep;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif // __SPARK_PL_SNBASICDEMO_H__
