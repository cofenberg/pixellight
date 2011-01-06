/*********************************************************\
 *  File: Parameter.cpp                                  *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/Tokenizer.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix3x4.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/Program.h"
#include "PLRenderer/Renderer/ProgramUniform.h"
#include "PLRenderer/Texture/Texture.h"
#include "PLRenderer/Texture/TextureHandler.h"
#include "PLRenderer/Material/ParameterManager.h"
#include "PLRenderer/Material/Parameter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the parameter manager this parameter is in
*/
ParameterManager &Parameter::GetManager() const
{
	return *m_pManager;
}

/**
*  @brief
*    Sets the value of this parameter to a parameter within the given manager
*/
bool Parameter::SetManagerParameterValue(Parameters &cManager, const PLGeneral::String &sName) const
{
	// Set parameter
	switch (m_nType) {
		case Parameters::String:
			cManager.SetParameterString(sName, *((const PLGeneral::String*)m_pValue));
			break;

		case Parameters::Integer:
			cManager.SetParameter1i(sName, *((const int*)m_pValue));
			break;

		case Parameters::Integer2:
			cManager.SetParameter2iv(sName, (const int*)m_pValue);
			break;

		case Parameters::Integer3:
			cManager.SetParameter3iv(sName, (const int*)m_pValue);
			break;

		case Parameters::Integer4:
			cManager.SetParameter4iv(sName, (const int*)m_pValue);
			break;

		case Parameters::Float:
			cManager.SetParameter1f(sName, *((const float*)m_pValue));
			break;

		case Parameters::Float2:
			cManager.SetParameter2fv(sName, (const float*)m_pValue);
			break;

		case Parameters::Float3:
			cManager.SetParameter3fv(sName, (const float*)m_pValue);
			break;

		case Parameters::Float4:
			cManager.SetParameter4fv(sName, (const float*)m_pValue);
			break;

		case Parameters::Double:
			cManager.SetParameter1d(sName, *((const double*)m_pValue));
			break;

		case Parameters::Double2:
			cManager.SetParameter2dv(sName, (const double*)m_pValue);
			break;

		case Parameters::Double3:
			cManager.SetParameter3dv(sName, (const double*)m_pValue);
			break;

		case Parameters::Double4:
			cManager.SetParameter4dv(sName, (const double*)m_pValue);
			break;

		case Parameters::Float3x3:
			cManager.SetParameterFloat3x3(sName, (const float*)m_pValue);
			break;

		case Parameters::Float3x4:
			cManager.SetParameterFloat3x4(sName, (const float*)m_pValue);
			break;

		case Parameters::Float4x4:
			cManager.SetParameterMatrixfv(sName, (const float*)m_pValue);
			break;

		case Parameters::Double4x4:
			cManager.SetParameterMatrixdv(sName, (const double*)m_pValue);
			break;

		case Parameters::TextureBuffer:
			return false; // Error, not supported

		default:
			return false; // Error, not supported
	}

	// Done
	return true;
}

