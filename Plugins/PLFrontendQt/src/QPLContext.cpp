/*********************************************************\
 *  File: QPLContext.cpp                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/RendererContext.h>
#include "PLFrontendQt/Application.h"
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/QPLContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
namespace PLFrontendQt {


QPLContext::QPLContext(const QString &sPainterName, RendererContext *pRendererContext) : QObject(),
	m_pRendererContext(pRendererContext ? pRendererContext : qApp->GetRendererContext()),
	m_sPainterName(sPainterName)
{
}

QPLContext::~QPLContext()
{
}

void QPLContext::Update()
{
	if (m_pRendererContext)
		m_pRendererContext->Update();
}

SurfacePainter *QPLContext::CreateSurfacePainter()
{
	return GetRendererContext() ? GetRendererContext()->GetRenderer().CreateSurfacePainter(QtStringAdapter::QtToPL(m_sPainterName)) : nullptr;
}

RendererContext *QPLContext::GetRendererContext()
{
	return m_pRendererContext;
}

const QString &QPLContext::GetPainterName()
{
	return m_sPainterName;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt
