/*********************************************************\
 *  File: PerlinNoise.cpp                                *
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
#include "PLMath/Math.h"
#include "PLMath/PerlinNoise.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#define B  0x1000
#define BM 0xff
#define N  0x1000
#define NP 12		// 2^N
#define NM 0xfff


//[-------------------------------------------------------]
//[ Macros                                                ]
//[-------------------------------------------------------]
#define s_curve(t) (t*t*(3 - 2*t))
#define lerp(t, a, b) (a + t*(b - a))
#define setup(i, b0, b1, r0, r1)\
	t  = i + N;\
	b0 = static_cast<int>(t) & BM;\
	b1 = (b0 + 1) & BM;\
	r0 = t - static_cast<int>(t);\
	r1 = r0 - 1;
#define at2(rx,ry) (rx*q[0] + ry*q[1])
#define at3(rx, ry, rz) (rx*q[0] + ry*q[1] + rz*q[2])


//[-------------------------------------------------------]
//[ Variables                                             ]
//[-------------------------------------------------------]
static int    p[B + B + 2];
static float g3[B + B + 2][3];
static float g2[B + B + 2][2];
static float g1[B + B + 2];


//[-------------------------------------------------------]
//[ Internal helper functions                             ]
//[-------------------------------------------------------]
float bias(float a, float b)
{
	return Math::Pow(a, Math::Log(b)/Math::Log(0.5f));
}

float gain(float a, float b)
{
	if (a < 0.001f)
		return 0;
	else if (a > 0.999f)
		return 1.0f;

	float p = Math::Log(1.0f - b)/Math::Log(0.5f);

	if (a < 0.5f)
		return static_cast<float>(Math::Pow(2*a, p)/2);
	else
		return 1 - static_cast<float>(Math::Pow(2*(1.0f - a), p) / 2);
}

void normalize2(float v[2])
{
	float s = 1.0f / Math::Sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] *= s;
	v[1] *= s;
}

void normalize3(float v[3])
{
	float s = 1.0f / Math::Sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= s;
	v[1] *= s;
	v[2] *= s;
}


//[-------------------------------------------------------]
//[ Functions                                             ]
//[-------------------------------------------------------]
void PLInitPerlin()
{
	int i, j, k;

	for (i=0; i<B; i++) {
		p[i] = i;

		g1[i] = static_cast<float>((Math::GetRand() % (B + B)) - B)/B;

		for (j=0; j<2; j++)
			g2[i][j] = static_cast<float>((Math::GetRand() % (B + B)) - B)/B;
		normalize2(g2[i]);

		for (j=0; j<3; j++)
			g3[i][j] = static_cast<float>((Math::GetRand() % (B + B)) - B)/B;
		normalize3(g3[i]);
	}

	while (--i) {
		k    = p[i];
		p[i] = p[j = Math::GetRand() % B];
		p[j] = k;
	}

	for (i=0; i<B+2; i++) {
		 p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j=0; j<2; j++)
			g2[B + i][j] = g2[i][j];
		for (j=0; j<3; j++)
			g3[B + i][j] = g3[i][j];
	}
}

float PLNoise1(float fX)
{
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v;

	setup(fX, bx0, bx1, rx0, rx1);

	sx = s_curve(rx0);

	u = rx0*g1[p[bx0]];
	v = rx1*g1[p[bx1]];

	return lerp(sx, u, v);
}

float PLNoise2(float fX, float fY)
{
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	int i, j;

	setup(fX, bx0, bx1, rx0, rx1);
	setup(fY, by0, by1, ry0, ry1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	sx = s_curve(rx0);
	sy = s_curve(ry0);


	q = g2[b00]; u = at2(rx0, ry0);
	q = g2[b10]; v = at2(rx1, ry0);
	a = lerp(sx, u, v);

	q = g2[b01]; u = at2(rx0, ry1);
	q = g2[b11]; v = at2(rx1, ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

float PLNoise3(float fX, float fY, float fZ)
{
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	int i, j;

	setup(fX, bx0, bx1, rx0, rx1);
	setup(fY, by0, by1, ry0, ry1);
	setup(fZ, bz0, bz1, rz0, rz1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[b00 + bz0];
	u = at3(rx0, ry0, rz0);
	q = g3[b10 + bz0];
	v = at3(rx1, ry0, rz0);
	a = lerp(t, u, v);

	q = g3[b01 + bz0];
	u = at3(rx0, ry1, rz0);
	q = g3[b11 + bz0];
	v = at3(rx1, ry1, rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[b00 + bz1];
	u = at3(rx0, ry0, rz1);
	q = g3[b10 + bz1];
	v = at3(rx1, ry0, rz1);
	a = lerp(t, u, v);

	q = g3[b01 + bz1];
	u = at3(rx0, ry1, rz1);
	q = g3[b11 + bz1];
	v = at3(rx1, ry1, rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

float PLTurbulence2(float fX, float fY, float fFreq)
{
	float t = 0.0f;

	do {
		t += PLNoise2(fFreq*fX, fFreq*fY)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PLTurbulence3(float fX, float fY, float fZ, float fFreq)
{
	float t = 0.0f;

	do {
		t += PLNoise3(fFreq*fX, fFreq*fY, fFreq*fZ)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PLTileableNoise1(float fX, float fW)
{
	return (PLNoise1(fX)   *(fW-fX) +
			PLNoise1(fX-fW)*    fX)/fW;
}

float PLTileableNoise2(float fX, float fY, float fW, float fH)
{
	return (PLNoise2(fX,    fY)   *(fW-fX)*(fH-fY) +
			PLNoise2(fX-fW, fY)   *    fX *(fH-fY) +
			PLNoise2(fX,    fY-fH)*(fW-fX)*    fY  +
			PLNoise2(fX-fW, fY-fH)*    fX *    fY)/(fW*fH);
}

float PLTileableNoise3(float fX, float fY, float fZ, float fW, float fH, float fD)
{
	return (PLNoise3(fX,    fY,    fZ)   *(fW-fX)*(fH-fY)*(fD-fZ) +
			PLNoise3(fX-fW, fY,    fZ)   *    fX *(fH-fY)*(fD-fZ) +
			PLNoise3(fX,    fY-fH, fZ)   *(fW-fX)*    fY *(fD-fZ) +
			PLNoise3(fX-fW, fY-fH, fZ)   *    fX *    fY *(fD-fZ) + 
			PLNoise3(fX,    fY,    fZ-fD)*(fW-fX)*(fH-fY)*    fZ  +
			PLNoise3(fX-fW, fY,    fZ-fD)*    fX *(fH-fY)*    fZ  +
			PLNoise3(fX,    fY-fH, fZ-fD)*(fW-fX)*    fY *    fZ  +
			PLNoise3(fX-fW, fY-fH, fZ-fD)*    fX *    fY *    fZ)/(fW*fH*fD);
}

float PLTileableTurbulence2(float fX, float fY, float fW, float fH, float fFreq)
{
	float t = 0.0f;

	do {
		t += PLTileableNoise2(fFreq*fX, fFreq*fY, fW*fFreq, fH*fFreq)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}

float PLTileableTurbulence3(float fX, float fY, float fZ, float fW, float fH, float fD, float fFreq)
{
	float t = 0.0f;

	do {
		t += PLTileableNoise3(fFreq*fX, fFreq*fY, fFreq*fZ, fW*fFreq, fH*fFreq, fD*fFreq)/fFreq;
		fFreq *= 0.5f;
	} while (fFreq >= 1.0f);
	
	return t;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
