/*********************************************************\
 *  File: ParameterManager.h                             *
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


#ifndef __PLRENDERER_MATERIAL_PARAMETERMANAGER_H__
#define __PLRENDERER_MATERIAL_PARAMETERMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Parameters.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}
namespace PLRenderer {
	class Parameter;
	class RendererContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parameter manager
*
*  @remarks
*    The implementation of the 'SetParameter()' functions automatically create 'missing' parameters,
*    if you don't want this, use for example 'IsParameter()' before calling 'SetParameter()'.
*/
class ParameterManager : public Parameters {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Effect;
	friend class Material;
	friend class Parameter;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the owner renderer context
		*
		*  @return
		*    Reference to the owner renderer context
		*/
		PLRENDERER_API RendererContext &GetRendererContext() const;

		/**
		*  @brief
		*    Gets the number of parameters
		*
		*  @return
		*    Number of parameters
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfParameters() const;

		/**
		*  @brief
		*    Creates a new parameter
		*
		*  @param[in] nType
		*    Type of the new parameter, NEVER UnknownDataType!
		*  @param[in] sName
		*    Name of the new parameter, if there's already a parameter with this name this
		*    parameter is returned instead creating a new one
		*
		*  @return
		*    The created parameter, a null pointer on error (maybe unknown data type?)
		*/
		PLRENDERER_API Parameter *CreateParameter(EDataType nType, const PLGeneral::String &sName);

