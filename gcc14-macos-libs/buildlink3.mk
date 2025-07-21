# $NetBSD$

BUILDLINK_TREE+=	gcc14-libs

.if !defined(GCC14_LIBS_BUILDLINK3_MK)
GCC14_LIBS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc14-libs+=	gcc14-libs>=14.2.0
BUILDLINK_PKGSRCDIR.gcc14-libs=		../../extra/gcc14-macos-libs
BUILDLINK_DEPMETHOD.gcc14-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc14-libs}/gcc14
BUILDLINK_FILES.gcc14-libs=	# empty
BUILDLINK_AUTO_VARS.gcc14-libs=	no

# Use custom specs file to ensure we link against the GCC libraries from
# this package, as well as sanitising the default library search path.
SPECS_PKGSRC=		${WRAPPER_DIR}/specs.pkgsrc
WRAPPER_TARGETS+=	${SPECS_PKGSRC}

${SPECS_PKGSRC}:
	${SED} \
	    -e '/^#/d' \
	    -e 's,@LIBGCC_PREFIX@,${BUILDLINK_PREFIX.gcc14-libs}/gcc14/${MACHINE_GNU_PLATFORM},g' \
		< ${BUILDLINK_PKGSRCDIR.gcc14-libs}/files/specs.pkgsrc \
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

BUILDLINK_TREE+=	-gcc14-libs
