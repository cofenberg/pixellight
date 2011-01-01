/*********************************************************\
 *  File: ImagePalette.cpp                               *
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
#include "PLGraphics/Image/ImagePalette.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImagePalette::ImagePalette() :
	m_pData(NULL),
	m_nSize(0),
	m_nColors(0)
{
}

/**
*  @brief
*    Copy constructor
*/
ImagePalette::ImagePalette(const ImagePalette &cSource) :
	m_pData(NULL),
	m_nSize(0),
	m_nColors(0)
{
	// Copy palette
	if (cSource.m_nSize > 0 && cSource.m_pData) {
		// Create buffer
		m_nSize   = cSource.m_nSize;
		m_nColors = cSource.m_nColors;
		m_pData   = new uint8[m_nSize*3];

		// Copy data
		MemoryManager::Copy(m_pData, cSource.m_pData, m_nSize*3);
	}
}

/**
*  @brief
*    Destructor
*/
ImagePalette::~ImagePalette()
{
	// Clear data
	Clear();
}

/**
*  @brief
*    Assignment operator
*/
ImagePalette &ImagePalette::operator =(const ImagePalette &cSource)
{
	// Clear data
	Clear();

	// Copy palette
	if (cSource.m_nSize > 0 && cSource.m_pData) {
		// Create buffer
		m_nSize   = cSource.m_nSize;
		m_nColors = cSource.m_nColors;
		m_pData   = new uint8[m_nSize*3];

		// Copy data
		MemoryManager::Copy(m_pData, cSource.m_pData, m_nSize*3);
	}

	// Return this
	return *this;
}

/**
*  @brief
*    Clear data
*/
void ImagePalette::Clear()
{
	// Delete palette
	if (m_pData) {
		delete [] m_pData;
	}

	// Reset data
	m_pData   = NULL;
	m_nSize   = 0;
	m_nColors = 0;
	m_mapColors.Clear();
}

/**
*  @brief
*    Create palette
*/
void ImagePalette::Create(uint32 nColors)
{
	// Clear palette
	Clear();

	// Check if size is valid
	if (nColors > 0) {
		// Get size as nearest multiple of 256
		m_nSize = nColors / 256;
		if (nColors % 256 > 0)
			m_nSize ++;
		m_nSize *= 256;

		// Create palette data
		m_pData   = new uint8[m_nSize*3];
		m_nColors = nColors;
		MemoryManager::Set(m_pData, 0, m_nSize*3);
	}
}

/**
*  @brief
*    Get number of colors
*/
uint32 ImagePalette::GetNumOfColors() const
{
	// Return number of colors
	return m_nColors;
}

/**
*  @brief
*    Get color
*/
Color3 ImagePalette::GetColor(uint32 nIndex) const
{
	// Is index valid?
	if (nIndex < m_nColors) {
		return Color3(m_pData[nIndex*3], m_pData[nIndex*3+1], m_pData[nIndex*3+2]);
	}

	// Invalid index
	return Color3::Null;
}

/**
*  @brief
*    Get index of color
*/
int ImagePalette::GetColorIndex(const Color3 &cColor) const
{
	// Do we need to build the color index?
	if (m_mapColors.GetNumOfElements() == 0) {
		// Build color index
		for (uint32 i=0; i<m_nColors; i++) {
			// Map color to index
			const uint32 nColorInt = cColor.ToUInt32();
			m_mapColors.Add(nColorInt, i);
		}
	}

	// Look up color index
	const uint32 nColorInt = cColor.ToUInt32();
	int nIndex = m_mapColors.Get(nColorInt);

	// If nIndex is 0, it can be either invalid or really index 0, so check if the colors are equal
	if (nIndex == 0) {
		// Check if color is valid
		const Color3 cColorLookup = GetColor(0);
		if (cColorLookup != cColor || cColorLookup == Color3::Null) {
			// Invalid index
			nIndex = -1;
		}
	}

	// Return color index
	return nIndex;
}

/**
*  @brief
*    Set color
*/
void ImagePalette::SetColor(uint32 nIndex, const Color3 &cColor)
{
	// Do we have to resize the palette?
	if (nIndex >= m_nColors)
		Resize(nIndex);

	// Set color
	if (m_pData) {
		m_pData[nIndex*3+0] = cColor.GetRInt();
		m_pData[nIndex*3+1] = cColor.GetGInt();
		m_pData[nIndex*3+2] = cColor.GetBInt();
	}

	// Rebuild color index
	RebuildColorIndex();
}

/**
*  @brief
*    Add color
*/
uint32 ImagePalette::AddColor(const Color3 &cColor)
{
	// Add color to next free place in palette
	const uint32 nIndex = m_nColors;
	SetColor(nIndex, cColor);

	// Return color index
	return nIndex;
}

/**
*  @brief
*    Rebuild color index
*/
void ImagePalette::RebuildColorIndex()
{
	// Clear hash map. It will be rebuilt next time GetColorIndex() is called
	m_mapColors.Clear();
}

/**
*  @brief
*    Get color palette data
*/
uint8 *ImagePalette::GetData() const
{
	// Return palette data
	return m_pData;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Resize palette
*/
void ImagePalette::Resize(uint32 nColors)
{
	// Check if size is valid
	if (nColors > 0) {
		// Get size as nearest multiple of 256
		uint32 nSize = nColors / 256;
		if (nColors % 256 > 0)
			nSize++;
		nSize *= 256;

		// Resize if new size is bigger than old size
		if (nSize > m_nSize) {
			// Create new palette
			uint8 *pData = new uint8[nSize*3];
			MemoryManager::Set(pData, 0, nSize*3);

			// Copy old palette
			if (m_pData != NULL) {
				// Copy old palette data
				if (m_nSize > 0)
					MemoryManager::Copy(pData, m_pData, m_nSize*3);

				// Destroy old palette data
				delete [] m_pData;
			}

			// Set new data
			m_pData = pData;
			m_nSize = nSize;
		}

		// Set new number of colors
		m_nColors = nColors;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
