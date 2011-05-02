/*********************************************************\
 *  File: Func.h                                         *
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


#ifndef __PLCORE_FUNC_H__
#define __PLCORE_FUNC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Type/DefaultValue.h"
#include "PLCore/Base/Func/Signature.h"
#include "PLCore/Base/Func/Params.h"
#include "PLCore/Base/Func/DynFunc.h"


// [DEBUG]
#ifdef _DEBUG
	#include <PLGeneral/System/System.h>
	#include <PLGeneral/System/Console.h>
	#define DEBUG_MESSAGE(MSG)	{ PLGeneral::System::GetInstance()->GetConsole().Print(MSG); }
#else
	#define DEBUG_MESSAGE(MSG)
#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for up to 16 parameters and a return value
*/
template <typename R, typename T0 = NullType, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType, typename T10 = NullType, typename T11 = NullType, typename T12 = NullType, typename T13 = NullType, typename T14 = NullType, typename T15 = NullType>
class Func : public DynFunc {
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
		typedef typename Type<T15>::_Type _T15;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14,
									cP.Param15);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14,
									cP.Param15);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for up to 16 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14,
						cP.Param15);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14,
						cP.Param15);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 15 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 15 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13, cP.Param14);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};


/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 14 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12, cP.Param13);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 14 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12, cP.Param13);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 13 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11, cP.Param12);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 13 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11, cP.Param12);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 12 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10, cP.Param11);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 12 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10, cP.Param11);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 11 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
									cP.Param10);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 11 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9,
						cP.Param10);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 10 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 10 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8,  cP.Param9);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 9 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 9 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7,  cP.Param8);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 8 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class Func<R, T0, T1, T2, T3, T4, T5, T6, T7> : public DynFunc {
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

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6, T7> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6, T7>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6, T7> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6, T7>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6,  cP.Param7);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6, T7>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 8 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class Func<void, T0, T1, T2, T3, T4, T5, T6, T7> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6, T7> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6, T7>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6, T7> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6, T7>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6,  cP.Param7);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6, T7> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6, T7>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 7 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Func<R, T0, T1, T2, T3, T4, T5, T6> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5, T6>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5, T6> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5, T6>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5, T6> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5, T6>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5,  cP.Param6);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5, T6> cParams = Params<R, T0, T1, T2, T3, T4, T5, T6>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 7 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Func<void, T0, T1, T2, T3, T4, T5, T6> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5, T6>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5, T6> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5, T6>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5, T6> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5, T6>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5,  cP.Param6);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5, T6> cParams = Params<void, T0, T1, T2, T3, T4, T5, T6>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 6 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class Func<R, T0, T1, T2, T3, T4, T5> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4, T5>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4, T5> &cP =
					static_cast<Params<R, T0, T1, T2, T3, T4, T5>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4, T5> &cP =
					static_cast<const Params<R, T0, T1, T2, T3, T4, T5>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
									cP.Param5);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5> cParams = Params<R, T0, T1, T2, T3, T4, T5>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5> cParams = Params<R, T0, T1, T2, T3, T4, T5>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4, T5> cParams = Params<R, T0, T1, T2, T3, T4, T5>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4, T5> cParams = Params<R, T0, T1, T2, T3, T4, T5>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 6 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class Func<void, T0, T1, T2, T3, T4, T5> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4, T5>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4, T5> &cP =
					static_cast<Params<void, T0, T1, T2, T3, T4, T5>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4, T5> &cP =
					static_cast<const Params<void, T0, T1, T2, T3, T4, T5>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4,
						cP.Param5);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5> cParams = Params<void, T0, T1, T2, T3, T4, T5>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5> cParams = Params<void, T0, T1, T2, T3, T4, T5>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4, T5> cParams = Params<void, T0, T1, T2, T3, T4, T5>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4, T5> cParams = Params<void, T0, T1, T2, T3, T4, T5>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 5 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
