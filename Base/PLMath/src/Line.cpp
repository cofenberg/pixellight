/*********************************************************\
 *  File: Line.cpp                                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/Matrix3x3.h"
#include "PLMath/Matrix3x4.h"
#include "PLMath/Matrix4x4.h"
#include "PLMath/Line.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Transformation                                        ]
//[-------------------------------------------------------]
Line Line::operator *(const Matrix3x3 &mRot) const
{
	Line cLine;
	cLine.vStart = mRot*vStart;
	cLine.vEnd   = mRot*vEnd;
	return cLine;
}

Line Line::operator *(const Matrix3x4 &mTrans) const
{
	Line cLine;
	cLine.vStart = mTrans*vStart;
	cLine.vEnd   = mTrans*vEnd;
	return cLine;
}

Line Line::operator *(const Matrix4x4 &mTrans) const
{
	Line cLine;
	cLine.vStart = mTrans*vStart;
	cLine.vEnd   = mTrans*vEnd;
	return cLine;
}

Line &Line::operator *=(const Matrix3x3 &mRot)
{
	vStart *= mRot;
	vEnd   *= mRot;
	return *this;
}

Line &Line::operator *=(const Matrix3x4 &mTrans)
{
	vStart *= mTrans;
	vEnd   *= mTrans;
	return *this;
}

Line &Line::operator *=(const Matrix4x4 &mTrans)
{
	vStart *= mTrans;
	vEnd   *= mTrans;
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
