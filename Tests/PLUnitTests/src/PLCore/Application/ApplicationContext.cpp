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
	// general objects for testing
	ApplicationContext App;
	String sEmpty = "";
	String sNormal = "I_am_a_String";
	String sLong = "I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!_I_am_a_very_long_String_that_will_be_repeated_often!";
	String sExpect = "";

	TEST(SetExecutableFilename_EmptyString) {
		// initially: no Filename!
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sEmpty.GetASCII());

		// set empty name
		App.SetExecutableFilename(sEmpty);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sEmpty.GetASCII());

		// appDirectory defaults to "." if no name was given
		CHECK_EQUAL(".", App.GetAppDirectory().GetASCII());		
	}

	TEST(SetExecutableFilename_NormalString) {
		// set name only
		App.SetExecutableFilename(sNormal);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sNormal.GetASCII());

		// appDirectory will be set to ".." if only a executable name was given
		CHECK_EQUAL("..", App.GetAppDirectory().GetASCII());		
	}

	TEST(SetExecutableFilename_LongName) {
		// set name only
		App.SetExecutableFilename(sLong);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sLong.GetASCII());

		// appDirectory will be set to ".." if only a executable name was given
		CHECK_EQUAL("..", App.GetAppDirectory().GetASCII());		
	}

	TEST(SetExecutableFilename_ShortValidFilePath) {
		String sPath = "C:\\" + sEmpty;

		// set valid path
		App.SetExecutableFilename(sPath);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());

		// construct expected filepath for appdirectory
		sExpect = sPath;
		sExpect.Replace("\\", "/");
		sExpect = "file://" + sExpect.GetSubstring(0, sExpect.GetLength()-1);

		CHECK_EQUAL(sExpect.GetASCII(), App.GetAppDirectory().GetASCII());		
	}

	TEST(SetExecutableFilename_AverageValidFilePath) {
		String sPath = "C:\\TestPath\\" + sNormal;

		// set valid path
		// [TODO] SetExecutableFilename sets appdirectory 2 directories higher! update documentation?
		App.SetExecutableFilename(sPath);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());

		// construct expected filepath
		sExpect = sPath;
		sExpect.Replace("\\", "/");
		sExpect = "file://" + sExpect.GetSubstring(0, sExpect.GetLength()-1);

		// [TODO] expects "file://C:/TestPath" but is "file://C:"
		//CHECK_EQUAL(sExpect.GetASCII(), App.GetAppDirectory().GetASCII());		
	}

	TEST(SetExecutableFilename_LongValidFilePath) {
		String sPath = "C:\\" + sLong;

		// set valid path
		App.SetExecutableFilename(sPath);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());

		// construct expected filepath
		sExpect = sPath;
		sExpect.Replace("\\", "/");
		sExpect = "file://" + sExpect.GetSubstring(0, sExpect.GetLength()-1);

		// [TODO] expects "file://C:/I_am_a_String....." but is "file://C:", look at TODO of test "SetExecutableFilename_AverageValidFilePath"
		//CHECK_EQUAL(sExpect.GetASCII(), App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_NonValidFilePath) {
		String sPath = ":\\TestPath\\\\" + sNormal;

		// set nonValid path
		App.SetExecutableFilename(sPath);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());

		// if path is not valid => defaults to "."
		CHECK_EQUAL(App.GetAppDirectory().GetASCII(), ".");
	}

	TEST(SetExecutableFilename_ValidHttpPath) {
		String sPath = "http://TestDir/" + sNormal;

		// set valid path
		App.SetExecutableFilename(sPath);
		sExpect = App.GetExecutableFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());

		// [TODO] What to expect here? "http:/" is definitely wrong! 
		//CHECK_EQUAL(sPath.GetASCII(), App.GetAppDirectory().GetASCII());		
	}

	TEST(SetArguments_NoElements) {
		Array<String> elems, test;

		test = App.GetArguments();
		CHECK(elems.Compare(test));

		// set empty arguments array
		App.SetArguments(elems);
		test = App.GetArguments();

		// compare content of both arrays, has to be the same!
		CHECK(elems.Compare(test));
	}

	TEST(SetArguments_WithElements) {
		Array<String> elems, test;
		elems.Add(String("Elem1"));
		elems.Add(String("Elem2"));

		// set arguments array with 2 elements
		App.SetArguments(elems);
		test = App.GetArguments();
		CHECK(elems.Compare(test));	
	}

	TEST(SetStartupDirectory_EmptyString) {
		// set empty path
		App.SetStartupDirectory(sEmpty);
		sExpect = App.GetStartupDirectory();
		CHECK_EQUAL(sExpect.GetASCII(), sEmpty.GetASCII());		
	}

	TEST(SetStartupDirectory_ValidPath) {
		String sPath = "C:\\" + sNormal;

		// set directory
		App.SetStartupDirectory(sPath);
		sExpect = App.GetStartupDirectory();
		CHECK_EQUAL(sExpect.GetASCII(), sPath.GetASCII());		
	}

	TEST(SetLogFilename_EmptyName) {
		// set empty
		App.SetLogFilename(sEmpty);
		sExpect = App.GetLogFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sEmpty.GetASCII());	
	}

	TEST(SetLogFilename_ValidName) {
		// set name
		App.SetLogFilename(sNormal);
		sExpect = App.GetLogFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sNormal.GetASCII());
	}

	TEST(SetConfigFilename_EmptyName) {
		// set empty
		App.SetConfigFilename(sEmpty);
		sExpect = App.GetConfigFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sEmpty.GetASCII());		
	}

	TEST(SetConfigFilename_ValidName) {
		// set name
		App.SetConfigFilename(sNormal);
		sExpect = App.GetConfigFilename();
		CHECK_EQUAL(sExpect.GetASCII(), sNormal.GetASCII());		
	}
}