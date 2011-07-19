/*********************************************************\
 *  File: Color3.cpp                                     *
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
#include <PLCore/String/RegEx.h>
#include "PLGraphics/Color/Color4.h"
#include "PLGraphics/Color/Color3.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Color3 Color3::Null		(-1.0f, -1.0f, -1.0f);
const Color3 Color3::Black		(static_cast<uint8>(  0),   0,   0);
const Color3 Color3::White		(static_cast<uint8>(255), 255, 255);
const Color3 Color3::Red		(static_cast<uint8>(255),   0,   0);
const Color3 Color3::Yellow		(static_cast<uint8>(255), 255,   0);
const Color3 Color3::Green		(static_cast<uint8>(  0), 128,   0);
const Color3 Color3::Aqua		(static_cast<uint8>(  0), 255, 255);
const Color3 Color3::Blue		(static_cast<uint8>(  0),   0, 255);
const Color3 Color3::Fuchsia	(static_cast<uint8>(255),   0, 255);
const Color3 Color3::Maroon		(static_cast<uint8>(128),   0,   0);
const Color3 Color3::Olive		(static_cast<uint8>(128), 128,   0);
const Color3 Color3::Navy		(static_cast<uint8>(  0),   0, 128);
const Color3 Color3::Purple		(static_cast<uint8>(128),   0, 128);
const Color3 Color3::Teal		(static_cast<uint8>(  0), 128, 128);
const Color3 Color3::Gray		(static_cast<uint8>(128), 128, 128);
const Color3 Color3::Silver		(static_cast<uint8>(192), 192, 192);
const Color3 Color3::Lime		(static_cast<uint8>(  0), 255,   0);


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Maps a RGB floating point channels (0.0f to 1.0f range) to PLCore::uint32
*/
uint32 Color3::ToUInt32(float fR, float fG, float fB)
{
	return static_cast<uint32>(static_cast<uint8>(fR*255.0f) | static_cast<uint16>(static_cast<uint8>(fG*255.0f))<<8 | static_cast<uint32>(static_cast<uint8>(fB*255.0f))<<16);
}

/**
*  @brief
*    Returns the red color component (float, 0.0-1.0) from a PLCore::uint32 RGB color
*/
float Color3::RedFromUInt32(uint32 nColor)
{
	return (static_cast<uint8>(nColor))/255.0f;
}

/**
*  @brief
*    Returns the green color component (float, 0.0-1.0) from a PLCore::uint32 RGB color
*/
float Color3::GreenFromUInt32(uint32 nColor)
{
	return (static_cast<uint8>((static_cast<uint16>(nColor)) >> 8))/255.0f;
}

/**
*  @brief
*    Returns the blue color component (float, 0.0-1.0) from a PLCore::uint32 RGB color
*/
float Color3::BlueFromUInt32(uint32 nColor)
{
	return (static_cast<uint8>((nColor)>>16))/255.0f;
}

