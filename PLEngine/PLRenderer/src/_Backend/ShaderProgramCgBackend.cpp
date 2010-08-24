/*********************************************************\
 *  File: ShaderProgramCgBackend.cpp                     *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Wrapper.h>
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/Renderer/Backend/RendererBackend.h"
#include "_PLRendererBackend/ShaderProgramCgBackend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Protected static data                                 ]
//[-------------------------------------------------------]
CGcontext ShaderProgramCgBackend::m_pCgContext     = NULL;
uint32    ShaderProgramCgBackend::m_nContexCounter = 0;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
ShaderProgramCgBackend::~ShaderProgramCgBackend()
{
	DeInit();

	// Check Cg context
	m_nContexCounter--;
	if (!m_nContexCounter && m_pCgContext) {
		PL_LOG(Info, String::Format("De-initialize Cg %d", CG_VERSION_NUM))
		cgSetErrorCallback(NULL); // Just for sure :)
		cgDestroyContext(m_pCgContext);
		m_pCgContext = NULL;
	}
}

/**
*  @brief
*    Returns the Cg shader program profile
*/
CGprofile ShaderProgramCgBackend::GetCgProfile() const
{
	return m_pCgProfile;
}

/**
*  @brief
*    Returns the Cg program
*/
CGprogram ShaderProgramCgBackend::GetCgProgram() const
{
	return m_pCgProgram;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ShaderProgramCgBackend::ShaderProgramCgBackend(Renderer &cRenderer, EType nType, const PLGeneral::String &sDefines, const PLGeneral::String &sEntry) :
	ShaderProgram(cRenderer, nType, sDefines, sEntry),
	m_pCgProfile(CG_PROFILE_UNKNOWN),
	m_pCgProgram(NULL),
	m_pCgProfileBackup(CG_PROFILE_UNKNOWN)
{
}

/**
*  @brief
*    De-initializes the shader program
*/
void ShaderProgramCgBackend::DeInit()
{
	// Destroy the Cg program
	if (m_pCgProgram) {
		cgDestroyProgram(m_pCgProgram);
		m_pCgProgram = NULL;
	}
	m_pCgProfile = CG_PROFILE_UNKNOWN;
}


//[-------------------------------------------------------]
//[ Protected static Cg callback functions                ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal Cg error callback function
*/
void ShaderProgramCgBackend::CgErrorCallback()
{
	CGerror nLastError = cgGetError();
	if (nLastError) {
		const char *pszListing = cgGetLastListing(m_pCgContext);
		PL_LOG(Error, "\n---------------------------------------------------")
		PL_LOG(Error, cgGetErrorString(nLastError))
		if (pszListing) PL_LOG(Error, pszListing)
		PL_LOG(Error, "---------------------------------------------------\n")
	}
}


//[-------------------------------------------------------]
//[ Public virtual ShaderProgram functions                ]
//[-------------------------------------------------------]
PLGeneral::String ShaderProgramCgBackend::GetProfile() const
{
	return cgGetProfileString(m_pCgProfile);
}


//[-------------------------------------------------------]
//[ Public virtual Parameters functions                   ]
//[-------------------------------------------------------]
bool ShaderProgramCgBackend::IsParameter(const PLGeneral::String &sName) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgIsParameter(pCgParameter) != 0);
}

PLGeneral::String ShaderProgramCgBackend::GetParameterString(const PLGeneral::String &sName) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		// [TODO]
	//	return cgGetStringParameterValue(pCgParameter);
	}

	// Error!
	return "";
}

