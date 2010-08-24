/*********************************************************\
 *  File: OcclusionQuery.h                               *
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


#ifndef __PLRENDERERD3D9_OCCLUSIONQUERY_H__
#define __PLRENDERERD3D9_OCCLUSIONQUERY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/OcclusionQuery.h>
#include "PLRendererD3D9/PLRendererD3D9.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D 9 occlusion query
*/
class OcclusionQuery : public PLRenderer::OcclusionQuery {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~OcclusionQuery();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		OcclusionQuery(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			   m_bHWOcclusionSupport;	/**< Occlusion query supported by hardware? */
		IDirect3DQuery9	  *m_pQuery;				/**< Direct3D9 occlusion query, can be NULL */
		PLGeneral::uint32  m_nSkipRate;				/**< Skip rate */
		PLGeneral::uint32  m_nSkipCounter;			/**< Skip counter */
		PLGeneral::uint32  m_nMinFragments;			/**< Minimum number of visible fragments */
		PLGeneral::uint32  m_nPixelCount;			/**< Last pixel count */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::OcclusionQuery functions   ]
	//[-------------------------------------------------------]
	public:
		virtual bool BeginOcclusionQuery();
		virtual void EndOcclusionQuery();
		virtual bool PullOcclusionQuery(PLGeneral::uint32 *pnNumOfFragments = NULL);
		virtual PLGeneral::uint32 GetLastQuerysPixelCount() const;
		virtual PLGeneral::uint32 GetSkipRate() const;
		virtual void SetSkipRate(PLGeneral::uint32 nRate = 0);
		virtual PLGeneral::uint32 GetMinFragments() const;
		virtual void SetMinFragments(PLGeneral::uint32 nMinFragments = 0);


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_OCCLUSIONQUERY_H__
