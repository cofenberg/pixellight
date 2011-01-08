/*********************************************************\
 *  File: EffectPass.h                                   *
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


#ifndef __PLRENDERER_EFFECT_PASS_H__
#define __PLRENDERER_EFFECT_PASS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/FixedFunctions.h"
#include "PLRenderer/Renderer/RenderStates.h"
#include "PLRenderer/Renderer/FixedFunctionsRenderStates.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Program;
class VertexShader;
class FragmentShader;
class EffectPassLayer;
class EffectTechnique;
class ParameterManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A effect pass will set the render states, textures etc.
*    required for proper rendering of the given pass.
*/
class EffectPass {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class EffectTechnique;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner effect technique
		*
		*  @return
		*    Owner effect technique
		*/
		PLRENDERER_API EffectTechnique &GetTechnique() const;

		/**
		*  @brief
		*    Returns the pass name
		*
		*  @return
		*    Pass name
		*/
		PLRENDERER_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Sets the pass name
		*
		*  @param[in] sName
		*    New pass name
		*/
		PLRENDERER_API void SetName(const PLGeneral::String &sName = "Pass");

		/**
		*  @brief
		*    Binds the pass
		*
		*  @param[in] pParameterManager
		*    Parameters set instead of existing effect parameters, can be a null pointer
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool Bind(ParameterManager *pParameterManager = nullptr);

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
		PLRENDERER_API EffectPass &operator =(const EffectPass &cSource);

		//[-------------------------------------------------------]
		//[ States                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the general color
		*
		*  @return
		*    General color
		*/
		PLRENDERER_API const PLGraphics::Color4 &GetColor() const;

		/**
		*  @brief
		*    Sets the general color
		*
		*  @param[in] cColor
		*    New general color
		*/
		PLRENDERER_API void SetColor(const PLGraphics::Color4 &cColor = PLGraphics::Color4::White);

		/**
		*  @brief
		*    Returns the render states
		*
		*  @return
		*    The render states
		*/
		PLRENDERER_API RenderStates &GetRenderStates();
		PLRENDERER_API const RenderStates &GetRenderStates() const;

		/**
		*  @brief
		*    Returns the fixed functions render states
		*
		*  @return
		*    The fixed functions render states
		*/
		PLRENDERER_API FixedFunctionsRenderStates &GetFixedFunctionsRenderStates();
		PLRENDERER_API const FixedFunctionsRenderStates &GetFixedFunctionsRenderStates() const;

		/**
		*  @brief
		*    Resets all material states to default
		*/
		PLRENDERER_API void ResetMaterialStates();

		/**
		*  @brief
		*    Retrieves a material-state value
		*
		*  @param[in] nState
		*    State variable that is being queried. This parameter can
		*    be any member of the renderer material enumerated type.
		*
		*  @return
		*    The value of the queried material state variable
		*/
		PLRENDERER_API PLGeneral::uint32 GetMaterialState(FixedFunctions::MaterialState::Enum nState) const;

		/**
		*  @brief
		*    Sets a single material-state parameter
		*
		*  @param[in] nState
		*    State variable that is being modified. This parameter
		*    can be any member of the renderer material enumerated type.
		*  @param[in] nValue
		*    New value for the material state to be set.
		*    You can also set the value to unknown - then this state is ignored.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool SetMaterialState(FixedFunctions::MaterialState::Enum nState, PLGeneral::uint32 nValue);

		//[-------------------------------------------------------]
		//[ Layers                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of texture layers
		*
		*  @return
		*    Number of texture layers
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfLayers() const;

		/**
		*  @brief
		*    Adds a new layer
		*
		*  @return
		*    The new effect pass layer, a null pointer on error
		*/
		PLRENDERER_API EffectPassLayer *AddLayer();

		/**
		*  @brief
		*    Returns a layer
		*
		*  @param[in] nIndex
		*    Layer index
		*
		*  @return
		*    Effect pass layer, a null pointer if there was an error
		*/
		PLRENDERER_API EffectPassLayer *GetLayer(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Removes a layer
		*
		*  @param[in] nIndex
		*    Index of the layer to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool RemoveLayer(PLGeneral::uint32 nIndex = 0);

		/**
		*  @brief
		*    Removes all layers
		*/
		PLRENDERER_API void RemoveAllLayers();

		//[-------------------------------------------------------]
		//[ Shaders                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Loads a vertex shader
		*
		*  @param[in] sFilename
		*    Shader filename
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg")
		*  @param[in] sProfile
		*    Profile that should be used (e.g. "arbvp1")
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool LoadVertexShader(const PLGeneral::String &sFilename, const PLGeneral::String &sShaderLanguage, const PLGeneral::String &sProfile = "");

		/**
		*  @brief
		*    Loads a fragment shader
		*
		*  @param[in] sFilename
		*    Shader filename
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg")
		*  @param[in] sProfile
		*    Profile that should be used (e.g. "arbfp1")
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool LoadFragmentShader(const PLGeneral::String &sFilename, const PLGeneral::String &sShaderLanguage, const PLGeneral::String &sProfile = "");

		/**
		*  @brief
		*    Returns the used GPU program
		*
		*  @return
		*    The used GPU program, a null pointer if there's no such GPU program
		*/
		PLRENDERER_API Program *GetProgram();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cTechnique
		*    Owner effect technique
		*/
		EffectPass(EffectTechnique &cTechnique);

		/**
		*  @brief
		*    Destructor
		*/
		~EffectPass();

		/**
		*  @brief
		*    Loads in a string by using a file
		*
		*  @param[in] sFilename
		*    Name of the file to read the string from
		*
		*  @return
		*    The read string, empty string on error
		*/
		PLGeneral::String LoadStringFromFile(const PLGeneral::String &sFilename) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EffectTechnique   *m_pTechnique;	/**< Owner effect technique (always valid!) */
		PLGeneral::String  m_sName;			/**< Pass name */
		// States
		PLGraphics::Color4		   m_cColor;												/**< General color */
		RenderStates			   m_cRenderStates;											/**< Render states */
		FixedFunctionsRenderStates m_cFixedFunctionsRenderStates;							/**< Fixed functions render states */
		PLGeneral::uint32		   m_nMaterialState[FixedFunctions::MaterialState::Number];	/**< List of material states (see 'Material') */
		// Layers
		PLGeneral::Array<EffectPassLayer*> m_lstLayers;	/**< Texture layers */
		// Shaders
		VertexShader   *m_pVertexShader;	/**< Used vertex shader, can be a null pointer */
		FragmentShader *m_pFragmentShader;	/**< Used fragment shader, can be a null pointer */
		Program		   *m_pProgram;			/**< GPU program, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_EFFECT_PASS_H__