/**
*  @brief
*    Swaps the RB components in the given buffer with 3 components (BGR <-> RGB)
*/
void Color3::SwapRB(uint8 nBuffer[], uint32 nNumOfPixels)
{
#if defined(WIN32) && !defined(WIN64) && !defined(NO_INLINE_ASM)
	// 32 Bit assembler method (Intel)
	void *p = nBuffer;			// Pointer to the buffer
	__asm						// Assembler code to follow
	{
		mov ecx, nNumOfPixels	// Counter set to dimensions of our memory block
		mov ebx, p				// Points ebx to our data (p)
		label:					// Label used for looping
			mov al, [ebx+0]		// Loads value at ebx into al
			mov ah, [ebx+2]		// Loads value at ebx+2 into ah
			mov [ebx+2], al		// Stores value in al at ebx+2
			mov [ebx+0], ah		// Stores value in ah at ebx
				
			add ebx, 3			// Moves through the data by 3 bytes
			dec ecx				// Decreases our loop counter
			jnz label			// If not zero jump back to label
	}
// [TODO] Check this: The Linux assembler version of this function is broken?
/*
#elif defined(LINUX) && !defined(NO_INLINE_ASM)
	// 32 Bit assembler method (AT&T)
	__asm__ __volatile__ (	"mov  %0,%%ecx\n" : :"r"(nNumOfPixels):"%ecx");	// Counter set to dimensions of our memory block
	__asm__ __volatile__ ("mov  %0,%%ebx\n" : :"r"(p));						// Points ebx to our data (p)
	__asm__ __volatile__ ("label1:\n\t"		// Label used for looping
			"mov 0(%ebx), %al\n\t"			// Loads value at ebx into al
			"mov 2(%ebx), %ah\n\t"			// Loads value at ebx+2 into ah
			"mov %al, 2(%ebx)\n\t"			// Stores value in al at ebx+2
			"mov %ah, 0(%ebx)\n\t"			// Stores value in ah at ebx

			"add $3, %ebx\n\t"				// Moves through the data by 3 bytes
			"dec %ecx\n\t"					// Decreases our loop counter
			"jnz label1\n\t"				// If not zero jump back to label
	);
*/
#else
	// C++ method
	for (uint32 i=0; i<nNumOfPixels; i+=3) {
		const uint8 nTemp = nBuffer[i];
		nBuffer[i] = nBuffer[i+2];
		nBuffer[i+2] = nTemp;
	}
#endif
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor (all components are set to 0.0)
*/
Color3::Color3() :
	r(0.0f),
	g(0.0f),
	b(0.0f)
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(float fR, float fG, float fB) :
	r(fR),
	g(fG),
	b(fB)
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(uint8 nR, uint8 nG, uint8 nB) :
	r(static_cast<float>(nR)/255.0f),
	g(static_cast<float>(nG)/255.0f),
	b(static_cast<float>(nB)/255.0f)
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(const float fColor[]) :
	r(fColor[0]),
	g(fColor[1]),
	b(fColor[2])
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(const uint8 nColor[]) :
	r(nColor[0]/255.0f),
	g(nColor[1]/255.0f),
	b(nColor[2]/255.0f)
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(float fColor) :
	r(fColor),
	g(fColor),
	b(fColor)
{
}

/**
*  @brief
*    Constructor
*/
Color3::Color3(uint8 nColor) :
	r(static_cast<float>(nColor)/255.0f),
	g(static_cast<float>(nColor)/255.0f),
	b(static_cast<float>(nColor)/255.0f)
{
}

/**
*  @brief
*    Copy constructor
*/
Color3::Color3(const Color3 &cSource) :
	r(cSource.r),
	g(cSource.g),
	b(cSource.b)
{
}

/**
*  @brief
*    Destructor
*/
Color3::~Color3()
{
}

/**
*  @brief
*    Maps this RGB floating point channels (0.0f to 1.0f range) to PLCore::uint32
*/
uint32 Color3::ToUInt32() const
{
	return static_cast<uint32>(static_cast<uint8>(r*255.0f) | static_cast<uint16>(static_cast<uint8>(g*255.0f))<<8 | static_cast<uint32>(static_cast<uint8>(b*255.0f))<<16);
}

/**
*  @brief
*    Maps from a PLCore::uint32 to RGB floating point channels (0.0f to 1.0f range)
*/
void Color3::FromUInt32(uint32 nColor)
{
	r = (static_cast<uint8>(nColor))/255.0f;
	g = (static_cast<uint8>((static_cast<uint16>(nColor)) >> 8))/255.0f;
	b = (static_cast<uint8>((nColor)>>16))/255.0f;
}

/**
*  @brief
*    Get the color component as float values
*/
void Color3::GetRGB(float &fR, float &fG, float &fB) const
{
	fR = r;
	fG = g;
	fB = b;
}

/**
*  @brief
*    Get the color component as integer values
*/
void Color3::GetRGB(uint8 &nR, uint8 &nG, uint8 &nB) const
{
	nR = static_cast<uint8>(r*255);
	nG = static_cast<uint8>(g*255);
	nB = static_cast<uint8>(b*255);
}

/**
*  @brief
*    Set the color components by using float values
*/
void Color3::SetRGB(float fR, float fG, float fB)
{
	r = fR;
	g = fG;
	b = fB;
}

/**
*  @brief
*    Set the color components by using integer values
*/
void Color3::SetRGB(uint8 nR, uint8 nG, uint8 nB)
{
	r = static_cast<float>(nR)/255.0f;
	g = static_cast<float>(nG)/255.0f;
	b = static_cast<float>(nB)/255.0f;
}

/**
*  @brief
*    Get the color component as array of float values
*/
void Color3::GetRGB(float fColor[]) const
{
	fColor[0] = r;
	fColor[1] = g;
	fColor[2] = b;
}

/**
*  @brief
*    Get the color component as array of integer values
*/
void Color3::GetRGB(uint8 nColor[]) const
{
	nColor[0] = static_cast<uint8>(r*255);
	nColor[1] = static_cast<uint8>(g*255);
	nColor[2] = static_cast<uint8>(b*255);
}

/**
*  @brief
*    Set the color components by using a reference to float values
*/
void Color3::SetRGB(const float fColor[])
{
	r = fColor[0];
	g = fColor[1];
	b = fColor[2];
}

/**
*  @brief
*    Set the color components by using a reference to integer values
*/
void Color3::SetRGB(const uint8 nColor[])
{
	r = static_cast<float>(nColor[0])/255.0f;
	g = static_cast<float>(nColor[1])/255.0f;
	b = static_cast<float>(nColor[2])/255.0f;
}

/**
*  @brief
*    Set all color component to the same float value
*/
void Color3::SetRGB(float fValue)
{
	r = fValue;
	g = fValue;
	b = fValue;
}

/**
*  @brief
*    Set all color component to the same integer value
*/
void Color3::SetRGB(uint8 nColor)
{
	r = static_cast<float>(nColor)/255.0f;
	g = static_cast<float>(nColor)/255.0f;
	b = static_cast<float>(nColor)/255.0f;
}

/**
*  @brief
*    Get the red color value as float
*/
float Color3::GetR() const
{
	return r;
}

/**
*  @brief
*    Get the red color value as integer
*/
uint8 Color3::GetRInt() const
{
	return static_cast<uint8>(r*255);
}

/**
*  @brief
*    Set the red color component using a float value
*/
void Color3::SetR(float fR)
{
	r = fR;
}

/**
*  @brief
*    Set the red color component using an integer value
*/
void Color3::SetR(uint8 nR)
{
	r = static_cast<float>(nR)/255.0f;
}

/**
*  @brief
*    Get the green color value as float
*/
float Color3::GetG() const
{
	return g;
}

/**
*  @brief
*    Get the green color value as integer
*/
uint8 Color3::GetGInt() const
{
	return static_cast<uint8>(g*255);
}

/**
*  @brief
*    Set the green color component using a float value
*/
void Color3::SetG(float fG)
{
	g = fG;
}

/**
*  @brief
*    Set the green color component using an integer value
*/
void Color3::SetG(uint8 nG)
{
	g = static_cast<float>(nG)/255.0f;
}

/**
*  @brief
*    Get the blue color value as float
*/
float Color3::GetB() const
{
	return b;
}

/**
*  @brief
*    Get the blue color value as integer
*/
uint8 Color3::GetBInt() const
{
	return static_cast<uint8>(b*255);
}

/**
*  @brief
*    Set the blue color component using a float value
*/
void Color3::SetB(float fB)
{
	b = fB;
}

/**
*  @brief
*    Set the blue color component using an integer value
*/
void Color3::SetB(uint8 nB)
{
	b = static_cast<float>(nB)/255.0f;
}

/**
*  @brief
*    Returns if the color is valid
*/
bool Color3::IsValid() const
{
	return (r >= 0.0f && r <= 1.0f && g >= 0.0f && g <= 1.0f && b >= 0.0f && b <= 1.0f);
}

/**
*  @brief
*    Clamps the color values between 0.0 and 1.0
*/
void Color3::Saturate()
{
	if (r < 0.0f)
		r = 0.0f;
	if (r > 1.0f)
		r = 1.0f;
	if (g < 0.0f)
		g = 0.0f;
	if (g > 1.0f)
		g = 1.0f;
	if (b < 0.0f)
		b = 0.0f;
	if (b > 1.0f)
		b = 1.0f;
}

/**
*  @brief
*    Get luminance of color as float
*/
float Color3::GetLuminance() const
{
	// "Human formula"... our eyes recognize color components not uniformly
	return r*0.299f + g*0.587f + b*0.114f;
}

/**
*  @brief
*    Get luminance of color as integer
*/
uint8 Color3::GetLuminanceInt() const
{
	// "Human formula"... our eyes recognize color components not uniformly
	return static_cast<uint8>(r*0.299f + g*0.587f + b*0.114f);
}

/**
*  @brief
*    Get luminance as color (results in a grayscale color)
*/
Color3 Color3::GetLuminanceColor() const
{
	// "Human formula"... our eyes recognize color components not uniformly
	float fLuminance = r*0.299f + g*0.587f + b*0.114f;

	// Return grayscale color
	return Color3(fLuminance, fLuminance, fLuminance);
}


//[-------------------------------------------------------]
//[ Assignment operators                                  ]
//[-------------------------------------------------------]
Color3 &Color3::operator =(const Color3 &cC)
{
	r = cC.r;
	g = cC.g;
	b = cC.b;

	return *this;
}

Color3 &Color3::operator =(const Color4 &cC)
{
	r = cC.r;
	g = cC.g;
	b = cC.b;

	return *this;
}

Color3 &Color3::operator =(const float fC[])
{
	r = fC[0];
	g = fC[1];
	b = fC[2];

	return *this;
}

Color3 &Color3::operator =(float fD)
{
	r = g = b = fD;

	return *this;
}

Color3::operator float *()
{
	return &r;
}

Color3::operator const float *() const
{
	return &r;
}


//[-------------------------------------------------------]
//[ Comparison                                            ]
//[-------------------------------------------------------]
bool Color3::operator ==(const Color3 &cC) const
{
	return (r == cC.r && g == cC.g && b == cC.b);
}

bool Color3::operator !=(const Color3 &cC) const
{
	return (r != cC.r || g != cC.g || b != cC.b);
}

bool Color3::operator ==(const Color4 &cC) const
{
	return (r == cC.r && g == cC.g && b == cC.b);
}

bool Color3::operator !=(const Color4 &cC) const
{
	return (r != cC.r || g != cC.g || b != cC.b);
}

bool Color3::operator ==(float f) const
{
	return (r == f && g == f && b == f);
}

bool Color3::operator !=(float f) const
{
	return (r != f || g != f || b != f);
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
Color3 Color3::operator +(const Color3 &cC) const
{
	return Color3(r+cC.r, g+cC.g, b+cC.b);
}

Color3 Color3::operator +(float fN) const
{
	return Color3(r+fN, g+fN, b+fN);
}

Color3 &Color3::operator +=(const Color3 &cC)
{
	r += cC.r;
	g += cC.g;
	b += cC.b;

	return *this;
}

Color3 &Color3::operator +=(float fN)
{
	r += fN;
	g += fN;
	b += fN;

	return *this;
}

Color3 Color3::operator -() const
{
	return Color3(-r, -g, -b);
}

Color3 Color3::operator -(const Color3 &cC) const
{
	return Color3(r-cC.r, g-cC.g, b-cC.b);
}

Color3 Color3::operator -(float fN) const
{
	return Color3(r-fN, g-fN, b-fN);
}

Color3 &Color3::operator -=(const Color3 &cC)
{
	r -= cC.r;
	g -= cC.g;
	b -= cC.b;

	return *this;
}

Color3 &Color3::operator -=(float fN)
{
	r -= fN;
	g -= fN;
	b -= fN;

	return *this;
}

Color3 Color3::operator *(const Color3 &cC) const 
{
	return Color3(r*cC.r, g*cC.g, b*cC.b);
}

Color3 Color3::operator *(float fS) const
{
	return Color3(r*fS, g*fS, b*fS);
}

Color3 &Color3::operator *=(const Color3 &cC)
{
	r *= cC.r;
	g *= cC.g;
	b *= cC.b;

	return *this;
}

Color3 &Color3::operator *=(float fS)
{
	r *= fS;
	g *= fS;
	b *= fS;

	return *this;
}

Color3 Color3::operator /(const Color3 &cC) const
{
	return Color3(r/cC.r, g/cC.g, b/cC.b);
}

Color3 Color3::operator /(float fS) const
{
	return Color3(r/fS, g/fS, b/fS);
}

Color3 &Color3::operator /=(const Color3 &cC)
{
	r /= cC.r;
	g /= cC.g;
	b /= cC.b;

	return *this;
}

Color3 &Color3::operator /=(float fS)
{
	r /= fS;
	g /= fS;
	b /= fS;

	return *this;
}

float &Color3::operator [](int nIndex)
{
	return fColor[nIndex];
}

/**
*  @brief
*    To string
*/
String Color3::ToString() const
{
	return String::Format("%g %g %g", r, g, b);
}

/**
*  @brief
*    From string
*/
bool Color3::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 3 && cRegEx.Match(sString, nParsePos)) {
			fColor[nComponent++] = cRegEx.GetResult(0).GetFloat();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused componts to 0
		while (nComponent < 3)
			fColor[nComponent++] = 0.0f;

		// Done
		return true;
	} else {
		// Error!
		r = g = b = 0.0f;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
