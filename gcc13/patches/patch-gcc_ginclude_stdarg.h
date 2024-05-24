$NetBSD$

Ensure va_copy visibility is retained on illumos in C++ mode after applying
the __STDC_VERSION__ -> _STDC_{C99,C11} patch.

--- gcc/ginclude/stdarg.h.orig	2024-05-24 11:43:06.932507694 +0000
+++ gcc/ginclude/stdarg.h
@@ -52,7 +52,7 @@ typedef __builtin_va_list __gnuc_va_list
 #define va_end(v)	__builtin_va_end(v)
 #define va_arg(v,l)	__builtin_va_arg(v,l)
 #if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L \
-    || __cplusplus + 0 >= 201103L
+    || __cplusplus + 0 >= 201103L || (defined(__cplusplus) && defined(__sun))
 #define va_copy(d,s)	__builtin_va_copy(d,s)
 #endif
 #define __va_copy(d,s)	__builtin_va_copy(d,s)
