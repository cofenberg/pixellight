nmake clean
configure -platform win32-msvc2010 -release -opensource -fast -sse -sse2 -no-qt3support -no-scripttools -no-stl -nomake examples -nomake demos -no-openssl -no-webkit -no-phonon -no-style-motif -no-style-cde -no-style-cleanlooks -no-style-plastique -no-sql-sqlite -qt-style-windowsvista -D NOMINMAX -D VC_EXTRA_LEAN -D WIN32 -D _WINDOWS -D _CRT_NONSTDC_NO_WARNINGS -D _CRT_SECURE_NO_WARNINGS -D _CRT_SECURE_NO_DEPRECATE -D _CRT_NONSTDC_NO_DEPRECATE -D _ATL_SECURE_NO_DEPRECATE -D _CRT_NON_CONFORMING_SWPRINTFS -D STRSAFE_NO_DEPRECATE -D _UNICODE -D UNICODE
nmake
