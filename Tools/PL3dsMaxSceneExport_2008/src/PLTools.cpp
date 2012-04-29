/*********************************************************\
 *  File: PLTools.cpp                                    *
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
#include <sstream>
#include <IGame/IGame.h>
#include <PixelLight.h>
#include <PLCore/PLCoreWindows.h>	// Depending on the used compiler, nullptr has to be defined by this header
#include <PLCore/String/ParseTools.h>
#if MAX_RELEASE < 13000
	// The following is required for legacy 3ds Max versions 2008, 2009 and 2010
	#undef GetFirstChild
	#undef GetNextSibling
#endif
#include <PLCore/Xml/XmlElement.h>
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLTools.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
bool PLTools::IsEmpty(const Box3 &cBox)
{
	return (cBox.pmin.x ==  1.0000000e+030f && cBox.pmin.y ==  1.0000000e+030f && cBox.pmin.z ==  1.0000000e+030f &&
		    cBox.pmax.x == -1.0000000e+030f && cBox.pmax.y == -1.0000000e+030f && cBox.pmax.z == -1.0000000e+030f);
}

void PLTools::Rotate(const Quat &qQuat, Point3 &vVector)
{
	Quat qRes = qQuat.Conjugate()*Quat(vVector.x, vVector.y, vVector.z, 0.0f)*qQuat;
	vVector.x = qRes.x;
	vVector.y = qRes.y;
	vVector.z = qRes.z;
}

void PLTools::ValidateMinimumMaximum(Box3 &cBox)
{
	// Loop through all components
	for (int i=0; i<3; i++) {
		// Minimum larger than maximum?
		if (cBox.pmin[i] > cBox.pmax[i]) {
			// Swap minimum/maximum
			float fTemp = cBox.pmin[i];
			cBox.pmin[i] = cBox.pmax[i];
			cBox.pmax[i] = fTemp;
		}
	}
}

bool PLTools::Compare(const Point3 &P1, const Point3 &P2, float fDelta)
{
	return (fabs(P1.x-P2.x) <= fDelta && fabs(P1.y-P2.y) <= fDelta && fabs(P1.z-P2.z) <= fDelta);
}

String PLTools::ToString(int nValue)
{
	return nValue;
}

String PLTools::ToString(unsigned long nValue)
{
	return static_cast<uint32>(nValue);
}

String PLTools::ToString(float fValue)
{
	return fValue;
}

void PLTools::XmlElementSetAttributeWithDefault(XmlElement &cXmlElement, const String &sName, float fValue, float fDefaultValue)
{
	// Is the given value equal to the given default value?
	if (fValue != fDefaultValue) {
		// Value to string
		const String sValue = String::Format("%f", fValue);

		// Due to rounding errors the string may now or may not contain the given default value, check for this
		if (sValue.GetFloat() != fDefaultValue)
			cXmlElement.SetAttribute(sName, sValue);
	} else {
		// The given value is equal to the default value -> nothing to do
	}
}

void PLTools::XmlElementSetAttributeWithDefault(XmlElement &cXmlElement, const String &sName, const Point3 &cPoint, const Point3 &cDefault)
{
	// Is the given value equal to the given default value?
	if (cPoint.x != cDefault.x || cPoint.y != cDefault.y || cPoint.z != cDefault.z) {
		// Value to string
		const String sValue = String::Format("%f %f %f", cPoint.x, cPoint.y, cPoint.z);

		// Due to rounding errors the string may now or may not contain the given default value, check for this
		float fValues[3] = { 0.0f, 0.0f, 0.0f };
		ParseTools::ParseFloatArray(sValue, fValues, 3);
		if (fValues[0] != cDefault.x || fValues[1] != cDefault.y || fValues[2] != cDefault.z)
			cXmlElement.SetAttribute(sName, sValue);
	} else {
		// The given value is equal to the default value -> nothing to do
	}
}

/**
*  @brief
*    Returns position, rotation and scale from a matrix
*/
void PLTools::GetPosRotScale(const GMatrix &mTransform, Point3 &vPos, Point3 &vRot, Point3 &vScale, bool bFlip)
{
	// Get the position
	vPos = mTransform.Translation();

	// Get the rotation of the node as quaternion
	Quat qRotation = mTransform.Rotation();

	// Flip 180 degree around the y-axis? (true for camera and spot lights)
	if (bFlip) {
		Quat qRotationOffset;

		// We have to add a rotation about the x-axis of -90 degree... is this a IGame transform bug or something other odd??
		float fAngles[] = {static_cast<float>(HALFPI), 0.0f, 0.0f};
		EulerToQuat(fAngles, qRotationOffset);
		qRotation = qRotationOffset*qRotation;

		// We have to 'invert the z-axis', this is no PixelLight bug or so, we decided to do so to make things more universal
		fAngles[0] = 0.0f;
		fAngles[2] = static_cast<float>(PI);
		EulerToQuat(fAngles, qRotationOffset);
		qRotation = qRotationOffset*qRotation;
	}

	// Get the rotation in Euler angles (in degree) as used in PixelLight
	float fAngles[3];
	QuatToEuler(qRotation, fAngles);
	vRot.x = RadToDeg(fAngles[0]);
	vRot.y = RadToDeg(fAngles[1]);
	vRot.z = RadToDeg(fAngles[2]);

	// Look out! We REALLY need to take the parity of the transform matrix into account!
	vScale = mTransform.Scaling()*static_cast<float>(mTransform.Parity());
}

