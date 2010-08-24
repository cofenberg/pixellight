/*********************************************************\
 *  File: Params.h                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLCORE_PARAMS_H__
#define __PLCORE_PARAMS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
#include <PLGeneral/Xml/XmlElement.h>
#include "PLCore/Base/Type/Type.h"
#include "PLCore/Base/Type/DefaultValue.h"
#include "PLCore/Base/Tools/TypeTraits.h"
#include "PLCore/Base/Tools/ParamsParser.h"
#include "PLCore/Base/Tools/ParamsParserXml.h"
#include "PLCore/Base/Func/Signature.h"
#include "PLCore/Base/Func/DynParams.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for up to 16 parameters and a return value
*/
template <typename R, typename T0 = NullType, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType, typename T10 = NullType, typename T11 = NullType, typename T12 = NullType, typename T13 = NullType, typename T14 = NullType, typename T15 = NullType>
class Params : public DynParams {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Storage types
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;
		typedef typename Type<T14>::_Type _T14;
		typedef typename Type<T15>::_Type _T15;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;
		_T14 Param14;
		_T15 Param15;


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()					? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			_T15 t15 = (cParser.Next()					? Type<T15>::ConvertFromString(cParser.GetValue()) : DefaultValue<T15>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()				? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			_T15 t15 = (cParser.Next()				? Type<T15>::ConvertFromString(cParser.GetValue()) : DefaultValue<T15>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
		}


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13),
			Param14(cParams.Param14),
			Param15(cParams.Param15)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13),
			Param14(t14),
			Param15(t15)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
			Param14 = cParams.Param14;
			Param15 = cParams.Param15;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignatureID();
		}


};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for up to 16 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;
		typedef typename Type<T14>::_Type _T14;
		typedef typename Type<T15>::_Type _T15;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;
		_T14 Param14;
		_T15 Param15;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()					? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			_T15 t15 = (cParser.Next()					? Type<T15>::ConvertFromString(cParser.GetValue()) : DefaultValue<T15>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()				? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			_T15 t15 = (cParser.Next()				? Type<T15>::ConvertFromString(cParser.GetValue()) : DefaultValue<T15>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13),
			Param14(cParams.Param14),
			Param15(cParams.Param15)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13),
			Param14(t14),
			Param15(t15)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
			Param14 = cParams.Param14;
			Param15 = cParams.Param15;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 15 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public DynParams {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;
		typedef typename Type<T14>::_Type _T14;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;
		_T14 Param14;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()					? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()				? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13),
			Param14(cParams.Param14)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13),
			Param14(t14)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
			Param14 = cParams.Param14;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 15 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;
		typedef typename Type<T14>::_Type _T14;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;
		_T14 Param14;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()					? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			_T14 t14 = (cParser.Next()				? Type<T14>::ConvertFromString(cParser.GetValue()) : DefaultValue<T14>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13),
			Param14(cParams.Param14)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13),
			Param14(t14)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
			Param14 = cParams.Param14;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 14 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public DynParams {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 14 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;
		typedef typename Type<T13>::_Type _T13;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;
		_T13 Param13;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()					? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			_T13 t13 = (cParser.Next()				? Type<T13>::ConvertFromString(cParser.GetValue()) : DefaultValue<T13>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12),
			Param13(cParams.Param13)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12),
			Param13(t13)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
			Param13 = cParams.Param13;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 13 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public DynParams {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 13 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;
		typedef typename Type<T12>::_Type _T12;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;
		_T12 Param12;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()					? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			_T12 t12 = (cParser.Next()				? Type<T12>::ConvertFromString(cParser.GetValue()) : DefaultValue<T12>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11),
			Param12(cParams.Param12)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11),
			Param12(t12)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
			Param12 = cParams.Param12;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 12 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public DynParams {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 12 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;
		typedef typename Type<T11>::_Type _T11;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;
		_T11 Param11;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()					? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			_T11 t11 = (cParser.Next()				? Type<T11>::ConvertFromString(cParser.GetValue()) : DefaultValue<T11>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10),
			Param11(cParams.Param11)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10),
			Param11(t11)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
			Param11 = cParams.Param11;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 11 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public DynParams {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return  = cParams.Return;
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 11 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public DynParams {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef typename Type<T8> ::_Type _T8;
		typedef typename Type<T9> ::_Type _T9;
		typedef typename Type<T10>::_Type _T10;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;
		_T10 Param10;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0  t0  = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()					? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()					? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()					? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()					? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()					? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()					? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()					? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()					? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()					? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()					? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0  t0  = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1  t1  = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2  t2  = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3  t3  = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4  t4  = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5  t5  = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6  t6  = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7  t7  = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8  t8  = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9  t9  = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			_T10 t10 = (cParser.Next()				? Type<T10>::ConvertFromString(cParser.GetValue()) : DefaultValue<T10>::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9),
			Param10(cParams.Param10)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9),
			Param10(t10)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0  = cParams.Param0;
			Param1  = cParams.Param1;
			Param2  = cParams.Param2;
			Param3  = cParams.Param3;
			Param4  = cParams.Param4;
			Param5  = cParams.Param5;
			Param6  = cParams.Param6;
			Param7  = cParams.Param7;
			Param8  = cParams.Param8;
			Param9  = cParams.Param9;
			Param10 = cParams.Param10;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 10 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;
		typedef typename Type<T8>::_Type _T8;
		typedef typename Type<T9>::_Type _T9;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9 t9 = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9 t9 = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
			Param8 = cParams.Param8;
			Param9 = cParams.Param9;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 10 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;
		typedef typename Type<T8>::_Type _T8;
		typedef typename Type<T9>::_Type _T9;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;
		_T9  Param9;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9 t9 = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			_T9 t9 = (cParser.Next()				? Type<T9> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T9> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8),
			Param9(cParams.Param9)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8),
			Param9(t9)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
			Param8 = cParams.Param8;
			Param9 = cParams.Param9;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 9 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;
		typedef typename Type<T8>::_Type _T8;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
			Param8 = cParams.Param8;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 9 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;
		typedef typename Type<T8>::_Type _T8;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;
		_T8  Param8;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			_T8 t8 = (cParser.Next()				? Type<T8> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T8> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7),
			Param8(cParams.Param8)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7),
			Param8(t8)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
			Param8 = cParams.Param8;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 8 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class Params<R, T0, T1, T2, T3, T4, T5, T6, T7> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 8 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class Params<void, T0, T1, T2, T3, T4, T5, T6, T7> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;
		typedef typename Type<T7>::_Type _T7;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;
		_T7  Param7;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			_T7 t7 = (cParser.Next()				? Type<T7> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T7> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6, t7);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6),
			Param7(cParams.Param7)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6),
			Param7(t7)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
			Param7 = cParams.Param7;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 7 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Params<R, T0, T1, T2, T3, T4, T5, T6> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 7 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Params<void, T0, T1, T2, T3, T4, T5, T6> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;
		typedef typename Type<T6>::_Type _T6;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;
		_T6  Param6;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			_T6 t6 = (cParser.Next()				? Type<T6> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T6> ::Default());
			return Params(t0, t1, t2, t3, t4, t5, t6);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5),
			Param6(cParams.Param6)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5),
			Param6(t6)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
			Param6 = cParams.Param6;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 6 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class Params<R, T0, T1, T2, T3, T4, T5> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			return Params(t0, t1, t2, t3, t4, t5);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			return Params(t0, t1, t2, t3, t4, t5);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 6 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class Params<void, T0, T1, T2, T3, T4, T5> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;
		typedef typename Type<T5>::_Type _T5;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;
		_T5  Param5;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			return Params(t0, t1, t2, t3, t4, t5);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			_T5 t5 = (cParser.Next()				? Type<T5> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T5> ::Default());
			return Params(t0, t1, t2, t3, t4, t5);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4),
			Param5(cParams.Param5)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4),
			Param5(t5)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
			Param5 = cParams.Param5;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 5 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
