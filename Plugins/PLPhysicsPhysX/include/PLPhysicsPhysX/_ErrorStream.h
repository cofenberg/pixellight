#ifndef ERRORSTREAM_H
#define ERRORSTREAM_H
#pragma once


#include <PLCore/File/File.h>
#ifdef WIN32
	#include <PLCore/PLCoreWindowsIncludes.h>
#endif

class ErrorStream : public NxUserOutputStream
	{
	public:
	void reportError(NxErrorCode e, const char* message, const char* file, int line)
		{
			PLCore::File::StandardOutput.Print(PLCore::String::Format("%s (%d) :", file, line));
		switch (e)
			{
			case NXE_INVALID_PARAMETER:
				PLCore::File::StandardOutput.Print( "invalid parameter");
				break;
			case NXE_INVALID_OPERATION:
				PLCore::File::StandardOutput.Print( "invalid operation");
				break;
			case NXE_OUT_OF_MEMORY:
				PLCore::File::StandardOutput.Print( "out of memory");
				break;
			case NXE_DB_INFO:
				PLCore::File::StandardOutput.Print( "info");
				break;
			case NXE_DB_WARNING:
				PLCore::File::StandardOutput.Print( "warning");
				break;
			default:
				PLCore::File::StandardOutput.Print("unknown error");
				break;
			}

		PLCore::File::StandardOutput.Print(PLCore::String::Format(" : %s\n", message));
		}

	NxAssertResponse reportAssertViolation(const char* message, const char* file, int line)
		{
		PLCore::File::StandardOutput.Print(PLCore::String::Format("access violation : %s (%s line %d)\n", message, file, line));
#ifdef WIN32
		switch (MessageBoxA(0, message, "AssertViolation, see console for details.", MB_ABORTRETRYIGNORE))
			{
			case IDRETRY:
				return NX_AR_CONTINUE;
			case IDIGNORE:
				return NX_AR_IGNORE;
			case IDABORT:
			default:
				return NX_AR_BREAKPOINT;
			}
#elif LINUX
		assert(0);
#endif
		}

	void print(const char* message)
		{
		PLCore::File::StandardOutput.Print(message);
		}
	};



#endif