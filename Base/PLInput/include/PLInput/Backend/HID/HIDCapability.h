/*********************************************************\
 *  File: HIDCapability.h                                *
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


#ifndef __PLINPUT_HIDCAPABILITY_H__
#define __PLINPUT_HIDCAPABILITY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Capability of a HID device
*/
class HIDCapability {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API HIDCapability();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Capability to copy from
		*/
		PLINPUT_API HIDCapability(const HIDCapability &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API ~HIDCapability();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    Capability to copy from
		*
		*  @return
		*    Reference to this HIDCapability
		*/
		PLINPUT_API HIDCapability &operator =(const HIDCapability &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    Capability to compare with
		*
		*  @return
		*    'true' if both are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const HIDCapability &cSource) const;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		// Capability info
		PLCore::uint8  m_nReportID;			/**< Report ID */
		PLCore::uint16 m_nLinkCollection;	/**< Link collection */
		PLCore::uint16 m_nUsagePage;		/**< Usage page ID */
		PLCore::uint16 m_nUsage;			/**< Usage ID */
		PLCore::uint16 m_nUsageMin;			/**< Usage ID minimum */
		PLCore::uint16 m_nUsageMax;			/**< Usage ID maximum */
		PLCore::uint16 m_nDataIndex;		/**< Data index (index in input report - NOT byte index!) */
		PLCore::uint16 m_nDataIndexMin;		/**< Data index minimum */
		PLCore::uint16 m_nDataIndexMax;		/**< Data index maximum */
		PLCore::uint16 m_nBitSize;			/**< Size of data in bits */
		PLCore::uint16 m_nLogicalMin;		/**< Logical minimum value (e.g. for axes) */
		PLCore::uint16 m_nLogicalMax;		/**< Logical maximum value (e.g. for axes) */
		PLCore::uint16 m_nPhysicalMin;		/**< Physical minimum value (e.g. for axes) */
		PLCore::uint16 m_nPhysicalMax;		/**< Physical maximum value (e.g. for axes) */

		// Current data value
		PLCore::uint32 m_nValue;			/**< Current value of input data */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_HIDCAPABILITY_H__
