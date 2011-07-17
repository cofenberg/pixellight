#[-------------------------------------------------------]
#[ Classes                                               ]
#[-------------------------------------------------------]
# The "MyScriptClass"-class declaration
class MyScriptClass(object):
	"My script class"

	# The default constructor - In Python, we can only have one constructor

	# Destructor
	def __del__(this):
		PL['System']['Console']['Print']("MyScriptClass::~MyScriptClass() - a=" + str(this.a) + "\n")

	# Another constructor
	def __init__(this, a):	# (most people are using the name "self" for this purpose, I stick with "this" to have as comparable as possible example scripts)
		# A public class attribute
		this.a = a

		PL['System']['Console']['Print']("MyScriptClass::MyScriptClass(a) - a=" + str(this.a) + "\n")

	# A public class method
	def DoSomething(this):
		this.a *= 2
		PL['System']['Console']['Print']("MyScriptClass::DoSomething() - a=" + str(this.a) + "\n")


# A derived class named "MyDerivedScriptClass"
class MyDerivedScriptClass(MyScriptClass):
	"My derived script class"

	# The default constructor
	def __init__(this):
		# Calling the non-default constructor of the base class
		MyScriptClass.__init__(this, 10)

		# A public class attribute
		this.b = 0

		# A private class attribute (actually, Python doesn't support private stuff, it's just a name convention!)
		this._privateX = 0

		PL['System']['Console']['Print']("MyDerivedScriptClass::MyDerivedScriptClass() - b=" + str(this.b) + "\n")
		PL['System']['Console']['Print']("MyDerivedScriptClass::MyDerivedScriptClass() - _privateX=" + str(this._privateX) + "\n")

	# Overloading a public virtual method
	def DoSomething(this):
		# Call the base class implementation
		MyScriptClass.DoSomething(this)

		# Do something more
		this.b = this.a
		PL['System']['Console']['Print']("MyDerivedScriptClass::DoSomething() - b=" + str(this.b) + "\n")

		# Call the private class method
		this._PrivateDoSomething()

	# A public class method
	def GetPrivateX(this):
		return this._privateX

	# A private class method (actually, Python doesn't support private stuff, it's just a name convention!)
	def _PrivateDoSomething(this):
		# Increment the private attribute
		this._privateX = this._privateX + 1
		PL['System']['Console']['Print']("MyDerivedScriptClass::PrivateDoSomething() - _privateX=" + str(this._privateX) + "\n")


#[-------------------------------------------------------]
#[ Global functions                                      ]
#[-------------------------------------------------------]
def OOP():
	# Create an instance of MyScriptClass
	firstObject = MyScriptClass(5)
	firstObject.a = 1
	firstObject.DoSomething()

	# Create an instance of MyDerivedScriptClass
	secondObject = MyDerivedScriptClass()
	secondObject.DoSomething()
	secondObject.a = firstObject.a
	secondObject.b = 2
	PL['System']['Console']['Print']("secondObject.GetPrivateX() = " + str(secondObject.GetPrivateX()) + "\n")
