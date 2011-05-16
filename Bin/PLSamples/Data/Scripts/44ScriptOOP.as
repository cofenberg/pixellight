//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
// The "MyScriptClass"-class declaration
class MyScriptClass
{
	// The default constructor
	MyScriptClass()
	{
		a = 0;
		PL_System_Console_Print("MyScriptClass::MyScriptClass() - a=" + a + "\n");
	}

	// Destructor
	~MyScriptClass()
	{
		PL_System_Console_Print("MyScriptClass::~MyScriptClass() - a=" + a + "\n");
	}

	// Another constructor
	MyScriptClass(int a)
	{
		this.a = a;
		PL_System_Console_Print("MyScriptClass::MyScriptClass(int a) - a=" + this.a + "\n");
	}

	// A public class method
	void DoSomething()
	{
		a *= 2;
		PL_System_Console_Print("MyScriptClass::DoSomething() - a=" + a + "\n");
	}

	// A public class attribute
	int a;
}

// A derived class named "MyDerivedScriptClass"
class MyDerivedScriptClass : MyScriptClass
{
	// The default constructor
	MyDerivedScriptClass()
	{
		// Calling the non-default constructor of the base class
		super(10);

		b = 0;
		privateX = 0;

		PL_System_Console_Print("MyDerivedScriptClass::MyDerivedScriptClass() - b=" + b + "\n");
		PL_System_Console_Print("MyDerivedScriptClass::MyDerivedScriptClass() - privateX=" + privateX + "\n");
	}

	// Overloading a public virtual method
	void DoSomething()
	{
		// Call the base class implementation
		MyScriptClass::DoSomething();

		// Do something more
		b = a;
		PL_System_Console_Print("MyDerivedScriptClass::DoSomething() - b=" + b + "\n");

		// Call the private class method
		PrivateDoSomething();
	}

	// A public class method
	int GetPrivateX()
	{
		return privateX;
	}

	// A public class attribute
	int b;

	// A private class method
	private void PrivateDoSomething()
	{
		// Increment the private attribute
		privateX++;
		PL_System_Console_Print("MyDerivedScriptClass::PrivateDoSomething() - privateX=" + privateX + "\n");
	}

	// A private class attribute
	private int privateX;
}


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
void OOP()
{
	// Create an instance of MyScriptClass
	MyScriptClass firstObject(5);
	firstObject.a = 1;
	firstObject.DoSomething();

	// Create an instance of MyDerivedScriptClass
	MyDerivedScriptClass secondObject();
	secondObject.DoSomething();
	secondObject.a = firstObject.a;
	secondObject.b = 2;
	PL_System_Console_Print("secondObject.GetPrivateX() = " + secondObject.GetPrivateX() + "\n");
}
