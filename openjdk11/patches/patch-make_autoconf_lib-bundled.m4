$NetBSD$

Ensure the correct zlib can be found.

--- make/autoconf/lib-bundled.m4.orig	2022-10-10 15:03:28.000000000 +0000
+++ make/autoconf/lib-bundled.m4
@@ -218,7 +218,7 @@ AC_DEFUN_ONCE([LIB_SETUP_ZLIB],
         LIBZ_CFLAGS="$LIBZ_CFLAGS -DHAVE_UNISTD_H"
     fi
   else
-    LIBZ_LIBS="-lz"
+    LIBZ_LIBS="@COMPILER_RPATH_FLAG@@BUILDLINK_PREFIX.zlib@/lib -L@BUILDLINK_PREFIX.zlib@/lib -lz"
   fi
 
   AC_SUBST(USE_EXTERNAL_LIBZ)
