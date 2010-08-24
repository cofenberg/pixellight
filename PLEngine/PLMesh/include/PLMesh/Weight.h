/*********************************************************\
 *  File: Weight.h                                       *
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


#ifndef __PLMESH_WEIGHT_H__
#define __PLMESH_WEIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMesh/PLMesh.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Weight class
*/
class Weight {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMESH_API Weight();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API ~Weight();

		/**
		*  @brief
		*    Get the weight joint number
		*
		*  @return
		*    Weight joint number, < 0 on error
		*/
		PLMESH_API int GetJoint() const;

		/**
		*  @brief
		*    Sets the weight joint number
		*
		*  @param[in] nJoint
		*    Weight joint number
		*/
		PLMESH_API void SetJoint(int nJoint = -1);

		/**
		*  @brief
		*    Get the weight bias
		*
		*  @return
		*    Weight bias
		*
		*  @remarks
		*    Scale factor for the influence. Usually the weights for all influences for a single
		*    vertex add up to one.
		*/
		PLMESH_API float GetBias() const;

		/**
		*  @brief
		*    Sets the weight bias
		*
		*  @param[in] fBias
		*    Weight bias
		*
		*  @see
		*    - GetBias()
		*/
		PLMESH_API void SetBias(float fBias = 0.0f);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This weight
		*/
		PLMESH_API Weight &operator =(const Weight &cSource);

		/**
		*  @brief
		*    Compares two weights
		*
		*  @param[in] cWeight
		*    Weight to compare with
		*
		*  @return
		*    'true' if both weights are equal, else 'false'
		*/
		PLMESH_API bool operator ==(const Weight &cWeight) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int   m_nJoint;	/**< Joint this weight is for */
		float m_fBias;	/**< Bias factor */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_WEIGHT_H__
