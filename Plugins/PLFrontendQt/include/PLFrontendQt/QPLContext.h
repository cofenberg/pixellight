/*********************************************************\
 *  File: QPLContext.h                                   *
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


#ifndef __PLFRONTENDQT_QPLCONTEXT_H__
#define __PLFRONTENDQT_QPLCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <QtCore/QObject>
#include <PLCore/Core/AbstractContext.h>
#include "PLFrontendQt/PLFrontendQt.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
	class RendererContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    This class defines an basic context which holds all needed information for rendering something via the painter interface of PixelLight
*
*  @remarks
*    These information are:
*    - The Name of the to be used surface painter. A surface painter is used to draw something onto a surface (eg. a window) for more information see the documentation of the SurfacePainter class
*    - The renderer context. A renderer context holds an instance of an renderer (eg. OpengGL, DirectX) which is used by an surface painter to draw something.
*/
class PLFRONTENDQT_API QPLContext : public QObject, public PLCore::AbstractContext {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Qt signals (MOC)                                      ]
	//[-------------------------------------------------------]
	signals:
		void BeginContextChange();
		void ContextChanged();
		void EndContextChange();


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sPainterName
		*    The name of the painter to be used by an surface. Defaults to "PLRenderer::SPDefault" an SurfacePainter which clears only the surface to an black background and shows the PixelLight logo.
		*  @param[in] pRendererContext
		*    The renderer context to be used for creating the actual surface painter. If this param is an nullptr then the renderer context of the Application is used
		*/
		QPLContext(const QString &sPainterName = "PLRenderer::SPDefault", PLRenderer::RendererContext *pRendererContext = nullptr);
		virtual ~QPLContext();

		/**
		*  @brief
		*    Updates the renderer context
		*/
		virtual void Update();

		/**
		*  @brief
		*    Creates an an instance of an SurfacePainter. Which SurfacePainter class should be used is determined via the PainterName given when the Context was constructed
		*
		*  @return
		*    An SurfacePainter instance, an nullptr on error (e.g. the SurfacePainter with the given name isn't known by the PixelLight RTTI system)
		*/
		virtual PLRenderer::SurfacePainter *CreateSurfacePainter();

		/**
		*  @brief
		*    Returns the renderer context instance of this context.
		*
		*  @return
		*    An RendererContext instance, can be nullptr (e.g. the Application class couldn't create an renderer context)
		*/
		PLRenderer::RendererContext *GetRendererContext();

		const QString &GetPainterName();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RendererContext	*m_pRendererContext;
		QString m_sPainterName;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_QPLCONTEXT_H__
