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
			cManager.SetParameterString(sName, *static_cast<const PLGeneral::String*>(m_pValue));
			break;

		case Parameters::Integer:
			cManager.SetParameter1i(sName, *static_cast<const int*>(m_pValue));
			break;

		case Parameters::Integer2:
			cManager.SetParameter2iv(sName, static_cast<const int*>(m_pValue));
			break;

		case Parameters::Integer3:
			cManager.SetParameter3iv(sName, static_cast<const int*>(m_pValue));
			break;

		case Parameters::Integer4:
			cManager.SetParameter4iv(sName, static_cast<const int*>(m_pValue));
			break;

		case Parameters::Float:
			cManager.SetParameter1f(sName, *static_cast<const float*>(m_pValue));
			break;

		case Parameters::Float2:
			cManager.SetParameter2fv(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Float3:
			cManager.SetParameter3fv(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Float4:
			cManager.SetParameter4fv(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Double:
			cManager.SetParameter1d(sName, *static_cast<const double*>(m_pValue));
			break;

		case Parameters::Double2:
			cManager.SetParameter2dv(sName, static_cast<const double*>(m_pValue));
			break;

		case Parameters::Double3:
			cManager.SetParameter3dv(sName, static_cast<const double*>(m_pValue));
			break;

		case Parameters::Double4:
			cManager.SetParameter4dv(sName, static_cast<const double*>(m_pValue));
			break;

		case Parameters::Float3x3:
			cManager.SetParameterFloat3x3(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Float3x4:
			cManager.SetParameterFloat3x4(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Float4x4:
			cManager.SetParameterMatrixfv(sName, static_cast<const float*>(m_pValue));
			break;

		case Parameters::Double4x4:
			cManager.SetParameterMatrixdv(sName, static_cast<const double*>(m_pValue));
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
				pProgramUniform->Set(*static_cast<const int*>(m_pValue));
				break;

			case Parameters::Integer2:
				pProgramUniform->Set2(static_cast<const int*>(m_pValue));
				break;

			case Parameters::Integer3:
				pProgramUniform->Set3(static_cast<const int*>(m_pValue));
				break;

			case Parameters::Integer4:
				pProgramUniform->Set4(static_cast<const int*>(m_pValue));
				break;

			case Parameters::Float:
				pProgramUniform->Set(*static_cast<const float*>(m_pValue));
				break;

			case Parameters::Float2:
				pProgramUniform->Set2(static_cast<const float*>(m_pValue));
				break;

			case Parameters::Float3:
				pProgramUniform->Set3(static_cast<const float*>(m_pValue));
				break;

			case Parameters::Float4:
				pProgramUniform->Set4(static_cast<const float*>(m_pValue));
				break;

			case Parameters::Double:
				pProgramUniform->Set(*static_cast<const double*>(m_pValue));
				break;

			case Parameters::Double2:
				pProgramUniform->Set2(static_cast<const double*>(m_pValue));
				break;

			case Parameters::Double3:
				pProgramUniform->Set3(static_cast<const double*>(m_pValue));
				break;

			case Parameters::Double4:
				pProgramUniform->Set4(static_cast<const double*>(m_pValue));
				break;

			case Parameters::Float3x3:
				// [TODO] New shader interface: Add Set3x3 method?
				//pProgramUniform->Set(static_cast<const float*>(m_pValue));
				pProgramUniform->Set(Matrix3x3(static_cast<const float*>(m_pValue)));
				break;

			case Parameters::Float3x4:
				// [TODO] New shader interface: Add Set3x4 method?
				//pProgramUniform->Set(static_cast<const float*>(m_pValue));
				break;

			case Parameters::Float4x4:
				// [TODO] New shader interface: Add Set4x4 method?
				pProgramUniform->Set(Matrix4x4(static_cast<const float*>(m_pValue)));
				break;

			case Parameters::Double4x4:
				// [TODO] New shader interface: Add Set4x4 method?
				//pProgramUniform->Set(static_cast<const double*>(m_pValue));
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

			// Inform the parameter manager about the change
			m_pManager->OnParameterChange(*this);

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
			return *static_cast<const PLGeneral::String*>(m_pValue);

		case Parameters::Integer:
			return PLGeneral::String(*static_cast<const int*>(m_pValue));

		case Parameters::Integer2:
			return PLGeneral::String::Format("%d %d", static_cast<const int*>(m_pValue)[0], static_cast<const int*>(m_pValue)[1]);

		case Parameters::Integer3:
			return PLGeneral::String::Format("%d %d %d", static_cast<const int*>(m_pValue)[0], static_cast<const int*>(m_pValue)[1], static_cast<const int*>(m_pValue)[2]);

		case Parameters::Integer4:
			return PLGeneral::String::Format("%d %d %d %d", static_cast<const int*>(m_pValue)[0], static_cast<const int*>(m_pValue)[1], static_cast<const int*>(m_pValue)[2], static_cast<const int*>(m_pValue)[3]);

		case Parameters::Float:
			return PLGeneral::String::Format("%g", *static_cast<const float*>(m_pValue));

		case Parameters::Float2:
			return PLGeneral::String::Format("%g %g", static_cast<const float*>(m_pValue)[0], static_cast<const float*>(m_pValue)[1]);

		case Parameters::Float3:
			return PLGeneral::String::Format("%g %g %g", static_cast<const float*>(m_pValue)[0], static_cast<const float*>(m_pValue)[1], static_cast<const float*>(m_pValue)[2]);

		case Parameters::Float4:
			return PLGeneral::String::Format("%g %g %g %g", static_cast<const float*>(m_pValue)[0], static_cast<const float*>(m_pValue)[1], static_cast<const float*>(m_pValue)[2], static_cast<const float*>(m_pValue)[3]);

		case Parameters::Double:
			return PLGeneral::String::Format("%g", *static_cast<const double*>(m_pValue));

		case Parameters::Double2:
			return PLGeneral::String::Format("%g %g", static_cast<const double*>(m_pValue)[0], static_cast<const double*>(m_pValue)[1]);

		case Parameters::Double3:
			return PLGeneral::String::Format("%g %g %g", static_cast<const double*>(m_pValue)[0], static_cast<const double*>(m_pValue)[1], static_cast<const double*>(m_pValue)[2]);

		case Parameters::Double4:
			return PLGeneral::String::Format("%g %g %g %g", static_cast<const double*>(m_pValue)[0], static_cast<const double*>(m_pValue)[1], static_cast<const double*>(m_pValue)[2], static_cast<const double*>(m_pValue)[3]);

		case Parameters::Float3x3:
		{
			const float *pfValue = static_cast<const float*>(m_pValue);
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2],
											 pfValue[3], pfValue[4], pfValue[5],
											 pfValue[6], pfValue[7], pfValue[8]);
		}

		case Parameters::Float3x4:
		{
			const float *pfValue = static_cast<const float*>(m_pValue);
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2], pfValue[3],
											 pfValue[4], pfValue[5], pfValue[6], pfValue[7],
											 pfValue[8], pfValue[9], pfValue[10], pfValue[11]);
		}

		case Parameters::Float4x4:
		{
			const float *pfValue = static_cast<const float*>(m_pValue);
			return PLGeneral::String::Format("%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
											 pfValue[0], pfValue[1], pfValue[2], pfValue[3],
											 pfValue[4], pfValue[5], pfValue[6], pfValue[7],
											 pfValue[8], pfValue[9], pfValue[10], pfValue[11],
											 pfValue[12], pfValue[13], pfValue[14], pfValue[15]);
		}

		case Parameters::Double4x4:
		{
			const double *pfValue = static_cast<const double*>(m_pValue);
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
				*static_cast<PLGeneral::String*>(m_pValue) = sValue;
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Integer:
				while (cTokenizer.GetNextToken().GetLength()) {
					*static_cast<int*>(m_pValue) = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Integer2:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<int*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Integer3:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<int*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Integer4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<int*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetInt();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float:
				while (cTokenizer.GetNextToken().GetLength()) {
					*static_cast<float*>(m_pValue) = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float2:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float3:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Double:
				while (cTokenizer.GetNextToken().GetLength()) {
					*static_cast<double*>(m_pValue) = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 1)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Double2:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<double*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 2)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Double3:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<double*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 3)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Double4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<double*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float3x3:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3*3)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float3x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 3*4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Float4x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<float*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetFloat();
					nIndex++;
					if (nIndex >= 4*4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
				break;

			case Parameters::Double4x4:
				while (cTokenizer.GetNextToken().GetLength()) {
					static_cast<double*>(m_pValue)[nIndex] = cTokenizer.GetToken().GetDouble();
					nIndex++;
					if (nIndex >= 4*4)
						break;
				}
				m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
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
	nX = *static_cast<const int*>(m_pValue);
	return true; // Done
}

int Parameter::GetValue1i() const
{
	return (m_nType == Parameters::Integer) ? *static_cast<const int*>(m_pValue) : 0;
}

bool Parameter::SetValue1i(int nX)
{
	if (m_nType != Parameters::Integer)
		return false; // Error!
	*static_cast<int*>(m_pValue) = nX;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Integer2
bool Parameter::GetValue2i(int &nX, int &nY) const
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	return true; // Done
}

const int *Parameter::GetValue2iv() const
{
	return (m_nType == Parameters::Integer2) ? static_cast<const int*>(m_pValue) : nullptr;
}

bool Parameter::SetValue2i(int nX, int nY)
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nX;
	static_cast<int*>(m_pValue)[1] = nY;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue2iv(const int nValue[])
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nValue[0];
	static_cast<int*>(m_pValue)[1] = nValue[1];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Integer3
bool Parameter::GetValue3i(int &nX, int &nY, int &nZ) const
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	nZ = static_cast<const int*>(m_pValue)[2];
	return true; // Done
}

