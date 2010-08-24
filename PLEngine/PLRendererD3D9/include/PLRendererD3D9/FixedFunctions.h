/*********************************************************\
 *  File: FixedFunctions.h                               *
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


#ifndef __PLRENDERERD3D9_FIXEDFUNCTIONS_H__
#define __PLRENDERERD3D9_FIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/FixedFunctions.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererD3D9 {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Direct3D fixed functions renderer interface implementation
*/
class FixedFunctions : public PLRenderer::FixedFunctions {


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
		*    Constructor
		*
		*  @param[in] cRendererD3D9
		*    D3D9 renderer instance
		*/
		FixedFunctions(Renderer &cRendererD3D9);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FixedFunctions();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Updates the current D3D 9 projection matrix
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool UpdateCurrentD3D9ProjectionMatrix();

		/**
		*  @brief
		*    Updates the current D3D 9 texture matrix of the given stage
		*
		*  @param[im] nStage
		*    Texture stage where to update the current D3D9 matrix
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool UpdateCurrentD3D9TextureMatrix(PLGeneral::uint32 nStage);

		/**
		*  @brief
		*    Set vertex declaration
		*
		*  @return
		*    'true' if all went fine, else 'false' (there are no vertex streams?)
		*
		*  @note
		*    - Normally ONLY called within a draw primitive call
		*/
		bool SetVertexDeclaration();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer		   *m_pRendererD3D9;									/**< D3D9 renderer instance, always valid! */
		Capabilities	    m_sCapabilities;									/**< The renderer fixed functions capabilities */
		// Render states
		PLGeneral::uint32   m_nDefaultRenderState[RenderState::Number];			/**< Default renderer states */
		PLGeneral::uint32   m_nRenderState[RenderState::Number];				/**< List of render states (see RenderState) */
		PLGraphics::Color4  m_cColor;											/**< Current color */
		// Transform states
		PLMath::Matrix4x4   m_mProj;											/**< Projection transformation matrix */
		PLMath::Matrix4x4   m_mView;											/**< View transformation matrix */
		PLMath::Matrix4x4   m_mWorld;											/**< World transformation matrix */
		PLMath::Matrix4x4   m_mTextureMatrix[8];								/**< Texture transformation matrix */
		PLMath::Matrix4x4   m_mOriginalProj;									/**< Original projection matrix */
		PLMath::Matrix4x4   m_mOriginalTexture[8];								/**< Original texture transformation matrix (only used of matrix is scaled) */
		// Texture stage states
		PLGeneral::uint32   m_nDefaultTextureStageState[TextureStage::Number];	/**< Default texture stage states */
		PLGeneral::uint32 **m_ppnTextureStageState;								/**< List of texture stage states for each stage (see TextureStage) */
		PLGeneral::uint32 **m_ppnInternalTextureStageState;						/**< List of internal texture stage states for each stage (see TextureStage) */
		// Material states
		PLGeneral::uint32   m_nDefaultMaterialState[MaterialState::Number];		/**< Default material states */
		PLGeneral::uint32   m_nMaterialState[MaterialState::Number];			/**< List of material states */
		// Vertex buffer states
		PLRenderer::VertexBuffer	 **m_ppCurrentVertexBuffer;					/**< Current vertex buffer */
		PLGeneral::uint32			  *m_nVertexBufferOffsets;					/**< Current vertex buffer offsets */
		PLGeneral::uint32			   m_nVertexOffset;							/**< Current vertex offset */
		bool						   m_bUpdateVertexDeclaration;				/**< Update the vertex declaration at the next draw call? */
		LPDIRECT3DVERTEXDECLARATION9   m_pConstructedVertexDeclaration;			/**< Constructed vertex declaration (if multiple streams are used) */
		D3DVERTEXELEMENT9			  *m_pConstructedDeclarations;				/**< Used during dynamic vertex declaration construction */
		PLGeneral::uint32			   m_nNumOfVertexStreams;					/**< Current number of vertex streams */
		// All this wrappers will map PL renderer values to API dependent values
		PLGeneral::Array<PLGeneral::uint32> m_cPLE_FMWrapper;		/**< Fog */
		PLGeneral::Array<PLGeneral::uint32> m_cPLE_SHADEWrapper;	/**< Shade */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::FixedFunctions functions   ]
	//[-------------------------------------------------------]
	public:
		virtual const Capabilities &GetCapabilities() const;
		virtual void Reset();
		// Render states
		virtual PLGeneral::uint32 GetDefaultRenderState(RenderState::Enum nState) const;
		virtual void ResetRenderStates();
		virtual int GetRenderState(RenderState::Enum nState) const;
		virtual bool SetRenderState(RenderState::Enum nState, PLGeneral::uint32 nValue);
		virtual PLGraphics::Color4 GetColor() const;
		virtual void SetColor(const PLGraphics::Color4 &cColor = PLGraphics::Color4::White);
		// Transform states
		virtual const PLMath::Matrix4x4 &GetTransformState(Transform::Enum nState, bool bOriginal = true) const;
		virtual void ResetTransformStates();
		virtual bool SetTransformState(Transform::Enum nState, const PLMath::Matrix3x4 &mTrans);
		virtual bool SetTransformState(Transform::Enum nState, const PLMath::Matrix4x4 &mTrans);
		// Texture stage states
		virtual PLGeneral::uint32 GetDefaultTextureStageState(TextureStage::Enum nState) const;
		virtual void ResetTextureStageStates();
		virtual int GetTextureStageState(PLGeneral::uint32 nStage, TextureStage::Enum nState) const;
		virtual bool SetTextureStageState(PLGeneral::uint32 nStage, TextureStage::Enum nState, PLGeneral::uint32 nValue);
		// Material states
		virtual PLGeneral::uint32 GetDefaultMaterialState(MaterialState::Enum nState) const;
		virtual void ResetMaterialStates();
		virtual int GetMaterialState(MaterialState::Enum nState) const;
		virtual bool SetMaterialState(MaterialState::Enum nState, PLGeneral::uint32 nValue);
		// Light states
		virtual void GetDefaultLightSettings(Light &sLight) const;
		virtual void ResetLights();
		virtual bool IsLightEnabled(PLGeneral::uint32 nLightID) const;
		virtual bool SetLightEnabled(PLGeneral::uint32 nLightID, bool bEnabled);
		virtual bool GetLight(PLGeneral::uint32 nLightID, Light &sLight) const;
		virtual bool SetLight(PLGeneral::uint32 nLightID, const Light &sLight);
		// Clip plane states
		virtual bool IsClipPlaneEnabled(PLGeneral::uint8 nIndex) const;
		virtual bool SetClipPlaneEnabled(char nIndex = -1, bool bEnable = false);
		virtual bool GetClipPlane(PLGeneral::uint8 nIndex, float &fA, float &fB, float &fC, float &fD) const;
		virtual bool SetClipPlane(char nIndex = -1, float fA = 0.0f, float fB = 0.0f, float fC = 0.0f, float fD = 0.0f);
		// Vertex buffer states
		virtual PLRenderer::VertexBuffer *GetVertexBuffer(PLGeneral::uint32 nStreamNumber = 0, PLGeneral::uint32 *pnOffset = NULL) const;
		virtual bool SetVertexBuffer(PLRenderer::VertexBuffer *pVertexBuffer = NULL, PLGeneral::uint32 nOffset = 0, PLGeneral::uint32 nStreamNumber = 0);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererD3D9


#endif // __PLRENDERERD3D9_FIXEDFUNCTIONS_H__
