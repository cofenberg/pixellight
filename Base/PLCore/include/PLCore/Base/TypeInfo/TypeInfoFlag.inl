/*********************************************************\
 *  File: TypeInfoFlag.inl                               *
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


#ifndef __PLCORE_TYPEINFO_FLAG_INL__
#define __PLCORE_TYPEINFO_FLAG_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for flag types
*/
template <typename ENUM>
class TypeInfo< FlagType<ENUM> > : public DynTypeInfo {


	//[-------------------------------------------------------]
	//[ Public data types                                     ]
	//[-------------------------------------------------------]
	public:
		// Type
		typedef typename ENUM::_Type _Type;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static TypeInfo Instance;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		TypeInfo()
		{
			// Fill enum values
			for (int i=0; i<EnumType<ENUM>::GetNumOfEnumValues(); i++)
				m_lstEnumValues.Add(EnumType<ENUM>::GetEnumName(i));
		}

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~TypeInfo()
		{
		}


	//[-------------------------------------------------------]
	//[ Public virtual DynTypeInfo functions                  ]
	//[-------------------------------------------------------]
	public:
		virtual int GetTypeID() const override
		{
			return Type<_Type>::TypeID;
		}

		virtual String GetTypeName() const override
		{
			return Type<_Type>::GetTypeName();
		}

		virtual bool IsEnumType() const override
		{
			return false;
		}

		virtual bool IsFlagType() const override
		{
			return true;
		}

		virtual String GetEnumValue(const String &sEnum) const override
		{
			String sName = sEnum;
			String sDesc;
			_Type nValue = DefaultValue<_Type>::Default();
			ENUM::GetEnumValue(-1, nValue, sName, sDesc);
			return Type<_Type>::ConvertToString(nValue);
		}

		virtual String GetEnumDescription(const String &sEnum) const override
		{
			String sName = sEnum;
			String sDesc;
			_Type nValue = DefaultValue<_Type>::Default();
			ENUM::GetEnumValue(-1, nValue, sName, sDesc);
			return sDesc;
		}


};


//[-------------------------------------------------------]
//[ Static variables                                      ]
//[-------------------------------------------------------]
template <typename ENUM> TypeInfo< FlagType<ENUM> > TypeInfo< FlagType<ENUM> >::Instance;


#endif // __PLCORE_TYPEINFO_FLAG_INL__