const int *Parameter::GetValue3iv() const
{
	return (m_nType == Parameters::Integer3) ? static_cast<const int*>(m_pValue) : nullptr;
}

bool Parameter::SetValue3i(int nX, int nY, int nZ)
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nX;
	static_cast<int*>(m_pValue)[1] = nY;
	static_cast<int*>(m_pValue)[2] = nZ;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue3iv(const int nValue[])
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nValue[0];
	static_cast<int*>(m_pValue)[1] = nValue[1];
	static_cast<int*>(m_pValue)[2] = nValue[2];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Integer4
bool Parameter::GetValue4i(int &nX, int &nY, int &nZ, int &nW) const
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	nZ = static_cast<const int*>(m_pValue)[2];
	nW = static_cast<const int*>(m_pValue)[3];
	return true; // Done
}

const int *Parameter::GetValue4iv() const
{
	return (m_nType == Parameters::Integer4) ? static_cast<const int*>(m_pValue) : nullptr;
}

bool Parameter::SetValue4i(int nX, int nY, int nZ, int nW)
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nX;
	static_cast<int*>(m_pValue)[1] = nY;
	static_cast<int*>(m_pValue)[2] = nZ;
	static_cast<int*>(m_pValue)[3] = nW;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue4iv(const int nValue[])
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	static_cast<int*>(m_pValue)[0] = nValue[0];
	static_cast<int*>(m_pValue)[1] = nValue[1];
	static_cast<int*>(m_pValue)[2] = nValue[2];
	static_cast<int*>(m_pValue)[3] = nValue[3];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Float
