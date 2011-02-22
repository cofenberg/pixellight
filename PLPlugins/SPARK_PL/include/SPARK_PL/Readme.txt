SPARK 1.05.04
- License: "SPARK is a free software under zlib license" (see "zlib.txt")
- SPARK download from: http://spark.developpez.com/
- Used within the "SPARK_PL" plugin (statically linked and therefore without additional external dependencies)


Notes:
- "SPK_DEF.h" was slightly changed so it compiles fine under Linux as well, the code is marked with a [HACK]
- Added missing forward declaration within "SPK_Particle.h"
- SPARK is using the C++ RTTI ("dynamic_cast") while PixelLight is not, changed "dynamic_cast" into "static_cast" to avoid compiler problems
... [TODO]... try to fix those issues...

