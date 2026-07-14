$NetBSD$

Adjust the TGZ layout for pkgsrc: install the backup agent under
lib/foundationdb rather than usr/lib, and do not install the
configuration file or empty data/log/etc directories; the example
configuration and runtime directories are handled by the package
(CONF_FILES, OWN_DIRS).

--- cmake/InstallLayout.cmake.orig	2026-07-13 00:00:00.000000000 +0000
+++ cmake/InstallLayout.cmake
@@ -98,11 +98,11 @@
 install_destinations(TGZ
   BIN bin
   SBIN sbin
   LIB lib
   FDBMONITOR sbin
-  BACKUPAGENT usr/lib/foundationdb
+  BACKUPAGENT lib/foundationdb
   INCLUDE include
   ETC etc/foundationdb
   LOG log/foundationdb
   DATA lib/foundationdb)
 copy_install_destinations(TGZ VERSIONED PREFIX "usr/lib/foundationdb-${FDB_VERSION}${FDB_BUILDTIME_STRING}/")
@@ -270,9 +270,6 @@
 set(CPACK_RPM_SERVER-VERSIONED_PRE_UNINSTALL_SCRIPT_FILE   ${CMAKE_BINARY_DIR}/packaging/multiversion/server/prerm)

 file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/packaging/emptydir")
-fdb_install(DIRECTORY "${CMAKE_BINARY_DIR}/packaging/emptydir/" DESTINATION data COMPONENT server)
-fdb_install(DIRECTORY "${CMAKE_BINARY_DIR}/packaging/emptydir/" DESTINATION log COMPONENT server)
-fdb_install(DIRECTORY "${CMAKE_BINARY_DIR}/packaging/emptydir/" DESTINATION etc COMPONENT clients)

 set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION
   "/usr/sbin"
@@ -364,9 +361,6 @@
 set(CLUSTER_DESCRIPTION2 ${description2} CACHE STRING "Cluster description")

 if(NOT WIN32)
-  fdb_install(FILES ${CMAKE_SOURCE_DIR}/packaging/foundationdb.conf
-    DESTINATION etc
-    COMPONENT server)
   install(FILES ${CMAKE_SOURCE_DIR}/packaging/make_public.py
     DESTINATION "usr/lib/foundationdb"
     COMPONENT server-deb)
