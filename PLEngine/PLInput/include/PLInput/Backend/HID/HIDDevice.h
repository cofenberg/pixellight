/*********************************************************\
 *  File: HIDDevice.h                                    *
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


#ifndef __PLINPUT_HIDDEVICE_H__
#define __PLINPUT_HIDDEVICE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/List.h>
#include "PLInput/Backend/ConnectionDevice.h"
#include "PLInput/Backend/HID/HIDCapability.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Information about a HID device
*/
class HIDDevice : public ConnectionDevice {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HID;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLINPUT_API HIDDevice();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    HIDDevice to copy from
		*/
		PLINPUT_API HIDDevice(const HIDDevice &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API ~HIDDevice();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cSource
		*    HIDDevice to copy from
		*
		*  @return
		*    Reference to this HIDDevice
		*/
		PLINPUT_API HIDDevice &operator =(const HIDDevice &cSource);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSource
		*    HIDDevice to compare with
		*
		*  @return
		*    'true', if both are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const HIDDevice &cSource);

		/**
		*  @brief
		*    Get device name
		*
		*  @return
		*    Device name
		*/
		PLINPUT_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get vendor
		*
		*  @return
		*    Vendor ID
		*/
		PLINPUT_API PLGeneral::uint32 GetVendor() const;

		/**
		*  @brief
		*    Get product
		*
		*  @return
		*    Product ID
		*/
		PLINPUT_API PLGeneral::uint32 GetProduct() const;

		/**
		*  @brief
		*    Get usage
		*
		*  @return
		*    Usage ID
		*/
		PLINPUT_API PLGeneral::uint16 GetUsage() const;

		/**
		*  @brief
		*    Get usage page
		*
		*  @return
		*    Usage page ID
		*/
		PLINPUT_API PLGeneral::uint16 GetUsagePage() const;

		/**
		*  @brief
		*    Get input button controls
		*
		*  @return
		*    List of input button controls
		*/
		const PLGeneral::List<HIDCapability> &GetInputButtons() const;

		/**
		*  @brief
		*    Get input value controls
		*
		*  @return
		*    List of input value controls
		*/
		const PLGeneral::List<HIDCapability> &GetInputValues() const;

		/**
		*  @brief
		*    Get output value controls
		*
		*  @return
		*    List of output value controls
		*/
		const PLGeneral::List<HIDCapability> &GetOutputValues() const;

		/**
		*  @brief
		*    Parse input report
		*
		*  @param[in] pInputReport
		*    HID input report
		*  @param[in] nSize
		*    Size of input report (in bytes)
		*/
		void ParseInputReport(const PLGeneral::uint8 *pInputReport, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Send HID output report
		*
		*  @remarks
		*    This function will send an output report including the current values of all
		*    output values of the device. Use this to update e.g. LEDs or rumble effects.
		*/
		virtual void SendOutputReport();


	//[-------------------------------------------------------]
	//[ Protected virtual HIDDevice functions                 ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Parse HID input report
		*
		*  @param[in] pInputReport
		*    HID input report
		*  @param[in] nSize
		*    Size of input report (in bytes)
		*
		*  @remarks
		*    Implement this function to parse an input report using system specific
		*    functions (e.g. Windows HID API). This method will be called automatically
		*    by ParseInputReport.
		*/
		virtual void ParseInputReportData(const PLGeneral::uint8 *pInputReport, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Send HID output report
		*
		*  @remarks
		*    Implement this function to create an output report including the values of all
		*    output values using system specific functions (e.g. Windows HID API). This method
		*    will be called automatically by SendOutputReport.
		*/
		virtual void SendOutputReportData();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Device data
		PLGeneral::String m_sName;							/**< Device name */
		PLGeneral::uint32 m_nVendor;						/**< Vendor ID */
		PLGeneral::uint32 m_nProduct;						/**< Product ID */

		// Device capabilities
		PLGeneral::uint16 m_nUsagePage;						/**< Device usage page */
		PLGeneral::uint16 m_nUsage;							/**< Device usage */
		PLGeneral::uint16 m_nFeatureReportByteLength;		/**< Feature report byte length */
		PLGeneral::uint16 m_nNumberLinkCollectionNodes;		/**< Number of link collection nodes */
		PLGeneral::uint16 m_nNumberInputButtonCaps;			/**< Number of input buttons */
		PLGeneral::uint16 m_nNumberInputValueCaps;			/**< Number of input values */
		PLGeneral::uint16 m_nNumberInputDataIndices;		/**< Number of input data indices */
		PLGeneral::uint16 m_nNumberOutputButtonCaps;		/**< Number of output buttons */
		PLGeneral::uint16 m_nNumberOutputValueCaps;			/**< Number of output values */
		PLGeneral::uint16 m_nNumberOutputDataIndices;		/**< Number of output data indices */
		PLGeneral::uint16 m_nNumberFeatureButtonCaps;		/**< Number of feature buttons */
		PLGeneral::uint16 m_nNumberFeatureValueCaps;		/**< Number of feature values */
		PLGeneral::uint16 m_nNumberFeatureDataIndices;		/**< Number of feature data indices */

		// Controls
		PLGeneral::List<HIDCapability> m_lstInputButtons;	/**< List of input buttons */
		PLGeneral::List<HIDCapability> m_lstInputValues;	/**< List of input values */
		PLGeneral::List<HIDCapability> m_lstOutputValues;	/**< List of output values */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_HIDDEVICE_H__
