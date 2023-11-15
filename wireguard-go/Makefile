# $NetBSD$

DISTNAME=	wireguard-go-0.0.20220316
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=nshalman/}
GITHUB_TAG=	c8619d9e5497cf41e5c451dca83c58d9fd67eb5c

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://github.com/nshalman/wireguard-go
COMMENT=	Implementation of WireGuard in Go
LICENSE=	mit

# Support for 1.21 is in master but not this version.  Remove when updated.
GO_VERSION_REQD=	120

.include "go-modules.mk"

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/.gopath/bin/wireguard \
		${DESTDIR}${PREFIX}/bin/wireguard-go

.include "../../lang/go/go-module.mk"
.include "../../mk/bsd.pkg.mk"