/**
*  @brief
*    Sets the value of this parameter to a parameter within the given manager GPU program
*/
bool Parameter::SetManagerParameterValue(Program &cProgram, const PLGeneral::String &sName) const
{
	// Get the GPU program uniform
	ProgramUniform *pProgramUniform = cProgram.GetUniform(sName);
	if (pProgramUniform) {
		// Set parameter
		switch (m_nType) {
			case Parameters::String:
				// GPU programs don't have string parameters
				break;

			case Parameters::Integer:
				pProgramUniform->Set(*((const int*)m_pValue));
				break;

			case Parameters::Integer2:
				pProgramUniform->Set2((const int*)m_pValue);
				break;

			case Parameters::Integer3:
				pProgramUniform->Set3((const int*)m_pValue);
				break;

			case Parameters::Integer4:
				pProgramUniform->Set4((const int*)m_pValue);
				break;

			case Parameters::Float:
				pProgramUniform->Set(*((const float*)m_pValue));
				break;

			case Parameters::Float2:
				pProgramUniform->Set2((const float*)m_pValue);
				break;

			case Parameters::Float3:
				pProgramUniform->Set3((const float*)m_pValue);
				break;

			case Parameters::Float4:
				pProgramUniform->Set4((const float*)m_pValue);
				break;

			case Parameters::Double:
				pProgramUniform->Set(*((const double*)m_pValue));
				break;

			case Parameters::Double2:
				pProgramUniform->Set2((const double*)m_pValue);
				break;

			case Parameters::Double3:
				pProgramUniform->Set3((const double*)m_pValue);
				break;

			case Parameters::Double4:
				pProgramUniform->Set4((const double*)m_pValue);
				break;

			case Parameters::Float3x3:
				// [TODO] New shader interface: Add Set3x3 method?
				//pProgramUniform->Set((const float*)m_pValue);
				pProgramUniform->Set(Matrix3x3((const float*)m_pValue));
				break;

			case Parameters::Float3x4:
				// [TODO] New shader interface: Add Set3x4 method?
				//pProgramUniform->Set((const float*)m_pValue);
				break;

			case Parameters::Float4x4:
				// [TODO] New shader interface: Add Set4x4 method?
				pProgramUniform->Set(Matrix4x4((const float*)m_pValue));
				break;

			case Parameters::Double4x4:
				// [TODO] New shader interface: Add Set4x4 method?
				//pProgramUniform->Set((const double*)m_pValue);
				break;

			case Parameters::TextureBuffer:
				return false; // Error, not supported

			default:
				return false; // Error, not supported
		}

		// Done
		return true;
	}

	// Error!
	return false;
}

/**
*  @brief
*    Get the parameter type
*/
Parameters::EDataType Parameter::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Get the parameter name
*/
PLGeneral::String Parameter::GetName() const
{
	return m_sName;
}