bool Parameter::GetValue1f(float &fX) const
{
	if (m_nType != Parameters::Float)
		return false; // Error!
	fX = *static_cast<const float*>(m_pValue);
	return true; // Done
}

float Parameter::GetValue1f() const
{
	return (m_nType == Parameters::Float) ? *static_cast<const float*>(m_pValue) : 0.0f;
}

bool Parameter::SetValue1f(float fX)
{
	if (m_nType != Parameters::Float)
		return false; // Error!
	*static_cast<float*>(m_pValue) = fX;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Float2
bool Parameter::GetValue2f(float &fX, float &fY) const
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	return true; // Done
}

const float *Parameter::GetValue2fv() const
{
	return (m_nType == Parameters::Float2) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValue2f(float fX, float fY)
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fX;
	static_cast<float*>(m_pValue)[1] = fY;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue2fv(const float fValue[])
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fValue[0];
	static_cast<float*>(m_pValue)[1] = fValue[1];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Float3
bool Parameter::GetValue3f(float &fX, float &fY, float &fZ) const
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	fZ = static_cast<const float*>(m_pValue)[2];
	return true; // Done
}

const float *Parameter::GetValue3fv() const
{
	return (m_nType == Parameters::Float3) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValue3f(float fX, float fY, float fZ)
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fX;
	static_cast<float*>(m_pValue)[1] = fY;
	static_cast<float*>(m_pValue)[2] = fZ;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue3fv(const float fValue[])
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fValue[0];
	static_cast<float*>(m_pValue)[1] = fValue[1];
	static_cast<float*>(m_pValue)[2] = fValue[2];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Float4
bool Parameter::GetValue4f(float &fX, float &fY, float &fZ, float &fW) const
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	fZ = static_cast<const float*>(m_pValue)[2];
	fW = static_cast<const float*>(m_pValue)[3];
	return true; // Done
}

