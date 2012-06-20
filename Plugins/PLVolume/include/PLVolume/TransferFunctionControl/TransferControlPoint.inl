/*********************************************************\
 *  File: TransferControlPoint.inl                       *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
inline TransferControlPoint::TransferControlPoint() :
	m_nIsoValue(0),
	m_fValue(0.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
inline TransferControlPoint::TransferControlPoint(const TransferControlPoint &cSource) :
	m_nIsoValue(cSource.m_nIsoValue),
	m_fValue(cSource.m_fValue)
{
}

/**
*  @brief
*    Constructor for iso-value + value
*/
inline TransferControlPoint::TransferControlPoint(PLCore::uint32 nIsoValue, float fValue) :
	m_nIsoValue(nIsoValue),
	m_fValue(fValue)
{
}

/**
*  @brief
*    Destructor
*/
inline TransferControlPoint::~TransferControlPoint()
{
}

/**
*  @brief
*    Copy operator
*/
inline TransferControlPoint &TransferControlPoint::operator =(const TransferControlPoint &cSource)
{
	// Copy data
	m_nIsoValue = cSource.m_nIsoValue;
	m_fValue    = cSource.m_fValue;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
inline bool TransferControlPoint::operator ==(const TransferControlPoint &cOther) const
{
	// Compare data (no epsilon environment in here)
	return (m_nIsoValue == cOther.m_nIsoValue && m_fValue == cOther.m_fValue);
}

/**
*  @brief
*    Returns the iso-value
*/
inline PLCore::uint32 TransferControlPoint::GetIsoValue() const
{
	return m_nIsoValue;
}

/**
*  @brief
*    Sets the iso-value
*/
inline void TransferControlPoint::SetIsoValue(PLCore::uint32 nIsoValue)
{
	m_nIsoValue = nIsoValue;
}

/**
*  @brief
*    Returns the value
*/
float TransferControlPoint::GetValue() const
{
	return m_fValue;
}

/**
*  @brief
*    Sets the value
*/
inline void TransferControlPoint::SetValue(float fValue)
{
	m_fValue = fValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
