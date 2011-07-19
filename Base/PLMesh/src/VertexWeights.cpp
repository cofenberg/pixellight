/*********************************************************\
 *  File: VertexWeights.cpp                              *
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
#include "PLMesh/VertexWeights.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLMesh {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
VertexWeights::VertexWeights()
{
}

/**
*  @brief
*    Destructor
*/
VertexWeights::~VertexWeights()
{
}

/**
*  @brief
*    Get the vertex weight indices index array
*/
Array<uint32> &VertexWeights::GetWeights()
{
	return m_lstWeights;
}

const Array<uint32> &VertexWeights::GetWeights() const
{
	return m_lstWeights;
}

/**
*  @brief
*    Copy operator
*/
VertexWeights &VertexWeights::operator =(const VertexWeights &cSource)
{
	// Copy data
	m_lstWeights = cSource.m_lstWeights;

	// Return pointer
	return *this;
}

/**
*  @brief
*    Compares two vertex weights
*/
bool VertexWeights::operator ==(const VertexWeights &cVertexWeights) const
{
	return (m_lstWeights == cVertexWeights.m_lstWeights);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh
