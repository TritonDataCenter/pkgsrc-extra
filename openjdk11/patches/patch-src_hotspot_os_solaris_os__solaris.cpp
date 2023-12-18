$NetBSD$

Match original caddr_t prototype as we still ship the original headers.

--- src/hotspot/os/solaris/os_solaris.cpp.orig	2023-12-18 11:45:57.461845536 +0000
+++ src/hotspot/os/solaris/os_solaris.cpp
@@ -169,7 +169,7 @@ extern "C" {
 
   static int lwp_cond_init(cond_t *cv, int scope, void *arg){ memset(cv, 0, sizeof(cond_t)); return 0; }
   static int lwp_cond_destroy(cond_t *cv)                   { return 0; }
-  int memcntl(void *, size_t, int, void *, int, int);
+  int memcntl(caddr_t, size_t, int, caddr_t, int, int);
   int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *, uint_t *);
 }
 
