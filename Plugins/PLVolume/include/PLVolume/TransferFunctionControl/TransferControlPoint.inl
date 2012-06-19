/*********************************************************\
 *  File: TransferControlPoint.inl                       *
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
*    Default constructor
*/
inline TransferControlPoint::TransferControlPoint() :
	m_nIsoValue(0),
	m_fValue(0.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
inline TransferControlPoint::TransferControlPoint(const TransferControlPoint &cSource) :
	m_nIsoValue(cSource.m_nIsoValue),
	m_fValue(cSource.m_fValue)
{
}

/**
*  @brief
*    Constructor for iso-value + value
*/
inline TransferControlPoint::TransferControlPoint(PLCore::uint32 nIsoValue, float fValue) :
	m_nIsoValue(nIsoValue),
	m_fValue(fValue)
{
}

/**
*  @brief
*    Destructor
*/
inline TransferControlPoint::~TransferControlPoint()
{
}

/**
*  @brief
*    Copy operator
*/
inline TransferControlPoint &TransferControlPoint::operator =(const TransferControlPoint &cSource)
{
	// Copy data
	m_nIsoValue = cSource.m_nIsoValue;
	m_fValue    = cSource.m_fValue;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
inline bool TransferControlPoint::operator ==(const TransferControlPoint &cOther) const
{
	// Compare data (no epsilon environment in here)
	return (m_nIsoValue == cOther.m_nIsoValue && m_fValue == cOther.m_fValue);
}

/**
*  @brief
*    Returns the iso-value
*/
inline PLCore::uint32 TransferControlPoint::GetIsoValue() const
{
	return m_nIsoValue;
}

/**
*  @brief
*    Sets the iso-value
*/
inline void TransferControlPoint::SetIsoValue(PLCore::uint32 nIsoValue)
{
	m_nIsoValue = nIsoValue;
}

/**
*  @brief
*    Returns the value
*/
float TransferControlPoint::GetValue() const
{
	return m_fValue;
}

/**
*  @brief
*    Sets the value
*/
inline void TransferControlPoint::SetValue(float fValue)
{
	m_fValue = fValue;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
