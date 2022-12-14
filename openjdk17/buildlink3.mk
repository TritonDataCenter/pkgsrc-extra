# $NetBSD$

BUILDLINK_TREE+=	openjdk17

.if !defined(OPENJDK17_BUILDLINK3_MK)
OPENJDK17_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.openjdk17+=	openjdk17>=0
BUILDLINK_PKGSRCDIR.openjdk17?=		../../extra/openjdk17

BUILDLINK_LIBDIRS.openjdk17+=		java/openjdk17/lib
BUILDLINK_LIBDIRS.openjdk17+=		java/openjdk17/lib/server
.endif

BUILDLINK_TREE+=	-openjdk17
