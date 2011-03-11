/*********************************************************\
 *  File: ProgramGenerator.h                             *
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


#ifndef __PLRENDERER_PROGRAMGENERATOR_H__
#define __PLRENDERER_PROGRAMGENERATOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLCore/Base/Event/EventHandler.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Makro definitions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Adds a vertex shader flag to the program flags
*
*  @param[in] PROGRAMFLAGS
*    Program flags were to add the vertex shader flag
*  @param[in] FLAG
*    Flag to add
*/
#define PL_ADD_VS_FLAG(PROGRAMFLAGS, FLAG) PROGRAMFLAGS.AddVertexShaderFlag(static_cast<PLGeneral::uint32>(FLAG), #FLAG);

/**
*  @brief
*    Adds a fragment shader flag to the program flags
*
*  @param[in] PROGRAMFLAGS
*    Program flags were to add the fragment shader flag
*  @param[in] FLAG
*    Flag to add
*/
#define PL_ADD_FS_FLAG(PROGRAMFLAGS, FLAG) PROGRAMFLAGS.AddFragmentShaderFlag(static_cast<PLGeneral::uint32>(FLAG), #FLAG);


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;
class Program;
class VertexShader;
class FragmentShader;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Program generator for "Über-Shader"
*
*  @remarks
*    The program generator takes as input vertex shader and fragment shader source codes within a defined shader language and
*    returns dynamically composed program instances using given program flags. The generated programs are internally cached so
*    during runtime, they need to be dynamically compiled only once.
*/
class ProgramGenerator {