bool ShaderProgramCgBackend::SetParameterString(const PLGeneral::String &sName, const PLGeneral::String &sValue)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!

	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(sValue);

	// [TODO]
	CGtype nType = cgGetParameterType(pCgParameter);
	switch (nType) {
		case CG_FLOAT:
		{
			float fX = cTokenizer.GetNextToken().GetFloat();
			cgSetParameter1f(pCgParameter, fX);
			break;
		}

		case CG_FLOAT2:
		{
			float fValue[2];
			int nIndex = 0;
			while (cTokenizer.GetNextToken().GetLength()) {
				fValue[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 2) break;
			}
			cgSetParameter2fv(pCgParameter, fValue);
			break;
		}

		case CG_FLOAT3:
		{
			float fValue[3];
			int nIndex = 0;
			while (cTokenizer.GetNextToken().GetLength()) {
				fValue[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 3) break;
			}
			cgSetParameter3fv(pCgParameter, fValue);
			break;
		}

		case CG_FLOAT4:
		{
			float fValue[4];
			int nIndex = 0;
			while (cTokenizer.GetNextToken().GetLength()) {
				fValue[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 4) break;
			}
			cgSetParameter4fv(pCgParameter, fValue);
			break;
		}

		/* // [TODO] Double not jet supported in Cg?
		case CG_DOUBLE:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				*((double*)m_pValue) = cTokenizer.GetToken().GetDouble();
				nIndex++;
				if (nIndex >= 1) break;
			}
			break;
		}

		case CG_DOUBLE2:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
				nIndex++;
				if (nIndex >= 2) break;
			}
			break;
		}

		case CG_DOUBLE3:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
				nIndex++;
				if (nIndex >= 3) break;
			}
			break;
		}

		case CG_DOUBLE4:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
				nIndex++;
				if (nIndex >= 4) break;
			}
			break;
		}

		// [TODO] Add those
		case CG_FLOAT3x3:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 3*3) break;
			}
			break;
		}

		case CG_FLOAT3x4:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 3*4) break;
			}
			break;
		}

		case CG_FLOAT4x4:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
				nIndex++;
				if (nIndex >= 4*4) break;
			}
			break;
		}

		case CG_DOUBLE4x4:
		{
			while (cTokenizer.GetNextToken().GetLength()) {
				((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
				nIndex++;
				if (nIndex >= 4*4) break;
			}
			break;
		}
*/
/*		case Parameters::TextureBuffer:
			// Setting the texture buffer value using a string isn't possible!
			break;
*/
	}
	cTokenizer.Stop();

//	cgSetStringParameterValue(pCgParameter, sValue);

	// Done
	return true;
}


// Integer
bool ShaderProgramCgBackend::GetParameter1i(const PLGeneral::String &sName, int &nX) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValueic(pCgParameter, 1, &nX) == 1);
}

bool ShaderProgramCgBackend::SetParameter1i(const PLGeneral::String &sName, int nX)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter1i(pCgParameter, nX);

	// Done
	return true;
}

// Integer2
bool ShaderProgramCgBackend::GetParameter2i(const PLGeneral::String &sName, int &nX, int &nY) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		int nValues[2];
		if (cgGetParameterValueic(pCgParameter, 2, nValues) == 2) {
			nX = nValues[0];
			nY = nValues[1];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter2iv(const PLGeneral::String &sName, int nValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValueic(pCgParameter, 2, nValue) == 2);
}

bool ShaderProgramCgBackend::SetParameter2i(const PLGeneral::String &sName, int nX, int nY)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2i(pCgParameter, nX, nY);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter2iv(const PLGeneral::String &sName, const int nValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2iv(pCgParameter, nValue);

	// Done
	return true;
}

// Integer3
bool ShaderProgramCgBackend::GetParameter3i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		int nValues[3];
		if (cgGetParameterValueic(pCgParameter, 3, nValues) == 3) {
			nX = nValues[0];
			nY = nValues[1];
			nZ = nValues[2];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter3iv(const PLGeneral::String &sName, int nValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValueic(pCgParameter, 3, nValue) == 3);
}

bool ShaderProgramCgBackend::SetParameter3i(const PLGeneral::String &sName, int nX, int nY, int nZ)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3i(pCgParameter, nX, nY, nZ);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter3iv(const PLGeneral::String &sName, const int nValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3iv(pCgParameter, nValue);

	// Done
	return true;
}

// Integer4
bool ShaderProgramCgBackend::GetParameter4i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ, int &nW) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		int nValues[4];
		if (cgGetParameterValueic(pCgParameter, 4, nValues) == 4) {
			nX = nValues[0];
			nY = nValues[1];
			nZ = nValues[2];
			nW = nValues[3];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter4iv(const PLGeneral::String &sName, int nValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValueic(pCgParameter, 4, nValue) == 4);
}

