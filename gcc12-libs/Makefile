# $NetBSD$

PKGNAME=	gcc12-libs-12.2.0
CATEGORIES=	extra lang
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection (GCC) support shared libraries
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

USE_TOOLS+=	pax

NO_BUILD=	yes

CHECK_SHLIBS=			no		# RPATH will find gcc12 libraries
CHECK_SSP_SUPPORTED=		no		# Clean CFLAGS removes -fstack*

BUILD_DEPENDS+=		gcc12-[0-9]*:../../extra/gcc12

INSTALLATION_DIRS+=	gcc12/${MACHINE_GNU_PLATFORM}/lib

LIBRARY_FILES=	${WRKDIR}/lib_files
OBJECT_FILES=	${WRKDIR}/obj_files

${LIBRARY_FILES}:
	${PKG_INFO} -qL gcc12 | ${SED} -n				\
		-e's,^${PREFIX}/gcc12/,,'				\
		-e'/libexec\//d'					\
		-e'/libgij/d;/libgcj/d;/libjvm/d;/libgo\./d'		\
		-e'/libcc1plugin/d;/libcp1plugin/d;'			\
		-e'/lib.*\.so/p' > ${LIBRARY_FILES}

${OBJECT_FILES}:
	${PKG_INFO} -qL gcc12 | ${SED} -n				\
		-e 's,^${PREFIX}/gcc12/,,'				\
		-e '/\.o/p'						\
		-e '/libgcc\.a/p'					\
		-e '/libssp_nonshared\.a/p' > ${OBJECT_FILES}

do-install: ${LIBRARY_FILES} ${OBJECT_FILES}
	cd ${PREFIX}/gcc12 && ${PAX} \
		-rw ${DESTDIR}${PREFIX}/gcc12/${MACHINE_GNU_PLATFORM} \
		< ${LIBRARY_FILES}
	cd ${PREFIX}/gcc12 && ${PAX} \
		-r -s ',gcc/${MACHINE_GNU_PLATFORM}/${PKGVERSION_NOREV}/,,' \
		-w ${DESTDIR}${PREFIX}/gcc12/${MACHINE_GNU_PLATFORM} \
		< ${OBJECT_FILES}

PRINT_PLIST_AWK+=	{ gsub(/${MACHINE_GNU_PLATFORM}/, "$${MACHINE_GNU_PLATFORM}"); }

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