class Func<R, T0, T1, T2, T3, T4> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3, T4>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3, T4> &cP = static_cast<Params<R, T0, T1, T2, T3, T4>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3, T4> &cP = static_cast<const Params<R, T0, T1, T2, T3, T4>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4> cParams = Params<R, T0, T1, T2, T3, T4>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4> cParams = Params<R, T0, T1, T2, T3, T4>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3, T4> cParams = Params<R, T0, T1, T2, T3, T4>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3, T4> cParams = Params<R, T0, T1, T2, T3, T4>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 5 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4>
class Func<void, T0, T1, T2, T3, T4> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3, T4>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3, T4> &cP = static_cast<Params<void, T0, T1, T2, T3, T4>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3, T4> &cP = static_cast<const Params<void, T0, T1, T2, T3, T4>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3,  cP.Param4);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4> cParams = Params<void, T0, T1, T2, T3, T4>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4> cParams = Params<void, T0, T1, T2, T3, T4>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3, T4> cParams = Params<void, T0, T1, T2, T3, T4>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3, T4> cParams = Params<void, T0, T1, T2, T3, T4>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 4 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3>
class Func<R, T0, T1, T2, T3> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2, T3>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2, T3> &cP = static_cast<Params<R, T0, T1, T2, T3>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2, T3> &cP = static_cast<const Params<R, T0, T1, T2, T3>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3> cParams = Params<R, T0, T1, T2, T3>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3> cParams = Params<R, T0, T1, T2, T3>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2, T3> cParams = Params<R, T0, T1, T2, T3>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2, T3> cParams = Params<R, T0, T1, T2, T3>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 4 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3>
class Func<void, T0, T1, T2, T3> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2, T3>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2, T3> &cP = static_cast<Params<void, T0, T1, T2, T3>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2, T3> &cP = static_cast<const Params<void, T0, T1, T2, T3>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2,  cP.Param3);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3> cParams = Params<void, T0, T1, T2, T3>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3> cParams = Params<void, T0, T1, T2, T3>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2, T3> cParams = Params<void, T0, T1, T2, T3>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2, T3> cParams = Params<void, T0, T1, T2, T3>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 3 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2>
class Func<R, T0, T1, T2> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1, T2>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1, T2> &cP = static_cast<Params<R, T0, T1, T2>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1,  cP.Param2);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1, T2> &cP = static_cast<const Params<R, T0, T1, T2>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2> cParams = Params<R, T0, T1, T2>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2> cParams = Params<R, T0, T1, T2>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1, T2> cParams = Params<R, T0, T1, T2>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1, T2> cParams = Params<R, T0, T1, T2>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 3 parameters without a return value
*/
template <typename T0, typename T1, typename T2>
class Func<void, T0, T1, T2> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1, T2>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1, T2> &cP = static_cast<Params<void, T0, T1, T2>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1, T2> &cP = static_cast<const Params<void, T0, T1, T2>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1,  cP.Param2);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2> cParams = Params<void, T0, T1, T2>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2> cParams = Params<void, T0, T1, T2>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1, T2> cParams = Params<void, T0, T1, T2>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1, T2> cParams = Params<void, T0, T1, T2>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 2 parameters and a return value
*/
template <typename R, typename T0, typename T1>
class Func<R, T0, T1> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0, _T1 t1)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0, T1>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0, T1> &cP = static_cast<Params<R, T0, T1>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0,  cP.Param1);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0, T1> &cP = static_cast<const Params<R, T0, T1>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1> cParams = Params<R, T0, T1>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1> cParams = Params<R, T0, T1>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0, T1> cParams = Params<R, T0, T1>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0, T1> cParams = Params<R, T0, T1>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 2 parameters without a return value
*/
template <typename T0, typename T1>
class Func<void, T0, T1> : public DynFunc {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0, _T1 t1)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0, T1>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0, T1> &cP = static_cast<Params<void, T0, T1>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0, T1> &cP = static_cast<const Params<void, T0, T1>&>(cParams);

				// Call function
				(*this)(cP.Param0,  cP.Param1);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1> cParams = Params<void, T0, T1>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1> cParams = Params<void, T0, T1>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0, T1> cParams = Params<void, T0, T1>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0, T1> cParams = Params<void, T0, T1>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 1 parameters and a return value
