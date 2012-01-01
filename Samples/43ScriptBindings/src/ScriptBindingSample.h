/*********************************************************\
 *  File: ScriptBindingSample.h                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSAMPLE_43_SCRIPTBINDING_SAMPLE_H__
#define __PLSAMPLE_43_SCRIPTBINDING_SAMPLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Script/ScriptBinding.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sample script binding class, don't take it to serious
*/
class ScriptBindingSample : public PLCore::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBindingSample, "", PLCore::ScriptBinding, "Sample script binding class, don't take it to serious")
		// Properties
		pl_properties
			pl_property("Namespace",	"Sample")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_0(Return42,			pl_ret_type(int),			"Returns 42",						"")
		pl_method_1(IgnoreTheParameter,	pl_ret_type(void), float,	"Ignores the provided parameter",	"")
		pl_method_0(SaySomethingWise,	pl_ret_type(void),			"Says something wise",				"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		int Return42();
		void IgnoreTheParameter(float fValue);
		void SaySomethingWise();


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBindingSample();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBindingSample();


};


#endif // __PLSAMPLE_43_SCRIPTBINDING_SAMPLE_H__
