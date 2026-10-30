$NetBSD$

Remove conflicting memcntl prototype.
Fix crashes trying to use low memory addresses.

--- src/hotspot/os/solaris/os_solaris.cpp.orig	2026-10-30 12:27:06.000000000 +0000
+++ src/hotspot/os/solaris/os_solaris.cpp
@@ -155,7 +155,6 @@ os::Solaris::pthread_setname_np_func_t o
 
 // "default" initializers for missing libc APIs
 extern "C" {
-  int memcntl(void *, size_t, int, void *, int, int);
   int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *, uint_t *);
 }
 
@@ -1674,6 +1673,13 @@ char* os::pd_attempt_reserve_memory_at(c
   // in one of the methods further up the call chain.  See bug 5044738.
   assert(bytes % os::vm_page_size() == 0, "reserving unexpected size block");
 
+#ifdef _LP64
+  // Leave the low 4GB available for growth of the sbrk-based native heap.
+  if ((uintptr_t)requested_addr < nth_bit(32)) {
+    return nullptr;
+  }
+#endif
+
   // Since snv_84, Solaris attempts to honor the address hint - see 5003415.
   char* addr = Solaris::anon_mmap(requested_addr, bytes);
 
