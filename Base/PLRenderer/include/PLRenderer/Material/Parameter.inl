/*********************************************************\
 *  File: Parameter.inl                                  *
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
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the parameter manager this parameter is in
*/
inline ParameterManager &Parameter::GetManager() const
{
	return *m_pManager;
}

/**
*  @brief
*    Get the parameter type
*/
inline Parameters::EDataType Parameter::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Get the parameter name
*/
inline PLCore::String Parameter::GetName() const
{
	return m_sName;
}


//[-------------------------------------------------------]
//[ Get/set value                                         ]
//[-------------------------------------------------------]
// Integer
inline bool Parameter::GetValue1i(int &nX) const
{
	if (m_nType != Parameters::Integer)
		return false; // Error!
	nX = *static_cast<const int*>(m_pValue);
	return true; // Done
}

inline int Parameter::GetValue1i() const
{
	return (m_nType == Parameters::Integer) ? *static_cast<const int*>(m_pValue) : 0;
}

// Integer2
inline bool Parameter::GetValue2i(int &nX, int &nY) const
{
	if (m_nType != Parameters::Integer2)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	return true; // Done
}

inline const int *Parameter::GetValue2iv() const
{
	return (m_nType == Parameters::Integer2) ? static_cast<const int*>(m_pValue) : nullptr;
}

// Integer3
inline bool Parameter::GetValue3i(int &nX, int &nY, int &nZ) const
{
	if (m_nType != Parameters::Integer3)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	nZ = static_cast<const int*>(m_pValue)[2];
	return true; // Done
}

inline const int *Parameter::GetValue3iv() const
{
	return (m_nType == Parameters::Integer3) ? static_cast<const int*>(m_pValue) : nullptr;
}

// Integer4
inline bool Parameter::GetValue4i(int &nX, int &nY, int &nZ, int &nW) const
{
	if (m_nType != Parameters::Integer4)
		return false; // Error!
	nX = static_cast<const int*>(m_pValue)[0];
	nY = static_cast<const int*>(m_pValue)[1];
	nZ = static_cast<const int*>(m_pValue)[2];
	nW = static_cast<const int*>(m_pValue)[3];
	return true; // Done
}

inline const int *Parameter::GetValue4iv() const
{
	return (m_nType == Parameters::Integer4) ? static_cast<const int*>(m_pValue) : nullptr;
}


// Float
inline bool Parameter::GetValue1f(float &fX) const
{
	if (m_nType != Parameters::Float)
		return false; // Error!
	fX = *static_cast<const float*>(m_pValue);
	return true; // Done
}

inline float Parameter::GetValue1f() const
{
	return (m_nType == Parameters::Float) ? *static_cast<const float*>(m_pValue) : 0.0f;
}

// Float2
inline bool Parameter::GetValue2f(float &fX, float &fY) const
{
	if (m_nType != Parameters::Float2)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	return true; // Done
}

inline const float *Parameter::GetValue2fv() const
{
	return (m_nType == Parameters::Float2) ? static_cast<const float*>(m_pValue) : nullptr;
}

// Float3
inline bool Parameter::GetValue3f(float &fX, float &fY, float &fZ) const
{
	if (m_nType != Parameters::Float3)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	fZ = static_cast<const float*>(m_pValue)[2];
	return true; // Done
}

inline const float *Parameter::GetValue3fv() const
{
	return (m_nType == Parameters::Float3) ? static_cast<const float*>(m_pValue) : nullptr;
}

// Float4
inline bool Parameter::GetValue4f(float &fX, float &fY, float &fZ, float &fW) const
{
	if (m_nType != Parameters::Float4)
		return false; // Error!
	fX = static_cast<const float*>(m_pValue)[0];
	fY = static_cast<const float*>(m_pValue)[1];
	fZ = static_cast<const float*>(m_pValue)[2];
	fW = static_cast<const float*>(m_pValue)[3];
	return true; // Done
}

inline const float *Parameter::GetValue4fv() const
{
	return (m_nType == Parameters::Float4) ? static_cast<const float*>(m_pValue) : nullptr;
}


// Double
inline bool Parameter::GetValue1d(double &fX) const
{
	if (m_nType != Parameters::Double)
		return false; // Error!
	fX = *static_cast<const double*>(m_pValue);
	return true; // Done
}

// Double2
inline bool Parameter::GetValue2d(double &fX, double &fY) const
{
	if (m_nType != Parameters::Double2)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	return true; // Done
}

inline const double *Parameter::GetValue2dv() const
{
	return (m_nType == Parameters::Double2) ? static_cast<const double*>(m_pValue) : nullptr;
}

// Double3
inline bool Parameter::GetValue3d(double &fX, double &fY, double &fZ) const
{
	if (m_nType != Parameters::Double3)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	fZ = static_cast<const double*>(m_pValue)[2];
	return true; // Done
}

inline const double *Parameter::GetValue3dv() const
{
	return (m_nType == Parameters::Double3) ? static_cast<const double*>(m_pValue) : nullptr;
}

// Double4
inline bool Parameter::GetValue4d(double &fX, double &fY, double &fZ, double &fW) const
{
	if (m_nType != Parameters::Double4)
		return false; // Error!
	fX = static_cast<const double*>(m_pValue)[0];
	fY = static_cast<const double*>(m_pValue)[1];
	fZ = static_cast<const double*>(m_pValue)[2];
	fW = static_cast<const double*>(m_pValue)[3];
	return true; // Done
}

inline const double *Parameter::GetValue4dv() const
{
	return (m_nType == Parameters::Double4) ? static_cast<const double*>(m_pValue) : nullptr;
}


// Float3x3
inline const float *Parameter::GetValueFloat3x3() const
{
	return (m_nType == Parameters::Float3x3) ? static_cast<const float*>(m_pValue) : nullptr;
}


// Float3x4
inline const float *Parameter::GetValueFloat3x4() const
{
	return (m_nType == Parameters::Float3x4) ? static_cast<const float*>(m_pValue) : nullptr;
}


// Float4x4
inline const float *Parameter::GetValueMatrixfv() const
{
	return (m_nType == Parameters::Float4x4) ? static_cast<const float*>(m_pValue) : nullptr;
}


// Double4x4
inline const double *Parameter::GetValueMatrixdv() const
{
	return (m_nType == Parameters::Double4x4) ? static_cast<const double*>(m_pValue) : nullptr;
}


// Texture
inline TextureHandler *Parameter::GetValueTextureHandler() const
{
	return (m_nType == Parameters::TextureBuffer) ? static_cast<TextureHandler*>(m_pValue) : nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
