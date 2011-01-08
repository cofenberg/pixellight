/*********************************************************\
 *  File: SizeHint.cpp                                   *
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
#include <PLGeneral/String/RegEx.h>
#include "PLGui/Gui/Data/SizeHint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SizeHint::SizeHint(EPolicy nPolicy, uint32 nSize) :
	m_nPolicy(nPolicy),
	m_fSize((float)nSize)
{
}

/**
*  @brief
*    Copy constructor
*/
SizeHint::SizeHint(const SizeHint &cSizeHint) :
	m_nPolicy(cSizeHint.m_nPolicy),
	m_fSize(cSizeHint.m_fSize)
{
}

/**
*  @brief
*    Destructor
*/
SizeHint::~SizeHint()
{
}

/**
*  @brief
*    Copy operator
*/
SizeHint &SizeHint::operator =(const SizeHint &cSizeHint)
{
	// Copy data
	m_nPolicy	= cSizeHint.m_nPolicy;
	m_fSize		= cSizeHint.m_fSize;
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
bool SizeHint::operator ==(const SizeHint &cSizeHint) const
{
	// Compare data
	return (m_nPolicy == cSizeHint.m_nPolicy && m_fSize == cSizeHint.m_fSize);
}

/**
*  @brief
*    Get size policy
*/
SizeHint::EPolicy SizeHint::GetPolicy() const
{
	// Return policy
	return m_nPolicy;
}

/**
*  @brief
*    Set size policy
*/
void SizeHint::SetPolicy(EPolicy nPolicy)
{
	// Set policy
	m_nPolicy = nPolicy;
}

/**
*  @brief
*    Get size
*/
uint32 SizeHint::GetSize() const
{
	// Return size
	return (uint32)m_fSize;
}

/**
*  @brief
*    Get size in float
*/
float SizeHint::GetSizeFloat() const
{
	// Return size
	return m_fSize;
}

/**
*  @brief
*    Set size
*/
void SizeHint::SetSize(uint32 nSize)
{
	// Set size
	m_fSize = (float)nSize;
}

/**
*  @brief
*    Set size in float
*/
void SizeHint::SetSizeFloat(float fSize)
{
	// Set size
	m_fSize = fSize;
}

/**
*  @brief
*    Set policy and size
*/
void SizeHint::Set(EPolicy nPolicy, uint32 nSize)
{
	// Set policy
	m_nPolicy = nPolicy;

	// Set size
	m_fSize = (float)nSize;
}

/**
*  @brief
*    Set policy and size in float
*/
void SizeHint::SetFloat(EPolicy nPolicy, float fSize)
{
	// Set policy
	m_nPolicy = nPolicy;

	// Set size
	m_fSize = fSize;
}

/**
*  @brief
*    Calculate actual size specified by this size hint
*/
int SizeHint::CalculateSize(uint32 nParentSize, int nPreferredSize) const
{
	// Calculate size
		 if (m_nPolicy == Pixel)							return (int)m_fSize;
	else if (m_nPolicy == Percent)							return (int)((m_fSize / 100.0f) * nParentSize);
	else if (m_nPolicy == Preferred && nPreferredSize > -1)	return nPreferredSize;
	else													return -1;
}

/**
*  @brief
*    To string
*/
String SizeHint::ToString() const
{
	// Get policy
	switch (m_nPolicy) {
		// Pixel
		case Pixel:
			return PLGeneral::String() + (int)m_fSize + "px";

		// Percent
		case Percent:
			return PLGeneral::String() + m_fSize + "%";

		// Preferred
		case Preferred:
			return "preferred";

		// Floating
		case Floating:
		default:
			return "floating";
	}
}

/**
*  @brief
*    From string
*/
bool SizeHint::FromString(const String &sString)
{
	// Get policy
	if (sString == "floating") {
		// Floating
		m_nPolicy = Floating;
		m_fSize	  = 0.0f;
	} else if (sString == "preferred") {
		// Preferred
		m_nPolicy = Preferred;
		m_fSize	  = 0.0f;
	} else {
		// Pixel or Percent?
		static PLGeneral::RegEx cRegEx("\\s*([-+]?\\d*\\.?\\d+)\\s*(px|\\%)");
		if (cRegEx.Match(sString)) {
			// Pixel or Percent!
			PLGeneral::String sSize   = cRegEx.GetResult(0);
			PLGeneral::String sPolicy = cRegEx.GetResult(1);
			m_nPolicy = (sPolicy == "px" ? Pixel : Percent);
			m_fSize   = sSize.GetFloat();
		} else if (sString.GetFloat() > 0.0f) {
			// Just a number
			m_nPolicy = Pixel;
			m_fSize   = sString.GetFloat();
		} else {
			// Invalid
			return false;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
