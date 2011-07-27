/*********************************************************\
 *  File: PLPluginLinux.h                                *
 *      Linux definitions for PLPlugin
\*********************************************************/


#ifndef __PLPLUGIN_LINUX_H__
#define __PLPLUGIN_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Import/Export                                         ]
//[-------------------------------------------------------]
#ifdef PLPLUGIN_EXPORTS
	#ifdef HAVE_VISIBILITY_ATTR
		// To export classes, methods and variables
		#define PLPLUGIN_API __attribute__ ((visibility("default")))

		// To export explicit template instanciations
		#define PLPLUGIN_TEMPLATE
	#else
		// To export classes, methods and variables
		#define PLPLUGIN_API

		// To export explicit template instanciations
		#define PLPLUGIN_TEMPLATE
	#endif

	// To export RTTI elements
	#define PLPLUGIN_RTTI_EXPORT 1
#else
	// To import classes, methods and variables
	#define PLPLUGIN_API

	// To import explicit template instanciations (C++0x, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates)
	#define PLPLUGIN_TEMPLATE extern

	// To import RTTI elements
	#define PLPLUGIN_RTTI_EXPORT 0
#endif

#ifdef HAVE_VISIBILITY_ATTR
		// To import/export class templates
		#define PLPLUGIN_TMPL __attribute__ ((visibility("default")))
#else
		// To import/export class templates
		#define PLPLUGIN_TMPL
#endif


#endif // __PLPLUGIN_LINUX_H__
