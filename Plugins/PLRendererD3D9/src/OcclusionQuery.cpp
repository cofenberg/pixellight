/*********************************************************\
 *  File: OcclusionQuery.cpp                             *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererD3D9/Renderer.h"
#include "PLRendererD3D9/OcclusionQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
OcclusionQuery::~OcclusionQuery()
{
	// Destroy Direct3D9 occlusion query
	if (m_pQuery)
		m_pQuery->Release();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
OcclusionQuery::OcclusionQuery(PLRenderer::Renderer &cRenderer) : PLRenderer::OcclusionQuery(cRenderer),
	m_pQuery(nullptr),
	m_nSkipRate(0),
	m_nSkipCounter(0),
	m_nMinFragments(0),
	m_nPixelCount(100000)
{
	// Check if there are renderer information
	LPDIRECT3DDEVICE9 pDevice = static_cast<Renderer&>(cRenderer).GetDevice();
	if (pDevice) {
		// Create Direct3D9 occlusion query
		if (pDevice->CreateQuery(D3DQUERYTYPE_OCCLUSION, &m_pQuery) == D3D_OK)
			m_bHWOcclusionSupport = true;
		else
			m_bHWOcclusionSupport = false;
	} else {
		m_bHWOcclusionSupport = false;
	}
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::OcclusionQuery functions   ]
//[-------------------------------------------------------]
bool OcclusionQuery::BeginOcclusionQuery()
{
	// Check whether hardware occlusion query is supported or not
	if (m_bHWOcclusionSupport) {
		// Update the skip counter
		m_nSkipCounter++;
		if (m_nSkipCounter >= m_nSkipRate)
			m_nSkipCounter = 0;

		// New or none visible objects must always be tested but visible objects can be skipped
		if (!m_nSkipCounter || m_nPixelCount <= m_nMinFragments) {
			m_pQuery->Issue(D3DISSUE_BEGIN);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

void OcclusionQuery::EndOcclusionQuery()
{
	// Check whether hardware occlusion query is supported or not
	if (m_bHWOcclusionSupport) {
		// New or none visible objects must always be tested but visible objects can be skipped
		if (!m_nSkipCounter || m_nPixelCount <= m_nMinFragments)
			m_pQuery->Issue(D3DISSUE_END);
	}
}

bool OcclusionQuery::PullOcclusionQuery(uint32 *pnNumOfFragments)
{
	// Check whether hardware occlusion query is supported or not
	if (m_bHWOcclusionSupport) {
		// Query
		if (m_pQuery->GetData(static_cast<void*>(&m_nPixelCount), sizeof(uint32), D3DGETDATA_FLUSH) != S_OK)
			return false; // Error!
		if (pnNumOfFragments)
			*pnNumOfFragments = m_nPixelCount;
	} else {
		m_nPixelCount = 100000;
	}

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
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void OcclusionQuery::BackupDeviceData(uint8 **ppBackup)
{
	// Not used :)
	*ppBackup = nullptr;

	// Cleanup
	if (m_pQuery) {
		m_pQuery->Release();
		m_pQuery = nullptr;
	}
}

void OcclusionQuery::RestoreDeviceData(uint8 **ppBackup)
{
	if (m_bHWOcclusionSupport)
		static_cast<Renderer&>(GetRenderer()).GetDevice()->CreateQuery(D3DQUERYTYPE_OCCLUSION, &m_pQuery);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9
