lib3ds 1.3.0
- License: "GNU Lesser General Public License", (LGPL, "either version 2.1 of the License, or (at your option) any later version") see "lgpl-3.0.txt" and "gpl-3.0.txt" (refered)
- Used by the "MeshLoader3ds" mesh loader class inside "PLDefaultFileFormats" (statically linked and therefore without additional external dependencies)
- Download from: http://lib3ds.sourceforge.net/
- "types.h": I changed
    #ifdef _MSC_VER
  Back to
    #if defined (_LIB3DS_DLL) && defined(_WIN32) && (!defined(__GNUC__))
  from lib3ds version 1.2.0 for static build support
