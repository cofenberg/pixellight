//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
// The "MyScriptClass"-class declaration

	// The default constructor - In JavaScript, we can only have one constructor

	// Destructor - There's no destructor in JavaScript

	// Another constructor
	function MyScriptClass(a)
	{
		// A public class attribute
		this.a = a;

		PL.System.Console.Print("MyScriptClass::MyScriptClass(a) - a=" + this.a + "\n");
	}

	// A public class method
	MyScriptClass.prototype.DoSomething = function()
	{
		this.a *= 2;
		PL.System.Console.Print("MyScriptClass::DoSomething() - a=" + this.a + "\n");
	}

// A derived class named "MyDerivedScriptClass"
	MyDerivedScriptClass.prototype = new MyScriptClass;
	MyDerivedScriptClass.prototype.constructor = MyDerivedScriptClass;

	// The default constructor
	function MyDerivedScriptClass()
	{
		// Calling the non-default constructor of the base class
		MyScriptClass.call(this, 10);

		// A public class attribute
		this.b = 0;

		// A private class attribute - In JavaScript, private instance variables are only accessible to private methods (not even to public methods!)
		var privateX  = 0;

		PL.System.Console.Print("MyDerivedScriptClass::MyDerivedScriptClass() - b=" + this.b + "\n");
		PL.System.Console.Print("MyDerivedScriptClass::MyDerivedScriptClass() - privateX=" + privateX + "\n");

		// A private class method
		// - In JavaScript, private methods are inner functions of the constructor
		function PrivateDoSomething_Privileged()
		{
			// Increment the private attribute
			privateX++;
			PL.System.Console.Print("MyDerivedScriptClass::PrivateDoSomething() - privateX=" + privateX + "\n");
		}
		// - In JavaScript, private methods cannot be called by public methods, only a privileged method is able to access the private variables and methods, so create one
		this.PrivateDoSomething = function()
		{
			PrivateDoSomething_Privileged();
		}

		// This two private methods enable us to access the private attribute
		function GetPrivateX_Privileged()
		{
			// In this privileged method we have finally access to the private attribute!
			return privateX;
		}
		this.GetPrivateX_Internal = function()
		{
			// JavaScript doesn't give us access to the private attribute, so call the privileged method...
			return GetPrivateX_Privileged();
		}
	}

	// Overloading a public virtual method
	MyDerivedScriptClass.prototype.DoSomething = function()
	{
		// Call the base class implementation
		MyScriptClass.prototype.DoSomething.call(this);

		// Do something more
		this.b = this.a;
		PL.System.Console.Print("MyDerivedScriptClass::DoSomething() - b=" + this.b + "\n");

		// Call the private class method
		this.PrivateDoSomething();
	}

	// A public class method
	MyDerivedScriptClass.prototype.GetPrivateX = function()
	{
		// This is somewhat nasty: Call "GetPrivateX_Internal()" which calls "GetPrivateX_Privileged()" which is finally able to access the private attribute
		return this.GetPrivateX_Internal();
	}


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
function OOP()
{
	// Create an instance of MyScriptClass
	var firstObject = new MyScriptClass(5);
	firstObject.a = 1;
	firstObject.DoSomething();

	// Create an instance of MyDerivedScriptClass
	var secondObject = new MyDerivedScriptClass();
	secondObject.DoSomething();
	secondObject.a = firstObject.a;
	secondObject.b = 2;
	PL.System.Console.Print("secondObject.GetPrivateX() = " + secondObject.GetPrivateX() + "\n");
}
