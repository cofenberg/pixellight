/*********************************************************\
 *  File: CubicSpline.cpp                                *
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
#include "PLVolume/TransferFunctionControl/CubicSpline.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
// [TODO] Comment/Cleanup
void CubicSpline::CalculateCubicSpline(uint32 n, Array<TransferControlPoint> &v, Array<CubicSpline> &cubic)
{
	if (n) {
		// From: http://graphicsrunner.blogspot.com/2009/01/volume-rendering-102-transfer-functions.html

		float *gamma = new float[n + 1];
		float *delta = new float[n + 1];
		float *D = new float[n + 1];

		// We need to solve the equation
		//	* taken from: http://mathworld.wolfram.com/CubicSpline.html
		//	[2 1       ] [D[0]]   [3(v[1] - v[0])  ]
		//	|1 4 1     | |D[1]|   |3(v[2] - v[0])  |
		//	|  1 4 1   | | .  | = |      .         |
		//	|    ..... | | .  |   |      .         |
		//	|     1 4 1| | .  |   |3(v[n] - v[n-2])|
		//	[       1 2] [D[n]]   [3(v[n] - v[n-1])]

		//	by converting the matrix to upper triangular.
		//	The D[i] are the derivatives at the control points.

		// This builds the coefficients of the left matrix
		gamma[0] = 1.0f / 2.0f;
		for (uint32 i=1; i<n; i++)
			gamma[i] = 1.0f / ((4 * 1.0f) - gamma[i - 1]);
		gamma[n] = 1.0f / ((2 * 1.0f) - gamma[n - 1]);

		delta[0] = 3 * (v[1].GetValue() - v[0].GetValue()) * gamma[0];
		for (uint32 i=1; i<n; i++)
			delta[i] = (3 * (v[i + 1].GetValue() - v[i - 1].GetValue()) - delta[i - 1]) * gamma[i];
		delta[n] = (3 * (v[n].GetValue() - v[n - 1].GetValue()) - delta[n - 1]) * gamma[n];

		D[n] = delta[n];
		for (int i=n-1; i>= 0; i--)
			D[i] = delta[i] - gamma[i] * D[i + 1];

		// Now compute the coefficients of the cubics
		cubic.Clear();
		for (uint32 i=0; i<n; i++)
			cubic.Add(CubicSpline(v[i].GetValue(), D[i], 3*(v[i + 1].GetValue() - v[i].GetValue()) - 2*D[i] - D[i + 1], 2*(v[i].GetValue() - v[i + 1].GetValue()) + D[i] + D[i + 1]));

		delete [] gamma;
		delete [] delta;
		delete [] D;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
