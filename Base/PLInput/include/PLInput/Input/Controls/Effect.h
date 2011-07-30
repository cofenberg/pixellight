/*********************************************************\
 *  File: Effect.h                                       *
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


#ifndef __PLINPUT_EFFECT_H__
#define __PLINPUT_EFFECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Input/Controls/Control.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect control
*
*  @remarks
*    Effects are output controls, such as rumble, force-feedback effects etc.
*/
class Effect : public Control {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLINPUT_RTTI_EXPORT, Effect, "PLInput", PLInput::Control, "Effect control")
		#ifdef PLINPUT_EXPORTS	// The following is only required when compiling PLInput
			// Methods
			pl_method_0(GetValue,	pl_ret_type(float),			"Returns the current value.",							"")
			pl_method_1(SetValue,	pl_ret_type(void),	float,	"Set effect value. Current value as first parameter.",	"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Effect
		*
		*  @param[in] pController
		*    Owning controller, can, but shouldn't be a null pointer
		*  @param[in] sName
		*    Control name
		*  @param[in] sDescription
		*    Control description
		*/
		PLINPUT_API Effect(Controller *pController, const PLCore::String &sName, const PLCore::String &sDescription);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Other effect
		*/
		PLINPUT_API Effect(const Effect &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		PLINPUT_API virtual ~Effect();

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Effect to compare with
		*
		*  @return
		*    'true', if both effects are equal, else 'false'
		*/
		PLINPUT_API bool operator ==(const Effect &cOther) const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cOther
		*    Other effect
		*
		*  @return
		*    Reference to this effect
		*/
		PLINPUT_API Effect &operator =(const Effect &cOther);

		/**
		*  @brief
		*    Get effect value
		*
		*  @return
		*    Current value
		*
		*  @remarks
		*    Usually, an effect value should be in the range of 0..1 (but it's up to the actual device definition)
		*/
		PLINPUT_API float GetValue() const;

		/**
		*  @brief
		*    Set effect value
		*
		*  @param[in] fValue
		*    Current value
		*
		*  @remarks
		*    Usually, an effect value should be in the range of 0..1 (but it's up to the actual device definition)
		*/
		PLINPUT_API void SetValue(float fValue);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fValue;	/**< Value of the effect */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_EFFECT_H__
