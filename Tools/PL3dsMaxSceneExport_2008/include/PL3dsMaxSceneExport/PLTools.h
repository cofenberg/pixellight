/*********************************************************\
 *  File: PLTools.h                                      *
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


#ifndef __PL_TOOLS_H__
#define __PL_TOOLS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string>
#include <max.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Quat;
class Box3;
class Point3;
class GMatrix;
namespace PLCore {
	class String;
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Some useful tools
*/
class PLTools {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Resource type
		*/
		enum EResourceType {
			ResourceMesh,		/**< Mesh */
			ResourceMaterial,	/**< Material */
			ResourceSkin,		/**< Skin */
			ResourceKeyframes,	/**< Keyframes */
			ResourcePath		/**< Path */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		// Because the Box3::IsEmpty()-function returns nearly ALWAYS '1', I wrote this own function...
		static bool IsEmpty(const Box3 &cBox);

		// Rotates a given vertex by using a given quaternion
		static void Rotate(const Quat &qQuat, Point3 &vVector);

		// Validates the minimum/maximum values of the given box so that the minimum is ALWAYS smaller
		// than the maximum
		static void ValidateMinimumMaximum(Box3 &cBox);

		static bool Compare(const Point3 &P1, const Point3 &P2, float fDelta = 0.0005f);
		static std::string ToString(int nValue);
		static std::string ToString(unsigned long nValue);
		static std::string ToString(float fValue);
		static std::string ToLower(const std::string &sString);
		static void XmlElementSetAttributeWithDefault(PLCore::XmlElement &cXmlElement, const PLCore::String &sName, float fValue, float fDefaultValue);
		static void XmlElementSetAttributeWithDefault(PLCore::XmlElement &cXmlElement, const PLCore::String &sName, const Point3 &cPoint, const Point3 &cDefault);

		/**
		*  @brief
		*    Returns position, rotation and scale from a matrix
		*
		*  @param[in]  mTransform
		*    Transform matrix
		*  @param[out] vPos
		*    Receives the position
		*  @param[out] vRot
		*    Receives the rotation
		*  @param[out] vScale
		*    Receives the scale
		*  @param[in]  bFlip
		*    Flip 180 degree around the y-axis?
		*/
		static void GetPosRotScale(const GMatrix &mTransform, Point3 &vPos, Point3 &vRot, Point3 &vScale, bool bFlip = false);

		/**
		*  @brief
		*    Returns position, rotation and scale from a matrix
		*
		*  @param[in]  mTransform
		*    Transform matrix
		*  @param[out] vPos
		*    Receives the position
		*  @param[out] qRot
		*    Receives the rotation
		*  @param[out] vScale
		*    Receives the scale
		*  @param[in]  bFlip
		*    Flip 180 degree around the y-axis?
		*/
		static void GetPosRotScale(const GMatrix &mTransform, Point3 &vPos, Quat &qRot, Point3 &vScale, bool bFlip = false);

		/**
		*  @brief
		*    Transforms a 3ds Max vector to a OpenGL vector
		*
		*  @param[in] vVector
		*    3ds Max vector to transform
		*
		*  @return
		*    The transformed OpenGL vector
		*/
		static Point3 Convert3dsMaxVectorToOpenGLVector(const Point3 &vVector);

		/**
		*  @brief
		*    Transforms a 3ds Max matrix to a OpenGL matrix
		*
		*  @param[in] mMatrix
		*    3ds Max matrix to transform
		*
		*  @return
		*    The transformed OpenGL matrix
		*/
		static Matrix3 Convert3dsMaxMatrixToOpenGLMatrix(const Matrix3 &mMatrix);

		/**
		*  @brief
		*    Returns whether or not the given controller has any key control interface (x, y, z)
		*
		*  @param[in] cController
		*    Controller to check
		*
		*  @return
		*    'true' if the given controller has any key control interface, else 'false'
		*/
		static bool HasKeyControlInterface(Control &cController);

		/**
		*  @brief
		*    Try to find the PixelLight runtime directory by reading the registry
		*
		*  @return
		*    The found directory, a null pointer on error, you have to free the memory
		*/
		static char *GetPixelLightRuntimeDirectory();

		/**
		*  @brief
		*    Returns the absolute filename of 'PLViewer'
		*
		*  @return
		*    The absolute filename of 'PLViewer'
		*/
		static std::string GetPLViewerFilename();

		/**
		*  @brief
		*    Constructs a resource filename by using the current options
		*
		*  @param[in] nResourceType
		*    Resource type
		*  @param[in] sFilename
		*    Filename
		*
		*  @return
		*    Resource filename
		*/
		static std::string GetResourceFilename(EResourceType nResourceType, const std::string &sFilename);


};


#endif // __PL_TOOLS_H__
