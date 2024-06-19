$NetBSD$

Handle out-of-srcdir builds.
pkgsrc cmake needs -lstdc++, OmniOS has different handling for -nodefaultlibs

--- cmake/sunos/default_libs.cmake.orig	2024-06-18 14:06:23.203199547 +0000
+++ cmake/sunos/default_libs.cmake
@@ -7,11 +7,11 @@ endif ()
 set (BUILTINS_LIBRARY "-lgcc_s")
 
 set (DEFAULT_LIBS "${DEFAULT_LIBS} ${BUILTINS_LIBRARY} ${COVERAGE_OPTION} -lc -lm -lsocket -lnsl -lsendfile -lproc")
-set (DEFAULT_LIBS "${DEFAULT_LIBS} -Lcontrib/libunwind-cmake/ -lunwind")
+set (DEFAULT_LIBS "${DEFAULT_LIBS} -L${CMAKE_CURRENT_BINARY_DIR}/contrib/libunwind-cmake/ -lunwind")
 
 message(STATUS "Default libraries: ${DEFAULT_LIBS}")
 
-set(CMAKE_CXX_STANDARD_LIBRARIES ${DEFAULT_LIBS})
+set(CMAKE_CXX_STANDARD_LIBRARIES "${DEFAULT_LIBS} -lstdc++")
 set(CMAKE_C_STANDARD_LIBRARIES ${DEFAULT_LIBS})
 
 set(CMAKE_HAVE_LIBC_PTHREAD ON)
