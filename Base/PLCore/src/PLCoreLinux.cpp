/*********************************************************\
 *  File: GeneralLinux.cpp                               *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>
#include <string.h>
#include <stdarg.h>
#include "PLCore/PLCoreLinux.h"
#include "PLCore/PLCoreLinuxWrapper.h"


char *_strupr(char *s)
{
    char *p = s;
    
    if (p) {
		while (*p) {
			*p = toupper(*p);
			p++;
		}
    }

    return s;
}

char *strlwr(char *s)
{
    char *p = s;
    
    if (p) {
		while (*p) {
		    *p = tolower(*p);
			p++;
		}
    }
    return s;
}








/*********************************************************/
// #ifdef isdigit
// #undef isdigit
// #endif
// #define isdigit(c) ((c) >= '0' && (c) <= '9')
// 
// #ifndef breakeven_point
// #  define breakeven_point   6	/* some reasonable one-size-fits-all value */
// #endif
// 
// #define fast_memcpy(d,s,n) \
  // { register size_t nn = (size_t)(n); \
    // if (nn >= breakeven_point) memcpy((d), (s), nn); \
    // else if (nn > 0) { /* proc call overhead is worth only for large strings*/\
      // register char *dd; register const char *ss; \
      // for (ss=(s), dd=(d); nn>0; nn--) *dd++ = *ss++; } }
// 
// #define fast_memset(d,c,n) \
  // { register size_t nn = (size_t)(n); \
    // if (nn >= breakeven_point) memset((d), (int)(c), nn); \
    // else if (nn > 0) { /* proc call overhead is worth only for large strings*/\
      // register char *dd; register const int cc=(int)(c); \
      // for (dd=(d); nn>0; nn--) *dd++ = cc; } }
/*****************************************************************************************/
/**start of the own vsnwprintf function with support to act like the vscwprintf from M$**/
#define _T(x) L ## x

