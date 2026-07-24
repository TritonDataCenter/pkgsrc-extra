$NetBSD$

Remove conflicting memcntl prototype.

--- src/hotspot/os/solaris/os_solaris.cpp.orig	2022-09-21 10:16:05.000000000 +0000
+++ src/hotspot/os/solaris/os_solaris.cpp
@@ -169,7 +169,6 @@ os::Solaris::pthread_setname_np_func_t o
 
 // "default" initializers for missing libc APIs
 extern "C" {
-  int memcntl(void *, size_t, int, void *, int, int);
   int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *, uint_t *);
 }
 
