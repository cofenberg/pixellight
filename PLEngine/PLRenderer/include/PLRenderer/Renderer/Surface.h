/*********************************************************\
 *  File: Surface.h                                      *
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


#ifndef __PLRENDERER_SURFACE_H__
#define __PLRENDERER_SURFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/List.h>
#include <PLMath/Vector2i.h>
#include <PLCore/Base/Event/Event.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;
class SurfaceHandler;
class SurfacePainter;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer surface where we can render in
*/
class Surface {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;
	friend class SurfaceHandler;
	friend class SurfacePainter;
	friend class RendererBackend;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Surface types
		*/
		enum EType {
			Window        = 0,	/**< Render to window */
			TextureBuffer = 1	/**< Render to texture buffer */
		};


	//[-------------------------------------------------------]
	//[ Events                                                ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>	EventPaintBegin;	/**< Paint begin event - emitted BEFORE any painting begins */
		PLCore::Event<>	EventPaint;			/**< Paint event - emitted BEFORE any painting */
		PLCore::Event<>	EventPaintEnd;		/**< Paint end event - emitted AFTER any painting ends */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~Surface();

		/**
		*  @brief
		*    Returns the owner renderer
		*
		*  @return
		*    The owner renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;

		/**
		*  @brief
		*    Returns the surface type
		*
		*  @return
		*    Surface type
		*/
		PLRENDERER_API EType GetType() const;

		/**
		*  @brief
		*    Returns whether the surface is active or not
		*
		*  @return
		*    'true' if the surface is active, else 'false'
		*/
		PLRENDERER_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the surface is active or not
		*
		*  @param[in] bActive
		*    'true' if the surface is active, else 'false'
		*/
		PLRENDERER_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Returns the surface painter
		*
		*  @return
		*    The surface painter, a null pointer if there's no surface painter
		*/
		PLRENDERER_API SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set a surface painter
		*
		*  @param[in] pPainter
		*    Pointer to the surface painter, can be a null pointer
		*  @param[in] bDestroy
		*    Destroy the current set surface painter? (if there's one)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    The painter will be destroyed by the surface, so don't delete it again!
		*/
		PLRENDERER_API bool SetPainter(SurfacePainter *pPainter, bool bDestroy = true);

		/**
		*  @brief
		*    Updates the surface
		*
		*  @remarks
		*    Just calls the OnPaint() function if there's a surface painter and if this surface
		*    is active.
		*/
		PLRENDERER_API void Update();

		/**
		*  @brief
		*    Returns the whether the surface is flipped along the y axis
		*
		*  @return
		*    'true' if the surface is flipped along the y axis, else 'false'
		*/
		PLRENDERER_API bool IsSwapY() const;

		/**
		*  @brief
		*    Sets the whether the surface is flipped along the y axis
		*
		*  @param[in] bSwapY
		*    'true' if the surface is flipped along the y axis, else 'false'
		*/
		PLRENDERER_API void SetSwapY(bool bSwapY = false);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the size of this renderer surface
		*
		*  @return
		*    The size of this renderer surface
		*/
		virtual PLMath::Vector2i GetSize() const = 0;

		/**
		*  @brief
		*    Returns the whether the surface is flipped along the y axis
		*
		*  @return
		*    'true' if the surface is flipped along the y axis, else 'false'
		*
		*  @note
		*    - By overwriting this function, the renderer backend can deside by itself how
		*      to flip the surface
		*/
		PLRENDERER_API virtual bool IsAPISwapY() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nType
		*    Surface type
		*/
		PLRENDERER_API Surface(Renderer &cRenderer, EType nType);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initializes the surface
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Init() = 0;

		/**
		*  @brief
		*    De-initializes the surface
		*/
		virtual void DeInit() = 0;

		/**
		*  @brief
		*    Makes this surface to the renderers current render target
		*
		*  @param[in] nFace
		*    Cube map face to render in (0-5) - only used if this is a cube texture buffer render target
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool MakeCurrent(PLGeneral::uint8 nFace = 0) = 0;

		/**
		*  @brief
		*    Unmakes this surface from the renderers current render target
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API virtual bool UnmakeCurrent();

		/**
		*  @brief
		*    Presents the contents of the next buffer in the sequence
		*    of back buffers owned by the device
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Present() = 0;

		/**
		*  @brief
		*    Backups the surface device data
		*
		*  @note
		*    - Used for instance if the diplay mode is changed to backup/restore
		*      all surface device data
		*    - Normally only used inside Renderer::BackupDeviceObjects()/Renderer::RestoreDeviceObjects()
		*/
		PLRENDERER_API virtual void BackupDeviceData();

		/**
		*  @brief
		*    Restores the surface device data
		*
		*  @see
		*    - BackupDeviceData()
		*/
		PLRENDERER_API virtual void RestoreDeviceData();


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
		Surface(const Surface &cSource);

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
		Surface &operator =(const Surface &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Renderer	   *m_pRenderer;	/**< Owner renderer (always valid!) */
		EType			m_nType;		/**< Surface type */
		bool			m_bActive;		/**< Is the surface active? */
		bool			m_bSwapY;		/**< Is the surface flipped along the y axis? */
		SurfacePainter *m_pPainter;		/**< The used surface painter, can be a null pointer */
		/** List of surface handlers */
		PLGeneral::List<SurfaceHandler*> m_lstHandler;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SURFACE_H__
