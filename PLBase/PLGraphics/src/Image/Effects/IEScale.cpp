/*********************************************************\
 *  File: IEScale.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix3x3.h>
#include "PLGraphics/Image/Image.h"
#include "PLGraphics/Image/ImagePart.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/Effects/IEScale.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IEScale)


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scale down data template
*/
template <typename DataType>
class ScaleDownData {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in]  cOldImageBuffer
		*    Old image buffer (MUST have valid data)
		*  @param[out] cImageBuffer
		*    Image buffer (MUST have valid data)
		*  @param[in]  nNewWidth
		*    New width
		*  @param[in]  nNewHeight
		*    New height
		*  @param[in]  nOldWidth
		*    Old height
		*  @param[in]  nOldHeight
		*    Old height
		*  @param[in]  mFilter
		*    Filter matrix
		*/
		ScaleDownData(const ImageBuffer &cOldImageBuffer, ImageBuffer &cImageBuffer, uint32 nNewWidth, uint32 nNewHeight, uint32 nOldWidth, uint32 nOldHeight, const Matrix3x3 &mFilter)
		{
			// Scale factors
			const float fToOriginalWidthFactor  = float(nOldWidth) /nNewWidth;
			const float fToOriginalHeightFactor = float(nOldHeight)/nNewHeight;

			// Get the number of components
			const uint32 nNumOfComponents = cOldImageBuffer.GetComponentsPerPixel();

			// Loop through all components
				  DataType *pNewData = (DataType*)cImageBuffer   .GetData();
			const DataType *pOldData = (DataType*)cOldImageBuffer.GetData();
			for (uint32 nComponent=0; nComponent<nNumOfComponents; nComponent++) {
				// Loop through x
				for (uint32 nX=0; nX<nNewWidth; nX++) {
					// Loop through y
					for (uint32 nY=0; nY<nNewHeight; nY++) {
						// Get the orignal byte
						const uint32 nOriginalX = uint32(nX*fToOriginalWidthFactor);
						const uint32 nOriginalY = uint32(nY*fToOriginalHeightFactor);

						// Sum up
						double fSum      = 0.0f;
						double fTotalSum = 0.0f;
						for (uint32 nFilterX=0; nFilterX<3; nFilterX++) {
							for (uint32 nFilterY=0; nFilterY<3; nFilterY++) {
								// Get the current position on the original image
								const int nCurrentX = (nOriginalX-1) + nFilterX;
								const int nCurrentY = (nOriginalY-1) + nFilterY;

								// Is this current position inside the original image?
								if (nCurrentX >= 0 && nCurrentY >= 0 &&
									nCurrentX < (int)nOldWidth && nCurrentY < (int)nOldHeight) {
									// Jap, get the factor to use this component with
									const float fFactor = mFilter.fM33[nFilterX][nFilterY];

									// Now we've got one more component within our sum
									fTotalSum += fFactor;

									// Get the component value of the original image
									const DataType nOriginalByte = pOldData[(nCurrentY*nOldWidth + nCurrentX)*nNumOfComponents + nComponent];

									// Add component value of the original image with the given factor
									fSum += nOriginalByte*fFactor;
								}
							}
						}

						// Set new byte
						pNewData[(nY*nNewWidth + nX)*nNumOfComponents + nComponent] = DataType(fSum/fTotalSum);
					}
				}
			}
		}


};


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IEScale::IEScale(const Vector3i &vNewSize, bool bUseMipmaps) :
	m_vNewSize(vNewSize),
	m_bUseMipmaps(bUseMipmaps)
{
}

/**
*  @brief
*    Destructor
*/
IEScale::~IEScale()
{
}

/**
*  @brief
*    Get new scale
*/
Vector3i IEScale::GetNewSize() const
{
	return m_vNewSize;
}

