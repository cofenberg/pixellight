/*********************************************************\
 *  File: ShaderFunction.h                               *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


#ifndef __PLVOLUMERENDERER_SHADERFUNCTION_H__
#define __PLVOLUMERENDERER_SHADERFUNCTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLVolumeRenderer/PLVolumeRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
}
namespace PLScene {
	class SQCull;
	class VisNode;
}
namespace PLVolumeRenderer {
	class SRPVolume;
	class ShaderCompositor;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract shader function base class
*
*  @remarks
*    Each shader function should have the following properties:
*    - "FunctionTitle":          Function tile
*    - "FunctionName":           Function name
*    - "FunctionSignature_GLSL": Function signature in GLSL syntax, including name
*    - "FunctionSignature_Cg":   Function signature in Cg syntax, including name
*    - "FunctionTemplate":       '1' if this is a function template, else '0'
*
*    The following shader languages and shader profiles are supported
*    - GLSL (OpenGL 3.3, "#version 330")
*    - Supported Cg profiles (modern features like "tex3Dsize()" are used)
*      - GLSL profile: "glslv", "glslg" and "glslf" in "version=150" (OpenGL 3.2)
*      - "gp4 - OpenGL profiles for NVIDIA GeForce 8/9/100/200/300 Series, OpenGL 3.x Quadro": "gp4vp", "gp4gp" and "gp4fp"
*
*  @note
*    - A shader function instance may be used across multiple shader compositions at the same time for efficient resource reuse
*/
class ShaderFunction : public PLCore::Object {


	// [TODO] Just a test
	friend class ShaderCompositor;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLCore::String GLSL;	/**< "GLSL" string */
		static const PLCore::String Cg;		/**< "Cg" string */


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Source code type
		*/
		enum ESourceCodeType {
			VertexShaderHeader     = 0,	/**< Vertex shader header */
			VertexShaderBody       = 1,	/**< Vertex shader body */
			VertexShaderTemplate   = 2,	/**< Vertex shader template */
			FragmentShaderHeader   = 3,	/**< Fragment shader header */
			FragmentShaderBody     = 4,	/**< Fragment shader body */
			FragmentShaderTemplate = 5	/**< Fragment shader template */
		};


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLVOLUMERENDERER_RTTI_EXPORT, ShaderFunction, "PLVolumeRenderer", PLCore::Object, "Abstract shader function base class")
		// Properties
		pl_properties
			pl_property("FunctionTitle",			"Unknown")
			pl_property("FunctionName",				"Unknown")
			pl_property("FunctionSignature_GLSL",	"Unknown")
			pl_property("FunctionSignature_Cg",		"Unknown")
			pl_property("FunctionTemplate",			"0")
		pl_properties_end
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the shader compositor owning this shader function instance
		*
		*  @return
		*    Shader compositor owning this shader function instance, can be a null pointer
		*/
		PLVOLUMERENDERER_API ShaderCompositor *GetShaderCompositor() const;


	//[-------------------------------------------------------]
	//[ Public virtual ShaderFunction functions               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the source code of the shader function
		*
		*  @param[in] sShaderLanguage
		*    The name of the shader language (for example "GLSL" or "Cg") to return the source code for
		*  @param[in] nSourceCodeType
		*    Source code type
		*
		*  @return
		*    The shader source code, empty string on error
		*/
		virtual PLCore::String GetSourceCode(const PLCore::String &sShaderLanguage, ESourceCodeType nSourceCodeType) = 0;

		// [TODO] Just a test
		virtual void SetProgram(PLRenderer::Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUMERENDERER_API ShaderFunction();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUMERENDERER_API virtual ~ShaderFunction();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ShaderCompositor *m_pShaderCompositor;	/**< Shader compositor owning this shader function instance, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer


#endif // __PLVOLUMERENDERER_SHADERFUNCTION_H__
