/*********************************************************\
 *  File: SNMScript.h                                    *
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


#ifndef __PLSCRIPTBINDINGS_SNMSCRIPT_H__
#define __PLSCRIPTBINDINGS_SNMSCRIPT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeModifier.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Script;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Script scene node modifier
*
*  @note
*    - Adds the global variable "this" to the script so that it's able to access "this" RTTI class instance
*/
class SNMScript : public PLScene::SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMScript, "PLScriptBindings", PLScene::SceneNodeModifier, "Script scene node modifier")
		// Attributes
		pl_attribute(Script,			PLCore::String,	"",			ReadWrite,	GetSet,			"Script to use (set the script again in order to reload it)",													"")
		pl_attribute(OnInitFunction,	PLCore::String,	"OnInit",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the scene node modifier should initialize itself",		"")
		pl_attribute(OnUpdateFunction,	PLCore::String,	"OnUpdate",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the scene node modifier should update itself",			"")
		pl_attribute(OnDeInitFunction,	PLCore::String,	"OnDeInit",	ReadWrite,	DirectValue,	"Name of the optional script function called by C++ when the scene node modifier should de-initialize itself",	"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
		// Methods
		pl_method_0(GetScriptInstance,	pl_ret_type(PLCore::Script*),	"Returns the instance of the used script (can be a null pointer)",	"")
		// Slots
		pl_slot_0(OnUpdate,	"Called when the scene node modifier needs to be updated",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::String GetScript() const;
		void SetScript(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		SNMScript(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMScript();

		/**
		*  @brief
		*    Returns the instance of the used script
		*
		*  @return
		*    The instance of the used script, can be a null pointer (don't destroy the returned instance!)
		*/
		PLCore::Script *GetScriptInstance() const;


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Destroys the script
		*/
		void DestroyScript();

		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void OnUpdate();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String  m_sScript;	/**< Script to use */
		PLCore::Script *m_pScript;	/**< Used script instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_SNMSCRIPT_H__
