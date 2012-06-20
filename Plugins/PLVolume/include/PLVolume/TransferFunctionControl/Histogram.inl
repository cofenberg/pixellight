/*********************************************************\
 *  File: Histogram.inl                                  *
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
inline Histogram::Histogram() :
	m_fMinScalarValue(0.0f),
	m_fMaxScalarValue(0.0f),
	m_fMinValue(-1.0f),
	m_fMaxValue(-1.0f),
	m_nBinWithHighestValue(-1),
	m_bNormalized(false)
{
}

/**
*  @brief
*    Copy constructor
*/
inline Histogram::Histogram(const Histogram &cSource) :
	m_lstData(cSource.m_lstData),
	m_fMinScalarValue(cSource.m_fMinScalarValue),
	m_fMaxScalarValue(cSource.m_fMaxScalarValue),
	m_fMinValue(cSource.m_fMinValue),
	m_fMaxValue(cSource.m_fMaxValue),
	m_nBinWithHighestValue(cSource.m_nBinWithHighestValue),
	m_bNormalized(cSource.m_bNormalized)
{
}

/**
*  @brief
*    Destructor
*/
inline Histogram::~Histogram()
{
}

/**
*  @brief
*    Constructor, creates the histogram data from luminance data (= one component per element)
*/
inline Histogram::Histogram(PLCore::uint32 nNumOfBytesPerElement, PLCore::uint32 nNumOfElements, const PLCore::uint8 *pnData)
{
	// Create the histogram data from luminance data (= one component per element)
	Create(nNumOfBytesPerElement, nNumOfElements, pnData);
}

/**
*  @brief
*    Copy operator
*/
inline Histogram &Histogram::operator =(const Histogram &cSource)
{
	// Copy data
	m_lstData				= cSource.m_lstData;
	m_fMinScalarValue		= cSource.m_fMinScalarValue;
	m_fMaxScalarValue		= cSource.m_fMaxScalarValue;
	m_fMinValue				= cSource.m_fMinValue;
	m_fMaxValue				= cSource.m_fMaxValue;
	m_nBinWithHighestValue	= cSource.m_nBinWithHighestValue;
	m_bNormalized			= cSource.m_bNormalized;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Returns the number of bins
*/
inline PLCore::uint32 Histogram::GetNumOfBins() const
{
	return m_lstData.GetNumOfElements();
}

/**
*  @brief
*    Returns the minimum value encountered while creating the histogram
*/
inline float Histogram::GetMinScalarValue() const
{
	return m_fMinScalarValue;
}

/**
*  @brief
*    Returns the maximum value encountered while creating the histogram
*/
inline float Histogram::GetMaxScalarValue() const
{
	return m_fMaxScalarValue;
}

/**
*  @brief
*    Returns the maximum value within the histogram
*/
inline float Histogram::GetMaxValue()
{
	// This initializes the value, if required
	if (m_fMinValue < 0.0f)
		GetMinValue();

	// Done
	return m_fMaxValue;
}

/**
*  @brief
*    List containing the histogram data
*/
inline const PLCore::Array<float> &Histogram::GetData() const
{
	return m_lstData;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