		/**
		*  @brief
		*    Gets a parameter by index
		*
		*  @param[in] nIndex
		*    Parameter index
		*
		*  @return
		*    The requested parameter, a null pointer on error
		*/
		PLRENDERER_API Parameter *GetParameter(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Gets a parameter by name
		*
		*  @param[in] sName
		*    Parameter name
		*
		*  @return
		*    The requested parameter, a null pointer on error
		*/
		PLRENDERER_API Parameter *GetParameter(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Add all parameters to a given XML element
		*
		*  @param[out] cElement
		*    XML element were the parameters should be added
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe invalid XML element)
		*/
		PLRENDERER_API bool AddParametersToXMLElement(PLGeneral::XmlElement &cElement) const;

		/**
		*  @brief
		*    Adds a parameter from a given XML element
		*
		*  @param[in] cElement
		*    XML element were the parameter should be added from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe invalid XML element or it's no known parameter type or no parameter name given)
		*
		*  @note
		*    - If there's already a parameter with this name, this parameter to add is ignored (returns false)
		*/
		PLRENDERER_API bool AddParameterFromXMLElement(const PLGeneral::XmlElement &cElement);

		/**
		*  @brief
		*    Removes a parameter by index
		*
		*  @param[in] nIndex
		*    Index of the parameter name to remove
		*
		*  @return
		*    'true' if all went fine and the parameter was removed, else 'false'
		*    (maybe unknown parameter?)
		*/
		PLRENDERER_API bool RemoveParameter(PLGeneral::uint32 nIndex);

		/**
		*  @brief
		*    Removes a parameter by name
		*
		*  @param[in] sName
		*    Name of the parameter name to remove
		*
		*  @return
		*    'true' if all went fine and the parameter was removed, else 'false'
		*    (maybe unknown parameter?)
		*/
		PLRENDERER_API bool RemoveParameter(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Removes all parameters
		*/
		PLRENDERER_API void RemoveAllParameters();


	//[-------------------------------------------------------]
	//[ Public virtual ParameterManager functions             ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Reloads all textures
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API virtual bool ReloadTextures() const;

		/**
		*  @brief
		*    Called when a parameter has been changed (created, destroyed, value changed)
		*
		*  @param[in] cParameter
		*    Changed parameter
		*
		*  @note
		*    - The default implementation is empty
		*/
		PLRENDERER_API virtual void OnParameterChange(Parameter &cParameter) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    Renderer context to use
		*/
		ParameterManager(RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ParameterManager();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		RendererContext									  *m_pRendererContext;	/**< Renderer context to use, always valid! */
		PLGeneral::Array<Parameter*>					   m_lstParameters;
		PLGeneral::HashMap<PLGeneral::String, Parameter*>  m_mapParameters;


	//[-------------------------------------------------------]
	//[ Public virtual Parameters functions                   ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool IsParameter(const PLGeneral::String &sName) const;
		PLRENDERER_API virtual PLGeneral::String GetParameterString(const PLGeneral::String &sName) const;
		PLRENDERER_API virtual bool SetParameterString(const PLGeneral::String &sName, const PLGeneral::String &sValue);
		// Integer
		PLRENDERER_API virtual bool GetParameter1i(const PLGeneral::String &sName, int &nX) const;
		PLRENDERER_API virtual bool SetParameter1i(const PLGeneral::String &sName, int nX);
		// Integer2
		PLRENDERER_API virtual bool GetParameter2i(const PLGeneral::String &sName, int &nX, int &nY) const;
		PLRENDERER_API virtual bool GetParameter2iv(const PLGeneral::String &sName, int nValue[]) const;
		PLRENDERER_API virtual bool SetParameter2i(const PLGeneral::String &sName, int nX, int nY);
		PLRENDERER_API virtual bool SetParameter2iv(const PLGeneral::String &sName, const int nValue[]);
		// Integer3
		PLRENDERER_API virtual bool GetParameter3i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ) const;
		PLRENDERER_API virtual bool GetParameter3iv(const PLGeneral::String &sName, int nValue[]) const;
		PLRENDERER_API virtual bool SetParameter3i(const PLGeneral::String &sName, int nX, int nY, int nZ);
		PLRENDERER_API virtual bool SetParameter3iv(const PLGeneral::String &sName, const int nValue[]);
		// Integer4
		PLRENDERER_API virtual bool GetParameter4i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ, int &nW) const;
		PLRENDERER_API virtual bool GetParameter4iv(const PLGeneral::String &sName, int nValue[]) const;
		PLRENDERER_API virtual bool SetParameter4i(const PLGeneral::String &sName, int nX, int nY, int nZ, int nW);
		PLRENDERER_API virtual bool SetParameter4iv(const PLGeneral::String &sName, const int nValue[]);
		// Float
		PLRENDERER_API virtual bool GetParameter1f(const PLGeneral::String &sName, float &fX) const;
		PLRENDERER_API virtual bool SetParameter1f(const PLGeneral::String &sName, float fX);
		// Float2
		PLRENDERER_API virtual bool GetParameter2f(const PLGeneral::String &sName, float &fX, float &fY) const;
		PLRENDERER_API virtual bool GetParameter2fv(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameter2f(const PLGeneral::String &sName, float fX, float fY);
		PLRENDERER_API virtual bool SetParameter2fv(const PLGeneral::String &sName, const float fValue[]);
		// Float3
		PLRENDERER_API virtual bool GetParameter3f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ) const;
		PLRENDERER_API virtual bool GetParameter3fv(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameter3f(const PLGeneral::String &sName, float fX, float fY, float fZ);
		PLRENDERER_API virtual bool SetParameter3fv(const PLGeneral::String &sName, const float fValue[]);
		// Float4
		PLRENDERER_API virtual bool GetParameter4f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ, float &fW) const;
		PLRENDERER_API virtual bool GetParameter4fv(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameter4f(const PLGeneral::String &sName, float fX, float fY, float fZ, float fW);
		PLRENDERER_API virtual bool SetParameter4fv(const PLGeneral::String &sName, const float fValue[]);
		// Double
		PLRENDERER_API virtual bool GetParameter1d(const PLGeneral::String &sName, double &fX) const;
		PLRENDERER_API virtual bool SetParameter1d(const PLGeneral::String &sName, double fX);
		// Double2
		PLRENDERER_API virtual bool GetParameter2d(const PLGeneral::String &sName, double &fX, double &fY) const;
		PLRENDERER_API virtual bool GetParameter2dv(const PLGeneral::String &sName, double fValue[]) const;
		PLRENDERER_API virtual bool SetParameter2d(const PLGeneral::String &sName, double fX, double fY);
		PLRENDERER_API virtual bool SetParameter2dv(const PLGeneral::String &sName, const double fValue[]);
		// Double3
		PLRENDERER_API virtual bool GetParameter3d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ) const;
		PLRENDERER_API virtual bool GetParameter3dv(const PLGeneral::String &sName, double fValue[]) const;
		PLRENDERER_API virtual bool SetParameter3d(const PLGeneral::String &sName, double fX, double fY, double fZ);
		PLRENDERER_API virtual bool SetParameter3dv(const PLGeneral::String &sName, const double fValue[]);
		// Double4
		PLRENDERER_API virtual bool GetParameter4d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ, double &fW) const;
		PLRENDERER_API virtual bool GetParameter4dv(const PLGeneral::String &sName, double fValue[]) const;
		PLRENDERER_API virtual bool SetParameter4d(const PLGeneral::String &sName, double fX, double fY, double fZ, double fW);
		PLRENDERER_API virtual bool SetParameter4dv(const PLGeneral::String &sName, const double fValue[]);
		// Float3x3
		PLRENDERER_API virtual bool GetParameterFloat3x3(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameterFloat3x3(const PLGeneral::String &sName, const float fValue[]);
		// Float3x4
		PLRENDERER_API virtual bool GetParameterFloat3x4(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameterFloat3x4(const PLGeneral::String &sName, const float fValue[]);
		// Float4x4
		PLRENDERER_API virtual bool GetParameterMatrixfv(const PLGeneral::String &sName, float fValue[]) const;
		PLRENDERER_API virtual bool SetParameterMatrixfv(const PLGeneral::String &sName, const float fValue[]);
		// Double4x4
		PLRENDERER_API virtual bool GetParameterMatrixdv(const PLGeneral::String &sName, double fValue[]) const;
		PLRENDERER_API virtual bool SetParameterMatrixdv(const PLGeneral::String &sName, const double fValue[]);
		// Texture buffer
		PLRENDERER_API virtual PLRenderer::TextureBuffer *GetParameterTextureBuffer(const PLGeneral::String &sName) const;
		PLRENDERER_API virtual int SetParameterTextureBuffer(const PLGeneral::String &sName, PLRenderer::TextureBuffer *pTextureBuffer);
		PLRENDERER_API virtual PLRenderer::Texture *GetParameterTexture(const PLGeneral::String &sName) const;
		PLRENDERER_API virtual int SetParameterTexture(const PLGeneral::String &sName, const PLGeneral::String &sFilename);
		PLRENDERER_API virtual int SetParameterTexture(const PLGeneral::String &sName, PLRenderer::Texture *pTexture);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_MATERIAL_PARAMETERMANAGER_H__
