$NetBSD$

Not sure why this is required and not on Tribblix.

--- src/hotspot/os/solaris/osThread_solaris.hpp.orig	2026-10-30 13:00:38.611141223 +0000
+++ src/hotspot/os/solaris/osThread_solaris.hpp
@@ -25,6 +25,7 @@
 #ifndef OS_SOLARIS_OSTHREAD_SOLARIS_HPP
 #define OS_SOLARIS_OSTHREAD_SOLARIS_HPP
 
+#include <thread.h>
 #include "runtime/osThreadBase.hpp"
 #include "suspendResume_posix.hpp"
 #include "utilities/globalDefinitions.hpp"
