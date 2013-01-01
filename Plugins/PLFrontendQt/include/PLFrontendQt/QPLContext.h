/*********************************************************\
 *  File: QPLContext.h                                   *
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
