/*********************************************************\
 *  File: HIDCapability.cpp                              *
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
#include "PLInput/Backend/HID/HIDCapability.h"


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
HIDCapability::HIDCapability() :
	m_nReportID(0),
	m_nLinkCollection(0),
	m_nUsagePage(0),
	m_nUsage(0),
	m_nUsageMin(0),
	m_nUsageMax(0),
	m_nDataIndex(0),
	m_nDataIndexMin(0),
	m_nDataIndexMax(0),
	m_nBitSize(0),
	m_nLogicalMin(0),
	m_nLogicalMax(0),
	m_nPhysicalMin(0),
	m_nPhysicalMax(0),
	m_nValue(0)
{
}

/**
*  @brief
*    Copy constructor
*/
HIDCapability::HIDCapability(const HIDCapability &cSource) :
	m_nReportID(cSource.m_nReportID),
	m_nLinkCollection(cSource.m_nLinkCollection),
	m_nUsagePage(cSource.m_nUsagePage),
	m_nUsage(cSource.m_nUsage),
	m_nUsageMin(cSource.m_nUsageMin),
	m_nUsageMax(cSource.m_nUsageMax),
	m_nDataIndex(cSource.m_nDataIndex),
	m_nDataIndexMin(cSource.m_nDataIndexMin),
	m_nDataIndexMax(cSource.m_nDataIndexMax),
	m_nBitSize(cSource.m_nBitSize),
	m_nLogicalMin(cSource.m_nLogicalMin),
	m_nLogicalMax(cSource.m_nLogicalMax),
	m_nPhysicalMin(cSource.m_nPhysicalMin),
	m_nPhysicalMax(cSource.m_nPhysicalMax),
	m_nValue(cSource.m_nValue)
{
}

/**
*  @brief
*    Destructor
*/
HIDCapability::~HIDCapability()
{
}

/**
*  @brief
*    Assignment operator
*/
HIDCapability &HIDCapability::operator =(const HIDCapability &cSource)
{
	m_nReportID			= cSource.m_nReportID;
	m_nLinkCollection	= cSource.m_nLinkCollection;
	m_nUsagePage		= cSource.m_nUsagePage;
	m_nUsage			= cSource.m_nUsage;
	m_nUsageMin			= cSource.m_nUsageMin;
	m_nUsageMax			= cSource.m_nUsageMax;
	m_nDataIndex		= cSource.m_nDataIndex;
	m_nDataIndexMin		= cSource.m_nDataIndexMin;
	m_nDataIndexMax		= cSource.m_nDataIndexMax;
	m_nBitSize			= cSource.m_nBitSize;
	m_nLogicalMin		= cSource.m_nLogicalMin;
	m_nLogicalMax		= cSource.m_nLogicalMax;
	m_nPhysicalMin		= cSource.m_nPhysicalMin;
	m_nPhysicalMax		= cSource.m_nPhysicalMax;
	m_nValue			= cSource.m_nValue;
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool HIDCapability::operator ==(const HIDCapability &cSource) const
{
	return (m_nReportID	== cSource.m_nReportID &&  m_nLinkCollection == cSource.m_nLinkCollection &&
			m_nUsagePage == cSource.m_nUsagePage && m_nUsage == cSource.m_nUsage &&
			m_nUsageMin == cSource.m_nUsageMin && m_nUsageMax == cSource.m_nUsageMax &&
			m_nDataIndex == cSource.m_nDataIndex && m_nDataIndexMin == cSource.m_nDataIndexMin && m_nDataIndexMax == cSource.m_nDataIndexMax &&
			m_nBitSize == cSource.m_nBitSize && m_nLogicalMin == cSource.m_nLogicalMin &&
			m_nLogicalMax == cSource.m_nLogicalMax && m_nPhysicalMin == cSource.m_nPhysicalMin &&
			m_nPhysicalMax == cSource.m_nPhysicalMax && m_nValue == cSource.m_nValue);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
