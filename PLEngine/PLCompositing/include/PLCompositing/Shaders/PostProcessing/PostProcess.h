/*********************************************************\
 *  File: PostProcess.h                                  *
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


#ifndef __PLCOMPOSITING_POSTPROCESSING_POSTPROCESS_H__
#define __PLCOMPOSITING_POSTPROCESSING_POSTPROCESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Element.h>
#include <PLGeneral/Base/ElementHandler.h>
#include <PLGeneral/Base/ElementManager.h>
#include <PLMath/Vector3.h>
#include <PLCompositing/PLCompositing.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Material;
	class MaterialHandler;
}
namespace PLCompositing {
	class PostProcessManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Post process class
*/
class PostProcess : public PLGeneral::Element<PostProcess> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Element name to set
		*  @param[in] cManager
		*    Post process manager using this element
		*/
		PLCOM_API PostProcess(const PLGeneral::String &sName, PostProcessManager &cManager);

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~PostProcess();

		/**
		*  @brief
		*    Returns whether the post process is active or not
		*
		*  @return
		*    'true' if the post process is active, else 'false'
		*/
		PLCOM_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the post process is active or not
		*
		*  @param[in] bActive
		*    'true' if the post process is active, else 'false'
		*/
		PLCOM_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Returns the post process material
		*
		*  @return
		*    Post process material, can be a null pointer
		*/
		PLCOM_API PLRenderer::Material *GetMaterial() const;

		/**
		*  @brief
		*    Sets the post process material
		*
		*  @param[in] pMaterial
		*    Post process material to set, can be a null pointer
		*/
		PLCOM_API void SetMaterial(PLRenderer::Material *pMaterial);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool						 m_bActive;				/**< Is this post process currently active? */
		PLRenderer::MaterialHandler *m_pMaterialHandler;	/**< Handler holding the used material (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_POSTPROCESSING_POSTPROCESS_H__