/**
*  @brief
*    Set the parameter name
*/
bool Parameter::SetName(const PLGeneral::String &sName)
{
	// Check parameter
	if (sName.GetLength()) {
		// Same name?
		if (m_sName == sName)
			return true; // Nothing to do

		// Is there already a parameter with the given name inside the parameter manager this parameter is in?
		if (!m_pManager->GetParameter(sName)) {
			// Set the new name
			m_sName = sName;

			// Done
			return true;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Get/set value                                         ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a parameter value as string (e.g. "1.0 5.4 0.21")
*/
PLGeneral::String Parameter::GetParameterString() const
{
	switch (m_nType) {
		case Parameters::String:
			return *((const PLGeneral::String*)m_pValue);

		case Parameters::Integer:
			return PLGeneral::String::Format("%d", *((const int*)m_pValue));

		case Parameters::Integer2:
			return PLGeneral::String::Format("%d %d", ((const int*)m_pValue)[0], ((const int*)m_pValue)[1]);

		case Parameters::Integer3:
			return PLGeneral::String::Format("%d %d %d", ((const int*)m_pValue)[0], ((const int*)m_pValue)[1], ((const int*)m_pValue)[2]);

		case Parameters::Integer4:
			return PLGeneral::String::Format("%d %d %d %d", ((const int*)m_pValue)[0], ((const int*)m_pValue)[1], ((const int*)m_pValue)[2], ((const int*)m_pValue)[3]);

		case Parameters::Float:
			return PLGeneral::String::Format("%g", *((const float*)m_pValue));

		case Parameters::Float2:
			return PLGeneral::String::Format("%g %g", ((const float*)m_pValue)[0], ((const float*)m_pValue)[1]);

		case Parameters::Float3:
			return PLGeneral::String::Format("%g %g %g", ((const float*)m_pValue)[0], ((const float*)m_pValue)[1], ((const float*)m_pValue)[2]);

		case Parameters::Float4:
			return PLGeneral::String::Format("%g %g %g %g", ((const float*)m_pValue)[0], ((const float*)m_pValue)[1], ((const float*)m_pValue)[2], ((const float*)m_pValue)[3]);

		case Parameters::Double:
			return PLGeneral::String::Format("%g", *((const double*)m_pValue));

		case Parameters::Double2:
			return PLGeneral::String::Format("%g %g", ((const double*)m_pValue)[0], ((const double*)m_pValue)[1]);

		case Parameters::Double3:
			return PLGeneral::String::Format("%g %g %g", ((const double*)m_pValue)[0], ((const double*)m_pValue)[1], ((const double*)m_pValue)[2]);

		case Parameters::Double4:
			return PLGeneral::String::Format("%g %g %g %g", ((const double*)m_pValue)[0], ((const double*)m_pValue)[1], ((const double*)m_pValue)[2], ((const double*)m_pValue)[3]);

		case Parameters::Float3x3:
		{
			const float *pfValue = (const float*)m_pValue;
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2],
											 pfValue[3], pfValue[4], pfValue[5],
											 pfValue[6], pfValue[7], pfValue[8]);
		}

		case Parameters::Float3x4:
		{
			const float *pfValue = (const float*)m_pValue;
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2], pfValue[3],
											 pfValue[4], pfValue[5], pfValue[6], pfValue[7],
											 pfValue[8], pfValue[9], pfValue[10], pfValue[11]);
		}

		case Parameters::Float4x4:
		{
			const float *pfValue = (const float*)m_pValue;
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2], pfValue[3],
											 pfValue[4], pfValue[5], pfValue[6], pfValue[7],
											 pfValue[8], pfValue[9], pfValue[10], pfValue[11],
											 pfValue[12], pfValue[13], pfValue[14], pfValue[15]);
		}

		case Parameters::Double4x4:
		{
			const double *pfValue = (const double*)m_pValue;
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2], pfValue[3],
											 pfValue[4], pfValue[5], pfValue[6], pfValue[7],
											 pfValue[8], pfValue[9], pfValue[10], pfValue[11],
											 pfValue[12], pfValue[13], pfValue[14], pfValue[15]);
		}

		case Parameters::TextureBuffer:
		{
			const Texture *pTexture = GetValueTexture();
			return pTexture ? pTexture->GetName() : "";
		}

		default:
			return ""; // Error!
	}
}

