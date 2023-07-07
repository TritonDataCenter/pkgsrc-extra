# $NetBSD$

BUILDLINK_TREE+=	gcc13

.if !defined(GCC13_BUILDLINK3_MK)
GCC13_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc13+=	gcc13>=13.1.0
BUILDLINK_ABI_DEPENDS.gcc13+=	gcc13>=13.1.0
BUILDLINK_PKGSRCDIR.gcc13=	../../extra/gcc13
BUILDLINK_DEPMETHOD.gcc13?=	build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc13}/gcc13

BUILDLINK_FILES.gcc13=		# empty
BUILDLINK_AUTO_VARS.gcc13=	no

pkgbase := gcc13
.include "../../mk/pkg-build-options.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc13
