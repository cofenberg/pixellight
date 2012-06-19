/*********************************************************\
 *  File: TransferFunction.h                             *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUME_TRANSFERFUNCTION_H__
#define __PLVOLUME_TRANSFERFUNCTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Image/Image.h>
#include "PLVolume/PLVolume.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
	class TextureBuffer;
	class ResourceHandler;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Transfer function
*/
class TransferFunction : public PLCore::Loadable {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		enum ETextureBufferType {
			StandardTextureBuffer,		/**< Texture buffer without any special applied features */
			PreMultipliedTextureBuffer,	/**< Texture buffer with pre-multipied color by their corresponding opacity value in order to avoid color bleeding due to interpolation */
			PreIntegratedTextureBuffer,	/**< Texture buffer with pre-integration */
			// Number of texture buffer types
			NumOfTextureBufferTypes
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUME_API TransferFunction();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUME_API virtual ~TransferFunction();

		/**
		*  @brief
		*    Returns the number of bins
		*
		*  @return
		*    The number of bins
		*/
		PLVOLUME_API PLCore::uint32 GetNumOfBins() const;

		/**
		*  @brief
		*    Returns the renderer texture buffer holding the transfer function
		*
		*  @param[in] cRenderer
		*    Used renderer instance
		*  @param[in] nType
		*    Texture buffer type
		*
		*  @return
		*    Renderer texture buffer holding the transfer function, can be a null pointer
		*
		*  @remarks
		*    The texture type can be "PLRenderer::Resource::TypeTextureBuffer1D".
		*/
		PLVOLUME_API PLRenderer::TextureBuffer *GetTextureBuffer(PLRenderer::Renderer &cRenderer, ETextureBufferType nType = StandardTextureBuffer);


	//[-------------------------------------------------------]
	//[ Public virtual TransferFunction functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the image holding the transfer function
		*
		*  @return
		*    The image holding the transfer function
		*
		*  @note
		*    - This method marks the image data to be dirty, meaning potential change by user, use the constant method version of this method whenever possible to avoid unnecessary recalculations
		*/
		PLVOLUME_API virtual PLGraphics::Image &GetImage();

		/**
		*  @brief
		*    Returns the image holding the transfer function
		*
		*  @return
		*    The image holding the transfer function
		*/
		PLVOLUME_API virtual const PLGraphics::Image &GetConstImage();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLVOLUME_API virtual bool Unload() override;
		PLVOLUME_API virtual PLCore::String GetLoadableTypeName() const override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		TransferFunction(const TransferFunction &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		TransferFunction &operator =(const TransferFunction &cSource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		PLGraphics::Image			 m_cImage;											/**< Image holding the transfer data (may be derived from data, access it via "GetImage()") */
		// Cached texture buffer
		PLRenderer::ResourceHandler *m_pTextureBufferHandler[NumOfTextureBufferTypes];	/**< Renderer texture buffer holding the transfer function, can be a null pointer (from "m_cImage" derived data, access it via "GetTextureBuffer()") */
		bool						 m_bTextureBufferDirty[NumOfTextureBufferTypes];	/**< Is the renderer texture buffer holding the transfer function marked to be dirty? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


#endif // __PLVOLUME_TRANSFERFUNCTION_H__
