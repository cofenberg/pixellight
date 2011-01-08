/*********************************************************\
 *  File: Rectangle.inl                                  *
 *      Rectangle inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor setting all minimum and maximum components to 0
*/
inline Rectangle::Rectangle()
{
}

/**
*  @brief
*    Copy constructor
*/
inline Rectangle::Rectangle(const Rectangle &cSource) :
	vMin(cSource.vMin),
	vMax(cSource.vMax)
{
}

/**
*  @brief
*    Constructor
*/
inline Rectangle::Rectangle(const Vector2 &vMinT, const Vector2 &vMaxT) :
	vMin(vMinT),
	vMax(vMaxT)
{
}

/**
*  @brief
*    Constructor
*/
inline Rectangle::Rectangle(float fMinX, float fMinY, float fMaxX, float fMaxY) :
	vMin(fMinX, fMinY),
	vMax(fMaxX, fMaxY)
{
}

/**
*  @brief
*    Destructor
*/
inline Rectangle::~Rectangle()
{
}

/**
*  @brief
*    Copy operator
*/
inline Rectangle &Rectangle::operator =(const Rectangle &cSource)
{
	// Copy data
	vMin = cSource.vMin;
	vMax = cSource.vMax;

	// Return this
	return *this;
}

/**
*  @brief
*    Returns the center of the rectangle
*/
inline Vector2 Rectangle::GetCenter() const
{
	return Vector2((vMax.x+vMin.x)*0.5f, (vMax.y+vMin.y)*0.5f);
}

/**
*  @brief
*    Returns the x position
*/
inline float Rectangle::GetX() const
{
	return vMin.x;
}

/**
*  @brief
*    Returns the y position
*/
inline float Rectangle::GetY() const
{
	return vMin.y;
}

/**
*  @brief
*    Returns the width
*/
inline float Rectangle::GetWidth() const
{
	return vMax.x-vMin.x;
}

/**
*  @brief
*    Returns the height
*/
inline float Rectangle::GetHeight() const
{
	return vMax.y-vMin.y;
}

/**
*  @brief
*    Calculates the surface of the rectangle
*/
inline float Rectangle::CalculateSurface() const
{
	return (vMax.x-vMin.x)*(vMax.y-vMin.y);
}

/**
*  @brief
*    Clips this rectangle with another one
*/
inline void Rectangle::ClipByRectangle(const Rectangle &cEnclosed)
{
	// x
	if (vMin.x > cEnclosed.vMax.x) {
		vMin.x = vMax.x = cEnclosed.vMax.x;
	} else {
		if (vMax.x < cEnclosed.vMin.x) {
			vMin.x = vMax.x = cEnclosed.vMin.x;
		} else {
			if (vMin.x < cEnclosed.vMin.x) vMin.x = cEnclosed.vMin.x;
			if (vMax.x > cEnclosed.vMax.x) vMax.x = cEnclosed.vMax.x;
		}
	}

	// y
	if (vMin.y > cEnclosed.vMax.y) {
		vMin.y = vMax.y = cEnclosed.vMax.y;
	} else {
		if (vMax.y < cEnclosed.vMin.y) {
			vMin.y = vMax.y = cEnclosed.vMin.y;
		} else {
			if (vMin.y < cEnclosed.vMin.y) vMin.y = cEnclosed.vMin.y;
			if (vMax.y > cEnclosed.vMax.y) vMax.y = cEnclosed.vMax.y;
		}
	}
}

/**
*  @brief
*    Appends a vertex to the rectangle
*/
inline void Rectangle::AppendToRectangle(const Vector2 &vV)
{
	if (vV.x < vMin.x) vMin.x = vV.x;
	if (vV.y < vMin.y) vMin.y = vV.y;
	if (vV.x > vMax.x) vMax.x = vV.x;
	if (vV.y > vMax.y) vMax.y = vV.y;
}

/**
*  @brief
*    Combines two rectangles
*/
inline void Rectangle::CombineRectangles(const Rectangle &cRectangle)
{
	AppendToRectangle(cRectangle.vMin);
	AppendToRectangle(cRectangle.vMax);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
