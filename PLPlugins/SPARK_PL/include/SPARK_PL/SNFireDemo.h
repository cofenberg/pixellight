/*********************************************************\
 *  File: SNFireDemo.h                                   *
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


#ifndef __SPARK_PL_SNFIREDEMO_H__
#define __SPARK_PL_SNFIREDEMO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPARK_PL/SNSystem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fire SPARK particle system demo scene node
*
*  @note
*    - Basing on "SPARK Fire Demo"
*/
class SNFireDemo : public SNSystem {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(SPARK_PL_RTTI_EXPORT, SNFireDemo, "SPARK_PL", SPARK_PL::SNSystem, "Fire SPARK particle system demo scene node")
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
		SPARK_PL_API SNFireDemo();

		/**
		*  @brief
		*    Destructor
		*/
		SPARK_PL_API virtual ~SNFireDemo();


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif // __SPARK_PL_SNFIREDEMO_H__
