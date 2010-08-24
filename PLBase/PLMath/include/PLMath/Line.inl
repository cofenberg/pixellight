/*********************************************************\
 *  File: Line.inl                                       *
 *      Line inline implementation
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor setting all start- and end-position components to 0
*/
inline Line::Line()
{
}

/**
*  @brief
*    Copy constructor
*/
inline Line::Line(const Line &cSource) :
	vStart(cSource.vStart),
	vEnd(cSource.vEnd)
{
}

/**
*  @brief
*    Copy constructor
*/
inline Line::Line(const Vector3 &vStartPoint, const Vector3 &vEndPoint) :
	vStart(vStartPoint),
	vEnd(vEndPoint)
{
}

/**
*  @brief
*    Destructor
*/
inline Line::~Line()
{
}

/**
*  @brief
*    Copy operator
*/
inline Line &Line::operator =(const Line &cSource)
{
	// Copy data
	vStart = cSource.vStart;
	vEnd   = cSource.vEnd;

	// Return this
	return *this;
}

/**
*  @brief
*    Sets the start and end position of the line
*/
inline void Line::Set(const Vector3 &vStart, const Vector3 &vEnd)
{
	this->vStart = vStart;
	this->vEnd   = vEnd;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