	//[-------------------------------------------------------]
	//[ Public classes                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Class holding program flags describing the requested program features
		*
		*  @remarks
		*    In order to tell the program generator the requested program features, an instance of this class is used.
		*    This is done by using program flags, which internally will be added in front of the shader source code
		*    as #define preprocessor directives. The goal of the class design was to to make the implementation as
		*    performant as possible due the heavy usage of this class during rendering. Therfore definition strings are just
		*    stored as pointer to "char" instead of "PLGeneral::String" to avoid any overhead produced by strings. As a result,
		*    this definitions strings must stay valid until "ProgramGenerator::GetProgram()" was called with the program flags.
		*    To reduce dynamic memory allocations during rendering, it's recommended to just use one program flags instance during
		*    rendering. When starting the definition of current program flags, call "ProgramFlags::Reset()" to reset the current
		*    states - this method doesn't produce much overhead. If "m_cProgramFlags" is an instance of "ProgramGenerator", vertex
		*    shader program flags are usually added by using "PL_ADD_VS_FLAG(m_cProgramFlags, VS_TWOSIDED)" and program flags
		*    for the fragment shader by using "PL_ADD_FS_FLAG(m_cProgramFlags, FS_ALPHATEST)". The actual flag values "VS_TWOSIDED"
		*    and "FS_ALPHATEST" are implementation depended and usually defined as enumeration values like "VS_TWOSIDED=1<<0",
		*    "VS_ANYTHING=1<<1" and so on. Up to 32 flags per shader type are supported. Flags are only added once.
		*/
		class Flags {
			public:
				Flags() :
					m_nVertexShaderFlags(0),
					m_nFragmentShaderFlags(0)
				{
					m_lstVertexShaderDefinitions.Resize(32, false);
					m_lstFragmentShaderDefinitions.Resize(32, false);
				}
				inline void Reset()
				{
					m_nVertexShaderFlags   = 0;
					m_nFragmentShaderFlags = 0;
					m_lstVertexShaderDefinitions.Reset();
					m_lstFragmentShaderDefinitions.Reset();
				}
				inline void AddVertexShaderFlag(PLGeneral::uint32 nFlag, const char *pszDefinition)
				{
					// Is this flag already set?
					if (!(m_nVertexShaderFlags & nFlag)) {
						// Nope, set it right now
						m_nVertexShaderFlags |= nFlag;
						m_lstVertexShaderDefinitions.Add(pszDefinition);
					}
				}
				inline void AddFragmentShaderFlag(PLGeneral::uint32 nFlag, const char *pszDefinition)
				{
					// Is this flag already set?
					if (!(m_nFragmentShaderFlags & nFlag)) {
						// Nope, set it right now
						m_nFragmentShaderFlags |= nFlag;
						m_lstFragmentShaderDefinitions.Add(pszDefinition);
					}
				}
				inline PLGeneral::uint32 GetVertexShaderFlags() const
				{
					return m_nVertexShaderFlags;
				}
				inline const PLGeneral::Array<const char *> &GetVertexShaderDefinitions() const
				{
					return m_lstVertexShaderDefinitions;
				}
				inline PLGeneral::uint32 GetFragmentShaderFlags() const
				{
					return m_nFragmentShaderFlags;
				}
				inline const PLGeneral::Array<const char *> &GetFragmentShaderDefinitions() const
				{
					return m_lstFragmentShaderDefinitions;
				}
			private:
				PLGeneral::uint32				m_nVertexShaderFlags;
				PLGeneral::Array<const char *>  m_lstVertexShaderDefinitions;
				PLGeneral::uint32				m_nFragmentShaderFlags;
				PLGeneral::Array<const char *>  m_lstFragmentShaderDefinitions;
		};
		struct GeneratedProgram {
			Program			  *pProgram;				/**< The program, always valid! */
			PLGeneral::uint32  nVertexShaderFlags;		/**< Vertex shader flags used to generate the program */
			PLGeneral::uint32  nFragmentShaderFlags;	/**< Fragment shader flags used to generate the program */
			void			  *pUserData;				/**< User data for the generated program, can be a null pointer, is destroyed automatically of the generated
															 program is destroyed, may also become a null pointer if for example the program became dirty */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Removes precision qualifiers from the given GLSL shader source code
		*
		*  @param[in] sSourceCode
		*    Shader source code, usually blank ASCII code
		*
		*  @return
		*    The modified GLSL shader source code
		*
		*  @remarks
		*    From the "The OpenGL® Shading Language" specification "Language Version: 3.30, Document Revision: 6, 11-Mar-2010"
		*        "Precision qualifiers are added for code portability with OpenGL ES, not for functionality. They have the
		*         same syntax as in OpenGL ES, as described below, but they have no semantic meaning, which includes no
		*         effect on the precision used to store or operate on variables."
		*    Although the precision qualifiers "should" have no effect when not using OpenGL ES, we noticed that some NVIDIA GPU
		*    drivers produced compiler errors when using precision qualifiers. Due this buggy behaviour, we decided to remove the
		*    precision qualifiers before passing on the shader source code to the GPU.
		*/
		static PLRENDERER_API PLGeneral::String ApplyGLSLHacks(const PLGeneral::String &sSourceCode);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] sShaderLanguage
		*    The name of the shader language the shaders are using (for example "GLSL" or "Cg")
		*  @param[in] sVertexShader
		*    Vertex shader ("Über-Shader") source code to use, usually blank ASCII
		*  @param[in] sVertexShaderProfile
		*    Vertex shader profile to use (for example "arbvp1" or "glslv"), if empty string, a default profile will be used which usually
		*    tries to use the best available profile that runs on most hardware
		*  @param[in] sFragmentShader
		*    Fragment shader ("Über-Shader") source code to use, usually blank ASCII
		*  @param[in] sFragmentShaderProfile
		*    Fragment shader profile to use (for example "arbfp1" or "glslf"), if empty string, a default profile will be used which usually
		*    tries to use the best available profile that runs on most hardware
		*  @param[in] bGLSLHacks
		*    If the shader language is GLSL, and the used renderer not OpenGL ES 2.0, remove the precision qualifiers? (see ApplyGLSLHacks() documentation)
		*/
		PLRENDERER_API ProgramGenerator(Renderer &cRenderer, const PLGeneral::String &sShaderLanguage,
										const PLGeneral::String &sVertexShader, const PLGeneral::String &sVertexShaderProfile,
										const PLGeneral::String &sFragmentShader, const PLGeneral::String &sFragmentShaderProfile,
										bool bGLSLHacks = false);

