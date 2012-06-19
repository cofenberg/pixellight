/*********************************************************\
 *  File: TransferFunctionWidget.cpp                     *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtGui/qevent.h>
PL_WARNING_POP
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color4.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/Renderer/TextureBuffer.h>
#include <PLVolume/TransferFunctionControl/Histogram.h>
#include <PLVolume/TransferFunctionControl/TransferFunctionChannel.h>
#include <PLVolume/TransferFunctionControl/TransferFunctionControl.h>
#include <PLVolume/Volume.h>
#include "PLVolumeGui/DockWidgetVolumeTransferFunction.h"
#include "PLVolumeGui/TransferFunctionWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
namespace PLVolumeGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
TransferFunctionWidget::TransferFunctionWidget(DockWidgetVolumeTransferFunction &cDockWidgetVolumeTransferFunction, PLVolume::Volume &cVolume, QWidget *pQWidgetParent) : QLabel(pQWidgetParent),
	m_pDockWidgetVolumeTransferFunction(&cDockWidgetVolumeTransferFunction),
	m_pVolume(&cVolume),
	m_pHistogram(nullptr),
	m_pHistogramImage(nullptr),
	m_pComposedImage(nullptr),
	m_nSelectedChannel(-1),
	m_nSelectedControlPoint(-1),
	m_bLeftMouseButtonDown(false)
{
	// By default the alignment is set to center resulting within a mouse position offset within e.g. "mousePressEvent()" and
	// I was unable to figure out were to find the offset to the QPixmap coordinate system. Simple solution: Don't center.
	setAlignment(Qt::AlignTop | Qt::AlignLeft);

	// Create a histogram instance by using the base map of the volume data
	m_pHistogram = m_pVolume->CreateHistogram();
	if (m_pHistogram) {
		// Normalize the histogram (linear histogram is converted into a logarithmic histogram)
		PLVolume::Histogram cNormalizedHistogram = *m_pHistogram;
		cNormalizedHistogram.NormalizeLogarithmic();

		// Create the histogram image instance and fill it
		m_pHistogramImage = new Image();
		cNormalizedHistogram.ToNormalizedImage(256, *m_pHistogramImage, Color4::White, Color4::Black);
	}

	// Update the composed image
	UpdateComposedImage();

	// Update the Qt pixmap by using the content of the composed image
	UpdatePixmap();

	// Enable mouse tracking so we're also getting "mouseMoveEvent()" calls if currently no mouse button is pressed
	setMouseTracking(true);
}

/**
*  @brief
*    Destructor
*/
TransferFunctionWidget::~TransferFunctionWidget()
{
	// Destroy previous data
	if (m_pHistogram) {
		delete m_pHistogram;
		m_pHistogram = nullptr;
	}
	if (m_pHistogramImage) {
		delete m_pHistogramImage;
		m_pHistogramImage = nullptr;
	}
	if (m_pComposedImage) {
		delete m_pComposedImage;
		m_pComposedImage = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual QWidget functions                   ]
//[-------------------------------------------------------]
void TransferFunctionWidget::mousePressEvent(QMouseEvent *pQMouseEvent)
{
	// Is there an composed image and was the left mouse button pressed?
	if (m_pComposedImage && pQMouseEvent->button() == Qt::LeftButton) {
		// The left mouse button is now down
		m_bLeftMouseButtonDown = true;

		// Backup the current mouse position
		m_vPreviousMousePosition = pQMouseEvent->pos();

		// Get the image buffer
		ImageBuffer *pImageBuffer = m_pComposedImage->GetBuffer();
		if (pImageBuffer) {
			// Get transfer function control instance and transfer function channel instance
			PLVolume::TransferFunctionControl &cTransferFunctionControl = m_pVolume->GetTransferFunctionControl();
			const Array<PLVolume::TransferFunctionChannel*> &cTransferFunctionChannel = cTransferFunctionControl.GetChannels();

			// Update composed image?
			float fControlPointDistance = FLT_MAX;

			// Loop through all channels
			const int nPreviousSelectedChannel      = m_nSelectedChannel;
			const int nPreviousSelectedControlPoint = m_nSelectedControlPoint;
			for (uint32 nChannel=0; nChannel<cTransferFunctionChannel.GetNumOfElements(); nChannel++) {
				// Get the current selected control point
				float fCurrentControlPointDistance = FLT_MAX;
				const int nSelectedControlPoint = cTransferFunctionControl.GetControlPointOnImage(nChannel, pImageBuffer->GetSize().y, pQMouseEvent->x(), pQMouseEvent->y(), &fCurrentControlPointDistance);
				if (nSelectedControlPoint >= 0 && fControlPointDistance > fCurrentControlPointDistance) {
					m_nSelectedChannel      = nChannel;
					m_nSelectedControlPoint = nSelectedControlPoint;
					fControlPointDistance   = fCurrentControlPointDistance;
				}
			}

			// Update composed image?
			if (m_nSelectedChannel != nPreviousSelectedChannel || m_nSelectedControlPoint != nPreviousSelectedControlPoint) {
				// Update the composed image
				UpdateComposedImage();

				// Update the Qt pixmap by using the content of the composed image
				UpdatePixmap();
			}
		}
	}
}

void TransferFunctionWidget::mouseReleaseEvent(QMouseEvent *pQMouseEvent)
{
	// Is there an composed image and was the left mouse button released?
	if (pQMouseEvent->button() == Qt::LeftButton) {
		// The left mouse button is no longer down
		m_bLeftMouseButtonDown = false;

		// Any channel control point selected?
		if (m_nSelectedChannel >= 0 && m_nSelectedControlPoint >= 0) {
			// Reset the shape of the mouse cursor
			setCursor(QCursor());
		}
	}
}

void TransferFunctionWidget::mouseMoveEvent(QMouseEvent *pQMouseEvent)
{
	// Get transfer function control instance and transfer function channel instance
	PLVolume::TransferFunctionControl &cTransferFunctionControl = m_pVolume->GetTransferFunctionControl();
	const Array<PLVolume::TransferFunctionChannel*> &cTransferFunctionChannel = cTransferFunctionControl.GetChannels();

	// Is the left mouse button currently down?
	if (m_bLeftMouseButtonDown) {
		// Is there an composed image and any control point selected?
		if (m_pComposedImage && m_nSelectedChannel >= 0 && m_nSelectedControlPoint >= 0) {
			// Change the shape of the mouse cursor into a closed hand
			setCursor(Qt::ClosedHandCursor);

			// Get the mouse movement delta
			const QPoint cQPointDelta = pQMouseEvent->pos() - m_vPreviousMousePosition;

			// Backup the current mouse position
			m_vPreviousMousePosition = pQMouseEvent->pos();

			// Update control point?
			if (!cQPointDelta.isNull()) {
				// Get transfer function control instance
				PLVolume::TransferFunctionControl &cTransferFunctionControl = m_pVolume->GetTransferFunctionControl();

				// Get the image buffer
				ImageBuffer *pImageBuffer = m_pComposedImage->GetBuffer();
				if (pImageBuffer) {
					// Update control point
					cTransferFunctionControl.MoveTransferControlPoint(m_nSelectedChannel, m_nSelectedControlPoint, PLMath::Vector2(static_cast<float>(cQPointDelta.x()), -cQPointDelta.y()/static_cast<float>(pImageBuffer->GetSize().y)));

					// [TODO] Do this only on update
					// Update the composed image
					UpdateComposedImage();

					// Update the Qt pixmap by using the content of the composed image
					UpdatePixmap();
				}
			}
		}
	} else {
		// Get the image buffer
		ImageBuffer *pImageBuffer = m_pComposedImage->GetBuffer();
		if (pImageBuffer) {
			// Is the mouse over a control point?
			bool bMouseOverControlPoint = false;
			for (uint32 nChannel=0; nChannel<cTransferFunctionChannel.GetNumOfElements(); nChannel++) {
				if (cTransferFunctionControl.GetControlPointOnImage(nChannel, pImageBuffer->GetSize().y, pQMouseEvent->x(), pQMouseEvent->y()) >= 0) {
					bMouseOverControlPoint = true;
					nChannel = cTransferFunctionChannel.GetNumOfElements();
				}
			}

			// Change the shape of the mouse cursor
			setCursor(bMouseOverControlPoint ? Qt::PointingHandCursor : QCursor());
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the composed image
*/
void TransferFunctionWidget::UpdateComposedImage()
{
	// There must ba a histogram image instance
	if (m_pHistogram) {
		// Get transfer function control instance and transfer function channel instance
		PLVolume::TransferFunctionControl &cTransferFunctionControl = m_pVolume->GetTransferFunctionControl();
		const Array<PLVolume::TransferFunctionChannel*> &cTransferFunctionChannel = cTransferFunctionControl.GetChannels();

		// Create composed image instance, if required
		if (!m_pComposedImage)
			m_pComposedImage = new Image();

		// Use histogram image as background
		*m_pComposedImage = *m_pHistogramImage;

		// Add the final transfer function color values to an image representation, bins along the x axis, values along the y-axis
		for (uint32 nChannel=0; nChannel<cTransferFunctionChannel.GetNumOfElements(); nChannel++)
			cTransferFunctionControl.AddToImage(*m_pComposedImage, nChannel, cTransferFunctionChannel[nChannel]->GetVisualizationColor());

		// Add the alpha control points to an image representation, bins along the x axis, values along the y-axis
		for (uint32 nChannel=0; nChannel<cTransferFunctionChannel.GetNumOfElements(); nChannel++)
			cTransferFunctionControl.AddControlPointsToImage(*m_pComposedImage, nChannel, cTransferFunctionChannel[nChannel]->GetVisualizationColor(), Color3::Null, (m_nSelectedChannel == static_cast<int>(nChannel)) ? m_nSelectedControlPoint : -1);
//			cTransferFunctionControl.AddControlPointsToImage(*m_pComposedImage, nChannel, cTransferFunctionChannel[nChannel]->GetVisualizationColor(), Color3::Gray, (m_nSelectedChannel == static_cast<int>(nChannel)) ? m_nSelectedControlPoint : -1);
	}
}

/**
*  @brief
*    Updates the Qt pixmap by using the content of the composed image
*/
void TransferFunctionWidget::UpdatePixmap()
{
	// Is there an composed image
	if (m_pComposedImage) {
		// Create QPixmap
		QPixmap cQPixmap;

		// Get the image buffer
		ImageBuffer *pImageBuffer = m_pComposedImage->GetBuffer();
		if (pImageBuffer) {
			const uint8 *pnData = pImageBuffer->GetData();
			QImage cQImage(static_cast<const uchar*>(pnData), pImageBuffer->GetSize().width, pImageBuffer->GetSize().height, QImage::Format_ARGB32);
			cQPixmap = QPixmap::fromImage(cQImage.rgbSwapped());

			// Resize Qt widget
			resize(pImageBuffer->GetSize().width, pImageBuffer->GetSize().height);
		}

		// Set Qt pixmap
		setPixmap(cQPixmap);
	} else {
		// Set empty Qt pixmap
		setPixmap(QPixmap());
	}

	// [TODO] Remove this
	m_pDockWidgetVolumeTransferFunction->UpdateTransferFunctionResult();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeGui
