/*********************************************************\
 *  File: TransferControlPoint.h                         *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLVOLUME_TRANSFERCONTROLPOINT_H__
#define __PLVOLUME_TRANSFERCONTROLPOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Transfer control point
*/
class TransferControlPoint {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		inline TransferControlPoint();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		inline TransferControlPoint(const TransferControlPoint &cSource);

		/**
		*  @brief
		*    Constructor for iso-value + value
		*
		*  @param[in] nIsoValue
		*    Iso-value (e.g. along x-axis)
		*  @param[in] fValue
		*    Value (e.g. along y-axis)
		*/
		inline TransferControlPoint(PLCore::uint32 nIsoValue, float fValue);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~TransferControlPoint();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		inline TransferControlPoint &operator =(const TransferControlPoint &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Other instance to compare with
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		inline bool operator ==(const TransferControlPoint &cOther) const;

		/**
		*  @brief
		*    Returns the iso-value
		*
		*  @return
		*    The iso-value (e.g. along x-axis)
		*/
		inline PLCore::uint32 GetIsoValue() const;

		/**
		*  @brief
		*    Sets the iso-value
		*
		*  @param[in] nIsoValue
		*    Iso-value (e.g. along x-axis)
		*/
		inline void SetIsoValue(PLCore::uint32 nIsoValue);

		/**
		*  @brief
		*    Returns the value
		*
		*  @return
		*    The value (e.g. along y-axis)
		*/
		inline float GetValue() const;

		/**
		*  @brief
		*    Sets the value
		*
		*  @param[in] fValue
		*    Value to set (e.g. along y-axis)
		*/
		inline void SetValue(float fValue);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::uint32 m_nIsoValue;	/**< Iso-value (e.g. along x-axis) */
		float          m_fValue;	/**< Value (e.g. along y-axis) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLVolume/TransferFunctionControl/TransferControlPoint.inl"


#endif // __PLVOLUME_TRANSFERCONTROLPOINT_H__
