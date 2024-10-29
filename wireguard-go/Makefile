# $NetBSD$

DISTNAME=	wireguard-go-0.0.20230223
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=nshalman/}
GITHUB_TAG=	15692aa1ee10a9d35871afd3e60687be9217d73c

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://github.com/nshalman/wireguard-go
COMMENT=	Implementation of WireGuard in Go
LICENSE=	mit

# imports gvisor.dev/gvisor/pkg/gohacks: build constraints exclude all Go files
GO_VERSION_REQD=	120

.include "go-modules.mk"

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/.gopath/bin/wireguard \
		${DESTDIR}${PREFIX}/bin/wireguard-go

.include "../../lang/go/go-module.mk"
.include "../../mk/bsd.pkg.mk"