const float *Parameter::GetValue4fv() const
{
	return (m_nType == Parameters::Float4) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValue4f(float fX, float fY, float fZ, float fW)
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fX;
	static_cast<float*>(m_pValue)[1] = fY;
	static_cast<float*>(m_pValue)[2] = fZ;
	static_cast<float*>(m_pValue)[3] = fW;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue4fv(const float fValue[])
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	static_cast<float*>(m_pValue)[0] = fValue[0];
	static_cast<float*>(m_pValue)[1] = fValue[1];
	static_cast<float*>(m_pValue)[2] = fValue[2];
	static_cast<float*>(m_pValue)[3] = fValue[3];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Double
bool Parameter::GetValue1d(double &fX) const
{
	if (m_nType != Parameters::Double)
		return false; // Error!
	fX = *static_cast<const double*>(m_pValue);
	return true; // Done
}

bool Parameter::SetValue1d(double fX)
{
	if (m_nType != Parameters::Double)
		return false; // Error!
	*static_cast<double*>(m_pValue) = fX;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Double2
bool Parameter::GetValue2d(double &fX, double &fY) const
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	return true; // Done
}

const double *Parameter::GetValue2dv() const
{
	return (m_nType == Parameters::Double2) ? static_cast<const double*>(m_pValue) : nullptr;
}

bool Parameter::SetValue2d(double fX, double fY)
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fX;
	static_cast<double*>(m_pValue)[1] = fY;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue2dv(const double fValue[])
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fValue[0];
	static_cast<double*>(m_pValue)[1] = fValue[1];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Double3
bool Parameter::GetValue3d(double &fX, double &fY, double &fZ) const
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	fZ = static_cast<const double*>(m_pValue)[2];
	return true; // Done
}

const double *Parameter::GetValue3dv() const
{
	return (m_nType == Parameters::Double3) ? static_cast<const double*>(m_pValue) : nullptr;
}

bool Parameter::SetValue3d(double fX, double fY, double fZ)
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fX;
	static_cast<double*>(m_pValue)[1] = fY;
	static_cast<double*>(m_pValue)[2] = fZ;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue3dv(const double fValue[])
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fValue[0];
	static_cast<double*>(m_pValue)[1] = fValue[1];
	static_cast<double*>(m_pValue)[2] = fValue[2];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

// Double4
bool Parameter::GetValue4d(double &fX, double &fY, double &fZ, double &fW) const
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	fZ = static_cast<const double*>(m_pValue)[2];
	fW = static_cast<const double*>(m_pValue)[3];
	return true; // Done
}

const double *Parameter::GetValue4dv() const
{
	return (m_nType == Parameters::Double4) ? static_cast<const double*>(m_pValue) : nullptr;
}

