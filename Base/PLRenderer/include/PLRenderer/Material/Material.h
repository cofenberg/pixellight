/*********************************************************\
 *  File: Material.h                                     *
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


#ifndef __PLRENDERER_MATERIAL_MATERIAL_H__
#define __PLRENDERER_MATERIAL_MATERIAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
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
class Effect;
class Parameter;
class TextureBuffer;
class EffectHandler;
class MaterialHandler;
class MaterialManager;
class ParameterManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Material resource class
*
*  @remarks
*    A material is an abstract surface rendering description. Because a material is quite universal, this
*    resource has a special load implementation if a filename is given:
*    - If the given filename is a 'real' loadable material, (for instance 'Data/Materials/MyMaterial.mat') a 'Material' loader is used
*    - Else, if the given filename is a loadable effect, an 'Effect' loader is used
*    - Else, if the given filename is an texture animation 'tani', a texture animation is loaded
*    - Else, if the given filename is a loadable image, an 'Image' loader is used to load in a texture
*    - If there's a 'Create' in front of the given filename, an automatic texture is created
*    - Else, ERROR! :)
*    - The public static strings of this class are not any fixed function stuff, their only purpose is to
*      offer some 'standardized' attribute names you should use where ever possible instead of inventing new
*      ones that may lead to confusion!
*/
class Material : public PLCore::Resource<Material> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class MaterialManager;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API static const PLCore::String DiffuseMap;			/**< 'DiffuseMap' string (other usual name: 'decal map') */
		PLRENDERER_API static const PLCore::String LightMap;			/**< 'LightMap' string (global ambient lighting) */
		PLRENDERER_API static const PLCore::String AmbientOcclusionMap;	/**< 'AmbientOcclusionMap' string (global ambient occlusion) */
		PLRENDERER_API static const PLCore::String EmissiveMap;			/**< 'EmissiveMap' string (other usual name: 'self illumination map') */
		PLRENDERER_API static const PLCore::String ReflectionMap;		/**< 'ReflectionMap' string (other usual name: 'environment map') */
		PLRENDERER_API static const PLCore::String ReflectivityMap;		/**< 'ReflectivityMap' string */
		PLRENDERER_API static const PLCore::String NormalMap;			/**< 'NormalMap' string */
		PLRENDERER_API static const PLCore::String SpecularMap;			/**< 'SpecularMap' string */
		PLRENDERER_API static const PLCore::String HeightMap;			/**< 'HeightMap' string (other usual name: 'bump map') */


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<Parameter&> EventParameterChanged;	/**< Parameter changed (created, destroyed, value changed) event, changed parameter as parameter */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Material();

		/**
		*  @brief
		*    Returns the material manager this material is in
		*
		*  @return
		*     The material manager this material is in
		*/
		PLRENDERER_API MaterialManager &GetMaterialManager() const;

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
		PLRENDERER_API Material &operator =(const Material &cSource);

		/**
		*  @brief
		*    Gets a material/effect parameter
		*
		*  @param[in] sName
		*    Parameter name
		*
		*  @return
		*    The requested parameter, a null pointer on error
		*
		*  @remarks
		*    While ParameterManager::GetParameter(<Name>) ONLY returns parameters within the
		*    manager, this function will first look for a parameter with the given name within
		*    this material. If there's no such parameter within the material, the function will
		*    look for this parameter within it's own material list (sharing material parameters)
		*    and finally within the used effect. Because an effect may be used by multiple
		*    materials, try to add whenever possible an overwriting parameter to the material instead
		*    manipulating the effect parameter by hand.
		*/
		PLRENDERER_API Parameter *GetParameter(const PLCore::String &sName) const;

		/**
		*  @brief
		*    Gets a texture buffer
		*
		*  @param[in] sName
		*    Parameter name
		*
		*  @return
		*    The requested texture buffer, a null pointer on error
		*
		*  @see
		*    - GetParameter()
		*/
		PLRENDERER_API TextureBuffer *GetParameterTextureBuffer(const PLCore::String &sName) const;

		/**
		*  @brief
		*    Returns the parameter manager of the material
		*
		*  @return
		*    The parameter manager of the material
		*/
		PLRENDERER_API ParameterManager &GetParameterManager() const;

		/**
		*  @brief
		*    Reloads all textures used direct or indirect by the material
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool ReloadTextures();

		//[-------------------------------------------------------]
		//[ Materials                                             ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of materials
		*
		*  @return
		*    The number of materials
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfMaterials() const;

		/**
		*  @brief
		*    Adds a material
		*
		*  @param[in] cMaterial
		*    Material to add
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool AddMaterial(Material &cMaterial);

		/**
		*  @brief
		*    Returns a material
		*
		*  @param[in] nIndex
		*    Index of the material to return
		*
		*  @return
		*    Pointer to the requested material, a null pointer on error
		*/
		PLRENDERER_API Material *GetMaterial(PLCore::uint32 nIndex) const;

		/**
		*  @brief
		*    Removes a material
		*
		*  @param[in] nIndex
		*    Index of the material to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool RemoveMaterial(PLCore::uint32 nIndex);

		/**
		*  @brief
		*    Removes all materials
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool RemoveAllMaterials();

		//[-------------------------------------------------------]
		//[ Effect                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the effect of the material
		*
		*  @return
		*    The effect of the material, a null pointer if there's no effect
		*/
		PLRENDERER_API Effect *GetEffect() const;

		/**
		*  @brief
		*    Sets the effect of the material
		*
		*  @param[in] pFX
		*    The effect of the material, a null pointer if there's no effect
		*/
		PLRENDERER_API void SetEffect(Effect *pFX = nullptr);

		/**
		*  @brief
		*    Returns whether the material should be blend or not
		*
		*  @return
		*    'true' if the pass should be blend, else 'false'
		*
		*  @remarks
		*    This only a general setting whether the material is blend or not.
		*    Because transparent objects should be rendered after all solid objects this
		*    setting indicates when the object should be rendered.
		*/
		PLRENDERER_API bool GetBlend() const;

		/**
		*  @brief
		*    Gets the number of render passes the current technique is using
		*
		*  @return
		*    Number of passes
		*/
		PLRENDERER_API PLCore::uint32 GetNumOfPasses() const;

		/**
		*  @brief
		*    Setup the given path
		*
		*  @param[in] nIndex
		*    Index of the path to setup
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool SetupPass(PLCore::uint32 nIndex = 0) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Material manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		Material(MaterialManager &cManager, const PLCore::String &sName);

		/**
		*  @brief
		*    Called when a parameter has been changed (created, destroyed, value changed)
		*
		*  @param[in] cParameter
		*    The changed parameter
		*/
		void OnParameterChanged(Parameter &cParameter);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<Parameter&> EventHandlerParameterChanged;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ParameterManager				*m_pParameterManager;	/**< Parameter manager (NEVER a null pointer!) */
		PLCore::Array<MaterialHandler*>  m_lstMaterials;		/**< List of materials */
		EffectHandler				    *m_pFXHandler;			/**< Effect handler, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool Load(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "") override;
		PLRENDERER_API virtual bool Reload() override;
		PLRENDERER_API virtual bool Unload() override;
		PLRENDERER_API virtual PLCore::String GetLoadableTypeName() const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_MATERIAL_MATERIAL_H__
