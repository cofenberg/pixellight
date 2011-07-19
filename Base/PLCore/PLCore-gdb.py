import gdb
import re

class PLStringPrinter:
	def __init__(self, val):
		self.val = val
		
	def to_string(self):
		bufType = self.val['m_pStringBuffer']['m_nType']
		if bufType == 0:
			ty = gdb.lookup_type('PLCore::StringBufferASCII').pointer();
			return self.val['m_pStringBuffer'].cast(ty)['m_pszString']
		elif bufType == 1:
			ty = gdb.lookup_type('PLCore::StringBufferUnicode').pointer();
			return self.val['m_pStringBuffer'].cast(ty)['m_pszString'].string('UTF-32')
		return None
	def display_hint (self):
		return 'string'

def register_pl_printers (obj):
	if obj == None:
		obj = gdb
		
	obj.pretty_printers.append (lookup_function)
	
def lookup_function (val):
	"Look-up and return a pretty-printer that can print val."
	
	# Get the type.
	type = val.type;
	
	# If it points to a reference, get the reference.
	if type.code == gdb.TYPE_CODE_REF:
		type = type.target ()
		
	# Get the unqualified type, stripped of typedefs.
	type = type.unqualified ().strip_typedefs ()
	
	# Get the type name.
	typename = type.tag
	if typename == None:
		return None
		
	# Iterate over local dictionary of types to determine
	# if a printer is registered for that type. Return an
	# instantiation of the printer if found.
	for function in pretty_printers_dict:
		if function.search (typename):
			return pretty_printers_dict[function] (val)
	
	# Cannot find a pretty printer. Return None.
	return None

def build_dictionary ():
	pretty_printers_dict[re.compile('^PLCore::String$')] = lambda val: PLStringPrinter(val)

pretty_printers_dict = {}

build_dictionary ()
register_pl_printers(gdb.current_objfile ())