/**
*  @brief
*    Sets a parameter value from a string (e.g. "1.0 5.4 0.21")
*/
bool Parameter::SetParameterString(const PLGeneral::String &sValue)
{
	// Empty value string?
	if (!sValue.GetLength())
		return false; // Error!

	// Set parameter value
	if (m_nType == Parameters::TextureBuffer) {
		// We can use the value directly
		SetValueTexture(sValue);
	} else {
		// Setup tokenizer
		PLGeneral::Tokenizer cTokenizer;
		cTokenizer.Start(sValue);

		// Parse
		PLGeneral::uint32 nIndex = 0;
		switch (m_nType) {
			case Parameters::String:
				*((PLGeneral::String*)m_pValue) = sValue;
				break;

			case Parameters::Integer:
				while (cTokenizer.GetNextToken().GetLength()) {
					*((int*)m_pValue) = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				break;

			case Parameters::Integer2:
				while (cTokenizer.GetNextToken().GetLength()) {
					((int*)m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				break;

			case Parameters::Integer3:
				while (cTokenizer.GetNextToken().GetLength()) {
					((int*)m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				break;

			case Parameters::Integer4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((int*)m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				break;

			case Parameters::Float:
				while (cTokenizer.GetNextToken().GetLength()) {
					*((float*)m_pValue) = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				break;

			case Parameters::Float2:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				break;

			case Parameters::Float3:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				break;

			case Parameters::Float4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				break;

			case Parameters::Double:
				while (cTokenizer.GetNextToken().GetLength()) {
					*((double*)m_pValue) = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				break;

			case Parameters::Double2:
				while (cTokenizer.GetNextToken().GetLength()) {
					((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				break;

			case Parameters::Double3:
				while (cTokenizer.GetNextToken().GetLength()) {
					((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				break;

			case Parameters::Double4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				break;

			case Parameters::Float3x3:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3*3)
						break;
				}
				break;

			case Parameters::Float3x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3*4)
						break;
				}
				break;

			case Parameters::Float4x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((float*)m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 4*4)
						break;
				}
				break;

			case Parameters::Double4x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					((double*)m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 4*4)
						break;
				}
				break;
		}

		// Stop tokenizer
		cTokenizer.Stop();
	}

	// Done
	return true;
}

// Integer
bool Parameter::GetValue1i(int &nX) const
{
	if (m_nType != Parameters::Integer)
		return false; // Error!
	nX = *((const int*)m_pValue);
	return true; // Done
}

int Parameter::GetValue1i() const
{
	return (m_nType == Parameters::Integer) ? *((const int*)m_pValue) : 0;
}

bool Parameter::SetValue1i(int nX)
{
	if (m_nType != Parameters::Integer)
		return false; // Error!
	*((int*)m_pValue) = nX;
	return true; // Done
}

// Integer2
bool Parameter::GetValue2i(int &nX, int &nY) const
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	nX = ((const int*)m_pValue)[0];
	nY = ((const int*)m_pValue)[1];
	return true; // Done
}

const int *Parameter::GetValue2iv() const
{
	return (m_nType == Parameters::Integer2) ? (const int*)m_pValue : nullptr;
}

bool Parameter::SetValue2i(int nX, int nY)
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	((int*)m_pValue)[0] = nX;
	((int*)m_pValue)[1] = nY;
	return true; // Done
}

bool Parameter::SetValue2iv(const int nValue[])
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	((int*)m_pValue)[0] = nValue[0];
	((int*)m_pValue)[1] = nValue[1];
	return true; // Done
}

// Integer3
bool Parameter::GetValue3i(int &nX, int &nY, int &nZ) const
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	nX = ((const int*)m_pValue)[0];
	nY = ((const int*)m_pValue)[1];
	nZ = ((const int*)m_pValue)[2];
	return true; // Done
}

const int *Parameter::GetValue3iv() const
{
	return (m_nType == Parameters::Integer3) ? (const int*)m_pValue : nullptr;
}

bool Parameter::SetValue3i(int nX, int nY, int nZ)
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	((int*)m_pValue)[0] = nX;
	((int*)m_pValue)[1] = nY;
	((int*)m_pValue)[2] = nZ;
	return true; // Done
}

bool Parameter::SetValue3iv(const int nValue[])
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	((int*)m_pValue)[0] = nValue[0];
	((int*)m_pValue)[1] = nValue[1];
	((int*)m_pValue)[2] = nValue[2];
	return true; // Done
}

// Integer4
bool Parameter::GetValue4i(int &nX, int &nY, int &nZ, int &nW) const
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	nX = ((const int*)m_pValue)[0];
	nY = ((const int*)m_pValue)[1];
	nZ = ((const int*)m_pValue)[2];
	nW = ((const int*)m_pValue)[3];
	return true; // Done
}

const int *Parameter::GetValue4iv() const
{
	return (m_nType == Parameters::Integer4) ? (const int*)m_pValue : nullptr;
}

bool Parameter::SetValue4i(int nX, int nY, int nZ, int nW)
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	((int*)m_pValue)[0] = nX;
	((int*)m_pValue)[1] = nY;
	((int*)m_pValue)[2] = nZ;
	((int*)m_pValue)[3] = nW;
	return true; // Done
}

bool Parameter::SetValue4iv(const int nValue[])
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	((int*)m_pValue)[0] = nValue[0];
	((int*)m_pValue)[1] = nValue[1];
	((int*)m_pValue)[2] = nValue[2];
	((int*)m_pValue)[3] = nValue[3];
	return true; // Done
}