class Params<R, T0, T1, T2, T3, T4> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			return Params(t0, t1, t2, t3, t4);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			return Params(t0, t1, t2, t3, t4);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 5 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4>
class Params<void, T0, T1, T2, T3, T4> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;
		typedef typename Type<T4>::_Type _T4;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;
		_T4  Param4;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			return Params(t0, t1, t2, t3, t4);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			_T4 t4 = (cParser.Next()				? Type<T4> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T4> ::Default());
			return Params(t0, t1, t2, t3, t4);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3),
			Param4(cParams.Param4)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3),
			Param4(t4)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
			Param4 = cParams.Param4;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 4 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3>
class Params<R, T0, T1, T2, T3> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			return Params(t0, t1, t2, t3);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			return Params(t0, t1, t2, t3);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 4 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3>
class Params<void, T0, T1, T2, T3> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;
		typedef typename Type<T3>::_Type _T3;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;
		_T3  Param3;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			return Params(t0, t1, t2, t3);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			_T3 t3 = (cParser.Next()				? Type<T3> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T3> ::Default());
			return Params(t0, t1, t2, t3);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2),
			Param3(cParams.Param3)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2, _T3 t3) :
			Param0(t0),
			Param1(t1),
			Param2(t2),
			Param3(t3)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
			Param3 = cParams.Param3;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 3 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2>
