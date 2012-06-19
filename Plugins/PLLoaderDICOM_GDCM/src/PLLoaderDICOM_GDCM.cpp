/*********************************************************\
 *  File: PLLoaderDICOM_GDCM.cpp                         *
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
#include <PLCore/ModuleMain.h>


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module_plugin("PLLoaderDICOM_GDCM")
	pl_module_vendor("Christian Ofenberg")
	pl_module_license("Copyright (C) 2011-2012 Christian Ofenberg")
	pl_module_description("Loader implementation for the \"dcm\" image data file format by using GDCM (Grassroots DICOM) (http://sourceforge.net/projects/gdcm/) - Master thesis \"Scalable Realtime Volume Rendering\"")
pl_module_end
