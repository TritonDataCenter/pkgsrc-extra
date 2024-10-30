# $NetBSD$

BUILDLINK_TREE+=	gcc13-libs

.if !defined(GCC13_LIBS_BUILDLINK3_MK)
GCC13_LIBS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc13-libs+=	gcc13-libs>=13.2.0
BUILDLINK_PKGSRCDIR.gcc13-libs=		../../extra/gcc13-libs
BUILDLINK_DEPMETHOD.gcc13-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc13-libs}/gcc13
BUILDLINK_FILES.gcc13-libs=	# empty
BUILDLINK_AUTO_VARS.gcc13-libs=	no

# Use custom specs file to ensure we link against the GCC libraries from
# this package, as well as sanitising the default library search path.
SPECS_PKGSRC=		${WRAPPER_DIR}/specs.pkgsrc
WRAPPER_TARGETS+=	${SPECS_PKGSRC}

.if ${MACHINE_ARCH} == "x86_64"
LINK_ARCH_DEFAULT=	link_arch64
LINK_LIBGCC_DEFAULT=	link_libgcc_arch64
.else
LINK_ARCH_DEFAULT=	link_arch32
LINK_LIBGCC_DEFAULT=	link_libgcc_arch32
.endif

${SPECS_PKGSRC}:
	${SED} \
	    -e '/^#/d' \
	    -e 's,@LINK_ARCH_DEFAULT@,${LINK_ARCH_DEFAULT},g' \
	    -e 's,@LINK_LIBGCC_DEFAULT@,${LINK_LIBGCC_DEFAULT},g' \
	    -e 's,@LIBGCC_PREFIX@,${BUILDLINK_PREFIX.gcc13-libs}/gcc13/${MACHINE_GNU_PLATFORM},g' \
		< ${BUILDLINK_PKGSRCDIR.gcc13-libs}/files/specs.pkgsrc \
		> ${SPECS_PKGSRC}

_WRAP_EXTRA_ARGS.CC+=	-specs=${SPECS_PKGSRC}
_WRAP_EXTRA_ARGS.CXX+=	-specs=${SPECS_PKGSRC}
_WRAP_EXTRA_ARGS.FC+=	-specs=${SPECS_PKGSRC}
CWRAPPERS_APPEND.cc+=	-specs=${SPECS_PKGSRC}
CWRAPPERS_APPEND.cxx+=	-specs=${SPECS_PKGSRC}
CWRAPPERS_APPEND.f77+=	-specs=${SPECS_PKGSRC}

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc13-libs
