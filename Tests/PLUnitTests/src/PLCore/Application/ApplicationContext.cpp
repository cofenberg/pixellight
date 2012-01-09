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

	// SetExecutableFilename sets:
	// - executable filename
	// - executable directory
	// - application directory
	// and removes trailing '/'
	// and application directory defaults to '.' if no application directory was given
	//
	TEST(SetExecutableFilename_EmptyString) {
		// initially: no Filename!
		CHECK_EQUAL(sEmpty.GetASCII(), App.GetExecutableFilename().GetASCII());

		// set empty name
		App.SetExecutableFilename(sEmpty);
		CHECK_EQUAL(sEmpty.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory is empty if no path was given
		CHECK_EQUAL("", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory defaults to "." if no name was given
		CHECK_EQUAL(".", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_NormalString) {
		// set name only
		App.SetExecutableFilename(sNormal);
		CHECK_EQUAL(sNormal.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory is empty if no path was given
		CHECK_EQUAL("", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory will be set to ".." if only a executable name was given
		CHECK_EQUAL("..", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_LongName) {
		// set name only
		App.SetExecutableFilename(sLong);
		CHECK_EQUAL(sLong.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory is empty if no path was given
		CHECK_EQUAL("", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory will be set to ".." if only a executable name was given
		CHECK_EQUAL("..", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_ShortValidFilePath) {
		String sPath = "C:\\" + sEmpty;

		// set valid path
		App.SetExecutableFilename(sPath);
		CHECK_EQUAL(sPath.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory
		CHECK_EQUAL("C:", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory
		CHECK_EQUAL("C:", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_AverageValidFilePath) {
		String sPath = "C:\\TestPath\\" + sNormal;

		// set valid path
		App.SetExecutableFilename(sPath);
		CHECK_EQUAL(sPath.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory
		CHECK_EQUAL("C:\\TestPath", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory
		CHECK_EQUAL("C:", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_LongValidFilePath) {
		String sPath = "C:\\TestPathRoot\\TestPath\\" + sLong;

		// set valid path
		App.SetExecutableFilename(sPath);
		CHECK_EQUAL(sPath.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory
		CHECK_EQUAL("C:\\TestPathRoot\\TestPath", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory
		CHECK_EQUAL("C:\\TestPathRoot", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_NonValidFilePath) {
		String sPath = "!§%&:\\TestPath\\\\" + sNormal;

		// set nonValid path
		App.SetExecutableFilename(sPath);
		CHECK_EQUAL("TestPath\\" + sNormal, App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory
		CHECK_EQUAL("TestPath", App.GetExecutableDirectory().GetASCII());

		// ApplicationDirectory defaults to '.' if path is not valid
		CHECK_EQUAL(".", App.GetAppDirectory().GetASCII());
	}

	TEST(SetExecutableFilename_ValidHttpPath) {
		String sPath = "http://TestDir/" + sNormal;

		// [TODO] should this be possible?
		App.SetExecutableFilename(sPath);
		CHECK_EQUAL(sPath.GetASCII(), App.GetExecutableFilename().GetASCII());

		// ExecutableDirectory
		CHECK_EQUAL("http://TestDir", App.GetExecutableDirectory().GetASCII());

		// 
		CHECK_EQUAL("http:", App.GetAppDirectory().GetASCII());
	}

	TEST(SetArguments_NoElements) {
		Array<String> elems;
		CHECK(elems.Compare(App.GetArguments()));

		// set empty arguments array
		App.SetArguments(elems);

		// compare content of both arrays, has to be the same!
		CHECK(elems.Compare(App.GetArguments()));
	}

	TEST(SetArguments_WithElements) {
		Array<String> elems;
		elems.Add(String("Elem1"));
		elems.Add(String("Elem2"));

		// set arguments array with 2 elements
		App.SetArguments(elems);
		CHECK(elems.Compare(App.GetArguments()));	
	}

	TEST(SetStartupDirectory_EmptyString) {
		// set empty path
		App.SetStartupDirectory(sEmpty);
		CHECK_EQUAL(sEmpty.GetASCII(), App.GetStartupDirectory().GetASCII());		
	}

	TEST(SetStartupDirectory_ValidPath) {
		String sPath = "C:\\" + sNormal;

		// set directory
		App.SetStartupDirectory(sPath);
		CHECK_EQUAL(sPath.GetASCII(), App.GetStartupDirectory().GetASCII());		
	}

	TEST(SetLogFilename_EmptyName) {
		// set empty
		App.SetLogFilename(sEmpty);
		CHECK_EQUAL(sEmpty.GetASCII(), App.GetLogFilename().GetASCII());	
	}

	TEST(SetLogFilename_ValidName) {
		// set name
		App.SetLogFilename(sNormal);
		CHECK_EQUAL(sNormal.GetASCII(), App.GetLogFilename().GetASCII());
	}

	TEST(SetConfigFilename_EmptyName) {
		// set empty
		App.SetConfigFilename(sEmpty);
		CHECK_EQUAL(sEmpty.GetASCII(), App.GetConfigFilename().GetASCII());		
	}

	TEST(SetConfigFilename_ValidName) {
		// set name
		App.SetConfigFilename(sNormal);
		CHECK_EQUAL(sNormal.GetASCII(), App.GetConfigFilename().GetASCII());		
	}
}