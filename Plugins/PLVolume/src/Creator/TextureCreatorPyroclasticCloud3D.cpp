/*********************************************************\
 *  File: TextureCreatorPyroclasticCloud3D.cpp           *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/PerlinNoiseTurbulence.h>
#include <PLGraphics/Image/Image.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Texture/TextureManager.h>
#include "PLVolume/Creator/TextureCreatorPyroclasticCloud3D.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(TextureCreatorPyroclasticCloud3D)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TextureCreatorPyroclasticCloud3D::TextureCreatorPyroclasticCloud3D() :
	TextureSize(this),
	Radius(this)
{
}

/**
*  @brief
*    Destructor
*/
TextureCreatorPyroclasticCloud3D::~TextureCreatorPyroclasticCloud3D()
{
}


// [TODO] Cleanup/remove: This is just a first test to have automatically generated volume data for first render tests
/* --- harmonic summing functions - PDB --------------------------*/
/*
   In what follows "alpha" is the weight when the sum is formed.
   Typically it is 2, As this approaches 1 the function is noisier.
   "beta" is the harmonic scaling/spacing, typically 2.
*/

double PerlinNoise1D(double x,double alpha,double beta,int n)
{
	int i;
	double val,sum = 0;
	double p,scale = 1;

	p = x;
	for (i=0;i<n;i++) {
		val = PerlinNoise::Noise1(p);
		sum += val / scale;
		scale *= alpha;
		p *= beta;
	}
	return(sum);
}

double PerlinNoise2D(double x,double y,double alpha,double beta,int n)
{
	int i;
	double val,sum = 0;
	double p[2],scale = 1;

	p[0] = x;
	p[1] = y;
	for (i=0;i<n;i++) {
		val = PerlinNoise::Noise2(p);
		sum += val / scale;
		scale *= alpha;
		p[0] *= beta;
		p[1] *= beta;
	}
	return(sum);
}

double PerlinNoise3D(double x,double y,double z,double alpha,double beta,int n)
{
	int i;
	double val,sum = 0;
	double p[3],scale = 1;

	p[0] = x;
	p[1] = y;
	p[2] = z;
	for (i=0;i<n;i++) {
		val = PerlinNoise::Noise3(p);
		sum += val / scale;
		scale *= alpha;
		p[0] *= beta;
		p[1] *= beta;
		p[2] *= beta;
	}
	return(sum);
}


//[-------------------------------------------------------]
//[ Private virtual TextureCreator functions              ]
//[-------------------------------------------------------]
Texture *TextureCreatorPyroclasticCloud3D::Create(TextureManager &cTextureManager, Texture *pTexture) const
{
	// Create the texture
	pTexture = CreateTexture(cTextureManager, pTexture);

	// Create the image
	Image cImage;
	{
		int n = TextureSize.Get();
		float r = Radius.Get();

		unsigned char *data = new unsigned char[n*n*n];
		unsigned char *ptr = data;

		float frequency = 3.0f / n;
		float center = n / 2.0f + 0.5f;

		for(int x=0; x < n; ++x) {
			for (int y=0; y < n; ++y) {
				for (int z=0; z < n; ++z) {
					float dx = center-x;
					float dy = center-y;
					float dz = center-z;

					float off = fabsf((float) PerlinNoise3D(
						x*frequency,
						y*frequency,
						z*frequency,
						5,
						6, 3));

					float d = sqrtf(dx*dx+dy*dy+dz*dz)/(n);
					bool isFilled = (d-off) < r;
					*ptr++ = isFilled ? 255 : 0;
				}
			}
		}

		// Create image
		cImage = Image::CreateImageAndTakeoverData(DataByte, ColorGrayscale, Vector3i(n, n, n), CompressionNone, data);
	}

	// Create the 3D texture buffer
	pTexture->SetTextureBuffer(reinterpret_cast<TextureBuffer*>(cTextureManager.GetRendererContext().GetRenderer().CreateTextureBuffer3D(cImage)));

	// Return the created texture
	return pTexture;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
