$NetBSD: patch-source3_utils_net__offlinejoin.c,v 1.1 2022/03/07 21:40:38 thor Exp $

Fix netapi header usage to follow othertools, preferring local paths.
Otherwise, <netapi.h> can be easily resolved to an instance from an
old samba install in the system.

--- source3/utils/net_offlinejoin.c.orig	2024-01-31 20:35:59.923273000 +0000
+++ source3/utils/net_offlinejoin.c
@@ -19,8 +19,8 @@
 
 #include "includes.h"
 #include "utils/net.h"
-#include <netapi.h>
-#include "netapi/netapi_net.h"
+#include "lib/netapi/netapi.h"
+#include "lib/netapi/netapi_net.h"
 #include "libcli/registry/util_reg.h"
 #include "libcli/security/dom_sid.h"
 #include "lib/cmdline/cmdline.h"
