/*********************************************************\
 *  File: SPK_PLLineTrailRenderer.h                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __SPARK_PL_LINETRAILRENDERER_H__
#define __SPARK_PL_LINETRAILRENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace SPK {
	class Group;
	class Particle;
}
namespace SPARK_PL {
	class SPK_PLBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An abstract Renderer drawing particles as line trails defined by the positions of particles over time
*
*  @remarks
*    The trail coordinates are computed in a procedural manner over time.<br>
*    A trail i defined by a duration. The faster the particle, the longer the trail. It is defined by a numbers of samples.<br>
*    The sampling frequency of the trail is therefore computed by m_nNumOfSamples/duration and defines its resolution.<br>
*    The higher the sampling frequency, the smoother the trail but the bigger the computation time and the memory consumption.<br>
*    <br>
*    All the particles of a Group are rendered in a single batch of GL_LINE_STRIP,
*    which means every trails belong to the same object to reduce overhead on GPU side.<br>
*    To allow that, invisible lines link trails together. They are defined as degenerated lines.<br>
*    This imposes the alpha value is taken into account and the blending is therefore forced with SPK_PLLineTrailRenderer.<br>
*    The user has the possibility to set the RGBA values of degenerated lines to keep them invisible function of the blending mode and environment.<br>
*    By default it is set to (0.0f,0.0f,0.0f,0.0f).
*    <br>
*    Below are the parameters of Particle that are used in this Renderer (others have no effects) :
*    <ul>
*    <li>SPK::PARAM_RED</li>
*    <li>SPK::PARAM_GREEN</li>
*    <li>SPK::PARAM_BLUE</li>
*    <li>SPK::PARAM_ALPHA</li>
*    </ul>
*
*  @note
*    - Basing on "SPK::GL::GLLineTrailRenderer" (this includes most of the comments)
*/
class SPK_PLLineTrailRenderer : public SPK_PLRenderer {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor of SPK_PLLineTrailRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLLineTrailRenderer();

		/**
		*  @brief
		*    Gets the number of samples per trail
		*
		*  @return
		*    The number of samples per trail
		*/
		SPARK_PL_API PLCore::uint32 GetNumOfSamples() const;

		/**
		*  @brief
		*    Sets the number of samples in a trail
		*
		*  @param[in] nNumOfSamples
		*    The number of samples to construct the trails
		*
		*  @remarks
		*    The number of samples defines the number of points used to construct the trail.<br>
		*    The bigger the number of samples, the smoother the trail but the bigger the computation time and the memory consumption.
		*/
		SPARK_PL_API void SetNumOfSamples(PLCore::uint32 nNumOfSamples);

		/**
		*  @brief
		*    Gets the width of a trail
		*
		*  @return
		*    The width of a trail (in pixels)
		*/
		SPARK_PL_API float GetWidth() const;

		/**
		*  @brief
		*    Sets the width of a trail
		*
		*  @param[in] fWidth
		*    The width of trails in pixels
		*
		*  @remarks
		*    Like for SPK_PLLineRenderer, the width is defined in pixels and is not dependant of the distance of the trail from the camera
		*/
		SPARK_PL_API void SetWidth(float fWidth);

		/**
		*  @brief
		*    Gets the duration of a sample
		*
		*  @return
		*    The duration of a sample
		*/
		SPARK_PL_API float GetDuration() const;

		/**
		*  @brief
		*    Sets the duration of a sample
		*
		*  @param[in] fDuration
		*    The duration of a sample
		*
		*  @remarks
		*    The duration of a sample is defined by its life time from its creation to its destruction.<br>
		*    Note that the alpha of a sample will decrease linearly from its initial alpha to 0.
		*/
		SPARK_PL_API void SetDuration(float fDuration);

		/**
		*  @brief
		*    Gets the color components of degenerated lines
		*
		*  @return
		*    The color components of degenerated lines
		*/
		SPARK_PL_API const PLGraphics::Color4 &GetDegeneratedLines() const;

		/**
		*  @brief
		*    Sets the color components of degenerated lines
		*
		*  @param[in] cColor
		*    The color components of degenerated lines
		*/
		SPARK_PL_API void SetDegeneratedLines(const PLGraphics::Color4 &cColor);

		/**
		*  @brief
		*    Inits all the trails of the particle of the group
		*
		*  @param[in] cGroup
		*    The Group whose buffers need to be initialized
		*
		*  @remarks
		*    All the samples are set to the current position of the particle.<br>
		*    The trail of each particle has therefore a length of 0 and is ready for update.<br>
		*    This function allows to clear the buffers for SPK_PLLineTrailRenderer of the given group.
		*/
		SPARK_PL_API void Init(const SPK::Group &cGroup);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::BufferHandler functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void createBuffers(const SPK::Group &group) override;
		SPARK_PL_API virtual void destroyBuffers(const SPK::Group &group) override;


	//[-------------------------------------------------------]
	//[ Protected virtual SPK::BufferHandler functions        ]
	//[-------------------------------------------------------]
	protected:
		SPARK_PL_API virtual bool checkBuffers(const SPK::Group &group) override;


	//[-------------------------------------------------------]
	//[ Protected definitions                                 ]
	//[-------------------------------------------------------]
	protected:
		static const std::string VertexBufferName;
		static const std::string ColorBufferName;
		static const std::string ValueBufferName;
		static const std::string PLBufferName;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor of SPK_PLLineTrailRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*/
		SPK_PLLineTrailRenderer(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Inits a given particle
		*
		*  @param[in] cParticle
		*    Particle to initialize
		*  @param[in] fAge
		*    Particle age
		*/
		void Init(const SPK::Particle &cParticle, float fAge);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SPK_PLBuffer	  *m_pSPK_PLBuffer;	/**< Used SPK_PLBuffer instance, can be a null pointer */
		PLCore::uint32 	   m_nNumOfSamples;	/**< The number of samples to construct the trails */
		float			   m_fWidth;		/**< The width of trails in pixels */
		float			   m_fDuration;		/**< The duration of a sample */
		PLGraphics::Color4 m_cColor;		/**< The color components of degenerated lines */

		// Vertex buffers and iterators - not nice, but more performant as passing them around all over the place
		float *m_pfVertexBuffer;
		float *m_pfVertexIterator;
		float *m_pfColorBuffer;
		float *m_pfColorIterator;
		float *m_pfValueBuffer;
		float *m_pfValueIterator;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_LINETRAILRENDERER_H__
