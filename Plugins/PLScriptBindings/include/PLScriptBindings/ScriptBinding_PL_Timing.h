/*********************************************************\
 *  File: ScriptBinding_PL_Timing.h                      *
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


#ifndef __PLSCRIPTBINDINGS_PL_TIMING_H__
#define __PLSCRIPTBINDINGS_PL_TIMING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Script/ScriptBinding.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScriptBindings {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Timing script binding class
*/
class ScriptBinding_PL_Timing : public PLCore::ScriptBinding {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, ScriptBinding_PL_Timing, "PLScriptBindings", PLCore::ScriptBinding, "Timing script binding class")
		// Properties
		pl_properties
			pl_property("Namespace",	"PL.Timing")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_0(GetTimeDifference,	pl_ret_type(float),			"Returns the past time since last frame (seconds)",																																																																						"")
		pl_method_0(GetFramesPerSecond,	pl_ret_type(float),			"Returns the current frames per second (FPS)",																																																																							"")
		pl_method_0(IsPaused,			pl_ret_type(bool),			"Returns 'true' when the timing is paused, else 'false'. If the timing is paused scene nodes, particles etc. are not updated. The timing will still be updated.",																																										"")
		pl_method_1(Pause,				pl_ret_type(void),	bool,	"Set pause mode. 'true' as first parameter when timing should be pause, else 'false'.",																																																													"")
		pl_method_0(GetTimeScaleFactor,	pl_ret_type(float),			"Returns the time scale factor. The global time scale factor should only be manipulated for debugging. A factor of <= 0 is NOT allowed because this may cause problems in certain situations, pause the timer instead by hand! Do NOT make the factor 'too' (for example > 4) extreme, this may cause problems in certain situations!",	"")
		pl_method_1(SetTimeScaleFactor,	pl_ret_type(bool),	float,	"Sets the time scale factor. Time scale as first parameter (a factor of <= 0 is NOT allowed!). Returns 'true' if all went fine, else 'false' (maybe the given factor is <= 0?).",																																						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		float GetTimeDifference();
		float GetFramesPerSecond();
		bool IsPaused();
		void Pause(bool bPause);
		float GetTimeScaleFactor();
		bool SetTimeScaleFactor(float fFactor);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		ScriptBinding_PL_Timing();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ScriptBinding_PL_Timing();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptBindings


#endif // __PLSCRIPTBINDINGS_PL_TIMING_H__
