$NetBSD$

Add ${PREFIX}/lib to the default library search path.  These changes are
removed by subst if USE_GCC_LOCALBASE_PREFIX == "no".

--- gcc/config/sol2.h.orig	2023-08-04 21:07:54.000000000 +0000
+++ gcc/config/sol2.h
@@ -95,22 +95,6 @@ along with GCC; see the file COPYING3.
        library.  */					\
     if (c_dialect_cxx ())				\
       {							\
-	switch (cxx_dialect)				\
-	  {						\
-	  case cxx98:					\
-	  case cxx11:					\
-	  case cxx14:					\
-	    /* C++11 and C++14 are based on C99.	\
-	       libstdc++ makes use of C99 features	\
-	       even for C++98.  */			\
-	    builtin_define ("__STDC_VERSION__=199901L");\
-	    break;					\
-							\
-	  default:					\
-	    /* C++17 is based on C11.  */		\
-	    builtin_define ("__STDC_VERSION__=201112L");\
-	    break;					\
-	  }						\
 	builtin_define ("_XOPEN_SOURCE=600");		\
 	builtin_define ("_LARGEFILE_SOURCE=1");		\
 	builtin_define ("_LARGEFILE64_SOURCE=1");	\
@@ -308,8 +292,9 @@ along with GCC; see the file COPYING3.
 #define LINK_ARCH32_SPEC_BASE \
   "%{YP,*} \
    %{R*} \
-   %{!YP,*:%{p|pg:-Y P,%R/usr/lib/libp%R/lib:%R/usr/lib} \
-	   %{!p:%{!pg:-Y P,%R/lib:%R/usr/lib}}}"
+   -R@PREFIX@/lib \
+   %{!YP,*:%{p|pg:-Y P,%R/usr/lib/libp%R/lib:%R/usr/lib:%R@PREFIX@/lib} \
+	   %{!p:%{!pg:-Y P,%R/lib:%R/usr/lib:%R@PREFIX@/lib}}}"
 
 #undef LINK_ARCH32_SPEC
 #define LINK_ARCH32_SPEC LINK_ARCH32_SPEC_BASE
@@ -320,8 +305,9 @@ along with GCC; see the file COPYING3.
 #define LINK_ARCH64_SPEC_BASE \
   "%{YP,*} \
    %{R*} \
-   %{!YP,*:%{p|pg:-Y P,%R/usr/lib/libp/" ARCH64_SUBDIR ":%R/lib/" ARCH64_SUBDIR ":%R/usr/lib/" ARCH64_SUBDIR "}	\
-	   %{!p:%{!pg:-Y P,%R/lib/" ARCH64_SUBDIR ":%R/usr/lib/" ARCH64_SUBDIR "}}}"
+   -R@PREFIX@/lib \
+   %{!YP,*:%{p|pg:-Y P,%R/usr/lib/libp/" ARCH64_SUBDIR ":%R/lib/" ARCH64_SUBDIR ":%R/usr/lib/" ARCH64_SUBDIR ":%R@PREFIX@/lib}	\
+	   %{!p:%{!pg:-Y P,%R/lib/" ARCH64_SUBDIR ":%R/usr/lib/" ARCH64_SUBDIR ":%R@PREFIX@/lib}}}"
 
 #undef LINK_ARCH64_SPEC
 #ifndef USE_GLD
