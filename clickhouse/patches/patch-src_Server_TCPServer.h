$NetBSD$

illumos returns ENOTCONN for shutdown(SHUT_RD) on a listening socket, as
Darwin does. The uncaught exception aborts clickhouse-keeper on SIGTERM and
cuts short the clickhouse-server shutdown handler.

--- src/Server/TCPServer.h
+++ src/Server/TCPServer.h
@@ -44,8 +44,8 @@
         if (!is_open)
             return;
 
-        // FIXME: On darwin calling shutdown(SHUT_RD) on the socket blocked in accept() leads to ENOTCONN
-#ifndef OS_DARWIN
+        // FIXME: On darwin and illumos calling shutdown(SHUT_RD) on the socket blocked in accept() leads to ENOTCONN
+#if !defined(OS_DARWIN) && !defined(OS_SUNOS)
         // Shutdown the listen socket before stopping tcp server to avoid 2.5second delay
         socket.shutdownReceive();
 #endif
