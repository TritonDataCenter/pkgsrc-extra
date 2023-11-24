# $NetBSD$

DISTNAME=	build-essential-1.5
CATEGORIES=	devel meta-pkgs
MASTER_SITES=	# empty

MAINTAINER=	jperkin@mnx.io
HOMEPAGE=	https://pkgsrc.smartos.org/
COMMENT=	Meta-package for essential build utilities

META_PACKAGE=	yes

# Going via tools helps pick up pkgconf vs pkg-config.
USE_TOOLS+=	pkg-config:run

.include "../../mk/compiler.mk"

.if ${_GCC_DEPENDS:Mgcc13*}
DEPENDS+=	${_GCC_DEPENDS}:../../extra/gcc13
.elif ${_GCC_DEPENDS:Mgcc12*}
DEPENDS+=	${_GCC_DEPENDS}:../../extra/gcc12
.endif

DEPENDS+=	autoconf-[0-9]*:../../devel/autoconf
DEPENDS+=	automake-[0-9]*:../../devel/automake
DEPENDS+=	binutils-[0-9]*:../../devel/binutils
DEPENDS+=	bison-[0-9]*:../../devel/bison
DEPENDS+=	git-base-[0-9]*:../../devel/git-base
DEPENDS+=	git-docs-[0-9]*:../../devel/git-docs
DEPENDS+=	gmake-[0-9]*:../../devel/gmake
DEPENDS+=	libtool-[0-9]*:../../devel/libtool
DEPENDS+=	m4-[0-9]*:../../devel/m4
DEPENDS+=	patch-[0-9]*:../../devel/patch

.include "../../mk/bsd.pkg.mk"
