$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/time_members.cc.orig	2024-03-13 11:40:22.241476161 +0000
+++ libstdc++-v3/config/locale/dragonfly/time_members.cc
@@ -31,6 +31,7 @@
 // Modified for DragonFly by John Marino <gnugcc@marino.st>
 
 #include <locale>
+#include <cstring>
 #include <ctime>
 #include <cwchar>
 #include <stdlib.h>
@@ -196,8 +197,19 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
     _M_put(wchar_t* __s, size_t __maxlen, const wchar_t* __format,
 	   const tm* __tm) const throw()
     {
+#if defined(__illumos__)
+      char* __old = setlocale(LC_ALL, 0);
+      const size_t __llen = strlen(__old) + 1;
+      char* __sav = new char[__llen];
+      memcpy(__sav, __old, __llen);
+      setlocale(LC_ALL, _M_name_timepunct);
+      const size_t __len = wcsftime(__s, __maxlen, __format, __tm);
+      setlocale(LC_ALL, __sav);
+      delete [] __sav;
+#else
       const size_t __len = wcsftime_l(__s, __maxlen, __format, __tm,
 				      (locale_t)_M_c_locale_timepunct);
+#endif
       // Make sure __s is null terminated.
       if (__len == 0)
 	__s[0] = L'\0';
