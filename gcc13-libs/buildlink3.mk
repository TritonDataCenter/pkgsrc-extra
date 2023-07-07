# $NetBSD$

BUILDLINK_TREE+=	gcc13-libs

.if !defined(GCC13_LIBS_BUILDLINK3_MK)
GCC13_LIBS_BUILDLINK3_MK:=

.if ${USE_PKGSRC_GCC_RUNTIME:U:tl} == yes
BUILDLINK_API_DEPENDS.gcc13-libs+=	gcc13-libs>=13.1.0
.else
BUILDLINK_API_DEPENDS.gcc13-libs+=	gcc13>=13.1.0
.endif
BUILDLINK_PKGSRCDIR.gcc13-libs=		../../extra/gcc13-libs
BUILDLINK_DEPMETHOD.gcc13-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc13-libs}/gcc13

BUILDLINK_FILES.gcc13-libs=	# empty
BUILDLINK_AUTO_VARS.gcc13-libs=	no

.if ${USE_PKGSRC_GCC_RUNTIME:U:tl} == yes
# Use custom specs file to ensure we link against pkgsrc libraries.
SPECS_LIBGCC=		${WRAPPER_DIR}/specs.libgcc
WRAPPER_TARGETS+=	${SPECS_LIBGCC}

${SPECS_LIBGCC}:
	@${ECHO} "*link_libgcc:" >${SPECS_LIBGCC}
	@${ECHO} "%D ${LINKER_RPATH_FLAG}${BUILDLINK_PREFIX.gcc13-libs}/gcc13/${MACHINE_GNU_PLATFORM}/lib/%M" >>${SPECS_LIBGCC}

_WRAP_EXTRA_ARGS.CC+=	-specs=${SPECS_LIBGCC}
_WRAP_EXTRA_ARGS.CXX+=	-specs=${SPECS_LIBGCC}
_WRAP_EXTRA_ARGS.FC+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.cc+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.cxx+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.f77+=	-specs=${SPECS_LIBGCC}
.endif

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc13-libs
