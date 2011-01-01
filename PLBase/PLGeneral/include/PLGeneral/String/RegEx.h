/*********************************************************\
 *  File: RegEx.h                                        *
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


#ifndef __PLGENERAL_REGEX_H__
#define __PLGENERAL_REGEX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"
#include "PLGeneral/Container/Array.h"
#include "PLGeneral/Container/HashMap.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct real_pcre;
typedef struct real_pcre pcre;
typedef struct pcre_extra pcre_extra;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Regular expression class (PCRE syntax)
*
*  @remarks
*    Internally the PCRE library (http://www.pcre.org) is used -
*    this here is only a wrapper interface.
*    This class supports ASCII and UTF8 encoding. You can force a certain encoding by setting
*    special flags like 'EncodingASCII' for forced ASCII encoding. If no such encoding flags
*    are set by the user, the internal string format of the given regular expression is used
*    as encoding.
*/
class RegEx {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Matching and encoding flags
		*/
		enum EFlags {
			MatchCaseSensitive	= 1,	/**< Match is case sensitive */
			MatchGreedy			= 2,	/**< Match is greedy */
			EncodingASCII		= 4,	/**< ASCII encoding, 1 byte per character (American Standard Code for Information Interchange, 0-128 defined, above undefined) */
			EncodingUTF8		= 8		/**< UTF8  encoding (8-bit Unicode Transformation Format) with 1 to 6 bytes to encode one Unicode character */
		};


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Converts a given wildcard into a regular expression
		*
		*  @param[in] sWildcard
		*    String with wildcard to convert (for example "BeerNumber*")
		*
		*  @return
		*    The converted regular expression (for example "^BeerNumber.*$")
		*/
		PLGENERAL_API static String WildcardToRegEx(const String &sWildcard);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API RegEx();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sExpression
		*    Regular expression
		*  @param[in] nFlags
		*    Processing mode and encoding (combination of EFlags values)
		*/
		PLGENERAL_API RegEx(const String &sExpression, uint32 nFlags = MatchCaseSensitive | MatchGreedy);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cRegEx
		*    RegEx to copy
		*/
		PLGENERAL_API RegEx(const RegEx &cRegEx);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~RegEx();

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cRegEx
		*    RegEx to copy
		*
		*  @return
		*    Reference to this instance
		*/
		PLGENERAL_API RegEx &operator =(const RegEx &cRegEx);

		/**
		*  @brief
		*    Get regular expression
		*
		*  @return
		*    Regular expression
		*/
		PLGENERAL_API String GetExpression() const;

		/**
		*  @brief
		*    Set regular expression
		*
		*  @param[in] sExpression
		*    Regular expression
		*  @param[in] nFlags
		*    Processing mode  and encoding (combination of EFlags values)
		*/
		PLGENERAL_API void SetExpression(const String &sExpression, uint32 nFlags = MatchCaseSensitive | MatchGreedy);

		/**
		*  @brief
		*    Check if the regular expression is valid
		*
		*  @return
		*    Regular expression
		*/
		PLGENERAL_API bool IsValid() const;

		/**
		*  @brief
		*    Get mode and encoding flags
		*
		*  @return
		*    Mode and encoding flags (combination of EFlags values)
		*/
		PLGENERAL_API uint32 GetFlags() const;

		/**
		*  @brief
		*    Is the expression case sensitive?
		*
		*  @return
		*    'true', if the expression is treated case sensitive, else 'false'
		*/
		PLGENERAL_API bool IsCaseSensitive() const;

		/**
		*  @brief
		*    Is the expression greedy?
		*
		*  @return
		*    'true', if the matching is greedy, else 'false'
		*/
		PLGENERAL_API bool IsGreedy() const;

		/**
		*  @brief
		*    Is ASCII encoding used?
		*
		*  @return
		*    'true', if ASCII encoding, else 'false'
		*/
		PLGENERAL_API bool IsASCII() const;

		/**
		*  @brief
		*    Is UTF8 encoding used?
		*
		*  @return
		*    'true', if UTF8 encoding, else 'false'
		*/
		PLGENERAL_API bool IsUTF8() const;

		/**
		*  @brief
		*    Analyse the regular expression and store additional internal information
		*
		*  @remarks
		*    This function analyses and stores additional internal information about the
		*    regular expression, which is later used to speed up processing. So you should
		*    call this e.g. for rather complicated expressions and/or expressions that
		*    are used many times.
		*/
		PLGENERAL_API void Study();

		/**
		*  @brief
		*    Check if a string matches the given regular expression
		*
		*  @param[in] sSubject
		*    String to test
		*  @param[in] nPosition
		*    Start byte position in the string, for instance a value received by 'GetPosition()'
		*
		*  @remarks
		*    'sSubject' is internally automatically converted into the internal string format this
		*    regular expression is using. You can for instance use 'IsASCII()' to check whether or
		*    not ASCII is used.
		*
		*  @return
		*    'true' if the string matches, else 'false'
		*/
		PLGENERAL_API bool Match(const String &sSubject, uint32 nPosition = 0);

		/**
		*  @brief
		*    Get current byte position in the subject string
		*
		*  @return
		*    New byte position in the subject string after the last match
		*/
		PLGENERAL_API int GetPosition() const;

		/**
		*  @brief
		*    Get the results of the last check
		*
		*  @return
		*    List containing all matching groups
		*/
		PLGENERAL_API const Array<String> &GetResults() const;

		/**
		*  @brief
		*    Get a matching group from the last check
		*
		*  @param[in] nIndex
		*    Which group shall be returned?
		*
		*  @return
		*    The matching substring or ""
		*/
		PLGENERAL_API String GetResult(uint32 nIndex) const;

		/**
		*  @brief
		*    Get the results of the last check by name
		*
		*  @return
		*    Map containing all matching groups as pairs of name->substring
		*/
		PLGENERAL_API const Map<String, String> &GetNameResults() const;

		/**
		*  @brief
		*    Get a matching group from the last check by name
		*
		*  @param[in] sName
		*    Which group shall be returned?
		*
		*  @return
		*    The matching substring or ""
		*/
		PLGENERAL_API String GetNameResult(const String &sName) const;

		/**
		*  @brief
		*    Clear all results
		*/
		PLGENERAL_API void ClearResults();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Compiles the PCRE expression
		*/
		void CompilePCRE();

		/**
		*  @brief
		*    Deletes the PCRE expression
		*/
		void FreePCRE();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Regular expression
		String					 m_sExpression;		/**< Regular expression */
		pcre					*m_pPCRE;			/**< PCRE expression, can be NULL */
		pcre_extra				*m_pExtra;			/**< PCRE extra data, can be NULL */
		uint32					 m_nFlags;			/**< Processing mode and encoding (combination of EFlags values) */

		// Matches
		Array<String>			 m_lstGroups;		/**< List of substrings from the last match */
		HashMap<String, String>	 m_mapGroups;		/**< Map of name->substrings pairs from the last match */
		int						 m_nPosition;		/**< Current byte position in the subject */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_REGEX_H__
