/*********************************************************\
 *  File: Attribute.h                                    *
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


#ifndef __PLCORE_ATTRIBUTE_H__
#define __PLCORE_ATTRIBUTE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Var/Var.h"
#include "PLCore/Base/Var/VarDesc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Attribute of a class
*
*  @remarks
*    This class template represents attributes (variables that belong to objects).
*/
template <typename T, typename ACCESS, typename STORAGE, typename DESC>
class Attribute : public Var<T, ACCESS, STORAGE> {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Storage type
		typedef typename Type<T>::_Type _Type;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static DESC	Desc;	/**< Attribute descriptor */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] DefaultValue
		*    Default value for the attribute
		*  @param[in] pObject
		*    Pointer to object to which the attribute belongs
		*/
		Attribute(_Type DefaultValue, Object *pObject) : Var<T, ACCESS, STORAGE>(DefaultValue, pObject)
		{
			Desc.Dummy();
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Attribute()
		{
		}

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] Value
		*    New value
		*
		*  @remarks
		*    Unfortunatly, it is necessary to define assignment operators in the 'leaf'-classes,
		*    as they are not inherited from base classes. So we have to define it here and then
		*    call the implementation in the base class, which makes everything a bit more complicated
		*/
		Attribute &operator =(const _Type &Value)
		{
			// Call base implementation
			return static_cast<Attribute&>(Var<T, ACCESS, STORAGE>::operator =(Value));
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynVar functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get var descriptor
		*
		*  @return
		*    Var descriptor
		*/
		virtual const VarDesc *GetDesc() const
		{
			// Return descriptor
			return &Desc;
		}


};


// Static data instances
template<typename T, typename ACCESS, typename STORAGE, typename DESC>
DESC Attribute<T, ACCESS, STORAGE, DESC>::Desc;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_ATTRIBUTE_H__
