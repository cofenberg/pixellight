/*********************************************************\
 *  File: FileSystemTest.cpp                             *
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
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif
#ifdef LINUX
	#include <errno.h>
	#include <string.h>
	#include <malloc.h>
	#include <dirent.h>
	#include <unistd.h>
	#include <sys/stat.h>
#endif
#include <PLGeneral/System/System.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include "PLTestBase/General/FileSystemTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
unsigned char g_nBuffer[1024*1024];


//[-------------------------------------------------------]
//[ FileSystemTest implementation                         ]
//[-------------------------------------------------------]
void FileSystemTest::SpeedTest()
{
	// Try to create a temp directory
	bool bDirectoryCreated;
	Directory cDir("filetest");
	bDirectoryCreated = cDir.Create();

	// Run tests
	SpeedTest_CleanUp(); SpeedTest_OS_SmallFiles();
	SpeedTest_CleanUp(); SpeedTest_FS_SmallFiles();
	SpeedTest_CleanUp(); SpeedTest_OS_BigFile();
	SpeedTest_CleanUp(); SpeedTest_FS_BigFile();

	// Remove directory (if we had created by itself...)
	SpeedTest_CleanUp();
	if (bDirectoryCreated) cDir.Delete();
}

void FileSystemTest::SpeedTest_CleanUp()
{
#ifdef WIN32
	// Remove testfiles
	WIN32_FIND_DATA sFind;
	HANDLE hFind;
	hFind = FindFirstFile(TEXT("filetest\\*.*"), &sFind);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			DeleteFile(String::Format("filetest\\%s", sFind.cFileName));
		} while (FindNextFile(hFind, &sFind));
		FindClose(hFind);
	}
#elif defined(LINUX)
	DIR *pDir = opendir("filetest");
	if (pDir) {
		struct dirent *pEntry = readdir(pDir);
		struct stat d_stat;
		String sFile;

		// Get the current working directory (allocates the buffer dynamically)
		char *pszPath = getcwd(nullptr, 0);

		while (pEntry) {
			sFile = String::Format("%s/filetest/%s", pszPath, pEntry->d_name);
			int nError = stat(sFile.GetASCII(), &d_stat);
			if (nError) Print("Error: %d, %s\n", nError, strerror(errno));
			else {
				if (!S_ISDIR(d_stat.st_mode))
					remove(sFile.GetASCII());
			}
			pEntry = readdir(pDir);
		}

		// Cleanup
		if (pszPath) free(pszPath);
	}
	closedir(pDir);
#endif
}

void FileSystemTest::SpeedTest_OS_SmallFiles()
{
	uint32 nStart, nStop;
	StartTask("Small files [OS]");
	Print("\n");
	// Write files
	nStart = System::GetInstance()->GetMilliseconds();
	for (int i=1; i<=1000; i++) {
		String sFile;
#ifdef WIN32
		sFile = String::Format("filetest\\test%04d.txt", i);
#elif defined(LINUX)
		sFile = String::Format("filetest/test%04d.txt", i);
#endif
		FILE *f = fopen(sFile, "w");
		if (f) {
			fprintf(f, "This is text file #%d", i);
			fclose(f);
		} else {
			Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  Writing: %d\n", nStop - nStart);

	// Read files
	nStart = System::GetInstance()->GetMilliseconds();
	for (int i=1; i<=1000; i++) {
		char szString[256];
		String sFile;
#ifdef WIN32
		sFile = String::Format("filetest\\test%04d.txt", i);
		FILE *f = fopen(String::Format("filetest\\test%04d.txt", i), "r");
#elif defined(LINUX)
		sFile = String::Format("filetest/test%04d.txt", i);
		FILE *f = fopen(String::Format("filetest/test%04d.txt", i), "r");
#endif
		if (f) {
			fgets(szString, 256, f);
			fclose(f);
		} else {
			Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  Reading: %d\n", nStop - nStart);

	EndTask(true);
}

void FileSystemTest::SpeedTest_FS_SmallFiles()
{
	uint32 nStart, nStop;
	StartTask("Small files [fs]");
	Print("\n");

	// Get directory
	Directory cDir("filetest");
	if (cDir.Exists() && cDir.IsDirectory()) {
		// Write files
		nStart = System::GetInstance()->GetMilliseconds();
		for (int i=1; i<=1000; i++) {
			String sFile = String::Format("filetest/test%04d.txt", i);
			File f(sFile);
			if (f.Create()) {
				f.Open(File::FileWrite);
				f.Print(String::Format("This is text file #%d", i));
				f.Close();
			} else {
				Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
				EndTask(false);
				return;
			}
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  Writing: %d\n", nStop - nStart);

		// Read files
		nStart = System::GetInstance()->GetMilliseconds();
		for (int i=1; i<=1000; i++) {
			String sString;
			String sFile = String::Format("filetest/test%04d.txt", i);
			File f(sFile);
			if (f.Exists() && f.IsFile()) {
				f.Open(File::FileRead);
				sString = f.GetS();
				f.Close();
			} else {
				Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
				EndTask(false);
				return;
			}
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  Reading: %d\n", nStop - nStart);
		EndTask(true);
	} else EndTask(false);
}

void FileSystemTest::SpeedTest_OS_BigFile()
{
	uint32 nStart, nStop;
	StartTask("Big file [OS]");
	Print("\n");
#ifdef WIN32
	String sFile = "filetest\\bigone.bin";
#elif defined(LINUX)
	String sFile = "filetest/bigone.bin";
#endif
	// Write byte wise
	nStart = System::GetInstance()->GetMilliseconds();
	FILE *f = nullptr;
	f = fopen(sFile, "wb");
	unsigned char b = 0xFF;
	if (f) {
		for (unsigned long i=0; i<32*1024*1024; i++) {
			fwrite(&b, sizeof(b), 1, f);
		}
		fclose(f);
	} else {
		Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
		EndTask(false);
		return;
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  Writing   : %d\n", nStop - nStart);

	// Read byte wise
	nStart = System::GetInstance()->GetMilliseconds();
	f = fopen(sFile, "rb");

	if (f) {
		for (unsigned long i=0; i<32*1024*1024; i++) {
			fread(&b, sizeof(b), 1, f);
		}
		fclose(f);
	} else {
		Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
		EndTask(false);
		return;
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  Reading   : %d\n", nStop - nStart);

	// Write block
	nStart = System::GetInstance()->GetMilliseconds();
	f = fopen(sFile, "wb");
	if (f) {
		fwrite(g_nBuffer, sizeof(unsigned char), 1024*1024, f);
		fclose(f);
	} else {
		Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
		EndTask(false);
		return;
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  BlockWrite: %d\n", nStop - nStart);

	// Read block
	nStart = System::GetInstance()->GetMilliseconds();
	f = fopen(sFile, "rb");
	if (f) {
		fread(g_nBuffer, sizeof(unsigned char), 1024*1024, f);
		fclose(f);
	} else {
		Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
		EndTask(false);
		return;
	}
	nStop = System::GetInstance()->GetMilliseconds();
	Print("  BlockRead : %d\n", nStop - nStart);

	EndTask(true);
}

void FileSystemTest::SpeedTest_FS_BigFile()
{
	uint32 nStart, nStop;
	StartTask("Big file [fs]");
	Print("\n");

	// Get directory
	Directory cDir("filetest");
	if (cDir.Exists() && cDir.IsDirectory()) {
		String sFile = "filetest/bigone.bin";

		// Write byte wise
		nStart = System::GetInstance()->GetMilliseconds();
		unsigned char b = 0xFF;
		File fOut(sFile);
		if (fOut.Create()) {
			fOut.Open(File::FileWrite);
			for (unsigned long i=0; i<32*1024*1024; i++) {
				fOut.Write(&b, 1, sizeof(b));
			}
			fOut.Close();
		} else {
			Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  Writing   : %d\n", nStop - nStart);

		// Read byte wise
		nStart = System::GetInstance()->GetMilliseconds();
		File fIn(sFile);
		if (fIn.Exists() && fIn.IsFile()) {
			fIn.Open(File::FileRead);
			for (unsigned long i=0; i<32*1024*1024; i++) {
				fIn.Read(&b, 1, sizeof(b));
			}
			fIn.Close();
		} else {
			Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  Reading   : %d\n", nStop - nStart);

		// Write block
		nStart = System::GetInstance()->GetMilliseconds();
		sFile = "filetest/smallone.bin";
		fOut.Assign(sFile);
		if (fOut.Create()) {
			fOut.Open(File::FileWrite);
			fOut.Write(g_nBuffer, 1, 1024*1024);
			fOut.Close();
		} else {
			Print("Could not open file %s for writing..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  BlockWrite: %d\n", nStop - nStart);

		// Read block
		nStart = System::GetInstance()->GetMilliseconds();
		fIn.Assign(sFile);
		if (fIn.Exists() && fIn.IsFile()) {
			fIn.Open(File::FileRead);
			fIn.Read(g_nBuffer, 1, 1024*1024);
			fIn.Close();
		} else {
			Print("Could not open file %s for reading..exiting this test\n", sFile.GetASCII());
			EndTask(false);
			return;
		}
		nStop = System::GetInstance()->GetMilliseconds();
		Print("  BlockRead : %d\n", nStop - nStart);

		EndTask(true);
	} else EndTask(false);
}


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *FileSystemTest::GetName() const
{
	return "File system";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void FileSystemTest::Test()
{
	// Read directory list of 'test.zip'
	StartTask("Open directory 'test.zip/'");
	Directory cDir("test.zip/");
	if (cDir.Exists() && cDir.IsDirectory()) {
		// Read directory list
		StartTask("Read directory list of 'test.zip/'");
		FileSearch cSearch(cDir);
		bool bDirectory = false;
		bool bTestTxt   = false;
		bool bTest2Zip  = false;
		int  nFound     = 0;
		while (cSearch.HasNextFile()) {
			String sFile = cSearch.GetNextFile();
			nFound++;

			// directory/
			if (sFile == "directory/")
				bDirectory = true;

			// test.txt
			else if (sFile == "test.txt")
				bTestTxt = true;

			// test2.zip
			else if (sFile == "test2.zip")
				bTest2Zip = true;
		}
		EndTask(nFound == 3 && bDirectory && bTestTxt && bTest2Zip);

		// Open 'test.txt' inside 'test.zip/'
		StartTask("Open 'test.txt' inside 'test.zip/'");
		File cFile("test.zip/test.txt");
		if (cFile.Exists() && cFile.IsFile()) {
			// Open file
			if (cFile.Open(File::FileRead)) {
				// Read text
				String sString;
				int nOK = 0;
				sString = cFile.GetS();		// Read 'This is the first test-text,'
				if (sString == "This is the first test-text,") nOK++;
				sString = cFile.GetS();		// Read 'which is inside a ZIP-file.'
				if (sString == "which is inside a ZIP-file.") nOK++;
				sString = cFile.GetS();		// Read ''
				if (sString == "") nOK++;
				sString = cFile.GetS();		// Read 'blah'
				if (sString == "blah") nOK++;
				sString = cFile.GetS();		// Read ''
				if (sString == "") nOK++;
				sString = cFile.GetS();		// Read 'blub'
				if (sString == "blub") nOK++;

				// Close the file
				cFile.Close();

				// End task
				EndTask(nOK == 6);
			} else EndTask(false);
		} else EndTask(false);
	} else EndTask(false);

	// Perform some speed tests
	SpeedTest();
}
