/*********************************************************\
 *  File: FrontendContext.h                              *
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


#ifndef __PLCORE_FRONTENDCONTEXT_H__
#define __PLCORE_FRONTENDCONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Application/ApplicationContext.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Frontend context
*
*  @remarks
*    The frontend context stores data and information for an frontend,
*    such as startup information (what was the current directory when the
*    frontend started) or paths to needed resources.
*/
class FrontendContext : public ApplicationContext {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API FrontendContext();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~FrontendContext();


		//[-------------------------------------------------------]
		//[ Options and data                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get frontend executable name
		*
		*  @return
		*    Name of the frontend executable (default: "")
		*
		*  @remarks
		*    The name of the frontend executable (one can also call it "host", the running executable) is
		*    used as default whenever a name is required (log, configuration, window title and so on).
		*/
		inline String GetName() const;

		/**
		*  @brief
		*    Set frontend executable name
		*
		*  @param[in] sName
		*    Name of the frontend executable (default: "")
		*
		*  @see
		*    - GetName()
		*/
		inline void SetName(const String &sName);

		/**
		*  @brief
		*    Returns the name of the frontend RTTI class to use
		*
		*  @return
		*    The name of the frontend RTTI class to use (default: "PLCore::FrontendPixelLight")
		*/
		inline String GetFrontend() const;

		/**
		*  @brief
		*    Sets the name of the frontend RTTI class to use
		*
		*  @param[in] sFrontend
		*    The name of the frontend RTTI class to use (default: "PLCore::FrontendPixelLight")
		*/
		inline void SetFrontend(const String &sFrontend);

		/**
		*  @brief
		*    Returns the name of the frontend RTTI class constructor to use
		*
		*  @return
		*    The name of the frontend RTTI class constructor to use (default: "")
		*/
		inline String GetFrontendConstructor() const;

		/**
		*  @brief
		*    Sets the name of the frontend RTTI class constructor to use
		*
		*  @param[in]
		*    The name of the frontend RTTI class constructor to use (default: "")
		*/
		inline void SetFrontendConstructor(const String &sFrontendConstructor);

		/**
		*  @brief
		*    Returns the parameters for the frontend RTTI class constructor
		*
		*  @return
		*    Parameters for the frontend RTTI class constructor (default: "")
		*/
		inline String GetFrontendConstructorParameters() const;

		/**
		*  @brief
		*    Sets the parameters for the frontend RTTI class constructor
		*
		*  @param[in] sFrontendConstructorParameters
		*    Parameters for the frontend RTTI class constructor (default: "")
		*/
		inline void SetFrontendConstructorParameters(const String &sFrontendConstructorParameters);

		/**
		*  @brief
		*    Returns the parameters for the instanced frontend RTTI class
		*
		*  @return
		*    The parameters for the instanced frontend RTTI class (default: "")
		*/
		inline String GetFrontendParameters() const;

		/**
		*  @brief
		*    Sets the parameters for the instanced frontend RTTI class
		*
		*  @param[in] sFrontendParameters
		*    The parameters for the instanced frontend RTTI class (default: "")
		*/
		inline void SetFrontendParameters(const String &sFrontendParameters);

		/**
		*  @brief
		*    Returns the name of the frontend implementation RTTI class to use
		*
		*  @return
		*    The name of the frontend implementation RTTI class to use (default: "PLFrontendOS::Frontend")
		*/
		inline String GetFrontendImplementation() const;

		/**
		*  @brief
		*    Sets the name of the frontend implementation RTTI class to use
		*
		*  @param[in] sFrontendImplementation
		*    The name of the frontend implementation RTTI class to use (default: "PLFrontendOS::Frontend")
		*/
		inline void SetFrontendImplementation(const String &sFrontendImplementation);

		/**
		*  @brief
		*    Returns the name of the frontend implementation RTTI class constructor to use
		*
		*  @return
		*    The name of the frontend implementation RTTI class constructor to use (default: "")
		*/
		inline String GetFrontendImplementationConstructor() const;

		/**
		*  @brief
		*    Sets the name of the frontend implementation RTTI class constructor to use
		*
		*  @param[in] sFrontendImplementationConstructor
		*    The name of the frontend implementation RTTI class constructor to use (default: "")
		*/
		inline void SetFrontendImplementationConstructor(const String &sFrontendImplementationConstructor);

		/**
		*  @brief
		*    Returns the parameters for the frontend implementation RTTI class constructor
		*
		*  @return
		*    The parameters for the frontend implementation RTTI class constructor (default: "")
		*/
		inline String GetFrontendImplementationConstructorParameters() const;

		/**
		*  @brief
		*    Sets the parameters for the frontend implementation RTTI class constructor
		*
		*  @param[in] sFrontendImplementationConstructorParameters
		*    The parameters for the frontend implementation RTTI class constructor (default: "")
		*/
		inline void SetFrontendImplementationConstructorParameters(const String &sFrontendImplementationConstructorParameters);

		/**
		*  @brief
		*    Returns the parameters for the instanced frontend implementation RTTI class
		*
		*  @return
		*    The parameters for the instanced frontend implementation RTTI class (default: "")
		*/
		inline String GetFrontendImplementationParameters() const;

		/**
		*  @brief
		*    Sets the parameters for the instanced frontend implementation RTTI class
		*
		*  @param[in] sFrontendImplementationParameters
		*    The parameters for the instanced frontend implementation RTTI class (default: "")
		*/
		inline void SetFrontendImplementationParameters(const String &sFrontendImplementationParameters);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		String m_sName;											/**< Name of the frontend executable                                   (default: "") */
		String m_sFrontend;										/**< Name of the frontend RTTI class to use                            (default: "PLCore::FrontendPixelLight") */
		String m_sFrontendConstructor;							/**< Name of the frontend RTTI class constructor to use                (default: "") */
		String m_sFrontendConstructorParameters;				/**< Parameters for the frontend RTTI class constructor                (default: "") */
		String m_sFrontendParameters;							/**< Parameters for the instanced frontend RTTI class                  (default: "") */
		String m_sFrontendImplementation;						/**< Name of the frontend implementation RTTI class to use             (default: "PLFrontendOS::Frontend") */
		String m_sFrontendImplementationConstructor;			/**< Name of the frontend implementation RTTI class constructor to use (default: "") */
		String m_sFrontendImplementationConstructorParameters;	/**< Parameters for the frontend implementation RTTI class constructor (default: "") */
		String m_sFrontendImplementationParameters;				/**< Parameters for the instanced frontend implementation RTTI class   (default: "") */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Frontend/FrontendContext.inl"


#endif // __PLCORE_FRONTENDCONTEXT_H__
