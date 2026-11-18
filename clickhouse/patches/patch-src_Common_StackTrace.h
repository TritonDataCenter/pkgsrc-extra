commit ce835522b203c943a482bf89b888cf31024e6dd4
Author: Josh Carp <jm.carp@gmail.com>
Date:   Mon Aug 31 15:51:58 2026 +0000

    illumos: misc portability fixes.
    
    * Include termios.h in openpty.h. Under linux and darwin, ioctl.h
      provides `winsize`. Under illumos, it doesn't. For portability,
      explicitly include termios.h.
    * Fix macro pollution in StackTrace.h. Under illumos, regset.h defines a
      set of unprefixed gregset_t index macros (ERR, FS, etc.). ClickHouse
      only uses the analogous prefixed macros (REG_ERR, REG_FS, etc.), so we
      conditionally undef the conflicting macros.
    * Fix illumos-specific double/float cast errors in FPEnvironment, so
      that we don't widen or truncate inappropriately.
    * Set `-z rescan-now` on illumos so that we don't have to manage
      dependencies in DEPENDS.
    
    Part of #23777.

diff --git a/src/Common/StackTrace.h b/src/Common/StackTrace.h
index a12733b0275..01a07ac7af6 100644
--- src/Common/StackTrace.h
+++ src/Common/StackTrace.h
@@ -29,6 +29,14 @@
 #   define _XOPEN_SOURCE 700
 #endif
 #include <ucontext.h>
+
+#if defined(OS_SUNOS)
+/** illumos regset.h includes unprefixed macros for i386 gregset_t indices. These macros aren't used
+  * in ClickHouse, and conflict with `ProgressOption::ERR` and the `FS` namespace.
+  */
+#undef ERR
+#undef FS
+#endif
 #endif
 
 /** The stack trace of the throw that created an exception, recorded inside the `std::exception`
