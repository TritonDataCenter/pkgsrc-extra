# $NetBSD: Makefile,v 1.70 2017/08/24 20:03:38 adam Exp $
#
# Stripped down, modified version of gnupg20.  With the introduction of
# libassuan 3.x into pkgsrc, gpg-agent no longer builds.  Thus, until netpgp
# is finally updated to handle newer GPG keys, the solution is to run an agent
# from an older gnupg20 package, while signing packages with this version.
#

DISTNAME=	gnupg-2.0.31
PKGNAME=	${DISTNAME:S/gnupg/gnupg20/}
CATEGORIES=	security
MASTER_SITES=	ftp://ftp.gnupg.org/gcrypt/gnupg/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.gnupg.org/
COMMENT=	GnuPG with OpenPGP and S/MIME capabilities
LICENSE=	gnu-gpl-v3

INFO_FILES=		yes
USE_LIBTOOL=		yes
USE_PKGLOCALEDIR=	yes
USE_TOOLS+=		gmake
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--sharedstatedir=${VARBASE}
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}
CONFIGURE_ARGS+=	--with-pinentry-pgm=${PREFIX}/bin/pinentry
CONFIGURE_ARGS+=	--disable-gpgsm
CONFIGURE_ARGS+=	--disable-agent
CONFIGURE_ARGS+=	--disable-scdaemon
CONFIGURE_ARGS+=	--disable-tools
CONFIGURE_ARGS+=	--disable-doc
CONFIGURE_ARGS+=	--disable-bzip2
CONFIGURE_ARGS+=	--disable-ldap
CONFIGURE_ARGS+=	--disable-nls

.include "../../mk/bsd.prefs.mk"

# Sometimes wrong include file gets detected, e.g. for Clang
.if defined(OSX_SDK_PATH) && exists(${OSX_SDK_PATH:Q}/usr/include/stdint.h)
CONFIGURE_ENV+=		gl_cv_absolute_stdint_h=${OSX_SDK_PATH:Q}/usr/include/stdint.h
.elif exists(/usr/include/stdint.h)
CONFIGURE_ENV+=		gl_cv_absolute_stdint_h=/usr/include/stdint.h
.endif

TEST_TARGET=		check

DEPENDS+=	pinentry-[0-9]*:../../security/pinentry

.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/pth/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/readline.buildlink3.mk"
.include "../../security/libassuan2/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../security/libgpg-error/buildlink3.mk"
.include "../../security/libksba/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
