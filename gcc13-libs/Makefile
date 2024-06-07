# $NetBSD$

PKGNAME=	gcc13-libs-13.3.0
CATEGORIES=	extra lang
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection (GCC) support shared libraries
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

USE_TOOLS+=	pax

NO_BUILD=	yes

CHECK_SHLIBS=		no		# RPATH will find gcc13 libraries
CHECK_SSP_SUPPORTED=	no		# Clean CFLAGS removes -fstack*

BUILD_DEPENDS+=		gcc13-[0-9]*:../../extra/gcc13

INSTALLATION_DIRS+=	gcc13/${MACHINE_GNU_PLATFORM}/lib

LIBRARY_FILES=	${WRKDIR}/lib_files

# Exclude 32-bit libraries from 64-bit package, and vice versa.
.if ${MACHINE_ARCH} == "x86_64"
SKIP_ARCH_LIBS=		-e '/lib\/lib/d'
.else
SKIP_ARCH_LIBS=		-e '/lib\/amd64/d'
.endif

# Only include libraries that packages depend upon via REQUIRES.
${LIBRARY_FILES}:
	${PKG_INFO} -qL gcc13 | ${SED} -n				\
	    -e 's,^${PREFIX}/gcc13/,,'					\
	    ${SKIP_ARCH_LIBS}						\
	    -e '/gdb.py/d'						\
	    -e '/libatomic.so/p'					\
	    -e '/libgcc_s.so/p'						\
	    -e '/libgfortran.so/p'					\
	    -e '/libgomp.so/p'						\
	    -e '/libquadmath.so/p'					\
	    -e '/libstdc++.so/p'					\
		> ${LIBRARY_FILES}

do-install: ${LIBRARY_FILES}
	cd ${PREFIX}/gcc13 && ${PAX}					\
	    -rw ${DESTDIR}${PREFIX}/gcc13/${MACHINE_GNU_PLATFORM}	\
		< ${LIBRARY_FILES}

PRINT_PLIST_AWK+=	{ gsub(/${MACHINE_GNU_PLATFORM}/, "$${MACHINE_GNU_PLATFORM}"); }

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
