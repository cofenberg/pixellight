/*********************************************************\
 *  File: PLTools.h                                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PL_TOOLS_H__
#define __PL_TOOLS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <max.h>
#include <IGame/IGameType.h>
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Quat;
class Box3;
class Point3;
namespace PLCore {
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
		static PLCore::String ToString(int nValue);
		static PLCore::String ToString(unsigned long nValue);
		static PLCore::String ToString(float fValue);
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
		static PLCore::String GetPLViewerFilename();

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
		static PLCore::String GetResourceFilename(EResourceType nResourceType, const PLCore::String &sFilename);

		// [HACK] Wow, "GMatrix::Inverse()" appears to be buggy...
		static GMatrix Inverse(const GMatrix &mMatrix);


};


#endif // __PL_TOOLS_H__
