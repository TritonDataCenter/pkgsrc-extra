# $NetBSD$

DISTNAME=	foundationdb-7.3.78
CATEGORIES=	extra
MASTER_SITES=	${MASTER_SITE_GITHUB:=jperkin/}
GITHUB_PROJECT=	foundationdb
GITHUB_TAG=	ba5229f3c2a3ace8f11e4839f2e60373302301b7

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://github.com/jperkin/foundationdb
COMMENT=	Distributed, transactional, key-value store
LICENSE=	apache-2.0

BOOST_DISTFILE=			boost_1_78_0.tar.bz2
SITES.${BOOST_DISTFILE}=	https://archives.boost.io/release/1.78.0/source/
TOML11_DISTFILE=		toml11-3.4.0.tar.gz
SITES.${TOML11_DISTFILE}=	-https://github.com/ToruNiina/toml11/archive/v3.4.0.tar.gz
MSGPACK_DISTFILE=		msgpack-3.3.0.tar.gz
SITES.${MSGPACK_DISTFILE}=	https://github.com/msgpack/msgpack-c/releases/download/cpp-3.3.0/

DISTFILES=	${DEFAULT_DISTFILES} ${BOOST_DISTFILE} ${TOML11_DISTFILE} ${MSGPACK_DISTFILE}
EXTRACT_ONLY=	${DEFAULT_DISTFILES}

WRKSRC=		${WRKDIR}/${GITHUB_PROJECT}-${GITHUB_TAG}

USE_LANGUAGES=	c c++
USE_TOOLS+=	cmake

TOOL_DEPENDS+=	git-base-[0-9]*:../../devel/git-base

CMAKE_GENERATOR=	ninja

CMAKE_CONFIGURE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_CONFIGURE_ARGS+=	-DSSD_ROCKSDB_EXPERIMENTAL=OFF
CMAKE_CONFIGURE_ARGS+=	-DBUILD_DOCUMENTATION=OFF
CMAKE_CONFIGURE_ARGS+=	-DGENERATE_DEBUG_PACKAGES=ON
CMAKE_CONFIGURE_ARGS+=	-DBUILD_JAVA_BINDING=OFF
CMAKE_CONFIGURE_ARGS+=	-DENABLE_SIMULATION_TESTS=ON

BUILD_TARGET=	fdbserver fdbcli fdbbackup fdbmonitor fdb_c
TEST_TARGET=	test

PYTHON_FOR_BUILD_ONLY=	tool

FDB_USER?=		foundationdb
FDB_GROUP?=		foundationdb
PKG_GROUPS_VARS+=	FDB_GROUP
PKG_USERS_VARS+=	FDB_USER
PKG_GROUPS=		${FDB_GROUP}
PKG_USERS=		${FDB_USER}:${FDB_GROUP}
PKG_GECOS.${FDB_USER}=	FoundationDB database user
PKG_HOME.${FDB_USER}=	${FDB_DATADIR}

FDB_DATADIR=		${VARBASE}/lib/foundationdb
FDB_LOGDIR=		${VARBASE}/log/foundationdb
BUILD_DEFS+=		VARBASE

FILES_SUBST+=		FDB_USER=${FDB_USER} FDB_GROUP=${FDB_GROUP}
FILES_SUBST+=		FDB_DATADIR=${FDB_DATADIR}

PKG_SYSCONFSUBDIR=	foundationdb
EGDIR=			${PREFIX}/share/examples/foundationdb
CONF_FILES=		${EGDIR}/foundationdb.conf \
			${PKG_SYSCONFDIR}/foundationdb.conf
CONF_FILES_PERMS+=	${EGDIR}/fdb.cluster \
			${PKG_SYSCONFDIR}/fdb.cluster \
			${FDB_USER} ${FDB_GROUP} 0664
OWN_DIRS_PERMS+=	${FDB_DATADIR} ${FDB_USER} ${FDB_GROUP} 0750
OWN_DIRS_PERMS+=	${FDB_LOGDIR} ${FDB_USER} ${FDB_GROUP} 0750

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_MESSAGE.paths=	Setting pkgsrc paths in defaults
SUBST_FILES.paths=	flow/Platform.actor.cpp packaging/foundationdb.conf
SUBST_SED.paths=	-e 's,/usr/local/etc/foundationdb,${PKG_SYSCONFDIR},g'
SUBST_SED.paths+=	-e 's,/etc/foundationdb,${PKG_SYSCONFDIR},g'
SUBST_SED.paths+=	-e 's,/usr/sbin/fdbserver,${PREFIX}/sbin/fdbserver,g'
SUBST_SED.paths+=	-e 's,/usr/lib/foundationdb,${PREFIX}/lib/foundationdb,g'
SUBST_SED.paths+=	-e 's,/var/lib/foundationdb,${FDB_DATADIR},g'
SUBST_SED.paths+=	-e 's,/var/log/foundationdb,${FDB_LOGDIR},g'
SUBST_SED.paths+=	-e 's,^user = foundationdb$$,user = ${FDB_USER},'
SUBST_SED.paths+=	-e 's,^group = foundationdb$$,group = ${FDB_GROUP},'

post-configure:
	${MKDIR} ${WRKSRC}/${CMAKE_BUILD_DIR}/boost_targetProject-prefix/src
	${CP} ${DISTDIR}/${BOOST_DISTFILE} \
		${WRKSRC}/${CMAKE_BUILD_DIR}/boost_targetProject-prefix/src/
	${MKDIR} ${WRKSRC}/${CMAKE_BUILD_DIR}/toml11Project-prefix/src
	${CP} ${DISTDIR}/${TOML11_DISTFILE} \
		${WRKSRC}/${CMAKE_BUILD_DIR}/toml11Project-prefix/src/v3.4.0.tar.gz
	${MKDIR} ${WRKSRC}/${CMAKE_BUILD_DIR}/msgpackProject-prefix/src
	${CP} ${DISTDIR}/${MSGPACK_DISTFILE} \
		${WRKSRC}/${CMAKE_BUILD_DIR}/msgpackProject-prefix/src/

do-install:
.for component in clients-tgz server-tgz
	cd ${WRKSRC} && cmake --install ${CMAKE_BUILD_DIR} \
		--component ${component} --prefix ${DESTDIR}${PREFIX}
.endfor

post-install:
	${MKDIR} ${DESTDIR}${EGDIR}
	${INSTALL_DATA} ${WRKSRC}/packaging/foundationdb.conf \
		${DESTDIR}${EGDIR}/foundationdb.conf
	${ECHO} 'local:local@127.0.0.1:4500' > ${DESTDIR}${EGDIR}/fdb.cluster

.include "../../devel/cmake/build.mk"
.include "../../lang/python/tool.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
