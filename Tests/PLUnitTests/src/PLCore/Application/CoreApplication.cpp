//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Application/CoreApplication.h>
#include <PLCore/String/String.h>

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(CoreApplication) {
	TEST(Enum_ESignal) {
		CoreApplication::ESignal sig = CoreApplication::SignalInterrupt;
		CHECK_EQUAL(1, sig);

		sig = CoreApplication::SignalTerm;
		CHECK_EQUAL(2, sig);
	}

	TEST(GetName) {
		CoreApplication* pCoreApp = new CoreApplication();
		
		String name = pCoreApp->GetName();
		CHECK_EQUAL("PLUnitTestsD", name.GetASCII());

		delete pCoreApp;
	}
}