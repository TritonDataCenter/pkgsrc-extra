# $NetBSD$
#
# This is a GCC 13.x package specific to SmartOS:
#
#   - The GITHUB_TAG is the last commit to the ooce-13_3_0 branch prior to the
#     OmniOS-specific library paths commit (which we do not want).
#   - Some patches from the SmartOS "miscfix" branch are integrated.
#   - Sections for non-SunOS are removed for clarity.
#   - Every modification from the stock build should be clearly documented.
#

DISTNAME=	gcc13-13.3.0
CATEGORIES=	extra lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=omniosorg/}
GITHUB_PROJECT=	gcc
GITHUB_TAG=	37558d7e1fe0263ed5202ab9074bc0bb00f2155a

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection (GCC) - 13.x Release Series
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

USE_LANGUAGES=	c99 c++
USE_TOOLS+=	flex gmake m4 makeinfo perl sed:run tar:build

DEPENDS+=	binutils-[0-9]*:../../devel/binutils

GNU_CONFIGURE=		yes
GNU_CONFIGURE_STRICT=	no

#
# Perform the build outside of ${WRKSRC}
#
WRKSRC=			${WRKDIR}/gcc-${GITHUB_TAG}
OBJDIR=			../build
CONFIGURE_DIRS=		${OBJDIR}
CONFIGURE_SCRIPT=	../gcc-${GITHUB_TAG}/configure

GCC_PREFIX=		${PREFIX}/${PKGBASE}
GNU_CONFIGURE_PREFIX=	${GCC_PREFIX}

SUBST_CLASSES+=		vars
SUBST_STAGE.vars=	pre-configure
SUBST_FILES.vars=	gcc/Makefile.in
SUBST_VARS.vars=	MACHINE_GNU_PLATFORM

.include "../../mk/bsd.prefs.mk"

#
# Usually we want GCC to default to searching PREFIX for headers/libraries
# but sometimes, specifically in the tools build, we can't do that as then libs
# will leak from there into the non-tools builds (e.g. libiconv).
#
# Headers are handled by the --with-local-prefix configure argument, libraries by
# a patch to gcc/config/sol2.h.  When not using PREFIX the patch needs to be
# undone.
#
SUBST_CLASSES+=		libpath
SUBST_STAGE.libpath=	pre-configure
SUBST_FILES.libpath=	gcc/config/sol2.h
SUBST_NOOP_OK.libpath=	yes

.if ${USE_GCC_LOCALBASE_PREFIX:Uno:tl} == "yes"
SUBST_VARS.libpath=	PREFIX
CONFIGURE_ARGS+=	--with-local-prefix=${PREFIX:Q}
.else
CONFIGURE_ARGS+=	--with-local-prefix=${GCC_PREFIX:Q}
SUBST_SED.libpath+=	-e '/-R@PREFIX@/d'
SUBST_SED.libpath+=	-e 's/:%R@PREFIX@[^}]*//'
.endif

#
# Try to ensure a clean build where possible, unaffected by our general
# compiler flags.
#
CLEAN_GCC_CFLAGS=	-pipe -g -O2
CONFIGURE_ENV+=		STAGE1_CFLAGS=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		STAGE1_LDFLAGS=
CONFIGURE_ENV+=		CFLAGS_FOR_TARGET=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		LDFLAGS_FOR_TARGET=

CONFIGURE_ARGS+=	--enable-languages="c,c++,fortran,objc,lto"
CONFIGURE_ARGS+=	--enable-__cxa_atexit
CONFIGURE_ARGS+=	--enable-initfini-array
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--disable-libitm
CONFIGURE_ARGS+=	--with-gnu-as --with-as=${PREFIX}/bin/gas
CONFIGURE_ARGS+=	--without-gnu-ld --with-ld=/bin/ld
CONFIGURE_ARGS+=	--with-zstd=no

# If the bootstrap compiler version is identical to the one we are building
# then disabling the full three-stage bootstrap saves a lot of time.
#
# XXX: Unfortunately this fails the toxic library check, somehow libiconv
# from the bootstrap prefix is leaking into the final binaries.  This must be
# resolved before this can be enabled.
#
#.include "../../mk/compiler.mk"
#
#.if ${DISTNAME:M*${_GCC_VERSION:Uundefined}}
#CONFIGURE_ARGS+=	--disable-bootstrap
#.endif

#
# Disable --as-needed as it pulls in libgcc_s as a dependency into libstdc++
#
MAKE_ENV+=		gcc_cv_ld_as_needed=no

UNLIMIT_RESOURCES+=	datasize
UNLIMIT_RESOURCES+=	stacksize

FILES_SUBST+=		MACHINE_GNU_PLATFORM=${MACHINE_GNU_PLATFORM}

PRINT_PLIST_AWK+=	{ gsub(/${MACHINE_GNU_PLATFORM}/, "$${MACHINE_GNU_PLATFORM}"); }
PRINT_PLIST_AWK+=	{ gsub(/${PKGBASE}/, "$${PKGBASE}"); }

CHECK_PORTABILITY_SKIP+=	contrib/*
CHECK_SSP_SUPPORTED=		no		# Clean CFLAGS removes -fstack*
CTF_FILES_SKIP+=		*/gengtype	# Causes ctfconvert to hang

INFO_FILES=		yes

pre-configure:
	${RUN} cd ${WRKSRC} && ${MKDIR} ${OBJDIR}

TEST_TARGET=	-j ${MAKE_JOBS} -k check
TEST_DEPENDS+=	dejagnu-[0-9]*:../../devel/dejagnu

post-test:
	${RUN} cd ${WRKSRC} && cd ${OBJDIR} &&		\
	${SHELL} ${WRKSRC}/contrib/test_summary >${WRKDIR}/test_summary.log
	${INFO_MSG} "Test summary are available in ${WRKDIR}/test_summary.log"

post-install:
	${TEST} -f ${DESTDIR}${GCC_PREFIX}/bin/cc || \
		( cd ${DESTDIR}${GCC_PREFIX}/bin ; ${LN} -f gcc cc )

.include "../../devel/gmp/inplace.mk"
.include "../../math/mpcomplex/inplace.mk"
.include "../../math/mpfr/inplace.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