bool ShaderProgramCgBackend::SetParameter4i(const PLGeneral::String &sName, int nX, int nY, int nZ, int nW)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4i(pCgParameter, nX, nY, nZ, nW);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter4iv(const PLGeneral::String &sName, const int nValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4iv(pCgParameter, nValue);

	// Done
	return true;
}


// Float
bool ShaderProgramCgBackend::GetParameter1f(const PLGeneral::String &sName, float &fX) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 1, &fX) == 1);
}

bool ShaderProgramCgBackend::SetParameter1f(const PLGeneral::String &sName, float fX)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter1f(pCgParameter, fX);

	// Done
	return true;
}

// Float2
bool ShaderProgramCgBackend::GetParameter2f(const PLGeneral::String &sName, float &fX, float &fY) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		float fValues[2];
		if (cgGetParameterValuefc(pCgParameter, 2, fValues) == 2) {
			fX = fValues[0];
			fY = fValues[1];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter2fv(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 2, fValue) == 2);
}

bool ShaderProgramCgBackend::SetParameter2f(const PLGeneral::String &sName, float fX, float fY)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2f(pCgParameter, fX, fY);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter2fv(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2fv(pCgParameter, fValue);

	// Done
	return true;
}

// Float3
bool ShaderProgramCgBackend::GetParameter3f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		float fValues[3];
		if (cgGetParameterValuefc(pCgParameter, 3, fValues) == 3) {
			fX = fValues[0];
			fY = fValues[1];
			fZ = fValues[2];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter3fv(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 3, fValue) == 3);
}

bool ShaderProgramCgBackend::SetParameter3f(const PLGeneral::String &sName, float fX, float fY, float fZ)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3f(pCgParameter, fX, fY, fZ);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter3fv(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3fv(pCgParameter, fValue);

	// Done
	return true;
}

// Float4
bool ShaderProgramCgBackend::GetParameter4f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ, float &fW) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		float fValues[4];
		if (cgGetParameterValuefc(pCgParameter, 4, fValues) == 4) {
			fX = fValues[0];
			fY = fValues[1];
			fZ = fValues[2];
			fW = fValues[3];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter4fv(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 4, fValue) == 4);
}

bool ShaderProgramCgBackend::SetParameter4f(const PLGeneral::String &sName, float fX, float fY, float fZ, float fW)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4f(pCgParameter, fX, fY, fZ, fW);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter4fv(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4fv(pCgParameter, fValue);

	// Done
	return true;
}


// Double
bool ShaderProgramCgBackend::GetParameter1d(const PLGeneral::String &sName, double &fX) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuedc(pCgParameter, 1, &fX) == 1);
}

bool ShaderProgramCgBackend::SetParameter1d(const PLGeneral::String &sName, double fX)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter1d(pCgParameter, fX);

	// Done
	return true;
}


// Double2
bool ShaderProgramCgBackend::GetParameter2d(const PLGeneral::String &sName, double &fX, double &fY) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		double fValues[2];
		if (cgGetParameterValuedc(pCgParameter, 2, fValues) == 2) {
			fX = fValues[0];
			fY = fValues[1];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter2dv(const PLGeneral::String &sName, double fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuedc(pCgParameter, 2, fValue) == 2);
}

bool ShaderProgramCgBackend::SetParameter2d(const PLGeneral::String &sName, double fX, double fY)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2d(pCgParameter, fX, fY);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter2dv(const PLGeneral::String &sName, const double fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter2dv(pCgParameter, fValue);

	// Done
	return true;
}

// Double3
bool ShaderProgramCgBackend::GetParameter3d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		double fValues[3];
		if (cgGetParameterValuedc(pCgParameter, 3, fValues) == 3) {
			fX = fValues[0];
			fY = fValues[1];
			fZ = fValues[2];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter3dv(const PLGeneral::String &sName, double fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuedc(pCgParameter, 3, fValue) == 3);
}

