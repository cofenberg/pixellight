/*********************************************************\
 *  File: SNMPostProcess.h                               *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_POSTPROCESS_H__
#define __PLSCENE_SCENENODEMODIFIER_POSTPROCESS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLScene/Scene/SceneNodeModifier.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Parameter;
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
*    Abstract camera scene node post process modifier class
*
*  @note
*    - This class is NOT derived from SNMDraw because in fact, nothing is 'drawn over' the owner scene node!
*/
class SNMPostProcess : public PLScene::SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SNMPostProcess, "PLCompositing", PLScene::SceneNodeModifier, "Abstract camera scene node post process modifier class")
		pl_attribute(Filename,		PLGeneral::String,	"",		ReadWrite,	GetSet,			"Filename of the post process to use",														"Type='PostProcess'")
		pl_attribute(EffectWeight,	float,				1.0f,	ReadWrite,	DirectValue,	"Effect weight, 0 means that this effect has no influence, 1 for the intended influence",	"Min=0 Max=1")
		pl_properties
			pl_property("SceneNodeClass", "PLScene::SNCamera")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API PLGeneral::String GetFilename() const;
		PLCOM_API void SetFilename(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the post process manager
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLCOM_API PostProcessManager &GetPostProcessManager();

		/**
		*  @brief
		*    Returns a post process effect parameter
		*
		*  @param[in] sName
		*    Parameter name
		*  @param[in] nIndex
		*    Post process index
		*  @param[in] bActiveOnly
		*    Do only take active post processes into account?
		*
		*  @return
		*    The requested post process parameter, NULL if no such parameter was found or 'bActiveOnly' is used
		*/
		PLCOM_API PLRenderer::Parameter *GetParameter(const PLGeneral::String &sName, PLGeneral::uint32 nIndex = 0, bool bActiveOnly = false);

		/**
		*  @brief
		*    Returns all post process effect parameters of a given parameter name
		*
		*  @param[in]  sName
		*    Parameter name
		*  @param[out] lstParameters
		*    Will receive all parameters with the given name (the array is not cleared before filling it)
		*  @param[in]  bActiveOnly
		*    Do only add active post process parameters into the output array?
		*
		*  @return
		*    'true' if all went fine and at least one parameter with the give name was found, else 'false'
		*
		*  @remarks
		*    This function loops through all (or just active) post processes and adds the material parameter
		*    of a given name into the output array.
		*/
		PLCOM_API bool GetParameters(const PLGeneral::String &sName, PLGeneral::Array<PLRenderer::Parameter*> &lstParameters, bool bActiveOnly = false);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sets all current parameter values as current post process settings
		*
		*  @note
		*    - The default implementation sets "EffectWeight" of all post processes to 1, except of the last one - this is set to m_fEffectWeight
		*    - Called before the post process is applied (synchronize post process effect and RTTI parameters)
		*/
		PLCOM_API virtual void SetParameters();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLCOM_API virtual void InformedOnInit();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLCOM_API SNMPostProcess(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SNMPostProcess();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String m_sFilename;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PostProcessManager *m_pPostProcessManager;	/**< Post process manager (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLSCENE_SCENENODEMODIFIER_POSTPROCESS_H__
