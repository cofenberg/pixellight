/*********************************************************\
 *  File: Parameter.h                                    *
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


#ifndef __PLRENDERER_MATERIAL_PARAMETER_H__
#define __PLRENDERER_MATERIAL_PARAMETER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Parameters.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Texture;
class Program;
class TextureHandler;
class ParameterManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parameters are used for material/effect parameters
*
*  @note
*    - You can only use the functions of the given parameter type!
*/
class Parameter {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ParameterManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the parameter manager this parameter is in
		*
		*  @return
		*    The parameter manager this parameter is in
		*/
		PLRENDERER_API ParameterManager &GetManager() const;

		/**
		*  @brief
		*    Sets the value of this parameter to a parameter within the given manager
		*
		*  @param[in] cManager
		*    Parameter manager to use
		*  @param[in] sName
		*    Name of the parameter within the given manager
		* 
		*  @return
		*    'true' if all went fine, else 'false' (maybe incompatible parameter types?)
		*/
		PLRENDERER_API bool SetManagerParameterValue(Parameters &cManager, const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Sets the value of this parameter to a parameter within the given GPU program
		*
		*  @param[in] cProgram
		*    GPU program to use
		*  @param[in] sName
		*    Name of the parameter within the given manager
		* 
		*  @return
		*    'true' if all went fine, else 'false' (maybe incompatible parameter types?)
		*/
		PLRENDERER_API bool SetManagerParameterValue(Program &cProgram, const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get the parameter type
		*
		*  @return
		*    Parameter type, NEVER Parameters::UnknownDataType!
		*/
		PLRENDERER_API Parameters::EDataType GetType() const;

		/**
		*  @brief
		*    Get the parameter name
		*
		*  @return
		*    Parameter name
		*/
		PLRENDERER_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Set the parameter name
		*
		*  @param[in] sName
		*    New parameter name
		*
		*  @return
		*    'true' if all went fine and the parameter name was changed, else 'false'
		*    (maybe the given name is empty or there's already a parameter with this name
		*    within the parameter manager this parameter is in)
		*/
		PLRENDERER_API bool SetName(const PLGeneral::String &sName);

		//[-------------------------------------------------------]
		//[ Get/set value                                         ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns a parameter value as string (e.g. "1.0 5.4 0.21")
		*
		*  @return
		*    The value of the parameter as string, empty string on error
		*
		*  @note
		*    - Not that performant, try to avoid using this multiple times within each frame
		*/
		PLRENDERER_API PLGeneral::String GetParameterString() const;

		/**
		*  @brief
		*    Sets a parameter value from a string (e.g. "1.0 5.4 0.21")
		*
		*  param[in] sValue
		*    New parameter value
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe unknown parameter)
		*
		*  @see
		*    - GetParameterString()
		*/
		PLRENDERER_API bool SetParameterString(const PLGeneral::String &sValue);

		// Integer
		PLRENDERER_API bool GetValue1i(int &nX) const;
		PLRENDERER_API int GetValue1i() const;
		PLRENDERER_API bool SetValue1i(int nX);

		// Integer2
		PLRENDERER_API bool GetValue2i(int &nX, int &nY) const;
		PLRENDERER_API const int *GetValue2iv() const;
		PLRENDERER_API bool SetValue2i(int nX, int nY);
		PLRENDERER_API bool SetValue2iv(const int nValue[]);

		// Integer3
		PLRENDERER_API bool GetValue3i(int &nX, int &nY, int &nZ) const;
		PLRENDERER_API const int *GetValue3iv() const;
		PLRENDERER_API bool SetValue3i(int nX, int nY, int nZ);
		PLRENDERER_API bool SetValue3iv(const int nValue[]);

		// Integer4
		PLRENDERER_API bool GetValue4i(int &nX, int &nY, int &nZ, int &nW) const;
		PLRENDERER_API const int *GetValue4iv() const;
		PLRENDERER_API bool SetValue4i(int nX, int nY, int nZ, int nW);
		PLRENDERER_API bool SetValue4iv(const int nValue[]);

		// Float
		PLRENDERER_API bool GetValue1f(float &fX) const;
		PLRENDERER_API float GetValue1f() const;
		PLRENDERER_API bool SetValue1f(float fX);

		// Float2
		PLRENDERER_API bool GetValue2f(float &fX, float &fY) const;
		PLRENDERER_API const float *GetValue2fv() const;
		PLRENDERER_API bool SetValue2f(float fX, float fY);
		PLRENDERER_API bool SetValue2fv(const float fValue[]);

		// Float3
		PLRENDERER_API bool GetValue3f(float &fX, float &fY, float &fZ) const;
		PLRENDERER_API const float *GetValue3fv() const;
		PLRENDERER_API bool SetValue3f(float fX, float fY, float fZ);
		PLRENDERER_API bool SetValue3fv(const float fValue[]);

		// Float4
		PLRENDERER_API bool GetValue4f(float &fX, float &fY, float &fZ, float &fW) const;
		PLRENDERER_API const float *GetValue4fv() const;
		PLRENDERER_API bool SetValue4f(float fX, float fY, float fZ, float fW);
		PLRENDERER_API bool SetValue4fv(const float fValue[]);

		// Double
		PLRENDERER_API bool GetValue1d(double &fW) const;
		PLRENDERER_API bool SetValue1d(double fW);

		// Double2
		PLRENDERER_API bool GetValue2d(double &fX, double &fY) const;
		PLRENDERER_API const double *GetValue2dv() const;
		PLRENDERER_API bool SetValue2d(double fX, double fY);
		PLRENDERER_API bool SetValue2dv(const double fValue[]);

		// Double3
		PLRENDERER_API bool GetValue3d(double &fX, double &fY, double &fZ) const;
		PLRENDERER_API const double *GetValue3dv() const;
		PLRENDERER_API bool SetValue3d(double fX, double fY, double fZ);
		PLRENDERER_API bool SetValue3dv(const double fValue[]);

		// Double4
		PLRENDERER_API bool GetValue4d(double &fX, double &fY, double &fZ, double &fW) const;
		PLRENDERER_API const double *GetValue4dv() const;
		PLRENDERER_API bool SetValue4d(double fX, double fY, double fZ, double fW);
		PLRENDERER_API bool SetValue4dv(const double fValue[]);

		// Float3x3
		PLRENDERER_API const float *GetValueFloat3x3() const;
		PLRENDERER_API bool SetValueFloat3x3(const float fValue[]);

		// Float3x4
		PLRENDERER_API const float *GetValueFloat3x4() const;
		PLRENDERER_API bool SetValueFloat3x4(const float fValue[]);

		// Float4x4
		PLRENDERER_API const float *GetValueMatrixfv() const;
		PLRENDERER_API bool SetValueMatrixfv(const float fValue[]);

		// Double4x4
		PLRENDERER_API const double *GetValueMatrixdv() const;
		PLRENDERER_API bool SetValueMatrixdv(const double fValue[]);

		// Texture
		PLRENDERER_API Texture *GetValueTexture() const;
		PLRENDERER_API TextureHandler *GetValueTextureHandler() const;
		PLRENDERER_API bool SetValueTexture(Texture *pTexture);
		PLRENDERER_API bool SetValueTexture(const PLGeneral::String &sFilename);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    The parameter manager this parameter is in
		*  @param[in] nType
		*    Type of the parameter, NEVER Parameters::UnknownDataType!
		*  @param[in] sName
		*    Name of the parameter
		*/
		Parameter(ParameterManager &cManager, Parameters::EDataType nType, const PLGeneral::String &sName);

		/**
		*  @brief
		*    Destructor
		*/
		~Parameter();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ParameterManager	  *m_pManager;	/**< The parameter manager this parameter is in (NEVER a null pointer!) */
		Parameters::EDataType  m_nType;		/**< Parameter type */
		PLGeneral::String	   m_sName;		/**< Parameter name */
		void				  *m_pValue;	/**< Parameter value, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_MATERIAL_PARAMETER_H__
