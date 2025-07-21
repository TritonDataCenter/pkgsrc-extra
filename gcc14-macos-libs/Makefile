# $NetBSD$

PKGNAME=	gcc14-libs-14.2.0
CATEGORIES=	extra lang
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection (GCC) support shared libraries
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

USE_TOOLS+=	pax

NO_BUILD=	yes

CHECK_SSP_SUPPORTED=	no		# Clean CFLAGS removes -fstack*

BUILD_DEPENDS+=		gcc14-[0-9]*:../../extra/gcc14-macos

LIBRARY_FILES=	${WRKDIR}/lib_files

LIBPATH=	gcc14/${MACHINE_GNU_PLATFORM}/lib

INSTALLATION_DIRS+=	${LIBPATH}

# Only include libraries that packages depend upon via REQUIRES.
${LIBRARY_FILES}:
	${RUN} ${PKG_INFO} -qL gcc14 | ${SED} -n			\
	    -e 's,^${PREFIX}/gcc14/,,'					\
	    -e '/gdb.py/d'						\
	    -e '/\.dylib$$/p'						\
		> ${LIBRARY_FILES}

do-install: ${LIBRARY_FILES}
	${RUN} cd ${PREFIX}/gcc14 && ${PAX}				\
	    -rw ${DESTDIR}${PREFIX}/gcc14/${MACHINE_GNU_PLATFORM}	\
		< ${LIBRARY_FILES}
	${RUN} for f in ${DESTDIR}${PREFIX}/${LIBPATH}/*.dylib; do	\
		${TEST} -L $$f && continue;				\
		install_name_tool -id `${ECHO} $$f | sed -e 's,${DESTDIR},,'` $$f; \
	done
	${RUN} install_name_tool -change				\
		${PREFIX}/gcc14/lib/libquadmath.0.dylib			\
		${PREFIX}/${LIBPATH}/libquadmath.0.dylib		\
		${DESTDIR}${PREFIX}/${LIBPATH}/libgfortran.dylib

PRINT_PLIST_AWK+=	{ gsub(/${MACHINE_GNU_PLATFORM}/, "$${MACHINE_GNU_PLATFORM}"); }

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
