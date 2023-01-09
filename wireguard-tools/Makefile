# $NetBSD$

DISTNAME=	wireguard-tools-1.0.20210914
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=nshalman/}
GITHUB_TAG=	8588ad10c513e50f2b051a4c48ffe33af562a9d5

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://github.com/nshalman/wireguard-tools
COMMENT=	Tools for configuring WireGuard
LICENSE=	gnu-gpl-v2

DEPENDS+=	wireguard-go-[0-9]*:../../extra/wireguard-go

USE_TOOLS+=	bash:run gmake

BUILD_DIRS=	src
MAKE_FLAGS+=	MANDIR=${PREFIX}/${PKGMANDIR}
MAKE_FLAGS+=	WITH_WGQUICK=yes

REPLACE_BASH+=	src/wg-quick/darwin.bash
REPLACE_BASH+=	src/wg-quick/sunos.bash

.include "../../mk/bsd.pkg.mk"
