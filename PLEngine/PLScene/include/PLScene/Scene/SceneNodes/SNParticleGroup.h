/*********************************************************\
 *  File: SNParticleGroup.h                              *
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


#ifndef __PLSCENE_SCENENODE_PARTICLEGROUP_H__
#define __PLSCENE_SCENENODE_PARTICLEGROUP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/FastPool.h>
#include <PLGraphics/Color/Color4.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLMesh/Mesh.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract particle group scene node
*
*  @remarks
*    If 'Material' is not a material or an effect, the effect of the default value of
*    'Material' is used together with the given texture.
*
*  @note
*    - The 'UpdateAABoundingBox()' implementation for dirty axis align bounding box in 'scene node space'
*      gets the current bounding box by checking each particle. Try to avoid calling the 'dirty' function
*      within your particle group implementation each frame. (performance!)
*/
class SNParticleGroup : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			ForceUpdate             = 1<<10,	/**< Do always update the particle group, even if it's currently not visible on the screen. */
			PointSprites            = 1<<11,	/**< Use point sprites. Setup the point sprites within the material. */
			UseGlobalColor          = 1<<12,	/**< Use global particle color. Only possible if the 'PointSprites'-flag is set! */
			SceneNodeSpaceParticles = 1<<13		/**< Particles are within the local scene node space */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(ForceUpdate,				"Do always update the particle group, even if it's currently not visible on the screen.")
			pl_enum_value(PointSprites,				"Use point sprites. Setup the point sprites within the material.")
			pl_enum_value(UseGlobalColor,			"Use global particle color. Only possible if the 'PointSprites'-flag is set!")
			pl_enum_value(SceneNodeSpaceParticles,	"Particles are within the local scene node space")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNParticleGroup, "PLScene", PLScene::SceneNode, "Abstract particle group scene node")
		pl_properties
			pl_property("Icon", "Data/Textures/IconParticles.dds")
		pl_properties_end
		pl_attribute(Material,					PLGeneral::String,		"Data/Effects/DefaultParticle.plfx",		ReadWrite,	GetSet,			"Particle group material",							"Type='Material Effect Image TextureAni'")
		pl_attribute(GlobalColor,				PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Global particle color",							"")
		pl_attribute(Particles,					PLGeneral::uint32,		10,											ReadWrite,	GetSet,			"Number of particles",								"Min=1")
		pl_attribute(TextureAnimationColumns,	PLGeneral::uint32,		1,											ReadWrite,	GetSet,			"Number of animation frame columns in the texture",	"")
		pl_attribute(TextureAnimationRows,		PLGeneral::uint32,		1,											ReadWrite,	GetSet,			"Number of animation frame rows in the texture",	"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,						pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",											"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetMaterial() const;
		PLS_API void SetMaterial(const PLGeneral::String &sValue);
		PLS_API PLGeneral::uint32 GetParticles() const;
		PLS_API void SetParticles(const PLGeneral::uint32 &nValue);
		PLS_API PLGeneral::uint32 GetTextureAnimationColumns() const;
		PLS_API void SetTextureAnimationColumns(const PLGeneral::uint32 &nValue);
		PLS_API PLGeneral::uint32 GetTextureAnimationRows() const;
		PLS_API void SetTextureAnimationRows(const PLGeneral::uint32 &nValue);
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);	// From SceneNode


	//[-------------------------------------------------------]
	//[ Public classes                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    A single particle of the particle group
		*/
		class Particle : public PLGeneral::FastPoolElement<Particle> {


			//[-------------------------------------------------------]
			//[ Public data                                           ]
			//[-------------------------------------------------------]
			public:
				// General
				bool				bActive;		/**< Is the particle active? If 'false' the particle is not rendered.
														 Use this only in special situations, use Add()/Remove() if possible!  */
				PLMath::Vector3		vPos;			/**< Position */
				PLMath::Vector3		vFixPos;		/**< Fixed position */
				PLMath::Vector3		vVelocity;		/**< Velocity */
				PLGraphics::Color4	vColor;			/**< Color (RGBA) */
				float				fEnergy;		/**< Energy */
				float				fSize;			/**< Size */
				float				fRot;			/**< Rotation (more performance cost if not 0.0f) */

				// Texture animation related
				PLGeneral::uint32 nAnimationStep;	/**< Texture animation step */
				float			  fAnimationTimer;	/**< Animation timer */

				// Custom variables
				int   nCustom1;	/**< Custom variable 1 */
				int   nCustom2;	/**< Custom variable 2 */
				float fCustom1;	/**< Custom variable 3 */
				float fCustom2;	/**< Custom variable 4 */

				// Advanced features (more performance cost)
				// Own orientation
				PLMath::Quaternion *pRot;	/**< Rotation quaternion for individual particle rotation (no billbording!)
												 If you want to use it you have to use pRot = new PLMath::Quaternion() when
												 deactivating it delete pRot (Particle group will delete it on destruction
												 automatically) NULL if not used. */

				// Distortion
				bool			bDistorted;		/**< Distorted */
				PLMath::Vector3	vDistortion;	/**< Distortion */


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				PLS_API Particle();
				PLS_API virtual ~Particle();
				PLS_API bool operator ==(const Particle &cOther) const;


		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initializes the particle group
		*
		*  @param[in] nMaxNumOfParticles
		*    Maximum possible number of particles
		*  @param[in] sMaterial
		*    Name of the particle material/texture, if empty
		*    the material defined in 'Material' is used
		*  @param[in] pData
		*    Additional data, can be NULL
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Overwrite this function to be able to define your own particle group initialization
		*      which isn't required that often
		*    - Normally, this function calls InitParticles() which further calles
		*      the scene nodes InitFunction() in which you can initialize the individual particles
		*/
		PLS_API virtual bool InitParticleGroup(PLGeneral::uint32 nMaxNumOfParticles, const PLGeneral::String &sMaterial = "",
											  const void *pData = NULL);

		/**
		*  @brief
		*    Returns the maximum possible number of particles
		*
		*  @return
		*    The maximum possible number of particles
		*/
		PLS_API PLGeneral::uint32 GetMaxNumOfParticles() const;

		/**
		*  @brief
		*    Returns the current number of particles
		*
		*  @return
		*    The current number of particles
		*/
		PLS_API PLGeneral::uint32 GetNumOfParticles() const;

		/**
		*  @brief
		*    Adds a new particle
		*
		*  @return
		*    Pointer to the new particle, NULL on error
		*    (particle limit of this group reached?)
		*
		*  @note
		*    - If GetCreateParticles() is 'false', this function will always return NULL
		*/
		PLS_API Particle *AddParticle();

		/**
		*  @brief
		*    Removes a particle
		*
		*  @param[in] cParticle
		*    Particle to remove
		*/
		PLS_API void RemoveParticle(Particle &cParticle);

		/**
		*  @brief
		*    Returns a particle iterator
		*
		*  @return
		*    Particle iterator (always valid!)
		*
		*  @note
		*    - You have to delete this iterator by yourself if you no longer need it!
		*/
		PLS_API PLGeneral::Iterator<Particle> GetParticleIterator() const;

		/**
		*  @brief
		*    Returns whether the particle group can create new particles or not
		*
		*  @return
		*    'true' the particle group can create new particles, else 'false'
		*/
		PLS_API bool GetCreateParticles() const;

		/**
		*  @brief
		*    Sets whether the particle group can create new particles or not
		*
		*  @param[in] bCreate
		*    Can the particle group create new particles?
		*
		*  @see
		*    - GetCreateParticles()
		*/
		PLS_API void SetCreateParticles(bool bCreate = true);

		/**
		*  @brief
		*    Configures the texture animation
		*
		*  @param[in] nColumns
		*    Number of animation frame columns in the texture
		*  @param[in] nRows
		*    Number of animation frame rows in the texture
		*/
		PLS_API void SetupTextureAnimation(PLGeneral::uint32 nColumns = 1, PLGeneral::uint32 nRows = 1);

		/**
		*  @brief
		*    Returns the number of texture animation steps
		*
		*  @return
		*    The number of texture animation steps
		*/
		PLS_API PLGeneral::uint32 GetTextureAnimationSteps() const;

		/**
		*  @brief
		*    Returns whether the particle group should be removed automatically after all particles are inactive or not
		*
		*  @return
		*    'true' if the particle group should be removed automatically, else 'false'
		*/
		PLS_API bool GetRemoveAutomatically() const;

		/**
		*  @brief
		*    Should the particle group be removed automatically after all particles are inactive?
		*
		*  @param[in] bRemoveAutomatically
		*    Should the particle group be removed automatically?
		*/
		PLS_API void RemoveAutomatically(bool bRemoveAutomatically = false);

		/**
		*  @brief
		*    Returns the handler of the particle group material
		*
		*  @return
		*    Handler of the particle group material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetMaterialHandler();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNParticleGroup();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNParticleGroup();

		/**
		*  @brief
		*    Initializes the particles
		*
		*  @param[in] nMaxNumOfParticles
		*    Maximum possible number of particles
		*  @param[in] sMaterial
		*    Name of the particle material, if empty the particle
		*    group default material is used
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLS_API bool InitParticles(PLGeneral::uint32 nMaxNumOfParticles, const PLGeneral::String &sMaterial = "");


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Create the particle shapes
		*/
		void CreateShapes();

		/**
		*  @brief
		*    Draws the particle shapes
		*
		*  @param[in] cRenderer
		*    The used renderer
		*/
		void DrawShapes(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal particle texture coordinate
		*/
		class ParticleTexCoord {
			public:
			PLMath::Vector2 vTexCoord[4];
			ParticleTexCoord &operator =(const ParticleTexCoord &cSource)
			{
				vTexCoord[0] = cSource.vTexCoord[0];
				vTexCoord[1] = cSource.vTexCoord[1];
				vTexCoord[2] = cSource.vTexCoord[2];
				vTexCoord[3] = cSource.vTexCoord[3];
				return *this;
			}
			bool operator ==(const ParticleTexCoord &cT) const
			{
				for (int i=0; i<4; i++) {
					if (vTexCoord[i] != cT.vTexCoord[i])
						return false;
				}
				return true;
			}
		};


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String					 m_sMaterial;					/**< Particle group material */
		PLRenderer::MaterialHandler			 m_cMaterial;					/**< Used material */
		PLGeneral::uint32					 m_nParticles;					/**< Number of particles */
		PLGeneral::uint32					 m_nTextureAnimationColumns;	/**< Number of animation frame columns in the texture */
		PLGeneral::uint32					 m_nTextureAnimationRows;		/**< Number of animation frame rows in the texture */
		PLRenderer::IndexBuffer				*m_pIndexBuffer;				/**< Index buffer, can be NULL */
		PLRenderer::VertexBuffer			*m_pVertexBuffer;				/**< Vertex buffer, can be NULL */
		PLGeneral::uint32					 m_nUsedIndices;				/**< Number of used indices */
		PLGeneral::uint32					 m_nUsedVertices;				/**< Number of used vertices */
		bool								 m_bRemoveAutomatically;		/**< Should the particle group be removed automatically? */
		PLGeneral::uint32					 m_nMaxNumOfParticles;			/**< Maximum number of allowed particles */
		PLGeneral::FastPool<Particle>		 m_lstParticles;				/**< Particle list */
		bool								 m_bCreateParticles;			/**< Create new particles? */
		PLGeneral::Array<ParticleTexCoord>	 m_lstTexCoord;					/**< A list of all texture coordinates */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = NULL);


	//[-------------------------------------------------------]
	//[ Proteced virtual SceneNode functions                  ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void InitFunction();
		PLS_API virtual void DeInitFunction();
		PLS_API virtual void UpdateAABoundingBox();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_PARTICLEGROUP_H__
