/*********************************************************\
 *  File: CubicSpline.inl                                *
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
inline CubicSpline::CubicSpline()
{
}

/**
*  @brief
*    Constructor
*/
inline CubicSpline::CubicSpline(float _a, float _b, float _c, float _d) :
	a(_a),
	b(_b),
	c(_c),
	d(_d)
{
}

/**
*  @brief
*    Copy constructor
*/
inline CubicSpline::CubicSpline(const CubicSpline &cSource) :
	a(cSource.a),
	b(cSource.b),
	c(cSource.c),
	d(cSource.d)
{
}

/**
*  @brief
*    Destructor
*/
inline CubicSpline::~CubicSpline()
{
}

/**
*  @brief
*    Copy operator
*/
inline CubicSpline &CubicSpline::operator =(const CubicSpline &cSource)
{
	// Copy coefficients
	a = cSource.a;
	b = cSource.b;
	c = cSource.c;
	d = cSource.d;

	// Return a reference to this instance
	return *this;
}

/**
*  @brief
*    Comparison operator
*/
inline bool CubicSpline::operator ==(const CubicSpline &cOther) const
{
	// Compare coefficients (no epsilon environment in here)
	return (a == cOther.a && b == cOther.b && c == cOther.c && d == cOther.d);
}

/**
*  @brief
*    Evaluate value using a cubic equation
*/
inline float CubicSpline::GetValueOnSpline(float fValue) const
{
	return (((d*fValue) + c)*fValue + b)*fValue + a;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