int _vsnwprintf(wchar_t *buf, size_t lenMax,
                             const wchar_t *format, va_list argptr)
{
    // number of characters in the buffer so far, must be less than lenMax
    size_t lenCur = 0;
	for ( size_t n = 0;  ; n++ )
    {
        const wchar_t chCur = format[n];

        if ( chCur == _T('%') )
        {
            static wchar_t s_szFlags[256] = _T("%");
            size_t flagofs = 1;
            bool adj_left = false,
                 in_prec = false,
                 prec_dot = false,
                 done = false;
            int ilen = 0;
            size_t min_width = 0,
                   max_width = lenMax - lenCur;
            do
            {

#define CHECK_PREC \
                if (in_prec && !prec_dot) \
                { \
                    s_szFlags[flagofs++] = '.'; \
                    prec_dot = true; \
                }

#define APPEND_CH(ch) \
                { \
                    if ( lenCur == lenMax ) \
                        return -1; \
                    \
                    buf[lenCur++] = ch; \
                }

#define APPEND_STR(s) \
                { \
                    for ( const wchar_t *p = s; *p; p++ ) \
                    { \
                        APPEND_CH(*p); \
                    } \
                }

                // what follows '%'?
                const wchar_t ch = format[++n];
                switch ( ch )
                {
                    case _T('\0'):
                        APPEND_CH(_T('\0'));

                        done = true;
                        break;

                    case _T('%'):
                        APPEND_CH(_T('%'));
                        done = true;
                        break;

                    case _T('#'):
                    case _T('0'):
                    case _T(' '):
                    case _T('+'):
                    case _T('\''):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('-'):
                        CHECK_PREC
                        adj_left = true;
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('.'):
                        CHECK_PREC
                        in_prec = true;
                        prec_dot = false;
                        max_width = 0;
                        // dot will be auto-added to s_szFlags if non-negative
                        // number follows
                        break;

                    case _T('h'):
                        ilen = -1;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('l'):
                        ilen = 1;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('q'):
                    case _T('L'):
                        ilen = 2;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('Z'):
                        ilen = 3;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('*'):
                        {
                            int len = va_arg(argptr, int);
                            if (in_prec)
                            {
                                if (len<0) break;
                                CHECK_PREC
                                    max_width = len;
                            }
                            else
                            {
                                if (len<0)
                                {
                                    adj_left = !adj_left;
                                    s_szFlags[flagofs++] = '-';
                                    len = -len;
                                }
                                min_width = len;
                            }
                            flagofs += ::swprintf(s_szFlags+flagofs,256-flagofs,_T("%d"),len);
                        }
                        break;

                    case _T('1'): case _T('2'): case _T('3'):
                    case _T('4'): case _T('5'): case _T('6'):
                    case _T('7'): case _T('8'): case _T('9'):
                        {
                            int len = 0;
                            CHECK_PREC
                            while ( (format[n] >= _T('0')) &&
                                    (format[n] <= _T('9')) )
                            {
                                s_szFlags[flagofs++] = format[n];
                                len = len*10 + (format[n] - _T('0'));
                                n++;
                            }

                            if (in_prec)
                                max_width = len;
                            else
                                min_width = len;

                            n--; // the main loop pre-increments n again
                        }
                        break;

                    case _T('d'):
                    case _T('i'):
                    case _T('o'):
                    case _T('u'):
                    case _T('x'):
                    case _T('X'):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        s_szFlags[flagofs] = '\0';
                        if (ilen == 0 )
                        {
                            int val = va_arg(argptr, int);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }
                        else if (ilen == -1)
                        {
                            // NB: 'short int' value passed through '...'
                            //      is promoted to 'int', so we have to get
                            //      an int from stack even if we need a short
                            short int val = static_cast<short int>(va_arg(argptr, int));
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }
                        else if (ilen == 1)
                        {
                            long int val = va_arg(argptr, long int);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }
                        else if (ilen == 2)
                        {
#if SIZEOF_LONG_LONG
                            long long int val = va_arg(argptr, long long int);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
#else // !long long
                            long int val = va_arg(argptr, long int);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
#endif // long long/!long long
                        }
                        else if (ilen == 3)
                        {
                            size_t val = va_arg(argptr, size_t);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }

                        done = true;
                        break;

                    case _T('e'):
                    case _T('E'):
                    case _T('f'):
                    case _T('g'):
                    case _T('G'):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        s_szFlags[flagofs] = '\0';
                        if (ilen == 2)
                        {
                            long double val = va_arg(argptr, long double);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }
                        else
                        {
                            double val = va_arg(argptr, double);
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);
                        }
                        done = true;
                        break;

                    case _T('p'):
                        {
                            void *val = va_arg(argptr, void *);
                            CHECK_PREC
                            s_szFlags[flagofs++] = ch;
                            s_szFlags[flagofs] = '\0';
                            lenCur +=::swprintf(&buf[lenCur],lenMax - lenCur, s_szFlags, val);

                            done = true;
                        }
                        break;

                    case _T('c'):
                        {
                            int val = va_arg(argptr, int);
#if wxUSE_UNICODE
                            if (ilen == -1)
                            {
                                const char buf[2] = { val, 0 };
                                val = wxString(buf, wxConvLibc)[0u];
                            }
#elif wxUSE_WCHAR_T
                            if (ilen == 1)
                            {
                                const wchar_t buf[2] = { val, 0 };
                                val = wxString(buf, wxConvLibc)[0u];
                            }
#endif
                            size_t i;

                            if (!adj_left)
                                for (i = 1; i < min_width; i++)
                                    APPEND_CH(_T(' '));

                            APPEND_CH(val);

                            if (adj_left)
                                for (i = 1; i < min_width; i++)
                                    APPEND_CH(_T(' '));

                            done = true;
                        }
                        break;

                    case _T('s'):
                        {
                            const wchar_t *val = nullptr;
#if wxUSE_UNICODE
                            wxString s;

                            if (ilen == -1)
                            {
                                // wx extension: we'll let %hs mean non-Unicode
                                // strings
                                char *v = va_arg(argptr, char *);

                                if (v)
                                    val = s = wxString(v, wxConvLibc);
                            }
                            else
#elif wxUSE_WCHAR_T
                            wxString s;

                            if (ilen == 1)
                            {
                                // %ls means Unicode strings
                                wchar_t *v = va_arg(argptr, wchar_t *);

                                if (v)
                                    val = s = wxString(v, wxConvLibc);
                            }
                            else
#endif
                            {
								val = va_arg(argptr, wchar_t*);
                            }

                            size_t len = 0;

                            if (val)
                            {
                                for ( len = 0;
                                      val[len] && (len < max_width);
                                      len++ )
                                    ;
                            }
                            else if (max_width >= 6)
                            {
                                val = _T("(null)");
                                len = 6;
                            }
                            else
                            {
                                val = _T("");
                                len = 0;
                            }

                            size_t i;

                            if (!adj_left)
                                for (i = len; i < min_width; i++)
                                    APPEND_CH(_T(' '));

                            for (i = 0; i < len; i++)
                                APPEND_CH(val[i]);

                            if (adj_left)
                                for (i = len; i < min_width; i++)
                                    APPEND_CH(_T(' '));
                            done = true;
                        }
                        break;

                    case _T('n'):
                        if (ilen == 0)
                        {
                            int *val = va_arg(argptr, int *);
                            *val = lenCur;
                        }
                        else if (ilen == -1)
                        {
                            short int *val = va_arg(argptr, short int *);
                            *val = lenCur;
                        }
                        else if (ilen >= 1)
                        {
                            long int *val = va_arg(argptr, long int *);
                            *val = lenCur;
                        }
                        done = true;
                        break;

                    default:
                        // bad format, leave unchanged
                        APPEND_CH(_T('%'));
                        APPEND_CH(ch);
                        done = true;
                        break;
                }
            }
            while (!done);
        }
        else
        {
            APPEND_CH(chCur);
        }

        // terminating zero?
        if ( !chCur )
            break;
    }

	//buf[lenCur] = _T('\0');
	// return the string length which would be written without the string end terminator'\0'
    return lenCur-1;
}

