TinyXML 2.5.3
- License: "zlib/libpng", see "license.txt"
- Used by the XML classes inside "PLGeneral" (statically linked and therefore without additional external dependencies)
- Download from: http://www.sourceforge.net/projects/tinyxml/
  Includes 4 changes to make the PL TinyXML Wrapper not too complex:
  - TiXmlNode::CopyTo() does not copy the user data, too
  - TiXmlBase: Destructor will call a Destroy Callback function - this way we can be informed within the wrapper
    when a TinyXML object was destroyed
  - TiXmlBase::ReadName: [ and ] are now valid in argument names - that was required for RTTI array variables
  - TiXmlAttribute: There was a 'NameTStr()'-function but no 'ValueTStr()'-function
- From repository, last change: Sun Sep 2 02:39:34 2007 UTC
