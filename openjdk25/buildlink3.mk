# $NetBSD$

BUILDLINK_TREE+=	openjdk25

.if !defined(OPENJDK25_BUILDLINK3_MK)
OPENJDK25_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.openjdk25+=	openjdk25>=0
BUILDLINK_PKGSRCDIR.openjdk25?=		../../extra/openjdk25

BUILDLINK_LIBDIRS.openjdk25+=		java/openjdk25/lib
BUILDLINK_LIBDIRS.openjdk25+=		java/openjdk25/lib/server
.endif

BUILDLINK_TREE+=	-openjdk25