/**
*  @brief
*    Is it allowed to use existing mipmaps to scale down?
*/
bool IEScale::GetUseMipmaps() const
{
	return m_bUseMipmaps;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Apply effect to image
*/
bool IEScale::Apply(Image &cImage) const
{
	// Are we allowed to use our mipmap trick?
	if (m_bUseMipmaps) {
		// Backup the given image
		Image cOriginalImage = cImage;

		// Loop through all image parts (for example for cube maps)
		bool bSuccess = true;
		for (uint32 nPart=0; nPart<cImage.GetNumOfParts() && bSuccess; nPart++) {
			// Get the image part
			ImagePart *pImagePart = cImage.GetPart(nPart);
			if (pImagePart) {
				// Scale all down via mipmap usage possible without predictable troubles?
				ImageBuffer *pImageBuffer = pImagePart->GetMipmap(0);
				if (pImageBuffer && pImageBuffer->GetSize() >= m_vNewSize) {
					// Loop through all available mipmaps while each MUST be smaller than the previous one
					// AND the formats MUST be the same (we just assume this, else this are totally invalid mipmaps!)
					while (bSuccess) {
						// Get the image buffer of the first mipmap
						pImageBuffer = pImagePart->GetMipmap(0);
						if (pImageBuffer) {
							// Is this the perfect mipmap for us?
							if (pImageBuffer->GetSize() == m_vNewSize) {
								// We're done, get us out of this loop right now! :D
								break;
							} else {
								// Throw away this mipmap
								pImagePart->DeleteMipmap(*pImageBuffer);
							}
						} else {
							bSuccess = false;
						}
					}
				} else {
					bSuccess = false;
				}
			}
		}

		// Success?
		if (bSuccess)
			return true; // Done

		// Restore the original image
		cImage = cOriginalImage;
	}

	// We have to scale in the classic and slow way... call the base implementation
	return ImageEffect::Apply(cImage);
}

bool IEScale::Apply(ImageBuffer &cImageBuffer) const
{
	// Get dimensions
	const uint32 nNewWidth  = m_vNewSize.x;
	const uint32 nNewHeight = m_vNewSize.y;
	const uint32 nOldWidth  = cImageBuffer.GetSize().x;
	const uint32 nOldHeight = cImageBuffer.GetSize().y;

	// [TODO] 3D support
	// [TODO] Currently we only support 'scale down'
	// New width and new height must be >0, ColorPalette as color format is not supported
	if (cImageBuffer.GetColorFormat() != ColorPalette && nNewWidth <= nOldWidth && nNewHeight <= nOldHeight && nNewWidth && nNewHeight) {
		// 3x3 filter matrix
		static const Matrix3x3 mFilter(0.1f, 0.5f, 0.1f,
									   0.5f, 1.0f, 0.5f,
									   0.1f, 0.5f, 0.1f);

		// Create the new image buffer
		ImageBuffer cOldImageBuffer = cImageBuffer;
		// [TODO] Currently compressing data is not implemented, yet
		cImageBuffer.CreateImage(cOldImageBuffer.GetDataFormat(), cOldImageBuffer.GetColorFormat(), Vector3i(nNewWidth, nNewHeight, 1));
//		cImageBuffer.CreateImage(cOldImageBuffer.GetDataFormat(), cOldImageBuffer.GetColorFormat(), Vector3i(nNewWidth, nNewHeight, 1), cOldImageBuffer.GetCompression());

		// Process data format dependent
		switch (cImageBuffer.GetDataFormat()) {
			case DataByte:
			{
				ScaleDownData<uint8> cScaleDownData(cOldImageBuffer, cImageBuffer, nNewWidth, nNewHeight, nOldWidth, nOldHeight, mFilter);
				break;
			}

			case DataWord:
			{
				ScaleDownData<uint16> cScaleDownData(cOldImageBuffer, cImageBuffer, nNewWidth, nNewHeight, nOldWidth, nOldHeight, mFilter);
				break;
			}

			case DataFloat:
			{
				ScaleDownData<float> cScaleDownData(cOldImageBuffer, cImageBuffer, nNewWidth, nNewHeight, nOldWidth, nOldHeight, mFilter);
				break;
			}

			case DataDouble:
			{
				ScaleDownData<double> cScaleDownData(cOldImageBuffer, cImageBuffer, nNewWidth, nNewHeight, nOldWidth, nOldHeight, mFilter);
				break;
			}
		}

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