		/**
		*  @brief
		*    Destructur
		*/
		PLRENDERER_API ~ProgramGenerator();

		/**
		*  @brief
		*    Returns the used renderer
		*
		*  @return
		*    The used renderer
		*/
		PLRENDERER_API Renderer &GetRenderer() const;

		/**
		*  @brief
		*    Returns the name of the used shader language
		*
		*  @return
		*    The name of the used shader language
		*/
		PLRENDERER_API PLGeneral::String GetShaderLanguage() const;

		/**
		*  @brief
		*    Returns the used vertex shader source code
		*
		*  @return
		*    The used vertex shader source code
		*/
		PLRENDERER_API PLGeneral::String GetVertexShaderSourceCode() const;

		/**
		*  @brief
		*    Returns the used fragment shader source code
		*
		*  @return
		*    The used fragment shader source code
		*/
		PLRENDERER_API PLGeneral::String GetFragmentShaderSourceCode() const;

		/**
		*  @brief
		*    Returns a program
		*
		*  @param[in] cFlags
		*    Program flags describing the requested program features
		*
		*  @return
		*    Generated program, can be a null pointer
		*/
		PLRENDERER_API GeneratedProgram *GetProgram(const Flags &cFlags);

		/**
		*  @brief
		*    Clears the cache of the program generator
		*
		*  @remarks
		*    All already generated and cached vertex shaders, fragment shaders and linked programs will be destroyed. Don't
		*    call this method frequently, else the shader programs must be regenerated to often which will have an impact on
		*    the performance.
		*/
		PLRENDERER_API void ClearCache();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ProgramGenerator(const ProgramGenerator &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ProgramGenerator &operator =(const ProgramGenerator &cSource);

		/**
		*  @brief
		*    Called when a program became dirty
		*
		*  @param[in] pProgram
		*    Program which became dirty
		*/
		void OnDirty(Program *pProgram);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<Program*> EventHandlerDirty;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Input
		Renderer		  *m_pRenderer;					/**< Renderer to use, always valid! */
		PLGeneral::String  m_sShaderLanguage;			/**< The name of the shader language the shaders are using (for example "GLSL" or "Cg") */
		PLGeneral::String  m_sVertexShader;				/**< Vertex shader ("Über-Shader") source code to use, usually blank ASCII */
		PLGeneral::String  m_sVertexShaderProfile;		/**< Vertex shader profile to use, if empty string, a default profile will be used which usually
															 tries to use the best available profile that runs on most hardware */
		PLGeneral::String  m_sFragmentShader;			/**< Fragment shader ("Über-Shader") source code to use, usually blank ASCII */
		PLGeneral::String  m_sFragmentShaderProfile;	/**< Fragment shader profile to use, if empty string, a default profile will be used which usually
															 tries to use the best available profile that runs on most hardware */
		// Cache
		PLGeneral::Array<VertexShader*>						     m_lstVertexShaders;	/**< List of generated vertex shader instances */
		PLGeneral::HashMap<PLGeneral::uint32, VertexShader*>     m_mapVertexShaders;	/**< Program flags -> vertex shader instance */
		PLGeneral::Array<FragmentShader*>					     m_lstFragmentShaders;	/**< List of generated fragment shader instances */
		PLGeneral::HashMap<PLGeneral::uint32, FragmentShader*>   m_mapFragmentShaders;	/**< Program flags -> fragment shader instance */
		PLGeneral::Array<GeneratedProgram*>					     m_lstPrograms;			/**< List of generated program instances */
		PLGeneral::HashMap<PLGeneral::uint64, GeneratedProgram*> m_mapPrograms;			/**< Program flags -> program instance */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_PROGRAMGENERATOR_H__
