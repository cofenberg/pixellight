OpenGL ES 2.0
- Used by the renderer backend "PLRendererOpenGLES2" which is dynamically linking at runtime against the EGL and OpenGL ES 2.0 dynamic libraries
- The include files were downloaded from The Khronos Group (http://www.khronos.org/)
	http://www.khronos.org/registry/egl/api/EGL/egl.h
	http://www.khronos.org/registry/egl/api/EGL/eglext.h		-> Added Android part: "EGL_ANDROID_image_native_buffer", "EGL_ANDROID_swap_rectangle"
	http://www.khronos.org/registry/egl/api/EGL/eglplatform.h	-> Added Android part: "#elif defined(__ANDROID__) || defined(ANDROID)"-section
	http://www.khronos.org/registry/egl/api/KHR/khrplatform.h
	http://www.khronos.org/registry/gles/api/2.0/gl2.h
	http://www.khronos.org/registry/gles/api/2.0/gl2ext.h
	http://www.khronos.org/registry/gles/api/2.0/gl2platform.h
- When using desktop PC GPU drivers capable of OpenGL ES 2.0 you don't need any additional external packages at all
- When using mobile devices you don't need any additional external packages at all
- Internally for testing OpenGL ES 2.0 on a desktop PC one can use "OpenGL ES 2.0 Emulator v1.3 [05 August 2011]"
	- OpenGL ES 2.0 Emulator from ARM (http://www.malideveloper.com/tools/software-development/opengl-es-20-emulator.php)
	- We're sorry but due to legal issues we can't provide you with a downloadable ready-to-use package
	- Here's what you need for the Windows platform and where to put the files:
		- "Bin\Runtime"
			- "libEGL.dll"
			- "libGLESv2.dll"
	- Here's what you need for the Linux platform and where to put the files:
		- "External\_Linux_x86_32\OpenGLES2\lib"
			- "libEGL.so"
			- "libGLESv2.so"
