/*********************************************************\
 *  File: ConsoleCommand.h                               *
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


#ifndef __PLSCENE_SCENENODE_CONSOLECOMMAND_H__
#define __PLSCENE_SCENENODE_CONSOLECOMMAND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLCore/Base/Func/Functor.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SNConsoleBase;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Console command
*/
class ConsoleCommand {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SNConsoleBase;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*     Console message parameter types
		*
		*  @remarks
		*  @verbatim
		*     A paramCode of "FFBIS" would mean:
		*     Param Type
		*     0     ParamUnknown
		*     1     ParamFloat
		*     2     ParamInt
		*     3     ParamString
		*     4     ParamBool
		*  @endverbatim
		*/
		enum EMsgParamID {
			ParamUnknown,	/**< May not occur! */
			ParamFloat,		/**< 'F' */
			ParamInt,		/**< 'I' */
			ParamString,	/**< 'S' */
			ParamBool		/**< 'B' */
		};


	//[-------------------------------------------------------]
	//[ Public classes                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Console variable
		*/
		class Variable {


			//[-------------------------------------------------------]
			//[ Public data                                           ]
			//[-------------------------------------------------------]
			public:
				float			  f;
				bool			  b;
				int				  i;
				PLGeneral::String s;


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Variable() :
					f(0.0f), b(false), i(0)
				{
				}

				// [TODO] Implement this?
				Variable &operator =(const Variable &cSource)
				{
					return *this;
				}
				bool operator ==(const Variable &cVar) const
				{
					return false;
				}


		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] bDebug
		*    'true' if it is a debug command, else 'false'
		*  @param[in] sCommand
		*    Command string
		*  @param[in] sParameters
		*    Parameter string
		*  @param[in] sHelp
		*    Help string
		*  @param[in] cFunctor
		*    Execution functor
		*/
		PLS_API ConsoleCommand(bool bDebug, const PLGeneral::String &sCommand, const PLGeneral::String &sParameters,
							  const PLGeneral::String &sHelp, const PLCore::Functor<void, ConsoleCommand &> &cFunctor);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLS_API ConsoleCommand(const ConsoleCommand &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API ~ConsoleCommand();

		/**
		*  @brief
		*    Returns the owner console
		*
		*  @return
		*    Owner console, can be NULL
		*/
		PLS_API SNConsoleBase *GetConsole() const;

		/**
		*  @brief
		*    Returns whether this is a debug command or not
		*
		*  @return
		*    'true' if it is a debug command, else 'false'
		*/
		PLS_API bool IsDebug() const;

		/**
		*  @brief
		*    Returns the command string
		*
		*  @return
		*    Command string
		*/
		PLS_API PLGeneral::String GetCommand() const;

		/**
		*  @brief
		*    Returns the parameter string
		*
		*  @return
		*    Parameter string
		*/
		PLS_API PLGeneral::String GetParameters() const;

		/**
		*  @brief
		*    Returns the help string
		*
		*  @return
		*    Help string
		*/
		PLS_API PLGeneral::String GetHelp() const;

		/**
		*  @brief
		*    Returns the execution functor
		*
		*  @return
		*    Command execution functor
		*/
		PLS_API PLCore::Functor<void, ConsoleCommand &> &GetFunctor();

		/**
		*  @brief
		*    Check if the params are valid
		*
		*  @return
		*    'true' if the parameters are valid, else 'false'
		*/
		PLS_API bool HasValidParams() const;

		/**
		*  @brief
		*    Returns the number of parameters
		*
		*  @return
		*    Number of command parameters
		*/
		PLS_API PLGeneral::uint32 GetNumOfParams() const;

		/**
		*  @brief
		*    Returns the parameter type of parameter <nr>
		*
		*  @param[in] nNr
		*    Vars index (must be in range from 0..GetNumOfParams())
		*
		*  @return
		*    The parameter type of parameter
		*/
		PLS_API EMsgParamID GetParamType(PLGeneral::uint32 nNr) const;

		/**
		*  @brief
		*    Create vars from params (convert string into vars)
		*
		*  @param[in] sParameters
		*    Parameter string
		*/
		PLS_API void CreateVarsFromString(const PLGeneral::String &sParameters);

		/**
		*  @brief
		*    Returns the vars at the given index
		*
		*  @param[in] nNr
		*    Vars index
		*
		*  @return
		*    The vars at the given index
		*
		*  @note
		*    - CreateVarsFromString() must have been called before this function...
		*/
		PLS_API Variable &GetVar(PLGeneral::uint32 nNr) const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*/
		PLS_API ConsoleCommand &operator =(const ConsoleCommand &cSource);

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] cCommand
		*    Command to compare with
		*/
		PLS_API bool operator ==(const ConsoleCommand &cCommand) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SNConsoleBase							*m_pConsole;	/**< Owner console, can be NULL */
		bool									 m_bDebug;		/**< Is this a debug command? */
		PLGeneral::String						 m_sCommand;	/**< For example "/fogcolor" */
		PLGeneral::String						 m_sParameters;	/**< For example "III" in case you want R G B values (3 integers) */
		PLGeneral::String						 m_sHelp;		/**< For example "<r> <g> <n>" if you want to display "Usage: /fogcolor <r> <g> <b>" as help */
		PLCore::Functor<void, ConsoleCommand &>  m_cFunctor;	/**< The console functor which executes this command, always valid! */
		PLGeneral::Array<Variable>				 m_lstVars;		/**< Values for the parameters, which the user entered */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_CONSOLECOMMAND_H__
