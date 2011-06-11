/*********************************************************\
 *  File: FuncFunPtr.h                                   *
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


#ifndef __PLCORE_FUNC_FUNPTR_H__
#define __PLCORE_FUNC_FUNPTR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Func/Func.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Static function pointer
*
*  @remarks
*    This is a functoid that calls a static function
*/
template <typename R, typename T0 = NullType, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType, typename T10 = NullType, typename T11 = NullType, typename T12 = NullType, typename T13 = NullType, typename T14 = NullType, typename T15 = NullType>
class FuncFunPtr : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for up to 16 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14, _T15 t15) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 15 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 15 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13, _T14 t14) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 14 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 14 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12, _T13 t13) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 13 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 13 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11, _T12 t12) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 12 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 12 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10, _T11 t11) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 11 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 11 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9, _T10 t10) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 10 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 10 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8, _T9 t9) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 9 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7, T8> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 9 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> {
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
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7, T8> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7, T8>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7, _T8 t8) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 8 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6, T7> : public Func<R, T0, T1, T2, T3, T4, T5, T6, T7> {
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
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6, T7> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6, T7>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 8 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6, T7> : public Func<void, T0, T1, T2, T3, T4, T5, T6, T7> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef typename Type<T7> ::_Type _T7;
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6, T7> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6, T7>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6, _T7 t7) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6, t7);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 7 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5, T6> : public Func<R, T0, T1, T2, T3, T4, T5, T6> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef Func<R, T0, T1, T2, T3, T4, T5, T6> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5, T6>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5, t6) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 7 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5, T6> : public Func<void, T0, T1, T2, T3, T4, T5, T6> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef typename Type<T6> ::_Type _T6;
		typedef Func<void, T0, T1, T2, T3, T4, T5, T6> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5, T6>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5, _T6 t6) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5, t6);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 6 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class FuncFunPtr<R, T0, T1, T2, T3, T4, T5> : public Func<R, T0, T1, T2, T3, T4, T5> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef Func<R, T0, T1, T2, T3, T4, T5> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4, T5>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4, t5) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 6 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class FuncFunPtr<void, T0, T1, T2, T3, T4, T5> : public Func<void, T0, T1, T2, T3, T4, T5> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef typename Type<T5> ::_Type _T5;
		typedef Func<void, T0, T1, T2, T3, T4, T5> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4, T5>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4, _T5 t5) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4, t5);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 5 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
class FuncFunPtr<R, T0, T1, T2, T3, T4> : public Func<R, T0, T1, T2, T3, T4> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef Func<R, T0, T1, T2, T3, T4> _Func;
		typedef typename Signature<R, T0, T1, T2, T3, T4>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3, t4) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 5 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3, typename T4>
class FuncFunPtr<void, T0, T1, T2, T3, T4> : public Func<void, T0, T1, T2, T3, T4> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef typename Type<T4> ::_Type _T4;
		typedef Func<void, T0, T1, T2, T3, T4> _Func;
		typedef typename Signature<void, T0, T1, T2, T3, T4>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3, _T4 t4) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3, t4);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 4 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2, typename T3>
class FuncFunPtr<R, T0, T1, T2, T3> : public Func<R, T0, T1, T2, T3> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef Func<R, T0, T1, T2, T3> _Func;
		typedef typename Signature<R, T0, T1, T2, T3>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2, t3) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 4 parameters without a return value
*/
template <typename T0, typename T1, typename T2, typename T3>
class FuncFunPtr<void, T0, T1, T2, T3> : public Func<void, T0, T1, T2, T3> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef typename Type<T3> ::_Type _T3;
		typedef Func<void, T0, T1, T2, T3> _Func;
		typedef typename Signature<void, T0, T1, T2, T3>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2, _T3 t3) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2, t3);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 3 parameters and a return value
*/
template <typename R, typename T0, typename T1, typename T2>
class FuncFunPtr<R, T0, T1, T2> : public Func<R, T0, T1, T2> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef Func<R, T0, T1, T2> _Func;
		typedef typename Signature<R, T0, T1, T2>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1, _T2 t2) {
			return m_pFunc ? (*m_pFunc)(t0, t1, t2) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 3 parameters without a return value
*/
template <typename T0, typename T1, typename T2>
class FuncFunPtr<void, T0, T1, T2> : public Func<void, T0, T1, T2> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef typename Type<T2> ::_Type _T2;
		typedef Func<void, T0, T1, T2> _Func;
		typedef typename Signature<void, T0, T1, T2>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1, _T2 t2) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1, t2);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 2 parameters and a return value
*/
template <typename R, typename T0, typename T1>
class FuncFunPtr<R, T0, T1> : public Func<R, T0, T1> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef Func<R, T0, T1> _Func;
		typedef typename Signature<R, T0, T1>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0, _T1 t1) {
			return m_pFunc ? (*m_pFunc)(t0, t1) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 2 parameters without a return value
*/
template <typename T0, typename T1>
class FuncFunPtr<void, T0, T1> : public Func<void, T0, T1> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef typename Type<T1> ::_Type _T1;
		typedef Func<void, T0, T1> _Func;
		typedef typename Signature<void, T0, T1>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0, _T1 t1) {
			if (m_pFunc)
				(*m_pFunc)(t0, t1);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 1 parameters and a return value
*/
template <typename R, typename T0>
class FuncFunPtr<R, T0> : public Func<R, T0> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef typename Type<T0> ::_Type _T0;
		typedef Func<R, T0> _Func;
		typedef typename Signature<R, T0>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()(_T0 t0) {
			return m_pFunc ? (*m_pFunc)(t0) : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 1 parameters without a return value
*/
template <typename T0>
class FuncFunPtr<void, T0> : public Func<void, T0> {
	public:
		typedef typename Type<T0> ::_Type _T0;
		typedef Func<void, T0> _Func;
		typedef typename Signature<void, T0>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()(_T0 t0) {
			if (m_pFunc)
				(*m_pFunc)(t0);
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 0 parameters and a return value
*/
template <typename R>
class FuncFunPtr<R> : public Func<R> {
	public:
		typedef typename Type<R>  ::_Type _R;
		typedef Func<R> _Func;
		typedef typename Signature<R>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual _R operator ()() {
			return m_pFunc ? (*m_pFunc)() : DefaultValue<R>::Default();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};

/**
*  @brief
*    Static function pointer
*
*  @remarks
*    Implementation for 0 parameters without a return value
*/
template <>
class FuncFunPtr<void> : public Func<void> {
	public:
		typedef Func<void> _Func;
		typedef Signature<void>::FuncType FUNC;

	public:
		FuncFunPtr(const FUNC &pFunc) : m_pFunc(pFunc) {
		}

		virtual ~FuncFunPtr() {
		}

		virtual void operator ()() {
			if (m_pFunc)
				(*m_pFunc)();
		}

		virtual DynFunc *Clone() const {
			return new FuncFunPtr(m_pFunc);
		}

	private:
		FUNC m_pFunc;	/**< Function pointer, can be a null pointer */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FUNC_H__