bool Parameter::SetValue4d(double fX, double fY, double fZ, double fW)
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fX;
	static_cast<double*>(m_pValue)[1] = fY;
	static_cast<double*>(m_pValue)[2] = fZ;
	static_cast<double*>(m_pValue)[3] = fW;
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValue4dv(const double fValue[])
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	static_cast<double*>(m_pValue)[0] = fValue[0];
	static_cast<double*>(m_pValue)[1] = fValue[1];
	static_cast<double*>(m_pValue)[2] = fValue[2];
	static_cast<double*>(m_pValue)[3] = fValue[3];
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Float3x3
const float *Parameter::GetValueFloat3x3() const
{
	return (m_nType == Parameters::Float3x3) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValueFloat3x3(const float fValue[])
{
	if (m_nType != Parameters::Float3x3)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*3*3);
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Float3x4
const float *Parameter::GetValueFloat3x4() const
{
	return (m_nType == Parameters::Float3x4) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValueFloat3x4(const float fValue[])
{
	if (m_nType != Parameters::Float3x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*3*4);
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Float4x4
const float *Parameter::GetValueMatrixfv() const
{
	return (m_nType == Parameters::Float4x4) ? static_cast<const float*>(m_pValue) : nullptr;
}

bool Parameter::SetValueMatrixfv(const float fValue[])
{
	if (m_nType != Parameters::Float4x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(float)*4*4);
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Double4x4
const double *Parameter::GetValueMatrixdv() const
{
	return (m_nType == Parameters::Double4x4) ? static_cast<const double*>(m_pValue) : nullptr;
}

bool Parameter::SetValueMatrixdv(const double fValue[])
{
	if (m_nType != Parameters::Double4x4)
		return false; // Error!
	PLGeneral::MemoryManager::Copy(m_pValue, fValue, sizeof(double)*4*4);
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}


// Texture
Texture *Parameter::GetValueTexture() const
{
	return (m_nType == Parameters::TextureBuffer) ? static_cast<const TextureHandler*>(m_pValue)->GetTexture() : nullptr;
}

TextureHandler *Parameter::GetValueTextureHandler() const
{
	return (m_nType == Parameters::TextureBuffer) ? static_cast<TextureHandler*>(m_pValue) : nullptr;
}

bool Parameter::SetValueTexture(Texture *pTexture)
{
	if (m_nType != Parameters::TextureBuffer)
		return false; // Error!
	static_cast<TextureHandler*>(m_pValue)->SetResource(pTexture);
	m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
	return true; // Done
}

bool Parameter::SetValueTexture(const PLGeneral::String &sFilename)
{
	if (m_nType != Parameters::TextureBuffer)
		return false; // Error!
	TextureHandler *pTextureHandler = static_cast<TextureHandler*>(m_pValue);
	if (!pTextureHandler->GetResource() || pTextureHandler->GetResource()->GetFilename() != sFilename) {
		pTextureHandler->Load(m_pManager->GetRendererContext().GetTextureManager(), sFilename);
		m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
		return (pTextureHandler->GetResource() != nullptr); // Done
	} else {
		// Done
		m_pManager->OnParameterChange(*this);	// Inform the parameter manager about the change
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
			*static_cast<int*>(m_pValue) = 0;
			break;

		case Parameters::Integer2:
			m_pValue = new int[2];
			static_cast<int*>(m_pValue)[0] = 0;
			static_cast<int*>(m_pValue)[1] = 0;
			break;

		case Parameters::Integer3:
			m_pValue = new int[3];
			static_cast<int*>(m_pValue)[0] = 0;
			static_cast<int*>(m_pValue)[1] = 0;
			static_cast<int*>(m_pValue)[3] = 0;
			break;

		case Parameters::Integer4:
			m_pValue = new int[4];
			static_cast<int*>(m_pValue)[0] = 0;
			static_cast<int*>(m_pValue)[1] = 0;
			static_cast<int*>(m_pValue)[2] = 0;
			static_cast<int*>(m_pValue)[3] = 0;
			break;

		case Parameters::Float:
			m_pValue = new float;
			*static_cast<float*>(m_pValue) = 0.0f;
			break;

		case Parameters::Float2:
			m_pValue = new float[2];
			static_cast<float*>(m_pValue)[0] = 0.0f;
			static_cast<float*>(m_pValue)[1] = 0.0f;
			break;

		case Parameters::Float3:
			m_pValue = new float[3];
			static_cast<float*>(m_pValue)[0] = 0.0f;
			static_cast<float*>(m_pValue)[1] = 0.0f;
			static_cast<float*>(m_pValue)[2] = 0.0f;
			break;

		case Parameters::Float4:
			m_pValue = new float[4];
			static_cast<float*>(m_pValue)[0] = 0.0f;
			static_cast<float*>(m_pValue)[1] = 0.0f;
			static_cast<float*>(m_pValue)[2] = 0.0f;
			static_cast<float*>(m_pValue)[3] = 0.0f;
			break;

		case Parameters::Double:
			m_pValue = new double;
			*static_cast<double*>(m_pValue) = 0.0;
			break;

		case Parameters::Double2:
			m_pValue = new double[2];
			static_cast<double*>(m_pValue)[0] = 0.0;
			static_cast<double*>(m_pValue)[1] = 0.0;
			break;

		case Parameters::Double3:
			m_pValue = new double[3];
			static_cast<double*>(m_pValue)[0] = 0.0;
			static_cast<double*>(m_pValue)[1] = 0.0;
			static_cast<double*>(m_pValue)[2] = 0.0;
			break;

		case Parameters::Double4:
			m_pValue = new double[4];
			static_cast<double*>(m_pValue)[0] = 0.0;
			static_cast<double*>(m_pValue)[1] = 0.0;
			static_cast<double*>(m_pValue)[2] = 0.0;
			static_cast<double*>(m_pValue)[3] = 0.0;
			break;

		case Parameters::Float3x3:
			m_pValue = new float[3*3];
			PLGeneral::MemoryManager::Set(m_pValue, 0, sizeof(float)*3*3);
			break;

		case Parameters::Float3x4:
			m_pValue = new float[3*4];
			PLGeneral::MemoryManager::Set(m_pValue, 0, sizeof(float)*3*4);
			break;

		case Parameters::Float4x4:
			m_pValue = new float[4*4];
			PLGeneral::MemoryManager::Set(m_pValue, 0, sizeof(float)*4*4);
			break;

		case Parameters::Double4x4:
			m_pValue = new double[4*4];
			PLGeneral::MemoryManager::Set(m_pValue, 0, sizeof(double)*4*4);
			break;

		case Parameters::TextureBuffer:
			m_pValue = new TextureHandler();
			break;

		default:
			m_pValue = nullptr;
			break;
	}

	// A new parameter was added - inform the parameter manager about the change
	m_pManager->OnParameterChange(*this);
}

/**
*  @brief
*    Destructor
*/
Parameter::~Parameter()
{
	// The parameter is in the process of getting killed - inform the parameter manager about the change
	m_pManager->OnParameterChange(*this);

	// Cleanup
	if (m_pValue) {
		// Cast pointer if required (MUST be one of this types!)
		switch (m_nType) {
			case Parameters::String:
				delete static_cast<PLGeneral::String*>(m_pValue);
				break;

			case Parameters::Integer:
				delete static_cast<int*>(m_pValue);
				break;

			case Parameters::Integer2:
				delete [] static_cast<int*>(m_pValue);
				break;

			case Parameters::Integer3:
				delete [] static_cast<int*>(m_pValue);
				break;

			case Parameters::Integer4:
				delete [] static_cast<int*>(m_pValue);
				break;

			case Parameters::Float:
				delete static_cast<float*>(m_pValue);
				break;

			case Parameters::Float2:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Float3:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Float4:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Double:
				delete static_cast<double*>(m_pValue);
				break;

			case Parameters::Double2:
				delete [] static_cast<double*>(m_pValue);
				break;

			case Parameters::Double3:
				delete [] static_cast<double*>(m_pValue);
				break;

			case Parameters::Double4:
				delete [] static_cast<double*>(m_pValue);
				break;

			case Parameters::Float3x3:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Float3x4:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Float4x4:
				delete [] static_cast<float*>(m_pValue);
				break;

			case Parameters::Double4x4:
				delete [] static_cast<double*>(m_pValue);
				break;

			case Parameters::TextureBuffer:
				delete static_cast<TextureHandler*>(m_pValue);
				break;
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
