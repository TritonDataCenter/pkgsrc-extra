# $NetBSD$

BUILDLINK_TREE+=	gcc12-libs

.if !defined(GCC12_LIBS_BUILDLINK3_MK)
GCC12_LIBS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc12-libs+=	gcc12-libs>=12.2.0
BUILDLINK_PKGSRCDIR.gcc12-libs=		../../extra/gcc12-libs
BUILDLINK_DEPMETHOD.gcc12-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc12-libs}/gcc12
BUILDLINK_FILES.gcc12-libs=	# empty
BUILDLINK_AUTO_VARS.gcc12-libs=	no

# Use custom specs file to ensure we link against the GCC libraries from
# this package, as well as sanitising the default library search path.
SPECS_PKGSRC=		${WRAPPER_DIR}/specs.pkgsrc
WRAPPER_TARGETS+=	${SPECS_PKGSRC}

${SPECS_PKGSRC}:
	${SED} -e \
	    's,@LIBGCC_PREFIX@,${BUILDLINK_PREFIX.gcc12-libs}/gcc12/${MACHINE_GNU_PLATFORM},g' \
	    < ${BUILDLINK_PKGSRCDIR.gcc12-libs}/files/specs.pkgsrc \
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

BUILDLINK_TREE+=	-gcc12-libs