/**
*  @brief
*    Returns position, rotation and scale from a matrix
*/
void PLTools::GetPosRotScale(const GMatrix &mTransform, Point3 &vPos, Quat &qRot, Point3 &vScale, bool bFlip)
{
	// Get the position
	vPos = mTransform.Translation();

	// Get the rotation of the node as quaternion
	qRot = mTransform.Rotation();

	// Flip 180 degree around the y-axis? (true for camera and spot lights)
	if (bFlip) {
		Quat qRotationOffset;

		// We have to add a rotation about the x-axis of -90 degree... is this a IGame transform bug or something other odd??
		float fAngles[] = {static_cast<float>(HALFPI), 0.0f, 0.0f};
		EulerToQuat(fAngles, qRotationOffset);
		qRot = qRotationOffset*qRot;

		// We have to 'invert the z-axis', this is no PixelLight bug or so, we decided to do so to make things more universal
		fAngles[0] = 0.0f;
		fAngles[2] = static_cast<float>(PI);
		EulerToQuat(fAngles, qRotationOffset);
		qRot = qRotationOffset*qRot;
	}

	// Look out! We REALLY need to take the parity of the transform matrix into account!
	vScale = mTransform.Scaling()*static_cast<float>(mTransform.Parity());
}

/**
*  @brief
*    Transforms a 3ds Max vector to a OpenGL vector
*/
Point3 PLTools::Convert3dsMaxVectorToOpenGLVector(const Point3 &vVector)
{
	return Point3(vVector[0], vVector[2], -vVector[1]);
}

/**
*  @brief
*    Transforms a 3ds Max matrix to a OpenGL matrix
*/
Matrix3 PLTools::Convert3dsMaxMatrixToOpenGLMatrix(const Matrix3 &mMatrix)
{
	return Matrix3( Convert3dsMaxVectorToOpenGLVector(mMatrix.GetRow(0)),
				    Convert3dsMaxVectorToOpenGLVector(mMatrix.GetRow(2)),
				   -Convert3dsMaxVectorToOpenGLVector(mMatrix.GetRow(1)),
					Convert3dsMaxVectorToOpenGLVector(mMatrix.GetRow(3)));
}

