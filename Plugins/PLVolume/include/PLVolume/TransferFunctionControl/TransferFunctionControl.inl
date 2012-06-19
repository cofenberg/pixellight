/*********************************************************\
 *  File: TransferFunctionControl.inl                    *
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the list of transfer function channels
*/
inline PLCore::Array<TransferFunctionChannel*> &TransferFunctionControl::GetChannels()
{
	// Cached image ise now considered to be dirty
	m_bImageDirty = true;

	// Return the list of transfer function channels
	return m_lstTransferControlChannels;
}

/**
*  @brief
*    Returns the list of transfer function channels
*/
inline const PLCore::Array<TransferFunctionChannel*> &TransferFunctionControl::GetChannels() const
{
	// Return the list of transfer function channels
	return m_lstTransferControlChannels;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
