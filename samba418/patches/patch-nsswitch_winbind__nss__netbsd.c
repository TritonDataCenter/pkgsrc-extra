$NetBSD: patch-nsswitch_winbind__nss__netbsd.c,v 1.2 2020/07/21 18:42:25 christos Exp $

Syntax error fix.
Add primary group support

--- nsswitch/winbind_nss_netbsd.c.orig	2024-01-31 20:35:59.875271800 +0000
+++ nsswitch/winbind_nss_netbsd.c
@@ -176,6 +176,7 @@ netbsdwinbind_getgroupmembership(void *n
 {
 	int		*result	= va_arg(ap, int *);
 	const char 	*uname	= va_arg(ap, const char *);
+	gid_t		 agroup	= va_arg(ap, gid_t);
 	gid_t		*groups	= va_arg(ap, gid_t *);
 	int		 maxgrp	= va_arg(ap, int);
 	int		*groupc	= va_arg(ap, int *);
@@ -189,6 +190,13 @@ netbsdwinbind_getgroupmembership(void *n
 	gid_t	*wblistv;
 	int	wblistc, i, isdup, dupc;
 
+	/* add the primary group */
+	if (*groupc < maxgrp)
+		groups[*groupc] = agroup;
+	else
+		*result = -1;
+	(*groupc)++;
+
 	strncpy(request.data.username, uname,
 				sizeof(request.data.username) - 1);
 	i = winbindd_request_response(NULL, WINBINDD_GETGROUPS,
