/*********************************************************\
 *  File: EffectTechnique.h                              *
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


#ifndef __PLRENDERER_EFFECT_EFFECTTECHNIQUE_H__
#define __PLRENDERER_EFFECT_EFFECTTECHNIQUE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Effect;
class EffectPass;
class ParameterManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect technique class
*/
class EffectTechnique {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Effect;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner effect
		*
		*  @return
		*    Owner effect
		*/
		PLRENDERER_API Effect &GetEffect() const;

		/**
		*  @brief
		*    Returns whether the technique is valid or not
		*
		*  @return
		*    'true' if the technique is valid, else 'false'
		*
		*  @remarks
		*    If an technique is invalid for instance because an used
		*    shader isn't supported by the hardware you shouldn't use this
		*    technique because it may produce ugly results!
		*/
		PLRENDERER_API bool IsValid() const;

		/**
		*  @brief
		*    Sets whether the technique is valid or not
		*
		*  @param[in] bValid
		*    Technique valid?
		*/
		PLRENDERER_API void SetValid(bool bValid);

		/**
		*  @brief
		*    Gets the name of the technique
		*
		*  @return
		*    Name of the technique
		*/
		PLRENDERER_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Sets the name of the technique
		*
		*  @param[in] sName
		*    New technique name
		*/
		PLRENDERER_API void SetName(const PLGeneral::String &sName = "");

		/**
		*  @brief
		*    Gets the number of render passes the technique is using
		*
		*  @return
		*    Number of passes
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfPasses() const;

		/**
		*  @brief
		*    Adds a pass
		*
		*  @param[in] nIndex
		*    Pass index in the technique where to add the new pass, if < 0 add at the end
		*
		*  @return
		*    The new pass, NULL on error
		*/
		PLRENDERER_API EffectPass *AddPass(int nIndex = -1);

		/**
		*  @brief
		*    Removes a pass
		*
		*  @param[in] nIndex
		*    Pass index in the technique to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool RemovePass(PLGeneral::uint32 nIndex = 0);

		/**
		*  @brief
		*    Removes all passes
		*/
		PLRENDERER_API void RemoveAllPasses();

		/**
		*  @brief
		*    Gets a pass
		*
		*  @param[in] nIndex
		*    Pass index in the technique
		*
		*  @return
		*    The requested pass, NULL on error
		*/
		PLRENDERER_API EffectPass *GetPass(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Setup the given path
		*
		*  @param[in] nIndex
		*    Index of the path to setup
		*  @param[in] pParameterManager
		*    Parameters set instead of existing effect parameters, if NULL, use THIS parameter manager
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool SetupPass(PLGeneral::uint32 nIndex = 0, ParameterManager *pParameterManager = NULL) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFX
		*    Owner effect
		*/
		EffectTechnique(Effect &cFX);

		/**
		*  @brief
		*    Destructor
		*/
		~EffectTechnique();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this effect technique
		*/
		EffectTechnique &operator =(const EffectTechnique &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Effect						  *m_pFX;		/**< Owner effect (always valid!) */
		bool						   m_bValid;	/**< Is the technique valid? */
		PLGeneral::String			   m_sName;		/**< Technique name */
		PLGeneral::Array<EffectPass*>  m_lstPass;	/**< List of passes */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_EFFECT_EFFECTTECHNIQUE_H__
