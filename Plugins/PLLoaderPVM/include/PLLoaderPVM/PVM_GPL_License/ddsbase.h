/*

This file is taken from V^3, the Versatile Volume Viewer.
Copyright (c) 2003-2007 by Stefan Roettger.

The volume viewer is licensed under the terms of the GPL (see
http://www.gnu.org/copyleft/ for more information on the license).
Any commercial use of the code or parts of it requires the explicit
permission of the author! The source code is distributed with
ABSOLUTELY NO WARRANTY; not even for MERCHANTABILITY etc.!

The author's contact address is:

   mailto:stefan@stereofx.org
   http://stereofx.org

*/

// (c) by Stefan Roettger

#ifndef DDSBASE_H
#define DDSBASE_H

void writeDDSfile(const char *filename,unsigned char *data,unsigned int bytes,unsigned int skip=0,unsigned int strip=0,int nofree=0);
unsigned char *readDDSfile(const char *filename, unsigned int *bytes);

void writeRAWfile(const char *filename,unsigned char *data,unsigned int bytes,int nofree=0);
unsigned char *readRAWfile(const char *filename, unsigned int *bytes);

void writePNMimage(const char *filename,unsigned char *image,unsigned int width,unsigned int height,unsigned int components,int dds=0);
unsigned char *readPNMimage(const char *filename, unsigned int *width,unsigned int *height,unsigned int *components);

void writePVMvolume(const char *filename,unsigned char *volume,
                    unsigned int width,unsigned int height,unsigned int depth,unsigned int components=1,
                    float scalex=1.0f,float scaley=1.0f,float scalez=1.0f,
                    unsigned char *description=0,
                    unsigned char *courtesy=0,
                    unsigned char *parameter=0,
                    unsigned char *comment=0);

unsigned char *readPVMvolume(const char *filename,
                             unsigned int *width,unsigned int *height,unsigned int *depth,unsigned int *components=0,
                             float *scalex=0,float *scaley=0,float *scalez=0,
                             unsigned char **description=0,
                             unsigned char **courtesy=0,
                             unsigned char **parameter=0,
                             unsigned char **comment=0);
/*
unsigned int checksum(unsigned char *data,unsigned int bytes);

void swapbytes(unsigned char *data,unsigned int bytes);
void convbytes(unsigned char *data,unsigned int bytes);
void convfloat(unsigned char *data,unsigned int bytes);
*/


unsigned char *quantize(unsigned char *volume,
                        unsigned int width,unsigned int height,unsigned int depth,
                        bool nofree=false,
                        bool linear=false,
                        bool verbose=false);

#endif