/**
*  @brief
*    Returns whether or not the given controller has any key control interface (x, y, z)
*/
bool PLTools::HasKeyControlInterface(Control &cController)
{
	// X
	Control *pXController = cController.GetXController();
	if (pXController) {
		IKeyControl *pKeyControl = GetKeyControlInterface(pXController);
		if (pKeyControl && pKeyControl->GetNumKeys())
			return true; // There's at least one key control interface
	}

	// Y
	Control *pYController = cController.GetYController();
	if (pYController) {
		IKeyControl *pKeyControl = GetKeyControlInterface(pYController);
		if (pKeyControl && pKeyControl->GetNumKeys())
			return true; // There's at least one key control interface
	}

	// Z
	Control *pZController = cController.GetZController();
	if (pZController) {
		IKeyControl *pKeyControl = GetKeyControlInterface(pZController);
		if (pKeyControl && pKeyControl->GetNumKeys())
			return true; // There's at least one key control interface
	}

	// Funny... but 'scale controller' (unlike position and rotation) seam to have their own way...
	IKeyControl *pKeyControl = GetKeyControlInterface(&cController);
	if (pKeyControl && pKeyControl->GetNumKeys())
		return true; // There's at least one key control interface

	// There are no key control interfaces
	return false;
}

/**
*  @brief
*    Try to find the PixelLight runtime directory by reading the registry
*/
char *PLTools::GetPixelLightRuntimeDirectory()
{
	// [HACK] We perform two 'rounds', one for the 'standard' and the second for 'Wow6432Node'. (32 bit application registry on 64 bit OS)
	//        If we don't do this, and use a 32 bit PixelLight SDK with a 64 bit version of 3ds Max, the exporter
	//        can't find automatically 'PLViewer'. (because it's a 32 bit application and we access the registry from
	//        a 64 bit application)
	for (int i=0; i<2; i++) {
		// Get PixelLight suffix and compose registry key from it
		char szSuffix[256];
		strcpy(szSuffix, PIXELLIGHT_SUFFIX);
		char szSubkeySDK[256];
		char szSubkeyRT[256];
		if (i) {
			strcpy(szSubkeySDK, "SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-SDK");
			strcpy(szSubkeyRT,  "SOFTWARE\\Wow6432Node\\PixelLight\\PixelLight-Runtime");
		} else {
			strcpy(szSubkeySDK, "SOFTWARE\\PixelLight\\PixelLight-SDK");
			strcpy(szSubkeyRT,  "SOFTWARE\\PixelLight\\PixelLight-Runtime");
		}
		if (szSuffix[0] != '\0') {
			strcat(szSubkeySDK, "-");
			strcat(szSubkeySDK, szSuffix);
			strcat(szSubkeyRT,  "-");
			strcat(szSubkeyRT,  szSuffix);
		}

		// Read registry key "PixelLight-SDK"
		HKEY hKey;
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, szSubkeySDK, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
			DWORD nSize;
			if (RegQueryValueEx(hKey, _T("Runtime"), 0, nullptr, nullptr, &nSize) == ERROR_SUCCESS) {
				char *pszBuffer = new char[nSize];
				if (RegQueryValueEx(hKey, _T("Runtime"), 0, nullptr, reinterpret_cast<BYTE*>(pszBuffer), &nSize) == ERROR_SUCCESS) {
					// Valid directory?
					if (GetFileAttributesA(pszBuffer) != INVALID_FILE_ATTRIBUTES) {
						RegCloseKey(hKey);
						return pszBuffer;
					}
				}
				delete [] pszBuffer;
			}
			RegCloseKey(hKey);
		}

		// Read registry key "PixelLight-Runtime"
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, szSubkeyRT, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
			DWORD nSize;
			if (RegQueryValueEx(hKey, _T("Runtime"), 0, nullptr, nullptr, &nSize) == ERROR_SUCCESS) {
				char *pszBuffer = new char[nSize];
				if (RegQueryValueEx(hKey, _T("Runtime"), 0, nullptr, reinterpret_cast<BYTE*>(pszBuffer), &nSize) == ERROR_SUCCESS) {
					// Valid directory?
					if (GetFileAttributesA(pszBuffer) != INVALID_FILE_ATTRIBUTES) {
						RegCloseKey(hKey);
						return pszBuffer;
					}
				}
				delete [] pszBuffer;
			}
			RegCloseKey(hKey);
		}
	}

	// No runtime directory was found in the registry
	return nullptr;
}

