$NetBSD$

libassuan 3.x does not support ASSUAN_SYSTEM_PTH.

--- agent/gpg-agent.c.orig	2016-03-31 10:46:07.000000000 +0000
+++ agent/gpg-agent.c
@@ -309,8 +309,6 @@ static void check_own_socket (void);
 static int check_for_running_agent (int silent, int mode);
 
 /* Pth wrapper function definitions. */
-ASSUAN_SYSTEM_PTH_IMPL;
-
 #if GCRYPT_VERSION_NUMBER < 0x010600
 GCRY_THREAD_OPTION_PTH_IMPL;
 #if GCRY_THREAD_OPTION_VERSION < 1
@@ -663,7 +661,6 @@ main (int argc, char **argv )
   assuan_set_malloc_hooks (&malloc_hooks);
   assuan_set_assuan_log_prefix (log_get_prefix (NULL));
   assuan_set_gpg_err_source (GPG_ERR_SOURCE_DEFAULT);
-  assuan_set_system_hooks (ASSUAN_SYSTEM_PTH);
   assuan_sock_init ();
 
   setup_libgcrypt_logging ();
