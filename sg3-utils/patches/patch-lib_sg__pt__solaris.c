$NetBSD$

Fix build.

--- lib/sg_pt_solaris.c.orig	2026-06-08 16:02:16.155704474 +0000
+++ lib/sg_pt_solaris.c
@@ -32,6 +32,7 @@
 
 #include "sg_pt.h"
 #include "sg_lib.h"
+#include "sg_pr2serr.h"
 
 
 #define DEF_TIMEOUT 60       /* 60 seconds */
