/*********************************************************\
 *  File: FixedFunctions.h                               *
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


#ifndef __PLRENDEREROPENGL_FIXEDFUNCTIONS_H__
#define __PLRENDEREROPENGL_FIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/FixedFunctions.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL fixed functions renderer interface implementation
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
		*  @param[in] cRendererOpenGL
		*    OpenGL renderer instance
		*/
		FixedFunctions(Renderer &cRendererOpenGL);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FixedFunctions();

		/**
		*  @brief
		*    General OpenGL settings
		*/
		void GeneralSettings();

		/**
		*  @brief
		*    Restores the device states
		*/
		void RestoreDeviceStates();

		/**
		*  @brief
		*    Updates the current OpenGL projection matrix
		*/
		void UpdateCurrentOpenGLProjectionMatrix();

		/**
		*  @brief
		*    Every time the view matrix changes we have to update some stuff
		*/
		void ViewMatrixUpdated();

		/**
		*  @brief
		*    Updates the current OpenGL texture matrix of the given stage
		*
		*  @param[in] nStage
		*    Texture stage where to update the current OpenGL matrix
		*
		*  @note
		*    - Activate the correct OpenGL texture stage before calling this function!
		*/
		void UpdateCurrentOpenGLTextureMatrix(PLCore::uint32 nStage);

		/**
		*  @brief
		*    Updates the current OpenGL texture matrix of the given stage
		*
		*  @param[in] nStage
		*    Texture stage where to update the current OpenGL matrix
		*
		*  @note
		*    - Activate the correct OpenGL texture stage before calling this function!
		*/
		void UpdateShaderOpenGLTextureMatrix(PLCore::uint32 nStage);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer		   *m_pRendererOpenGL;									/**< OpenGL renderer instance, always valid! */
		Capabilities	    m_sCapabilities;									/**< The renderer fixed functions capabilities */
		// Render states
		PLCore::uint32   	m_nDefaultRenderState[RenderState::Number];			/**< Default renderer states */
		PLCore::uint32   	m_nRenderState[RenderState::Number];				/**< List of render states (see RenderState) */
		PLGraphics::Color4  m_cColor;											/**< Current color */
		// Transform states
		PLMath::Matrix4x4   m_mProj;											/**< Projection transformation matrix */
		PLMath::Matrix4x4   m_mView;											/**< View transformation matrix */
		PLMath::Matrix4x4   m_mWorld;											/**< World transformation matrix */
		PLMath::Matrix4x4   m_mTextureMatrix[8];								/**< Texture transformation matrix */
		PLMath::Matrix4x4   m_mOriginalProj;									/**< Original projection matrix */
		PLMath::Matrix4x4   m_mOriginalTexture[8];								/**< Original texture transformation matrix (only used of matrix is scaled) */
		// Texture stage states
		PLCore::uint32   	m_nDefaultTextureStageState[TextureStage::Number];	/**< Default texture stage states */
		PLCore::uint32 	  **m_ppnTextureStageState;								/**< List of texture stage states for each stage (see TextureStage) */
		PLCore::uint32 	  **m_ppnInternalTextureStageState;						/**< List of internal texture stage states for each stage (see TextureStage) */
		// Material states
		PLCore::uint32   	m_nDefaultMaterialState[MaterialState::Number];		/**< Default material states */
		PLCore::uint32 	  	m_nMaterialState[MaterialState::Number];			/**< List of material states */
		// Light states
		bool			   *m_pLightEnabled;									/**< OpenGL light enabled, always valid! */
		Light			   *m_pLight;											/**< OpenGL light, always valid! */
		// Clip plane states
		bool	  *m_pbClipPlane;
		GLdouble **m_ppdClipPlane;
		// Vertex buffer states
		PLRenderer::VertexBuffer **m_ppCurrentVertexBuffer;						/**< Current vertex buffer */
		PLCore::uint32		  	  *m_nVertexBufferOffsets;						/**< Current vertex buffer offsets */
		// All this wrappers will map PL renderer values to API dependent values
		PLCore::Array<PLCore::uint32> m_cPLE_FMWrapper;		/**< Fog */
		PLCore::Array<PLCore::uint32> m_cPLE_SHADEWrapper;	/**< Shade */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::FixedFunctions functions   ]
	//[-------------------------------------------------------]
	public:
		virtual const Capabilities &GetCapabilities() const override;
		virtual void Reset() override;
		// Render states
		virtual PLCore::uint32 GetDefaultRenderState(RenderState::Enum nState) const override;
		virtual void ResetRenderStates() override;
		virtual int GetRenderState(RenderState::Enum nState) const override;
		virtual bool SetRenderState(RenderState::Enum nState, PLCore::uint32 nValue) override;
		virtual PLGraphics::Color4 GetColor() const override;
		virtual void SetColor(const PLGraphics::Color4 &cColor = PLGraphics::Color4::White) override;
		// Transform states
		virtual const PLMath::Matrix4x4 &GetTransformState(Transform::Enum nState, bool bOriginal = true) const override;
		virtual void ResetTransformStates() override;
		virtual bool SetTransformState(Transform::Enum nState, const PLMath::Matrix3x4 &mTrans) override;
		virtual bool SetTransformState(Transform::Enum nState, const PLMath::Matrix4x4 &mTrans) override;
		// Texture stage states
		virtual PLCore::uint32 GetDefaultTextureStageState(TextureStage::Enum nState) const override;
		virtual void ResetTextureStageStates() override;
		virtual int GetTextureStageState(PLCore::uint32 nStage, TextureStage::Enum nState) const override;
		virtual bool SetTextureStageState(PLCore::uint32 nStage, TextureStage::Enum nState, PLCore::uint32 nValue) override;
		// Material states
		virtual PLCore::uint32 GetDefaultMaterialState(MaterialState::Enum nState) const override;
		virtual void ResetMaterialStates() override;
		virtual int GetMaterialState(MaterialState::Enum nState) const override;
		virtual bool SetMaterialState(MaterialState::Enum nState, PLCore::uint32 nValue) override;
		// Light states
		virtual void GetDefaultLightSettings(Light &sLight) const override;
		virtual void ResetLights() override;
		virtual bool IsLightEnabled(PLCore::uint32 nLightID) const override;
		virtual bool SetLightEnabled(PLCore::uint32 nLightID, bool bEnabled) override;
		virtual bool GetLight(PLCore::uint32 nLightID, Light &sLight) const override;
		virtual bool SetLight(PLCore::uint32 nLightID, const Light &sLight) override;
		// Clip plane states
		virtual bool IsClipPlaneEnabled(PLCore::uint8 nIndex) const override;
		virtual bool SetClipPlaneEnabled(char nIndex = -1, bool bEnable = false) override;
		virtual bool GetClipPlane(PLCore::uint8 nIndex, float &fA, float &fB, float &fC, float &fD) const override;
		virtual bool SetClipPlane(char nIndex = -1, float fA = 0.0f, float fB = 0.0f, float fC = 0.0f, float fD = 0.0f) override;
		// Vertex buffer states
		virtual PLRenderer::VertexBuffer *GetVertexBuffer(PLCore::uint32 nStreamNumber = 0, PLCore::uint32 *pnOffset = nullptr) const override;
		virtual bool SetVertexBuffer(PLRenderer::VertexBuffer *pVertexBuffer = nullptr, PLCore::uint32 nOffset = 0, PLCore::uint32 nStreamNumber = 0) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_FIXEDFUNCTIONS_H__
