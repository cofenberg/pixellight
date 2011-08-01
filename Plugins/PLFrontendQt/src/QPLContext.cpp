/*********************************************************\
 *  File: QPLContext.cpp                                 *
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