class Params<R, T0, T1, T2> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			return Params(t0, t1, t2);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			return Params(t0, t1, t2);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1),
			Param2(t2)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 3 parameters without a return value
*/
template <typename T0, typename T1, typename T2>
class Params<void, T0, T1, T2> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;
		typedef typename Type<T2>::_Type _T2;

	public:
		_T0  Param0;
		_T1  Param1;
		_T2  Param2;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			return Params(t0, t1, t2);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			_T2 t2 = (cParser.Next()				? Type<T2> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T2> ::Default());
			return Params(t0, t1, t2);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1),
			Param2(cParams.Param2)
		{
		}

		Params(_T0 t0, _T1 t1, _T2 t2) :
			Param0(t0),
			Param1(t1),
			Param2(t2)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
			Param2 = cParams.Param2;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 2 parameters and a return value
*/
template <typename R, typename T0, typename T1>
class Params<R, T0, T1> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;

	public:
		_R   Return;
		_T0  Param0;
		_T1  Param1;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			return Params(t0, t1);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			return Params(t0, t1);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0),
			Param1(cParams.Param1)
		{
		}

		Params(_T0 t0, _T1 t1) :
			Return(DefaultValue<R>::Default()),
			Param0(t0),
			Param1(t1)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 2 parameters without a return value
*/
template <typename T0, typename T1>
class Params<void, T0, T1> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;
		typedef typename Type<T1>::_Type _T1;

	public:
		_T0  Param0;
		_T1  Param1;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			return Params(t0, t1);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement)	? Type<T0> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T0> ::Default());
			_T1 t1 = (cParser.Next()				? Type<T1> ::ConvertFromString(cParser.GetValue()) : DefaultValue<T1> ::Default());
			return Params(t0, t1);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0),
			Param1(cParams.Param1)
		{
		}

		Params(_T0 t0, _T1 t1) :
			Param0(t0),
			Param1(t1)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
			Param1 = cParams.Param1;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 1 parameters and a return value
*/
template <typename R, typename T0>
class Params<R, T0> : public DynParams {
	public:
		typedef typename Type<R> ::_Type _R;
		typedef typename Type<T0>::_Type _T0;

	public:
		_R   Return;
		_T0  Param0;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams) ? Type<T0>::ConvertFromString(cParser.GetValue()) : DefaultValue<T0>::Default());
			return Params(t0);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement) ? Type<T0>::ConvertFromString(cParser.GetValue()) : DefaultValue<T0>::Default());
			return Params(t0);
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default()),
			Param0(cParams.Param0)
		{
		}

		Params(_T0 t0) :
			Return(DefaultValue<R>::Default()),
			Param0(t0)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
			Param0 = cParams.Param0;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 1 parameters without a return value
*/
template <typename T0>
class Params<void, T0> : public DynParams {
	public:
		typedef typename Type<T0>::_Type _T0;

	public:
		_T0  Param0;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			ParamsParser cParser;
			_T0 t0 = (cParser.ParseString(sParams) ? Type<T0>::ConvertFromString(cParser.GetValue()) : DefaultValue<T0>::Default());
			return Params(t0);
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			ParamsParserXml cParser;
			_T0 t0 = (cParser.ParseXml(cElement) ? Type<T0>::ConvertFromString(cParser.GetValue()) : DefaultValue<T0>::Default());
			return Params(t0);
		}

	public:
		Params(const Params &cParams) :
			Param0(cParams.Param0)
		{
		}

		Params(_T0 t0) :
			Param0(t0)
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Param0 = cParams.Param0;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 0 parameters and a return value
*/
template <typename R>
class Params<R> : public DynParams {
	public:
		typedef typename Type<R>::_Type _R;

	public:
		_R	Return;

	public:
		static Params FromString(const PLGeneral::String &sParams) {
			return Params();
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			return Params();
		}

	public:
		Params(const Params &cParams) :
			Return(DefaultValue<R>::Default())
		{
		}

		Params() :
			Return(DefaultValue<R>::Default())
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
			Return = cParams.Return;
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R>::GetSignatureID();
		}
};

/**
*  @brief
*    Parameters
*
*  @remarks
*    Implementation for 0 parameters without a return value
*/
template <>
class Params<void> : public DynParams {
	public:
		static Params FromString(const PLGeneral::String &sParams) {
			return Params();
		}

		static Params FromXml(const PLGeneral::XmlElement &cElement) {
			return Params();
		}

	public:
		Params(const Params &cParams)
		{
		}

		Params()
		{
		}

		virtual ~Params() {
		}

		Params &operator =(const Params &cParams)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void>::GetSignatureID();
		}
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_PARAMS_H__