/**
*  @brief
*    Returns the absolute filename of 'PLViewer'
*/
String PLTools::GetPLViewerFilename()
{
	String sViewer;

	// Get get runtime directory
	char *pszBuffer = PLTools::GetPixelLightRuntimeDirectory();
	if (pszBuffer) {
		// Is there a '\' or '//' at the end?
		size_t nLength = strlen(pszBuffer);
		if (pszBuffer[nLength-1] == '\\' || pszBuffer[nLength-1] == '/') {
			pszBuffer[nLength-1] = '\0';
			nLength--;
		}

		// There MUST be a 'x86' at the end (first, we check for the public SDK structure)
		size_t nx86Length = strlen("x86");
		if (nLength > nx86Length && !_stricmp(&pszBuffer[nLength-nx86Length], "x86")) {
			// Remove the 'x86' and the slash
			nLength -= nx86Length+1;
			pszBuffer[nLength] = '\0';

			// There MUST be a 'Runtime' at the end (first, we check for the public SDK structure)
			size_t nRuntimeLength = strlen("Runtime");
			if (nLength > nRuntimeLength && !_stricmp(&pszBuffer[nLength-nRuntimeLength], "Runtime")) {
				// Remove the 'Runtime'
				nLength -= nRuntimeLength;
				pszBuffer[nLength] = '\0';

				{ // Maybe this is your internal developer version?
					// Construct the absolute filename
					sViewer = String(pszBuffer) + "Tools\\x86\\PLViewer.exe";

					// Valid filename?
					FILE *pFile = fopen(sViewer.GetASCII(), "r");
					if (pFile)
						fclose(pFile);
					else
						sViewer = ""; // IGHH!
				}

				// Installed PL SDK?
				if (!sViewer.GetLength()) {
					// Construct the absolute filename
					sViewer = String(pszBuffer) + "Tools\\Bin\\x86\\PLViewer.exe";

					// Valid filename?
					FILE *pFile = fopen(sViewer.GetASCII(), "r");
					if (pFile)
						fclose(pFile);
					else
						sViewer = ""; // IGHH!
				}
			}
		}

		// Cleanup
		delete [] pszBuffer;
	}

	// Return the filename of 'PLViewer'
	return sViewer;
}

/**
*  @brief
*    Constructs a resource filename by using the current options
*/
String PLTools::GetResourceFilename(EResourceType nResourceType, const String &sFilename)
{
	// Directory of the resource type
	if (g_SEOptions.bPLDirectories) {
		String sResourceDirectory;
		switch (nResourceType) {
			case ResourceMesh:
				sResourceDirectory = "Data\\Meshes\\";
				break;

			case ResourceMaterial:
				sResourceDirectory = "Data\\Materials\\";
				break;

			case ResourceSkin:
			case ResourceKeyframes:
			case ResourcePath:
				sResourceDirectory = "Data\\Misc\\";
				break;
		}

		// Scene subdirectory
		if (g_SEOptions.bSubdirectories)
			return sResourceDirectory + g_SEOptions.sFilenameOnly + "\\" + sFilename;
		else
			return sResourceDirectory + sFilename;
	}

	// Just return the given filename
	return sFilename;
}

// [HACK] Wow, "GMatrix::Inverse()" appears to be buggy...
GMatrix PLTools::Inverse(const GMatrix &mMatrix)
{
	Matrix3 mMatrix3 = mMatrix.ExtractMatrix3();
	mMatrix3.Invert();
	return mMatrix3;
}
