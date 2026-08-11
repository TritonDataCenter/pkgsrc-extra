# $NetBSD$

DISTNAME=	clickhouse-26.7.1.1
CATEGORIES=	extra
MASTER_SITES=	${MASTER_SITE_GITHUB:=jperkin/}
GITHUB_PROJECT=	ClickHouse
GITHUB_TAG=	4698a33fd1b9c031198b77b13aa9e0b27e03dd2b

# One distfile per submodule, from its original repository.
DISTFILES=	${DEFAULT_DISTFILES}
.include "submodules.mk"

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://clickhouse.com/
COMMENT=	Real-time analytics database management system
LICENSE=	apache-2.0

WRKSRC=		${WRKDIR}/${GITHUB_PROJECT}-${GITHUB_TAG}

USE_LANGUAGES=	c c++
USE_TOOLS+=	bash cmake

CMAKE_GENERATOR=	ninja

.include "../../mk/bsd.prefs.mk"

# Must be DEPENDS rather than bl3 to avoid llvm interference.
PKGSRC_COMPILER=	clang
TOOL_DEPENDS+=		clang-[0-9]*:../../lang/clang

# The wrappers discard -w, which the build relies on to suppress
# third-party warnings that -Werror would otherwise fatalize.
CWRAPPERS_APPEND.cc+=	-Wno-everything
CWRAPPERS_APPEND.cxx+=	-Wno-everything

# StorageSystemLicenses.sh requires GNU find, grep, and xargs as the
# plain tool names.
TOOLS_PLATFORM.find=	${PREFIX}/bin/gfind
TOOLS_PLATFORM.grep=	${PREFIX}/bin/ggrep
TOOLS_PLATFORM.xargs=	${PREFIX}/bin/gxargs
USE_TOOLS+=		find grep xargs
TOOL_DEPENDS+=		findutils-[0-9]*:../../sysutils/findutils
TOOL_DEPENDS+=		grep-[0-9]*:../../textproc/grep

CHECK_PORTABILITY_SKIP+=	contrib/*/autogen.sh
CHECK_PORTABILITY_SKIP+=	contrib/*/post_process_dist.sh
CHECK_PORTABILITY_SKIP+=	contrib/*/testTimezones.sh

SSLDIR=		${PKG_SYSCONFBASE}/openssl
SSLCERTS=	${SSLDIR}/certs

CMAKE_CONFIGURE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_CONFIGURE_ARGS+=	-DOPENSSLDIR=${SSLDIR}
CMAKE_CONFIGURE_ARGS+=	-DCOMPILER_CACHE=disabled
CMAKE_CONFIGURE_ARGS+=	-DENABLE_LIBRARIES=OFF
CMAKE_CONFIGURE_ARGS+=	-DENABLE_RUST=OFF
CMAKE_CONFIGURE_ARGS+=	-DENABLE_TESTS=OFF
CMAKE_CONFIGURE_ARGS+=	-DPARALLEL_LINK_JOBS=1

CLICKHOUSE_USER?=		clickhouse
CLICKHOUSE_GROUP?=		clickhouse
PKG_GROUPS_VARS+=		CLICKHOUSE_GROUP
PKG_USERS_VARS+=		CLICKHOUSE_USER
PKG_GROUPS=			${CLICKHOUSE_GROUP}
PKG_USERS=			${CLICKHOUSE_USER}:${CLICKHOUSE_GROUP}
PKG_GECOS.${CLICKHOUSE_USER}=	ClickHouse database user
PKG_HOME.${CLICKHOUSE_USER}=	${CLICKHOUSE_DATADIR}

CLICKHOUSE_DATADIR=	${VARBASE}/lib/clickhouse
CLICKHOUSE_LOGDIR=	${VARBASE}/log/clickhouse
BUILD_DEFS+=		VARBASE

FILES_SUBST+=		CLICKHOUSE_USER=${CLICKHOUSE_USER}
FILES_SUBST+=		CLICKHOUSE_GROUP=${CLICKHOUSE_GROUP}
FILES_SUBST+=		CLICKHOUSE_DATADIR=${CLICKHOUSE_DATADIR}

OWN_DIRS_PERMS+=	${CLICKHOUSE_DATADIR} ${CLICKHOUSE_USER} ${CLICKHOUSE_GROUP} 0750
OWN_DIRS_PERMS+=	${CLICKHOUSE_LOGDIR} ${CLICKHOUSE_USER} ${CLICKHOUSE_GROUP} 0750

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_MESSAGE.paths=	Setting pkgsrc paths in defaults
SUBST_FILES.paths=	src/Access/AccessControl.cpp
SUBST_FILES.paths+=	src/Common/Config/getClientConfigPath.cpp
SUBST_FILES.paths+=	src/Common/Config/getLocalConfigPath.cpp
SUBST_FILES.paths+=	programs/disks/DisksApp.cpp
SUBST_FILES.paths+=	programs/docker-init/docker-init.cpp
SUBST_SED.paths=	-e 's,/etc/clickhouse-,${PKG_SYSCONFDIR}/clickhouse-,g'

SUBST_CLASSES+=		certs
SUBST_STAGE.certs=	pre-configure
SUBST_MESSAGE.certs=	Setting pkgsrc CA bundle path
SUBST_FILES.certs=	base/poco/NetSSL_OpenSSL/src/Context.cpp
SUBST_SED.certs=	-e 's,/etc/pki/tls/certs/ca-bundle.crt,${SSLCERTS}/ca-certificates.crt,'

MAKE_DIRS+=	${PKG_SYSCONFDIR}/clickhouse-client
MAKE_DIRS+=	${PKG_SYSCONFDIR}/clickhouse-server

CONF_FILES+=	share/examples/clickhouse/clickhouse-client/config.xml \
		${PKG_SYSCONFDIR}/clickhouse-client/config.xml
CONF_FILES+=	share/examples/clickhouse/clickhouse-server/config.xml \
		${PKG_SYSCONFDIR}/clickhouse-server/config.xml
CONF_FILES+=	share/examples/clickhouse/clickhouse-server/users.xml \
		${PKG_SYSCONFDIR}/clickhouse-server/users.xml

post-extract:
.for sm_path sm_dir in ${SUBMODULES}
	${RMDIR} ${WRKSRC}/${sm_path} && \
		${MV} ${WRKDIR}/${sm_dir} ${WRKSRC}/${sm_path}
.endfor
# The llvm-project fork's LLVM 22 merge dropped this header but kept the
# illumos dispatch that includes it.
	${CP} ${FILESDIR}/llvm-locale-musl.h \
		${WRKSRC}/contrib/llvm-project/libcxx/include/__locale_dir/locale_base_api/musl.h

post-install:
	${RM} -rf ${DESTDIR}${PREFIX}/cmake
	# Dummy "not enabled" stubs installed when rust is disabled.
	${RM} -f ${DESTDIR}${PREFIX}/bin/chdig \
		${DESTDIR}${PREFIX}/bin/clickhouse-chdig
	# Empty debug-info placeholder installed for upstream's nfpm packaging.
	${RM} -rf ${DESTDIR}${PREFIX}/lib/debug

.include "../../devel/cmake/build.mk"
.include "../../mk/bsd.pkg.mk"
