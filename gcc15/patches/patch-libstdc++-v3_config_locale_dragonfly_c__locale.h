$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/c_locale.h.orig	2024-03-25 18:07:19.754974812 +0000
+++ libstdc++-v3/config/locale/dragonfly/c_locale.h
@@ -39,6 +39,11 @@
 
 #pragma GCC system_header
 
+// not ideal, but required for uselocale(3C) visibility
+#if defined(__illumos__)
+#  define _XPG7
+#endif
+
 #include <clocale>
 #include <xlocale.h>
 
