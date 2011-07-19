/*********************************************************\
 *  File: OcclusionQuery.h                               *
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


#ifndef __PLRENDERERNULL_OCCLUSION_QUERY_H__
#define __PLRENDERERNULL_OCCLUSION_QUERY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/OcclusionQuery.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null occlusion query
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
		PLCore::uint32 m_nSkipRate;		/**< Skip rate */
		PLCore::uint32 m_nMinFragments;	/**< Minimum number of visible fragments */
		PLCore::uint32 m_nPixelCount;	/**< Last pixel count */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::OcclusionQuery functions   ]
	//[-------------------------------------------------------]
	public:
		virtual bool BeginOcclusionQuery();
		virtual void EndOcclusionQuery();
		virtual bool PullOcclusionQuery(PLCore::uint32 *pnNumOfFragments = nullptr);
		virtual PLCore::uint32 GetLastQuerysPixelCount() const;
		virtual PLCore::uint32 GetSkipRate() const;
		virtual void SetSkipRate(PLCore::uint32 nRate = 0);
		virtual PLCore::uint32 GetMinFragments() const;
		virtual void SetMinFragments(PLCore::uint32 nMinFragments = 0);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererNull


#endif // __PLRENDERERNULL_OCCLUSION_QUERY_H__
