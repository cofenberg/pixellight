/*********************************************************\
 *  File: FuncScriptPtr.h                                *
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


#ifndef __PLSCRIPT_FUNCSCRIPTPTR_H__
#define __PLSCRIPT_FUNCSCRIPTPTR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Func/Func.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScript {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Script;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Script function pointer
*
*  @remarks
*    This is a functoid that calls a function of a script
*/
template <typename R, typename T0 = PLCore::NullType, typename T1 = PLCore::NullType, typename T2 = PLCore::NullType, typename T3 = PLCore::NullType, typename T4 = PLCore::NullType, typename T5 = PLCore::NullType, typename T6 = PLCore::NullType, typename T7 = PLCore::NullType, typename T8 = PLCore::NullType, typename T9 = PLCore::NullType, typename T10 = PLCore::NullType, typename T11 = PLCore::NullType, typename T12 = PLCore::NullType, typename T13 = PLCore::NullType, typename T14 = PLCore::NullType, typename T15 = PLCore::NullType>
class FuncScriptPtr : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;
		typedef typename PLCore::Type<T14>::_Type _T14;
		typedef typename PLCore::Type<T15>::_Type _T15;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				m_pScript->PushArgument(t14);
				m_pScript->PushArgument(t15);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for up to 16 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;
		typedef typename PLCore::Type<T14>::_Type _T14;
		typedef typename PLCore::Type<T15>::_Type _T15;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				m_pScript->PushArgument(t14);
				m_pScript->PushArgument(t15);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 15 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;
		typedef typename PLCore::Type<T14>::_Type _T14;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				m_pScript->PushArgument(t14);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 15 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;
		typedef typename PLCore::Type<T14>::_Type _T14;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				m_pScript->PushArgument(t14);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 14 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 14 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;
		typedef typename PLCore::Type<T13>::_Type _T13;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->PushArgument(t13);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 13 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 13 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;
		typedef typename PLCore::Type<T12>::_Type _T12;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->PushArgument(t12);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 12 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 12 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;
		typedef typename PLCore::Type<T11>::_Type _T11;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->PushArgument(t11);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 11 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 11 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;
		typedef typename PLCore::Type<T10>::_Type _T10;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->PushArgument(t10);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 10 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 10 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;
		typedef typename PLCore::Type<T9> ::_Type _T9;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->PushArgument(t9);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 9 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 9 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;
		typedef typename PLCore::Type<T8> ::_Type _T8;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->PushArgument(t8);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 8 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6, T7> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 8 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6, T7> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;
		typedef typename PLCore::Type<T7> ::_Type _T7;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6, T7>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->PushArgument(t7);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 7 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5, T6> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5, T6>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 7 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5, T6> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;
		typedef typename PLCore::Type<T6> ::_Type _T6;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5, T6>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->PushArgument(t6);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 6 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class FuncScriptPtr<R, T0, T1, T2, T3, T4, T5> : public PLCore::Func<R, T0, T1, T2, T3, T4, T5> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4, T5>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 6 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class FuncScriptPtr<void, T0, T1, T2, T3, T4, T5> : public PLCore::Func<void, T0, T1, T2, T3, T4, T5> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;
		typedef typename PLCore::Type<T5> ::_Type _T5;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4, T5>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->PushArgument(t5);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 5 parameters and a return value
*/
template < typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
class FuncScriptPtr<R, T0, T1, T2, T3, T4> : public PLCore::Func<R, T0, T1, T2, T3, T4> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3, T4>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 5 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4>
class FuncScriptPtr<void, T0, T1, T2, T3, T4> : public PLCore::Func<void, T0, T1, T2, T3, T4> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;
		typedef typename PLCore::Type<T4> ::_Type _T4;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3, T4>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->PushArgument(t4);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 4 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3>
class FuncScriptPtr<R, T0, T1, T2, T3> : public PLCore::Func<R, T0, T1, T2, T3> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2, T3>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 4 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3>
class FuncScriptPtr<void, T0, T1, T2, T3> : public PLCore::Func<void, T0, T1, T2, T3> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;
		typedef typename PLCore::Type<T3> ::_Type _T3;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2, T3>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->PushArgument(t3);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 3 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2>
class FuncScriptPtr<R, T0, T1, T2> : public PLCore::Func<R, T0, T1, T2> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1, T2>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 3 parameters without a return value
*/
template <typename T0, typename T1, typename T2>
class FuncScriptPtr<void, T0, T1, T2> : public PLCore::Func<void, T0, T1, T2> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;
		typedef typename PLCore::Type<T2> ::_Type _T2;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1, T2>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->PushArgument(t2);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 2 parameters and a return value
*/
template <typename R, typename T0, typename T1>
class FuncScriptPtr<R, T0, T1> : public PLCore::Func<R, T0, T1> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0, T1>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 2 parameters without a return value
*/
template <typename T0, typename T1>
class FuncScriptPtr<void, T0, T1> : public PLCore::Func<void, T0, T1> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;
		typedef typename PLCore::Type<T1> ::_Type _T1;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0, T1>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->PushArgument(t1);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 1 parameters and a return value
*/
template <typename R, typename T0>
class FuncScriptPtr<R, T0> : public PLCore::Func<R, T0> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;
		typedef typename PLCore::Type<T0> ::_Type _T0;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()(_T0 t0) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R, T0>::GetSignature())) {
				m_pScript->PushArgument(t0);
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 1 parameters without a return value
*/
template <typename T0>
class FuncScriptPtr<void, T0> : public PLCore::Func<void, T0> {
	public:
		typedef typename PLCore::Type<T0> ::_Type _T0;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()(_T0 t0) {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void, T0>::GetSignature())) {
				m_pScript->PushArgument(t0);
				m_pScript->EndCall();
			}
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 0 parameters and a return value
*/
template <typename R>
class FuncScriptPtr<R> : public PLCore::Func<R> {
	public:
		typedef typename PLCore::Type<R>  ::_Type _R;

	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual _R operator ()() {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<R>::GetSignature())) {
				if (m_pScript->EndCall()) {
					_R r = PLCore::DefaultValue<R>::Default();
					m_pScript->GetReturn(r);
					return r;
				}
			}
			return PLCore::DefaultValue<R>::Default();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};

/**
*  @brief
*    Script function pointer
*
*  @remarks
*    Implementation for 0 parameters without a return value
*/
template <>
class FuncScriptPtr<void> : public PLCore::Func<void> {
	public:
		FuncScriptPtr(Script *pScript, const PLGeneral::String &sFunction) : m_pScript(pScript), m_sFunction(sFunction) {
		}

		virtual ~FuncScriptPtr() {
		}

		virtual void operator ()() {
			if (m_pScript && m_pScript->BeginCall(m_sFunction, PLCore::Func<void>::GetSignature()))
				m_pScript->EndCall();
		}

		virtual PLCore::DynFunc *Clone() const {
			return new FuncScriptPtr(m_pScript, m_sFunction);
		}

	private:
		Script			  *m_pScript;	/**< Script instance the function is in, can be a null pointer */
		PLGeneral::String  m_sFunction;	/**< Name of the script function to use */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScript


#endif // __PLSCRIPT_FUNCSCRIPTPTR_H__
