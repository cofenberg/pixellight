/*********************************************************\
 *  File: Constructor.h                                  *
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


#ifndef __PLCORE_CONSTRUCTOR_H__
#define __PLCORE_CONSTRUCTOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/Func.h"
#include "PLCore/Base/Func/FuncConstructor.h"
#include "PLCore/Base/Func/ConstructorDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of a class
*
*  @remarks
*    This class template represents constructors.
*/
template <typename DESC>
class Constructor : public DESC::ConstType {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static DESC	Desc;	/**< Constructor descriptor */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		Constructor() : DESC::ConstType()
		{
			// Ensure that the compiler will actually create static instances
			Desc.Dummy();
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Constructor()
		{
		}


};


// Static data instances
template<typename DESC>
DESC Constructor<DESC>::Desc;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSTRUCTOR_H__
