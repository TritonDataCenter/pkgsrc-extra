$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/ctype_members.cc.orig	2024-03-13 11:58:35.185372635 +0000
+++ libstdc++-v3/config/locale/dragonfly/ctype_members.cc
@@ -135,6 +135,66 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
     return __hi;
   }
 
+/*
+ * Taken verbatim from config/locale/generic/ctype_members.cc.  DragonFly
+ * implements these in config/os/bsd/dragonfly/ctype_inline.h.
+ */
+#if defined(__illumos__)
+  bool
+  ctype<wchar_t>::
+  do_is(mask __m, char_type __c) const
+  {
+    bool __ret = false;
+    // Generically, 15 (instead of 11) since we don't know the numerical
+    // encoding of the various categories in /usr/include/ctype.h.
+    const size_t __bitmasksize = 15;
+    for (size_t __bitcur = 0; __bitcur <= __bitmasksize; ++__bitcur)
+      if (__m & _M_bit[__bitcur]
+          && iswctype(__c, _M_wmask[__bitcur]))
+        {
+          __ret = true;
+          break;
+        }
+    return __ret;
+  }
+
+  const wchar_t*
+  ctype<wchar_t>::
+  do_is(const wchar_t* __lo, const wchar_t* __hi, mask* __vec) const
+  {
+    for (;__lo < __hi; ++__vec, ++__lo)
+      {
+        // Generically, 15 (instead of 11) since we don't know the numerical
+        // encoding of the various categories in /usr/include/ctype.h.
+        const size_t __bitmasksize = 15;
+        mask __m = 0;
+        for (size_t __bitcur = 0; __bitcur <= __bitmasksize; ++__bitcur)
+          if (iswctype(*__lo, _M_wmask[__bitcur]))
+            __m |= _M_bit[__bitcur];
+        *__vec = __m;
+      }
+    return __hi;
+  }
+
+  const wchar_t*
+  ctype<wchar_t>::
+  do_scan_is(mask __m, const wchar_t* __lo, const wchar_t* __hi) const
+  {
+    while (__lo < __hi && !this->do_is(__m, *__lo))
+      ++__lo;
+    return __lo;
+  }
+
+  const wchar_t*
+  ctype<wchar_t>::
+  do_scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
+  {
+    while (__lo < __hi && this->do_is(__m, *__lo) != 0)
+      ++__lo;
+    return __lo;
+  }
+#endif
+
   wchar_t
   ctype<wchar_t>::
   do_widen(char __c) const
