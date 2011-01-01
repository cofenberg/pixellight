/*********************************************************\
 *  File: HIDDevice.cpp                                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/HID/HIDDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
HIDDevice::HIDDevice() :
	m_nVendor(0),
	m_nProduct(0),
	m_nUsage(0),
	m_nUsagePage(0),
	m_nFeatureReportByteLength(0),
	m_nNumberLinkCollectionNodes(0),
	m_nNumberInputButtonCaps(0),
	m_nNumberInputValueCaps(0),
	m_nNumberInputDataIndices(0),
	m_nNumberOutputButtonCaps(0),
	m_nNumberOutputValueCaps(0),
	m_nNumberOutputDataIndices(0),
	m_nNumberFeatureButtonCaps(0),
	m_nNumberFeatureValueCaps(0),
	m_nNumberFeatureDataIndices(0)
{
	// Set backend type
	m_nBackendType = BackendHID;

	// Set device type
	m_nDeviceType = ConnectionDevice::DeviceTypeHID;
}

/**
*  @brief
*    Copy constructor
*/
HIDDevice::HIDDevice(const HIDDevice &cSource) :
	m_sName(cSource.m_sName),
	m_nVendor(cSource.m_nVendor),
	m_nProduct(cSource.m_nProduct),
	m_nUsage(cSource.m_nUsage),
	m_nUsagePage(cSource.m_nUsagePage),
	m_nFeatureReportByteLength(cSource.m_nFeatureReportByteLength),
	m_nNumberLinkCollectionNodes(cSource.m_nNumberLinkCollectionNodes),
	m_nNumberInputButtonCaps(cSource.m_nNumberInputButtonCaps),
	m_nNumberInputValueCaps(cSource.m_nNumberInputValueCaps),
	m_nNumberInputDataIndices(cSource.m_nNumberInputDataIndices),
	m_nNumberOutputButtonCaps(cSource.m_nNumberOutputButtonCaps),
	m_nNumberOutputValueCaps(cSource.m_nNumberOutputValueCaps),
	m_nNumberOutputDataIndices(cSource.m_nNumberOutputDataIndices),
	m_nNumberFeatureButtonCaps(cSource.m_nNumberFeatureButtonCaps),
	m_nNumberFeatureValueCaps(cSource.m_nNumberFeatureValueCaps),
	m_nNumberFeatureDataIndices(cSource.m_nNumberFeatureDataIndices),
	m_lstInputButtons(cSource.m_lstInputButtons),
	m_lstInputValues(cSource.m_lstInputValues),
	m_lstOutputValues(cSource.m_lstOutputValues)
{
	// Set device type
	m_nDeviceType = ConnectionDevice::DeviceTypeHID;

	// Set input and output report sizes
	m_nInputReportSize  = cSource.m_nInputReportSize;
	m_nOutputReportSize = cSource.m_nOutputReportSize;
}

/**
*  @brief
*    Destructor
*/
HIDDevice::~HIDDevice()
{
}