// Float
bool Parameter::GetValue1f(float &fX) const
{
	if (m_nType != Parameters::Float)
		return false; // Error!
	fX = *((const float*)m_pValue);
	return true; // Done
}

float Parameter::GetValue1f() const
{
	return (m_nType == Parameters::Float) ? *((const float*)m_pValue) : 0.0f;
}

bool Parameter::SetValue1f(float fX)
{
	if (m_nType != Parameters::Float)
		return false; // Error!
	*((float*)m_pValue) = fX;
	return true; // Done
}

// Float2
bool Parameter::GetValue2f(float &fX, float &fY) const
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	fX = ((const float*)m_pValue)[0];
	fY = ((const float*)m_pValue)[1];
	return true; // Done
}

const float *Parameter::GetValue2fv() const
{
	return (m_nType == Parameters::Float2) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValue2f(float fX, float fY)
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	((float*)m_pValue)[0] = fX;
	((float*)m_pValue)[1] = fY;
	return true; // Done
}

bool Parameter::SetValue2fv(const float fValue[])
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	((float*)m_pValue)[0] = fValue[0];
	((float*)m_pValue)[1] = fValue[1];
	return true; // Done
}

// Float3
bool Parameter::GetValue3f(float &fX, float &fY, float &fZ) const
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	fX = ((const float*)m_pValue)[0];
	fY = ((const float*)m_pValue)[1];
	fZ = ((const float*)m_pValue)[2];
	return true; // Done
}

const float *Parameter::GetValue3fv() const
{
	return (m_nType == Parameters::Float3) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValue3f(float fX, float fY, float fZ)
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	((float*)m_pValue)[0] = fX;
	((float*)m_pValue)[1] = fY;
	((float*)m_pValue)[2] = fZ;
	return true; // Done
}

bool Parameter::SetValue3fv(const float fValue[])
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	((float*)m_pValue)[0] = fValue[0];
	((float*)m_pValue)[1] = fValue[1];
	((float*)m_pValue)[2] = fValue[2];
	return true; // Done
}

// Float4
bool Parameter::GetValue4f(float &fX, float &fY, float &fZ, float &fW) const
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	fX = ((const float*)m_pValue)[0];
	fY = ((const float*)m_pValue)[1];
	fZ = ((const float*)m_pValue)[2];
	fW = ((const float*)m_pValue)[3];
	return true; // Done
}

const float *Parameter::GetValue4fv() const
{
	return (m_nType == Parameters::Float4) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValue4f(float fX, float fY, float fZ, float fW)
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	((float*)m_pValue)[0] = fX;
	((float*)m_pValue)[1] = fY;
	((float*)m_pValue)[2] = fZ;
	((float*)m_pValue)[3] = fW;
	return true; // Done
}

bool Parameter::SetValue4fv(const float fValue[])
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	((float*)m_pValue)[0] = fValue[0];
	((float*)m_pValue)[1] = fValue[1];
	((float*)m_pValue)[2] = fValue[2];
	((float*)m_pValue)[3] = fValue[3];
	return true; // Done
}


// Double
bool Parameter::GetValue1d(double &fX) const
{
	if (m_nType != Parameters::Double)
		return false; // Error!
	fX = *((const double*)m_pValue);
	return true; // Done
}

bool Parameter::SetValue1d(double fX)
{
	if (m_nType != Parameters::Double)
		return false; // Error!
	*((double*)m_pValue) = fX;
	return true; // Done
}

// Double2
bool Parameter::GetValue2d(double &fX, double &fY) const
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	fX = ((const double*)m_pValue)[0];
	fY = ((const double*)m_pValue)[1];
	return true; // Done
}

const double *Parameter::GetValue2dv() const
{
	return (m_nType == Parameters::Double2) ? (const double*)m_pValue : nullptr;
}

