# $NetBSD$

DISTNAME=	tailscale-1.64.2
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=nshalman/}
GITHUB_TAG=	v${PKGVERSION_NOREV}-sunos

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://tailscale.com/
COMMENT=	The easiest, most secure way to use WireGuard and 2FA
LICENSE=	modified-bsd

GO_VERSION_REQD=	122

GO_LDFLAGS=	-X tailscale.com/version.Long=${PKGVERSION_NOREV}
GO_LDFLAGS+=	-X tailscale.com/version.Short=${PKGVERSION_NOREV}
GO_LDFLAGS+=	-X tailscale.com/version.GitCommit=${GITHUB_TAG}

GO_BUILD_PATTERN=	-tags=ts_include_cli
GO_BUILD_PATTERN+=	-ldflags ${GO_LDFLAGS:Q}
GO_BUILD_PATTERN+=	./cmd/tailscaled

INSTALLATION_DIRS=	bin sbin

.include "go-modules.mk"

post-build:
	${RUN} /usr/bin/elfedit \
		-e "ehdr:ei_osabi ELFOSABI_SOLARIS" \
		-e "ehdr:ei_abiversion EAV_SUNW_CURRENT" \
		${WRKDIR}/.gopath/bin/tailscaled

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/.gopath/bin/tailscaled \
		${DESTDIR}${PREFIX}/bin/tailscale
	${INSTALL_PROGRAM} ${WRKDIR}/.gopath/bin/tailscaled \
		${DESTDIR}${PREFIX}/sbin/tailscaled

.include "../../lang/go/go-module.mk"
.include "../../mk/bsd.pkg.mk"