bool ShaderProgramCgBackend::SetParameter3d(const PLGeneral::String &sName, double fX, double fY, double fZ)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3d(pCgParameter, fX, fY, fZ);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter3dv(const PLGeneral::String &sName, const double fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter3dv(pCgParameter, fValue);

	// Done
	return true;
}

// Double4
bool ShaderProgramCgBackend::GetParameter4d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ, double &fW) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter) {
		double fValues[4];
		if (cgGetParameterValuedc(pCgParameter, 4, fValues) == 4) {
			fX = fValues[0];
			fY = fValues[1];
			fZ = fValues[2];
			fW = fValues[3];

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderProgramCgBackend::GetParameter4dv(const PLGeneral::String &sName, double fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuedc(pCgParameter, 4, fValue) == 4);
}

bool ShaderProgramCgBackend::SetParameter4d(const PLGeneral::String &sName, double fX, double fY, double fZ, double fW)
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4d(pCgParameter, fX, fY, fZ, fW);

	// Done
	return true;
}

bool ShaderProgramCgBackend::SetParameter4dv(const PLGeneral::String &sName, const double fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetParameter4dv(pCgParameter, fValue);

	// Done
	return true;
}


// Float3x3
bool ShaderProgramCgBackend::GetParameterFloat3x3(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 9, fValue) == 9);
}

bool ShaderProgramCgBackend::SetParameterFloat3x3(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetMatrixParameterfc(pCgParameter, fValue);

	// Done
	return true;
}


// Float3x4
bool ShaderProgramCgBackend::GetParameterFloat3x4(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 12, fValue) == 12);
}

bool ShaderProgramCgBackend::SetParameterFloat3x4(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetMatrixParameterfc(pCgParameter, fValue);

	// Done
	return true;
}


// Float4x4
bool ShaderProgramCgBackend::GetParameterMatrixfv(const PLGeneral::String &sName, float fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuefc(pCgParameter, 16, fValue) == 16);
}

bool ShaderProgramCgBackend::SetParameterMatrixfv(const PLGeneral::String &sName, const float fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (pCgParameter)
		cgSetMatrixParameterfc(pCgParameter, fValue);
	else
		return false; // Error!

	// Done
	return true;
}


// Double4x4
bool ShaderProgramCgBackend::GetParameterMatrixdv(const PLGeneral::String &sName, double fValue[]) const
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	return (pCgParameter && cgGetParameterValuedc(pCgParameter, 16, fValue) == 16);
}

bool ShaderProgramCgBackend::SetParameterMatrixdv(const PLGeneral::String &sName, const double fValue[])
{
	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
	if (!pCgParameter)
		return false; // Error!
	cgSetMatrixParameterdc(pCgParameter, fValue);

	// Done
	return true;
}


// Texture buffer
TextureBuffer *ShaderProgramCgBackend::GetParameterTextureBuffer(const PLGeneral::String &sName) const
{
//	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
//	if (!pCgParameter) return NULL; // Error!
	// [TODO]
	return NULL;
}

Texture *ShaderProgramCgBackend::GetParameterTexture(const PLGeneral::String &sName) const
{
//	CGparameter pCgParameter = cgGetNamedParameter(m_pCgProgram, sName);
//	if (!pCgParameter) return NULL; // Error!
	// [TODO]
	return NULL;
}


//[-------------------------------------------------------]
//[ Protected virtual Resource functions                  ]
//[-------------------------------------------------------]
void ShaderProgramCgBackend::BackupDeviceData(uint8 **ppBackup)
{
	// Backup data
	const char *pszProgram = cgGetProgramString(m_pCgProgram, CG_PROGRAM_SOURCE);
	if (pszProgram) {
		m_pCgProfileBackup = m_pCgProfile;
		uint32 nNumOfBytes = Wrapper::GetStringLength(pszProgram) + 1;
		*ppBackup = new uint8[nNumOfBytes];
		MemoryManager::Copy(*ppBackup, pszProgram, nNumOfBytes);
		DeInit();
	} else *ppBackup = NULL;
}

void ShaderProgramCgBackend::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		Init(*ppBackup, m_pCgProfileBackup);
		delete [] *ppBackup;
		m_pCgProfileBackup = CG_PROFILE_UNKNOWN;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