bool Parameter::SetValue2d(double fX, double fY)
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	((double*)m_pValue)[0] = fX;
	((double*)m_pValue)[1] = fY;
	return true; // Done
}

bool Parameter::SetValue2dv(const double fValue[])
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	((double*)m_pValue)[0] = fValue[0];
	((double*)m_pValue)[1] = fValue[1];
	return true; // Done
}

// Double3
bool Parameter::GetValue3d(double &fX, double &fY, double &fZ) const
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	fX = ((const double*)m_pValue)[0];
	fY = ((const double*)m_pValue)[1];
	fZ = ((const double*)m_pValue)[2];
	return true; // Done
}

const double *Parameter::GetValue3dv() const
{
	return (m_nType == Parameters::Double3) ? (const double*)m_pValue : nullptr;
}

bool Parameter::SetValue3d(double fX, double fY, double fZ)
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	((double*)m_pValue)[0] = fX;
	((double*)m_pValue)[1] = fY;
	((double*)m_pValue)[2] = fZ;
	return true; // Done
}

bool Parameter::SetValue3dv(const double fValue[])
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	((double*)m_pValue)[0] = fValue[0];
	((double*)m_pValue)[1] = fValue[1];
	((double*)m_pValue)[2] = fValue[2];
	return true; // Done
}

// Double4
bool Parameter::GetValue4d(double &fX, double &fY, double &fZ, double &fW) const
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	fX = ((const double*)m_pValue)[0];
	fY = ((const double*)m_pValue)[1];
	fZ = ((const double*)m_pValue)[2];
	fW = ((const double*)m_pValue)[3];
	return true; // Done
}

const double *Parameter::GetValue4dv() const
{
	return (m_nType == Parameters::Double4) ? (const double*)m_pValue : nullptr;
}

bool Parameter::SetValue4d(double fX, double fY, double fZ, double fW)
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	((double*)m_pValue)[0] = fX;
	((double*)m_pValue)[1] = fY;
	((double*)m_pValue)[2] = fZ;
	((double*)m_pValue)[3] = fW;
	return true; // Done
}

bool Parameter::SetValue4dv(const double fValue[])
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	((double*)m_pValue)[0] = fValue[0];
	((double*)m_pValue)[1] = fValue[1];
	((double*)m_pValue)[2] = fValue[2];
	((double*)m_pValue)[3] = fValue[3];
	return true; // Done
}


// Float3x3
const float *Parameter::GetValueFloat3x3() const
{
	return (m_nType == Parameters::Float3x3) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValueFloat3x3(const float fValue[])
{
	if (m_nType != Parameters::Float3x3)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*3*3);
	return true; // Done
}