/**
*  @brief
*    Assignment operator
*/
HIDDevice &HIDDevice::operator =(const HIDDevice &cSource)
{
	m_sName							= cSource.m_sName;
	m_nVendor						= cSource.m_nVendor;
	m_nProduct						= cSource.m_nProduct;
	m_nUsage						= cSource.m_nUsage;
	m_nUsagePage					= cSource.m_nUsagePage;
	m_nInputReportSize				= cSource.m_nInputReportSize;
	m_nOutputReportSize				= cSource.m_nOutputReportSize;
	m_nFeatureReportByteLength		= cSource.m_nFeatureReportByteLength;
	m_nNumberLinkCollectionNodes	= cSource.m_nNumberLinkCollectionNodes;
	m_nNumberInputButtonCaps		= cSource.m_nNumberInputButtonCaps;
	m_nNumberInputValueCaps			= cSource.m_nNumberInputValueCaps;
	m_nNumberInputDataIndices		= cSource.m_nNumberInputDataIndices;
	m_nNumberOutputButtonCaps		= cSource.m_nNumberOutputButtonCaps;
	m_nNumberOutputValueCaps		= cSource.m_nNumberOutputValueCaps;
	m_nNumberOutputDataIndices		= cSource.m_nNumberOutputDataIndices;
	m_nNumberFeatureButtonCaps		= cSource.m_nNumberFeatureButtonCaps;
	m_nNumberFeatureValueCaps		= cSource.m_nNumberFeatureValueCaps;
	m_nNumberFeatureDataIndices		= cSource.m_nNumberFeatureDataIndices;
	m_lstInputButtons				= cSource.m_lstInputButtons;
	m_lstInputValues				= cSource.m_lstInputValues;
	m_lstOutputValues				= cSource.m_lstOutputValues;
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool HIDDevice::operator ==(const HIDDevice &cSource)
{
	return (m_nVendor						== cSource.m_nVendor &&
			m_nProduct						== cSource.m_nProduct &&
			m_nUsage						== cSource.m_nUsage &&
			m_nUsagePage					== cSource.m_nUsagePage &&
			m_nInputReportSize				== cSource.m_nInputReportSize &&
			m_nOutputReportSize				== cSource.m_nOutputReportSize &&
			m_nFeatureReportByteLength		== cSource.m_nFeatureReportByteLength &&
			m_nNumberLinkCollectionNodes	== cSource.m_nNumberLinkCollectionNodes &&
			m_nNumberInputButtonCaps		== cSource.m_nNumberInputButtonCaps &&
			m_nNumberInputValueCaps			== cSource.m_nNumberInputValueCaps &&
			m_nNumberInputDataIndices		== cSource.m_nNumberInputDataIndices &&
			m_nNumberOutputButtonCaps		== cSource.m_nNumberOutputButtonCaps &&
			m_nNumberOutputValueCaps		== cSource.m_nNumberOutputValueCaps &&
			m_nNumberOutputDataIndices		== cSource.m_nNumberOutputDataIndices &&
			m_nNumberFeatureButtonCaps		== cSource.m_nNumberFeatureButtonCaps &&
			m_nNumberFeatureValueCaps		== cSource.m_nNumberFeatureValueCaps &&
			m_nNumberFeatureDataIndices		== cSource.m_nNumberFeatureDataIndices &&
			m_lstInputButtons				== cSource.m_lstInputButtons &&
			m_lstInputValues				== cSource.m_lstInputValues &&
			m_lstOutputValues				== cSource.m_lstOutputValues);
}

/**
*  @brief
*    Get device name
*/
String HIDDevice::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Get vendor
*/
uint32 HIDDevice::GetVendor() const
{
	return m_nVendor;
}

/**
*  @brief
*    Get product
*/
uint32 HIDDevice::GetProduct() const
{
	return m_nProduct;
}

/**
*  @brief
*    Get usage
*/
uint16 HIDDevice::GetUsage() const
{
	return m_nUsage;
}

/**
*  @brief
*    Get usage page
*/
uint16 HIDDevice::GetUsagePage() const
{
	return m_nUsagePage;
}

/**
*  @brief
*    Get input button controls
*/
const List<HIDCapability> &HIDDevice::GetInputButtons() const
{
	return m_lstInputButtons;
}

/**
*  @brief
*    Get input value controls
*/
const List<HIDCapability> &HIDDevice::GetInputValues() const
{
	return m_lstInputValues;
}

/**
*  @brief
*    Get output value controls
*/
const List<HIDCapability> &HIDDevice::GetOutputValues() const
{
	return m_lstOutputValues;
}

/**
*  @brief
*    Parse input report
*/
void HIDDevice::ParseInputReport(const uint8 *pInputReport, uint32 nSize)
{
	// Call system specific backend function to parse input report data
	ParseInputReportData(pInputReport, nSize);

	// [TODO]
	// This function should contain an own implementation to parse the input report rather than
	// relying on system-specific APIs. However, my attempt to implement one failed because the data indices
	// seem to be awkward and I can't see how to parse the data items correctly. So, let's stick with this
	// for a while, until someone with time and knowledge takes the challenge :-)
}

/**
*  @brief
*    Send HID output report
*/
void HIDDevice::SendOutputReport()
{
	// Call system specific backend function
	SendOutputReportData();

	// [TODO]
	// This function should contain an own implementation rather than relying on system-specific APIs
}


//[-------------------------------------------------------]
//[ Protected virtual HIDDevice functions                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parse HID input report
*/
void HIDDevice::ParseInputReportData(const uint8 *pInputReport, uint32 nSize)
{
	// To be implemented in derived classes
}

/**
*  @brief
*    Send HID output report
*/
void HIDDevice::SendOutputReportData()
{
	// To be implemented in derived classes
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
