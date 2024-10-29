$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/c_locale.cc.orig	2024-03-13 11:28:33.603136755 +0000
+++ libstdc++-v3/config/locale/dragonfly/c_locale.cc
@@ -46,7 +46,11 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 		   const __c_locale& __cloc) throw()
     {
       char* __sanity;
+#if defined(__illumos__)
+      __v = strtof(__s, &__sanity);
+#else
       __v = strtof_l(__s, &__sanity, (locale_t)__cloc);
+#endif
 
       // _GLIBCXX_RESOLVE_LIB_DEFECTS
       // 23. Num_get overflow result.
@@ -73,7 +77,11 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 		   const __c_locale& __cloc) throw()
     {
       char* __sanity;
+#if defined(__illumos__)
+      __v = strtod(__s, &__sanity);
+#else
       __v = strtod_l(__s, &__sanity, (locale_t)__cloc);
+#endif
 
       // _GLIBCXX_RESOLVE_LIB_DEFECTS
       // 23. Num_get overflow result.
@@ -100,7 +108,11 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 		   const __c_locale& __cloc) throw()
     {
       char* __sanity;
+#if defined(__illumos__)
+      __v = strtold(__s, &__sanity);
+#else
       __v = strtold_l(__s, &__sanity, (locale_t)__cloc);
+#endif
 
       // _GLIBCXX_RESOLVE_LIB_DEFECTS
       // 23. Num_get overflow result.
