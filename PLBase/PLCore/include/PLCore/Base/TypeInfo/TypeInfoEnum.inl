/*********************************************************\
 *  File: TypeInfoEnum.inl                               *
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


#ifndef __PLCORE_TYPEINFO_ENUM_INL__
#define __PLCORE_TYPEINFO_ENUM_INL__
#pragma once


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Type wrapper for enum types
*/
template <typename ENUM>
class TypeInfo< EnumType<ENUM> > : public DynTypeInfo {


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
			for (int i=0; i<EnumType<ENUM>::GetNumOfEnumValues(); i++) {
				m_lstEnumValues.Add(EnumType<ENUM>::GetEnumName(i));
			}
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
		virtual int GetTypeID() const
		{
			return Type<_Type>::TypeID;
		}

		virtual PLGeneral::String GetTypeName() const
		{
			return Type<_Type>::GetTypeName();
		}

		virtual bool IsEnumType() const
		{
			return true;
		}

		virtual bool IsFlagType() const
		{
			return false;
		}

		virtual PLGeneral::String GetEnumValue(const PLGeneral::String &sEnum) const
		{
			PLGeneral::String sName = sEnum;
			PLGeneral::String sDesc;
			_Type nValue = DefaultValue<_Type>::Default();
			ENUM::GetEnumValue(-1, nValue, sName, sDesc);
			return Type<_Type>::ConvertToString(nValue);
		}

		virtual PLGeneral::String GetEnumDescription(const PLGeneral::String &sEnum) const
		{
			PLGeneral::String sName = sEnum;
			PLGeneral::String sDesc;
			_Type nValue = DefaultValue<_Type>::Default();
			ENUM::GetEnumValue(-1, nValue, sName, sDesc);
			return sDesc;
		}


};


//[-------------------------------------------------------]
//[ Static variables                                      ]
//[-------------------------------------------------------]
template <typename ENUM> TypeInfo< EnumType<ENUM> > TypeInfo< EnumType<ENUM> >::Instance;


#endif // __PLCORE_TYPEINFO_ENUM_INL__
