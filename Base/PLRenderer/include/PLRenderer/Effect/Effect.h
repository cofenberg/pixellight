/*********************************************************\
 *  File: Effect.h                                       *
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


#ifndef __PLRENDERER_EFFECT_EFFECT_H__
#define __PLRENDERER_EFFECT_EFFECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Resource.h>
#include <PLMath/Vector3.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class EffectPass;
class EffectManager;
class EffectTechnique;
class ParameterManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect resource class
*
*  @remarks
*    A effect is a powerful rendering description. It will manage the different render
*    techniques.
*    Each effect can have parameters to interact with the vertex/shader programs some technique
*    passes may use.
*    Each parameter is mapped to the corresponding shader parameter. Have a look at
*    'ParameterManager.h' for more information.
*/
class Effect : public PLCore::Resource<Effect> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class EffectManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Effect();

		/**
		*  @brief
		*    Returns the effect manager this effect is in
		*
		*  @return
		*     The effect manager this effect is in
		*/
		PLRENDERER_API EffectManager &GetEffectManager() const;

		/**
		*  @brief
		*    Returns the parameter manager of the effect
		*
		*  @return
		*    The parameter manager of the effect
		*/
		PLRENDERER_API ParameterManager &GetParameterManager() const;

		/**
		*  @brief
		*    Returns whether the effect should be blend or not
		*
		*  @return
		*    'true' if the pass should be blend, else 'false'
		*
		*  @remarks
		*    This only a general setting whether the effect is blend or not.
		*    Because transparent objects should be rendered after all solid objects this
		*    setting indicates when the object should be rendered.
		*/
		PLRENDERER_API bool GetBlend() const;

		/**
		*  @brief
		*    Activates/deactivates the effect blending
		*
		*  @param[in] bBlend
		*    Should the effect be blended?
		*
		*  @see
		*    - GetBlend()
		*/
		PLRENDERER_API void SetBlend(bool bBlend = false);

		/**
		*  @brief
		*    Returns whether the effect is loaded or not
		*
		*  @return
		*    'true' if the effect is loaded, else 'false'
		*/
		PLRENDERER_API bool IsLoaded() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*/
		PLRENDERER_API Effect &operator =(const Effect &cSource);

		//[-------------------------------------------------------]
		//[ General                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the flags
		*
		*  @return
		*    Flags
		*/
		PLRENDERER_API PLCore::uint32 GetFlags() const;

		/**
		*  @brief
		*    Sets the flags
		*
		*  @param[in] nFlags
		*    Flags
		*/
		PLRENDERER_API void SetFlags(PLCore::uint32 nFlags = 0);

		/**
		*  @brief
		*    Returns the internal timer
		*
		*  @return
		*    Internal timer
		*/
		PLRENDERER_API float GetTimer() const;

		/**
		*  @brief
		*    Sets the internal timer
		*
		*  @param[in] fTimer
		*    Time to set
		*/
		PLRENDERER_API void SetTimer(float fTimer = 0.0f);

		//[-------------------------------------------------------]
		//[ Technique functions                                   ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets the number of techniques
		*
		*  @return
		*    The number of techniques
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfTechniques() const;

		/**
		*  @brief
		*    Adds a technique
		*
		*  @param[in] nTechnique
		*    Index where the new technique should be added, if < 0 the add at the end
		*
		*  @return
		*    The new effect technique, a null pointer on error
		*/
		PLRENDERER_API EffectTechnique *AddTechnique(int nTechnique = -1);

		/**
		*  @brief
		*    Gets a technique
		*
		*  @param[in] nIndex
		*    Index of the technique to return
		*
		*  @return
		*    The effect technique, a null pointer on error
		*/
		PLRENDERER_API EffectTechnique *GetTechnique(PLCore::uint32 nIndex) const;

		/**
		*  @brief
		*    Removes a technique
		*
		*  @param[in] nTechnique
		*    Index of the technique to remove, if < 0 the current selected technique is chosen
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool RemoveTechnique(int nTechnique = -1);

		/**
		*  @brief
		*    Removes all techniques
		*/
		PLRENDERER_API void RemoveAllTechniques();

		/**
		*  @brief
		*    Gets the current selected technique
		*
		*  @return
		*    The current selected technique, a null pointer if no technique is selected
		*/
		PLRENDERER_API EffectTechnique *GetSelectedTechnique() const;

		/**
		*  @brief
		*    Gets the index of the current selected technique
		*
		*  @return
		*    Index of the current selected technique, < 0 if no technique is selected
		*/
		PLRENDERER_API int GetSelectedTechniqueIndex() const;

		/**
		*  @brief
		*    Select the current technique by index
		*
		*  @param[in] nIndex
		*    Technique index
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid or unknown technique)
		*/
		PLRENDERER_API bool SelectTechnique(PLCore::uint32 nIndex = 0);

		/**
		*  @brief
		*    Select the current technique by name
		*
		*  @param[in] sName
		*    Technique name
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid or unknown technique)
		*/
		PLRENDERER_API bool SelectTechnique(const PLCore::String &sName);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Effect manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		Effect(EffectManager &cManager, const PLCore::String &sName);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ParameterManager			   *m_pParameterManager;	/**< Parameter manager (NEVER a null pointer!) */
		PLCore::String					m_sFilename;			/**< Effect filename */
		PLCore::uint32					m_nFlags;				/**< Flags */
		bool							m_bBlend;				/**< Is the effect blend? */
		PLCore::Array<EffectTechnique*>	m_lstTechnique;			/**< List of techniques */
		int								m_nSelectedTechnique;	/**< The current selected technique */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool Reload() override;
		PLRENDERER_API virtual bool Unload() override;
		PLRENDERER_API virtual PLCore::String GetLoadableTypeName() const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_EFFECT_EFFECT_H__