// Float3x4
const float *Parameter::GetValueFloat3x4() const
{
	return (m_nType == Parameters::Float3x4) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValueFloat3x4(const float fValue[])
{
	if (m_nType != Parameters::Float3x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*3*4);
	return true; // Done
}


// Float4x4
const float *Parameter::GetValueMatrixfv() const
{
	return (m_nType == Parameters::Float4x4) ? (const float*)m_pValue : nullptr;
}

bool Parameter::SetValueMatrixfv(const float fValue[])
{
	if (m_nType != Parameters::Float4x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*4*4);
	return true; // Done
}


// Double4x4
const double *Parameter::GetValueMatrixdv() const
{
	return (m_nType == Parameters::Double4x4) ? (const double*)m_pValue : nullptr;
}

bool Parameter::SetValueMatrixdv(const double fValue[])
{
	if (m_nType != Parameters::Double4x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(double)*4*4);
	return true; // Done
}


// Texture
Texture *Parameter::GetValueTexture() const
{
	return (m_nType == Parameters::TextureBuffer) ? ((const TextureHandler*)m_pValue)->GetTexture() : nullptr;
}

TextureHandler *Parameter::GetValueTextureHandler() const
{
	return (m_nType == Parameters::TextureBuffer) ? (TextureHandler*)m_pValue : nullptr;
}

bool Parameter::SetValueTexture(Texture *pTexture)
{
	if (m_nType != Parameters::TextureBuffer)
		return false; // Error!
	((TextureHandler*)m_pValue)->SetResource(pTexture);
	return true; // Done
}

bool Parameter::SetValueTexture(const PLGeneral::String &sFilename)
{
	if (m_nType != Parameters::TextureBuffer)
		return false; // Error!
	TextureHandler *pTextureHandler = (TextureHandler*)m_pValue;
	if (!pTextureHandler->GetResource() || pTextureHandler->GetResource()->GetFilename() != sFilename) {
		pTextureHandler->Load(m_pManager->GetRendererContext().GetTextureManager(), sFilename);
		return pTextureHandler->GetResource() != nullptr; // Done
	} else {
		// Done
		return true;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Parameter::Parameter(ParameterManager &cManager, Parameters::EDataType nType, const PLGeneral::String &sName) :
	m_pManager(&cManager),
	m_nType(nType),
	m_sName(sName)
{
	switch (m_nType) {
		case Parameters::String:
			m_pValue = new PLGeneral::String();
			break;

		case Parameters::Integer:
			m_pValue = new int;
			break;

		case Parameters::Integer2:
			m_pValue = new int[2];
			break;

		case Parameters::Integer3:
			m_pValue = new int[3];
			break;

		case Parameters::Integer4:
			m_pValue = new int[4];
			break;

		case Parameters::Float:
			m_pValue = new float;
			break;

		case Parameters::Float2:
			m_pValue = new float[2];
			break;

		case Parameters::Float3:
			m_pValue = new float[3];
			break;

		case Parameters::Float4:
			m_pValue = new float[4];
			break;

		case Parameters::Double:
			m_pValue = new double;
			break;

		case Parameters::Double2:
			m_pValue = new double[2];
			break;

		case Parameters::Double3:
			m_pValue = new double[3];
			break;

		case Parameters::Double4:
			m_pValue = new double[4];
			break;

		case Parameters::Float3x3:
			m_pValue = new float[3*3];
			break;

		case Parameters::Float3x4:
			m_pValue = new float[3*4];
			break;

		case Parameters::Float4x4:
			m_pValue = new float[4*4];
			break;

		case Parameters::Double4x4:
			m_pValue = new double[4*4];
			break;

		case Parameters::TextureBuffer:
			m_pValue = new TextureHandler();
			break;

		default:
			m_pValue = nullptr;
			break;
	}
}

/**
*  @brief
*    Destructor
*/
Parameter::~Parameter()
{
	if (m_pValue) {
		// Cast pointer if required (MUST be one of this types!)
		switch (m_nType) {
			case Parameters::String:
				delete (PLGeneral::String*)m_pValue;
				break;

			case Parameters::Integer:
				delete (int*)m_pValue;
				break;

			case Parameters::Integer2:
				delete [] (int*)m_pValue;
				break;

			case Parameters::Integer3:
				delete [] (int*)m_pValue;
				break;

			case Parameters::Integer4:
				delete [] (int*)m_pValue;
				break;

			case Parameters::Float:
				delete (float*)m_pValue;
				break;

			case Parameters::Float2:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Float3:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Float4:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Double:
				delete (double*)m_pValue;
				break;

			case Parameters::Double2:
				delete [] (double*)m_pValue;
				break;

			case Parameters::Double3:
				delete [] (double*)m_pValue;
				break;

			case Parameters::Double4:
				delete [] (double*)m_pValue;
				break;

			case Parameters::Float3x3:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Float3x4:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Float4x4:
				delete [] (float*)m_pValue;
				break;

			case Parameters::Double4x4:
				delete [] (double*)m_pValue;
				break;

			case Parameters::TextureBuffer:
				delete (TextureHandler*)m_pValue;
				break;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
