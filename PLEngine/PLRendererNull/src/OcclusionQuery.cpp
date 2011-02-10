/*********************************************************\
 *  File: OcclusionQuery.cpp                             *
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
#include "PLRendererNull/OcclusionQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRendererNull {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
OcclusionQuery::~OcclusionQuery()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OcclusionQuery::OcclusionQuery(PLRenderer::Renderer &cRenderer) : PLRenderer::OcclusionQuery(cRenderer),
	m_nSkipRate(0),
	m_nMinFragments(0),
	m_nPixelCount(0)
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::OcclusionQuery functions   ]
//[-------------------------------------------------------]
bool OcclusionQuery::BeginOcclusionQuery()
{
	// Error!
	return false;
}

void OcclusionQuery::EndOcclusionQuery()
{
}

bool OcclusionQuery::PullOcclusionQuery(uint32 *pnNumOfFragments)
{
	m_nPixelCount = 0;
	if (pnNumOfFragments)
		*pnNumOfFragments = m_nPixelCount;

	// Done
	return true;
}

uint32 OcclusionQuery::GetLastQuerysPixelCount() const
{
	return m_nPixelCount;
}

uint32 OcclusionQuery::GetSkipRate() const
{
	return m_nSkipRate;
}

void OcclusionQuery::SetSkipRate(uint32 nRate)
{
	m_nSkipRate = nRate;
}

uint32 OcclusionQuery::GetMinFragments() const
{
	return m_nMinFragments;
}

void OcclusionQuery::SetMinFragments(uint32 nMinFragments)
{
	m_nMinFragments = nMinFragments;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererNull
