/*********************************************************\
 *  File: SNConsoleBase.h                                *
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


#ifndef __PLSCENE_SCENENODE_CONSOLE_H__
#define __PLSCENE_SCENENODE_CONSOLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class ConsoleCommand;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract console base class
*/
class SNConsoleBase : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Console state
		*/
		enum EState {
			Active       = 0,	/**< Console is active */
			Inactive     = 1,	/**< Console is inactive */
			Activating   = 2,	/**< Console is going active */
			Deactivating = 3	/**< Console is going inactive */
		};

		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoDebugCommands = 1<<10	/**< Do not allow debug commands */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(NoDebugCommands, "Do not allow debug commands")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNConsoleBase, "PLScene", PLScene::SceneNode, "Abstract console base class")
		// Attributes
			// Overwritten SceneNode attributes
		pl_attribute(Flags,	pl_flag_type(EFlags),	NoCulling,	ReadWrite,	GetSet,	"Flags",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether the console is active or not
		*
		*  @return
		*    'true' if the console is active, else 'false'
		*/
		PLS_API bool IsActive() const;

		/**
		*  @brief
		*    Activates the console
		*/
		PLS_API void Activate();

		/**
		*  @brief
		*    Deactivates the console
		*/
		PLS_API void Deactivate();

		/**
		*  @brief
		*    Returns the current console state
		*
		*  @return
		*    Console state
		*/
		PLS_API EState GetState() const;

		/**
		*  @brief
		*    Clear the command history
		*/
		PLS_API void ClearCommandHistory();

		/**
		*  @brief
		*    Returns the console description
		*
		*  @return
		*    Console description
		*/
		PLS_API virtual PLGeneral::String GetDescription() const;

		/**
		*  @brief
		*    Registers a new command
		*
		*  @param[in] bDebug
		*    Debug command?
		*  @param[in] sCommand
		*    Command string
		*  @param[in] sParameters
		*    Parameter string
		*  @param[in] sHelp
		*    Help string
		*  @param[in] cFunctor
		*    Execution functor
		*
		*  @remarks
		*    Example:\n
		*    RegisterCommand(0, "/fogcolor", "III", "<r> <g> <b>", Functor<void, ConsoleCommand &>(MyCommandFuncton));
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - Have a look at the definition of ConsoleCommand::EMsgParamID for more information
		*      about the command parameters
		*/
		PLS_API bool RegisterCommand(bool bDebug, const PLGeneral::String &sCommand, const PLGeneral::String &sParameters,
									const PLGeneral::String &sHelp, const PLCore::Functor<void, ConsoleCommand &> &cFunctor);

		/**
		*  @brief
		*    Register a new command
		*
		*  @param[in] cCommand
		*    Command which should be registered
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - RegisterCommand() above
		*/
		PLS_API bool RegisterCommand(const ConsoleCommand &cCommand);

		/**
		*  @brief
		*    Unregisters a command
		*
		*  @param[in] sCommand
		*    Commmand to remove
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - eg: "/fogcolor"... this will remove the /fogcolor command
		*/
		PLS_API bool UnRegisterCommand(const PLGeneral::String &sCommand);

		/**
		*  @brief
		*    Unregisters all commands
		*/
		PLS_API void UnRegisterAllCommands();

		/**
		*  @brief
		*    Returns the number of registered commands
		*
		*  @return
		*    The number of registered commands
		*/
		PLS_API PLGeneral::uint32 GetNumOfCommands() const;

		/**
		*  @brief
		*    Returns the number of parameters in a given string
		*
		*  @param[in] sString
		*    The string which should be checked
		*
		*  @return
		*    Number of parameters in the given string
		*
		*  @remarks
		*    Example: "/fogcolor 100 20 240" will return the value 3
		*/
		PLS_API PLGeneral::uint32 GetNumOfParamsInString(const PLGeneral::String &sString) const;

		/**
		*  @brief
		*    Process a keyboard message
		*/
		PLS_API void ProcessKeyMessage();

		/**
		*  @brief
		*    Process a command
		*
		*  @param[in] sCommand
		*    Command which should be executed
		*
		*  @note
		*    - If 'sCommand' is empty, the console own command line will be executed
		*/
		PLS_API void ProcessCommand(const PLGeneral::String &sCommand = "");

		/**
		*  @brief
		*    Prints a list of all available console commands into the log
		*
		*  @param[in] bDetailed
		*    Should the list have all available information about each command?
		*/
		PLS_API void List(bool bDetailed = false);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNConsoleBase();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNConsoleBase();

		/**
		*  @brief
		*    Process the syntactical correct command
		*
		*  @param[in] cCommand
		*    The syntactical correct command
		*/
		PLS_API void ProcessCommand(ConsoleCommand &cCommand);

		/**
		*  @brief
		*    Completes the command
		*/
		PLS_API void CompleteCommand();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// General
		EState			  m_nState;			/**< Current state of console */
		PLGeneral::String m_sCommand;		/**< Current command string */
		PLGeneral::String m_sFoundCommand;	/**< Found command string */
		PLGeneral::uint32 m_nCursor;		/**< Current cursor position */
		int				  m_nSelStart;		/**< Selection cursor start position */
		int				  m_nSelEnd;		/**< Selection cursor end position */

		// Commands
		PLGeneral::Array<ConsoleCommand*>					   m_lstCommands;	/**< The collection of registered commands */
		PLGeneral::HashMap<PLGeneral::String, ConsoleCommand*> m_mapCommands;	/**< Commands hash map */

		// Command history system
		PLGeneral::uint32					m_nCurrentCommand;		/**< Current selected command entry */
		PLGeneral::Array<PLGeneral::String> m_lstCommandHistory;	/**< Command history list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_CONSOLE_H__
