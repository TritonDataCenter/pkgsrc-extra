# $NetBSD$

BUILDLINK_TREE+=	openjdk21

.if !defined(OPENJDK21_BUILDLINK3_MK)
OPENJDK21_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.openjdk21+=	openjdk21>=0
BUILDLINK_PKGSRCDIR.openjdk21?=		../../extra/openjdk21

BUILDLINK_LIBDIRS.openjdk21+=		java/openjdk21/lib
BUILDLINK_LIBDIRS.openjdk21+=		java/openjdk21/lib/server
.endif

BUILDLINK_TREE+=	-openjdk21
