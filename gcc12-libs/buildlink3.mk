# $NetBSD$

BUILDLINK_TREE+=	gcc12-libs

.if !defined(GCC12_LIBS_BUILDLINK3_MK)
GCC12_LIBS_BUILDLINK3_MK:=

.if ${USE_PKGSRC_GCC_RUNTIME:U:tl} == yes
BUILDLINK_API_DEPENDS.gcc12-libs+=	gcc12-libs>=12.2.0
.else
BUILDLINK_API_DEPENDS.gcc12-libs+=	gcc12>=12.2.0
.endif
BUILDLINK_PKGSRCDIR.gcc12-libs=		../../extra/gcc12-libs
BUILDLINK_DEPMETHOD.gcc12-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc12-libs}/gcc12

BUILDLINK_FILES.gcc12-libs=	# empty
BUILDLINK_AUTO_VARS.gcc12-libs=	no

.if ${USE_PKGSRC_GCC_RUNTIME:U:tl} == yes
# Use custom specs file to ensure we link against pkgsrc libraries.
SPECS_LIBGCC=		${WRAPPER_DIR}/specs.libgcc
WRAPPER_TARGETS+=	${SPECS_LIBGCC}

${SPECS_LIBGCC}:
	@${ECHO} "*link_libgcc:" >${SPECS_LIBGCC}
	@${ECHO} "%D ${LINKER_RPATH_FLAG}${BUILDLINK_PREFIX.gcc12-libs}/gcc12/${MACHINE_GNU_PLATFORM}/lib/%M" >>${SPECS_LIBGCC}

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

BUILDLINK_TREE+=	-gcc12-libs
