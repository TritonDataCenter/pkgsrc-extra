# $NetBSD$

DISTNAME=	google-authenticator-compat32-1.0
CATEGORIES=	security
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://pkgsrc.smartos.org/
COMMENT=	Google Authenticator 32-bit library for PAM 2FA
LICENSE=	apache-2.0

NO_CHECKSUM=	yes
CTF_SUPPORTED=	no	# Files already have CTF

DEPENDS+=	google-authenticator-[0-9]*:../../security/google-authenticator

ONLY_FOR_PLATFORM=	SunOS-*-x86_64

BUILD_DEFS+=	PACKAGES

#
# This package re-bundles the Google Authenticator PAM library from the 32-bit
# package set, currently this is the cleanest method I could come up with.
#
# The illumos NSS/PAM libraries currently only support 32-bit objects, so this
# package is required when using a 64-bit package set.
#
# We take advantage of pkg_add's -P override to install the latest i386 package
# into a chroot, extract the libraries we require from it, then bundle them up
# with RPATHs rewritten to find each other.
#
# Note that even with -P and -I (do not execute INSTALL scripts) in place,
# there are still some artefects created under our real LOCALBASE, due to
# @pkgdir not honouring -P.  This shouldn't cause any problems however.
#

GAUTH_LIB_DIR=		lib/security/i386
INSTALLATION_DIRS=	${GAUTH_LIB_DIR}
PKG_CHROOT=		${WRKSRC}/pkg

#
# The GCC library locations are hacky, but trying to calculate them using
# ${PKG_CC} as we normally would will find the libraries from the native set,
# not the 32-bit set.
#
GAUTH_LIBS+=	lib/security/pam_google_authenticator.so
GAUTH_LIBS+=	gcc*/i486-sun-solaris2.11/lib/libgcc_s.so.1

ELFEDIT_ARGS=	-e 'dyn:runpath ${PREFIX}/${GAUTH_LIB_DIR}'

do-build:
	${PKGSRC_SETENV} PKG_PATH=${PACKAGES:S/x86_64/i386/:S/tools/i386/}/All \
		${PKG_ADD_CMD} -P ${PKG_CHROOT} -I -m i386 'google-authenticator'
.for lib in ${GAUTH_LIBS}
	/usr/bin/elfedit ${ELFEDIT_ARGS} \
		${PKG_CHROOT}${PREFIX:S,/opt/tools,/opt/local,}/${lib}
.endfor

do-install:
.for lib in ${GAUTH_LIBS}
	${INSTALL_LIB} ${PKG_CHROOT}${PREFIX:S,/opt/tools,/opt/local,}/${lib} \
		${DESTDIR}${PREFIX}/${GAUTH_LIB_DIR}
.endfor

.include "../../mk/bsd.pkg.mk"
