OpenGL ES 2.0
- Used by the renderer backend "PLRendererOpenGLES2"
- The include files were downloaded from The Khronos Group (http://www.khronos.org/)
	http://www.khronos.org/registry/egl/api/EGL/egl.h
	http://www.khronos.org/registry/egl/api/EGL/eglext.h
	http://www.khronos.org/registry/egl/api/EGL/eglplatform.h
	http://www.khronos.org/registry/egl/api/KHR/khrplatform.h
	http://www.khronos.org/registry/gles/api/2.0/gl2.h
	http://www.khronos.org/registry/gles/api/2.0/gl2ext.h
	http://www.khronos.org/registry/gles/api/2.0/gl2platform.h
- We're sorry but due to legal issues we can't provide you with a downloadable ready-to-compile package, but at least for the "desktop"-mode you don't need one
- Internally for testing OpenGL ES 2.0 on a desktop PC we're using "OpenGL ES 2.0 Emulator v1.3 [05 August 2011]"
	- OpenGL ES 2.0 Emulator from ARM (http://www.malideveloper.com/tools/software-development/opengl-es-20-emulator.php)
	- Here's what you need for the Windows platform and where to put the files:
		- "Bin\Runtime"
			- "libEGL.dll"
			- "libGLESv2.dll"
		- "External\_Windows_x86_32\OpenGLES2\include\EGL"
			- "egl.h"
			- "eglext.h"
			- "eglplatform.h"
			- "egl_native_types.h"
		- "External\_Windows_x86_32\OpenGLES2\include\KHR"
			- "khrplatform.h"
		- "External\_Windows_x86_32\OpenGLES2\include\GLES2"
			- "gl2.h"
			- "gl2ext.h"
			- "gl2platform.h"
		- "External\_Windows_x86_32\OpenGLES2\lib"
			- "libEGL.lib"
			- "libGLESv2.lib"
	- Here's what you need for the Linux platform and where to put the files:
		- "External\_Linux_x86_32\OpenGLES2\include\EGL"
			- "egl.h"
			- "eglext.h"
			- "eglplatform.h"
			- "egl_native_types.h"
		- "External\_Linux_x86_32\OpenGLES2\include\GLES2"
			- "gl2.h"
			- "gl2ext.h"
			- "gl2platform.h"
		- "External\_Linux_x86_32\OpenGLES2\include\KHR"
			- "khrplatform.h"
		- "External\_Linux_x86_32\OpenGLES2\lib"
			- "libEGL.so"
			- "libGLESv2.so"
