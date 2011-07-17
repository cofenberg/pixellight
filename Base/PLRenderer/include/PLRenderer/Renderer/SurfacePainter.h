/*********************************************************\
 *  File: SurfacePainter.h                               *
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


#ifndef __PLRENDERER_SURFACEPAINTER_H__
#define __PLRENDERER_SURFACEPAINTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Surface;
class Renderer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract surface painter base class
*
*  @note
*    - Derived classes should use a 'SP' name prefix (example: SPPreview)
*/
class SurfacePainter : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Surface;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, SurfacePainter, "PLRenderer", PLCore::Object, "Abstract surface painter base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Copy constructor (not implemented!)
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		SurfacePainter(const SurfacePainter &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLRENDERER_API SurfacePainter(Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~SurfacePainter();

		/**
		*  @brief
		*    Is called when the owner surface is paint process begins
		*
		*  @param[in] cSurface
		*    Surface we're painting on
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API virtual bool OnPaintBegin(Surface &cSurface);

		/**
		*  @brief
		*    Is called when the owner surface is painted
		*
		*  @param[in] cSurface
		*    Surface we're painting on
		*/
		virtual void OnPaint(Surface &cSurface) = 0;

		/**
		*  @brief
		*    Is called when the owner surface is paint process ends
		*
		*  @param[in] cSurface
		*    Surface we're painting on
		*/
		PLRENDERER_API virtual void OnPaintEnd(Surface &cSurface);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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
		SurfacePainter &operator =(const SurfacePainter &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer *m_pRenderer;	/**< The owner renderer (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SURFACEPAINTER_H__
