/*********************************************************\
 *  File: ShaderCompositionID.inl                        *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
inline ShaderCompositionID::~ShaderCompositionID()
{
}

/**
*  @brief
*    Returns the CRC32 checksum of this shader composition ID
*/
inline PLCore::uint32 ShaderCompositionID::GetChecksum() const
{
	return m_nChecksumCRC32;
}

/**
*  @brief
*    Returns the shader composition data the ID consists of
*/
inline const ShaderCompositionID::SData &ShaderCompositionID::GetData() const
{
	return m_sData;
}

/**
*  @brief
*    Returns whether or not this shader composition ID is valid
*/
bool ShaderCompositionID::IsValid() const
{
	// If this ID is valid, all pointers are no null pointer (the following formating is intended)
	return
		m_sData.pShaderLanguage						&&
		// 1.0 - Ray Setup
		m_sData.pShaderFunctionRaySetupClass		&&
		// 1.1 - Clip Ray
		m_sData.pShaderFunctionClipRayClass			&&
		// 1.2 - Jitter Position
		m_sData.pShaderFunctionJitterPositionClass	&&
		// 2.0 - Ray Traversal
		m_sData.pShaderFunctionRayTraversalClass	&&
		// 2.1 - Clip Position
		m_sData.pShaderFunctionClipPositionClass	&&
		// 2.2 - Reconstruction
		m_sData.pShaderFunctionReconstructionClass	&&
		// 2.2 - Fetch Scalar
		m_sData.pShaderFunctionFetchScalarClass		&&
		// 2.3 - Shading
		m_sData.pShaderFunctionShadingClass			&&
		// 2.4 - Classification
		m_sData.pShaderFunctionClassificationClass	&&
		// 2.5 - Gradient
		m_sData.pShaderFunctionGradientClass		&&
		// 2.5 - Gradient Input
		m_sData.pShaderFunctionGradientInputClass	&&
		// 2.6 - Illumination
		m_sData.pShaderFunctionIlluminationClass
	;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