int numlen(int num)
{
	int len = 0;
	if(!num) return 1;
	if(num < 0) len = 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(unsigned int num)
{
	int len = 0;
	if(!num) return 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(short int num)
{
	int len = 0;
	if(!num) return 1;
	if(num < 0) len = 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(unsigned short int num)
{
	int len = 0;
	if(!num) return 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(long num)
{
	int len = 0;
	if(!num) return 1;
	if(num < 0) len = 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(unsigned long num)
{
	int len = 0;
	if(!num) return 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(long long num)
{
	int len = 0;
	if(!num) return 1;
	if(num < 0) len = 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
int numlen(unsigned long long num)
{
	int len = 0;
	if(!num) return 1;
	while(num) {
		len++;
		num /=10;
	}
	return len;
}
#if 1
int _vscwprintf(const wchar_t *format, va_list argptr)
{
    // number of characters in the buffer so far, must be less than lenMax
    size_t lenCur = 0;
	for ( size_t n = 0;  ; n++ )
    {
        const wchar_t chCur = format[n];

        if ( chCur == _T('%') )
        {
            static wchar_t s_szFlags[256] = _T("%");
            size_t flagofs = 1;
            bool adj_left = false,
                 in_prec = false,
                 prec_dot = false,
                 done = false;
            int ilen = 0;
            size_t min_width = 0,
                   max_width = 0;
            do
            {

#define CHECK_PREC \
                if (in_prec && !prec_dot) \
                { \
                    s_szFlags[flagofs++] = '.'; \
                    prec_dot = true; \
                }
/*
#define APPEND_CH(ch) \
                { \
                    if ( lenCur == lenMax ) \
                        return -1; \
                    \
                    buf[lenCur++] = ch; \
                }

#define APPEND_STR(s) \
                { \
                    for ( const wchar_t *p = s; *p; p++ ) \
                    { \
                        APPEND_CH(*p); \
                    } \
                }
*/
                // what follows '%'?
                const wchar_t ch = format[++n];
                switch ( ch )
                {
                    case _T('\0'):
						lenCur++;
//                        APPEND_CH(_T('\0'));

                        done = true;
                        break;

                    case _T('%'):
//                        APPEND_CH(_T('%'));
						lenCur++;
                        done = true;
                        break;

                    case _T('#'):
                    case _T('0'):
                    case _T(' '):
                    case _T('+'):
                    case _T('\''):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('-'):
                        CHECK_PREC
                        adj_left = true;
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('.'):
                        CHECK_PREC
                        in_prec = true;
                        prec_dot = false;
                        max_width = 0;
                        // dot will be auto-added to s_szFlags if non-negative
                        // number follows
                        break;

                    case _T('h'):
                        ilen = -1;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('l'):
                        ilen = 1;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('q'):
                    case _T('L'):
                        ilen = 2;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('Z'):
                        ilen = 3;
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        break;

                    case _T('*'):
                        {
                            int len = va_arg(argptr, int);
                            if (in_prec)
                            {
                                if (len<0) break;
                                CHECK_PREC
                                    max_width = len;
                            }
                            else
                            {
                                if (len<0)
                                {
                                    adj_left = !adj_left;
                                    s_szFlags[flagofs++] = '-';
                                    len = -len;
                                }
                                min_width = len;
                            }
                            flagofs += ::swprintf(s_szFlags+flagofs,256-flagofs,_T("%d"),len);
                        }
                        break;

                    case _T('1'): case _T('2'): case _T('3'):
                    case _T('4'): case _T('5'): case _T('6'):
                    case _T('7'): case _T('8'): case _T('9'):
                        {
                            int len = 0;
                            CHECK_PREC
                            while ( (format[n] >= _T('0')) &&
                                    (format[n] <= _T('9')) )
                            {
                                s_szFlags[flagofs++] = format[n];
                                len = len*10 + (format[n] - _T('0'));
                                n++;
                            }

                            if (in_prec)
                                max_width = len;
                            else
                                min_width = len;

                            n--; // the main loop pre-increments n again
                        }
                        break;

                    case _T('d'):
                    case _T('i'):
                    case _T('o'):
                    case _T('u'):
                    case _T('x'):
                    case _T('X'):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        s_szFlags[flagofs] = '\0';
                        if (ilen == 0 )
                        {
                            int val = va_arg(argptr, int);
                            lenCur +=numlen(val);
                        }
                        else if (ilen == -1)
                        {
                            // NB: 'short int' value passed through '...'
                            //      is promoted to 'int', so we have to get
                            //      an int from stack even if we need a short
                            short int val = static_cast<short int>(va_arg(argptr, int));
                            lenCur +=numlen(val);
                        }
                        else if (ilen == 1)
                        {
                            long int val = va_arg(argptr, long int);
                            lenCur +=numlen(val);
                        }
                        else if (ilen == 2)
                        {
                            long long int val = va_arg(argptr, long long int);
                            lenCur +=numlen(val);
#if 0 // !long long
                            long int val = va_arg(argptr, long int);
                            lenCur +=numlen(val);
#endif // long long/!long long
                        }
                        else if (ilen == 3)
                        {
                            size_t val = va_arg(argptr, size_t);
                            lenCur +=numlen(val);
                        }

                        done = true;
                        break;

                    case _T('e'):
                    case _T('E'):
                    case _T('f'):
                    case _T('g'):
                    case _T('G'):
                        CHECK_PREC
                        s_szFlags[flagofs++] = ch;
                        s_szFlags[flagofs] = '\0';
						wchar_t tempbuf[512];
                        if (ilen == 2)
                        {
                            long double val = va_arg(argptr, long double);
                            lenCur +=::swprintf(tempbuf,512-1, s_szFlags, val);
                        }
                        else
                        {
                            double val = va_arg(argptr, double);
                            lenCur +=::swprintf(tempbuf,512-1, s_szFlags, val);
                        }
                        done = true;
                        break;

                    case _T('p'):
                        {
                            void *val = va_arg(argptr, void *);
                            CHECK_PREC
                            s_szFlags[flagofs++] = ch;
                            s_szFlags[flagofs] = '\0';
							wchar_t tempbuf[512];
                            lenCur +=::swprintf(tempbuf,512-1, s_szFlags, val);

                            done = true;
                        }
                        break;

                    case _T('c'):
                        {
                            int val = va_arg(argptr, int);
#if wxUSE_UNICODE
                            if (ilen == -1)
                            {
                                const char buf[2] = { val, 0 };
                                val = wxString(buf, wxConvLibc)[0u];
                            }
#elif wxUSE_WCHAR_T
                            if (ilen == 1)
                            {
                                const wchar_t buf[2] = { val, 0 };
                                val = wxString(buf, wxConvLibc)[0u];
                            }
#endif
                            size_t i;

                            if (!adj_left)
                                for (i = 1; i < min_width; i++)
                                    lenCur++;

                            lenCur++;

                            if (adj_left)
                                for (i = 1; i < min_width; i++)
                                    lenCur++;

                            done = true;
                        }
                        break;

                    case _T('s'):
                        {
                            const wchar_t *val = nullptr;
#if wxUSE_UNICODE
                            wxString s;

                            if (ilen == -1)
                            {
                                // wx extension: we'll let %hs mean non-Unicode
                                // strings
                                char *v = va_arg(argptr, char *);

                                if (v)
                                    val = s = wxString(v, wxConvLibc);
                            }
                            else
#elif wxUSE_WCHAR_T
                            wxString s;

                            if (ilen == 1)
                            {
                                // %ls means Unicode strings
                                wchar_t *v = va_arg(argptr, wchar_t *);

                                if (v)
                                    val = s = wxString(v, wxConvLibc);
                            }
                            else
#endif
                            {
								lenCur +=wcslen(va_arg(argptr, wchar_t*));
                            }

                            done = true;
                        }
                        break;

                    case _T('n'):
						//lenCur += numlen(lenCur);
                        /*if (ilen == 0)
                        {
                            int *val = va_arg(argptr, int *);
                            *val = lenCur;
							
                        }
                        else if (ilen == -1)
                        {
                            short int *val = va_arg(argptr, short int *);
                            *val = lenCur;
							lenCur += numlen(lenCur);
                        }
                        else if (ilen >= 1)
                        {
                            long int *val = va_arg(argptr, long int *);
                            *val = lenCur;
							lenCur += numlen(lenCur);
                        }*/
                        done = true;
                        break;

                    default:
                        // bad format, leave unchanged
						lenCur+=2;
                        done = true;
                        break;
                }
            }
            while (!done);
        }
        else
        {
            lenCur++;
        }

        // terminating zero?
        if ( !chCur )
            break;
    }

	//buf[lenCur] = _T('\0');
	// return the amount of written bytes without the terminating '\0'
    return lenCur-1;
}
#endif
/**end of the own vsnwprintf function */
/*****************************************************************************************/

int _vscprintf(const char *fmt,va_list ap)
{
    return vsnprintf( nullptr, static_cast<size_t>(0), fmt, ap);
}

/*// wchar functions
int _vscwprintf(const wchar_t *fmt,va_list ap)
{
	int ret = _vsnwprintf( nullptr,(size_t)0, fmt, ap);
	if (ret == -1)
		printf("error vscwprintf: %s\n", strerror(errno));
    return ret;
}*/

int _wtoi( const wchar_t *str )
{
	return static_cast<int>(wcstol(str, 0, 10));
}

long _wtol( const wchar_t *str )
{
	return static_cast<int>(wcstol(str, 0, 10));
}

float _wtof( const wchar_t *str )
{
	return wcstof(str,0);
}

wchar_t *_wcsupr(wchar_t *s)
{
    wchar_t *p = s;
    
    if (p) {
		while (*p) {
			*p = towupper(*p);
			p++;
		}
    }

    return s;
}
wchar_t *_wcslwr(wchar_t *s)
{
    wchar_t *p = s;
    
    if (p) {
		while (*p) {
		    *p = towlower(*p);
			p++;
		}
    }
    return s;
}
/*********************************************************/

