//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Application/ApplicationContext.h>
#include <PLCore/String/String.h>
#include <PLCore/Container/Array.h>

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(ApplicationContext) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	TEST(SetExecutableFilename_NameEmpty) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sExpect = "";

		// initially: no Filename!
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), "");

		// set empty name
		App.SetExecutableFilename("");
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), "");

		// appDirectory defaults to "." if no name was given
		CHECK_EQUAL(App.GetAppDirectory().GetASCII(), ".");		
	}

	TEST(SetExecutableFilename_NameOnly) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sExpect = "";

		// set name only
		App.SetExecutableFilename(sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());

		// appDirectory will be set to ".." if only a executable name was given
		CHECK_EQUAL(App.GetAppDirectory().GetASCII(), "..");		
	}
	
	TEST(SetExecutableFilename_ShortValidFilePath) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sPath = "C:\\";
		String sExpect = "";

		// set valid path
		App.SetExecutableFilename(sPath + sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), (sPath + sName).GetASCII());

		// construct expected filepath
		sPath.Replace("\\", "/");
		sPath = "file://" + sPath.GetSubstring(0, sPath.GetLength()-1);

		// [TODO] expects unified "file://C:" instead of local "C:"
		sExpect = "file://C:";
		CHECK_EQUAL(App.GetAppDirectory().GetASCII(), sPath.GetASCII());		
	}

	TEST(SetExecutableFilename_AverageValidFilePath) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sPath = "C:\\TestPath\\";
		String sExpect = "";

		// set valid path
		// [TODO] SetExecutableFilename sets appdirectory 2 directories higher! update documentation!
		App.SetExecutableFilename(sPath + sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), (sPath + sName).GetASCII());

		// construct expected filepath
		sPath.Replace("\\", "/");
		sPath = "file://" + sPath.GetSubstring(0, sPath.GetLength()-1);

		// [TODO] expects "file://C:" but is "file://C:/TestPath"
		//CHECK_EQUAL(App.GetAppDirectory().GetASCII(), sPath.GetASCII());		
	}

	TEST(SetExecutableFilename_LongValidFilePath) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sPath = "C:\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\TestPath\\";
		String sExpect = "";

		// set valid path
		App.SetExecutableFilename(sPath + sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), (sPath + sName).GetASCII());

		// construct expected filepath
		sPath.Replace("\\", "/");
		sPath = "file://" + sPath.GetSubstring(0, sPath.GetLength()-1);

		// [TODO] expects "file://C:/TestPath/...usw" but is one directory lower, look at Test SetExecutableFilename_AverageValidFilePath
		//CHECK_EQUAL(App.GetAppDirectory().GetASCII(), sPath.GetASCII());
	}

	TEST(SetExecutableFilename_NonValidFilePath) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sPath = ":\\TestPath\\\\";
		String sExpect = "";

		// set nonValid path
		App.SetExecutableFilename(sPath + sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), (sPath + sName).GetASCII());

		// if path is not valid => defaults to "."
		CHECK_EQUAL(App.GetAppDirectory().GetASCII(), ".");

				
	}

	TEST(SetExecutableFilename_ValidHttpPath) {
		ApplicationContext App;
		String sName = "TestName.ext";
		String sPath = "http://TestDir/";
		String sExpect = "";

		// set valid path
		App.SetExecutableFilename(sPath + sName);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), (sPath + sName).GetASCII());

		// [TODO] What to expect here? "http:/" is definitely wrong! 
		//CHECK_EQUAL(App.GetAppDirectory().GetASCII(), sPath.GetASCII());		
	}

	TEST(SetArguments_NoElements) {
		ApplicationContext App;
		Array<String> elems, test;

		test = App.GetArguments();
		// [TODO] these are not equal? both are empty!
		//CHECK(elems.Compare(test));

		// set empty arguments array
		App.SetArguments(elems);
		test = App.GetArguments();

		// compare content of both arrays, has to be the same!
		// [TODO] these are not equal? both are empty!
		//CHECK(elems.Compare(test));
	}

	TEST(SetArguments_WithElements) {
		ApplicationContext App;
		Array<String> elems, test;
		elems.Add(String("Elem1"));
		elems.Add(String("Elem2"));

		// set arguments array with 2 elements
		App.SetArguments(elems);
		test = App.GetArguments();
		CHECK(elems.Compare(test));	
	}

	TEST(SetStartupDirectory_EmptyString) {
		ApplicationContext App;
		String sPath = "";
		String sExpect = "";

		// set empty path
		App.SetStartupDirectory(sPath);
		sExpect = App.GetStartupDirectory();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());		
	}

	TEST(SetStartupDirectory_ValidPath) {
		ApplicationContext App;
		String sName = "C:\\PL\\";
		String sExpect = "";

		// set directory
		App.SetStartupDirectory(sName);
		sExpect = App.GetStartupDirectory();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());		
	}

	TEST(SetLogFilename_EmptyName) {
		ApplicationContext App;
		String sName = "";
		String sExpect = "";

		// set empty
		App.SetLogFilename(sName);
		sExpect = App.GetLogFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());	
	}

	TEST(SetLogFilename_ValidName) {
		ApplicationContext App;
		String sName = "PLlog.txt";
		String sExpect = "";

		// set name
		App.SetLogFilename(sName);
		sExpect = App.GetLogFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());
	}

	TEST(SetConfigFilename_EmptyName) {
		ApplicationContext App;
		String sName = "";
		String sExpect = "";

		// set empty
		App.SetConfigFilename(sName);
		sExpect = App.GetConfigFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());		
	}

	TEST(SetConfigFilename_ValidPath) {
		ApplicationContext App;
		String sName = "PLconfig.txt";
		String sExpect = "";

		// set name
		App.SetConfigFilename(sName);
		sExpect = App.GetConfigFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sName.GetASCII());		
	}
}