*/
template <typename R, typename T0>
class Func<R, T0> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()(_T0 t0)
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R, T0>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R, T0> &cP = static_cast<Params<R, T0>&>(cParams);

				// Call function
				cP.Return = (*this)(cP.Param0);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<R, T0> &cP = static_cast<const Params<R, T0>&>(cParams);

				// Call function
				(*this)(cP.Param0);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R, T0> cParams = Params<R, T0>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0> cParams = Params<R, T0>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R, T0> cParams = Params<R, T0>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R, T0> cParams = Params<R, T0>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 1 parameters without a return value
*/
template <typename T0>
class Func<void, T0> : public DynFunc {
	public:
		typedef typename Type<T0>::_Type _T0;

	public:
		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()(_T0 t0)
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void, T0>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<void, T0> &cP = static_cast<Params<void, T0>&>(cParams);

				// Call function
				(*this)(cP.Param0);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				const Params<void, T0> &cP = static_cast<const Params<void, T0>&>(cParams);

				// Call function
				(*this)(cP.Param0);
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void, T0> cParams = Params<void, T0>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0> cParams = Params<void, T0>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void, T0> cParams = Params<void, T0>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void, T0> cParams = Params<void, T0>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 0 parameters and a return value
*/
template <typename R>
class Func<R> : public DynFunc {
	public:
		typedef typename Type<R>  ::_Type _R;

		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual _R operator ()()
		{
			return DefaultValue<R>::Default();
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<R>::GetSignatureID();
		}

		virtual int GetReturnTypeID() const
		{
			return Type<R>::TypeID;
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Get typed params
				Params<R> &cP = static_cast<Params<R>&>(cParams);

				// Call function
				cP.Return = (*this)();
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Call function
				(*this)();
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<R> cParams = Params<R>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<R> cParams = Params<R>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<R> cParams = Params<R>::FromString(sParams);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<R> cParams = Params<R>::FromXml(cElement);
			Call(cParams);
			return Type<R>::ConvertToString(cParams.Return);
		}
};

/**
*  @brief
*    Function object (object that can be 'called' like a function / functoid)
*
*  @remarks
*    Implementation for 0 parameters without a return value
*/
template <>
class Func<void> : public DynFunc {
	public:
		Func()
		{
		}

		virtual ~Func()
		{
		}

		virtual void operator ()()
		{
		}

		virtual PLGeneral::String GetSignature() const
		{
			return Signature<void>::GetSignatureID();
		}

		virtual void Call(DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Call function
				(*this)();
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const DynParams &cParams)
		{
			// Check signature
			if (cParams.GetSignature() == GetSignature()) {
				// Call function
				(*this)();
			} else DEBUG_MESSAGE("ERROR: Signature mismatch!\n  Expected: " + GetSignature() + "\n  Found:    " + cParams.GetSignature() + '\n');
		}

		virtual void Call(const PLGeneral::String &sParams)
		{
			Params<void> cParams = Params<void>::FromString(sParams);
			Call(cParams);
		}

		virtual void Call(const PLGeneral::XmlElement &cElement)
		{
			Params<void> cParams = Params<void>::FromXml(cElement);
			Call(cParams);
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::String &sParams)
		{
			Params<void> cParams = Params<void>::FromString(sParams);
			Call(cParams);
			return "";
		}

		virtual PLGeneral::String CallWithReturn(const PLGeneral::XmlElement &cElement)
		{
			Params<void> cParams = Params<void>::FromXml(cElement);
			Call(cParams);
			return "";
		}
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FUNC_H__
