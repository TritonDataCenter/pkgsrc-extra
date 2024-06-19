# $NetBSD$

PKGNAME=	${DISTNAME:S/src-bundle-v//:S/-lts//}
DISTNAME=	clickhouse-src-bundle-v23.8.7.24-lts
CATEGORIES=	net
MASTER_SITES=	https://oxide-clickhouse-build.s3.us-west-2.amazonaws.com/

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://clickhouse.com/
COMMENT=	The real-time data warehouse
LICENSE=	apache-2.0

USE_LANGUAGES=	c c++

# Remove 0019-char-is-signed-on-illumos.patch as unsuitable on SmartOS/pkgsrc.
PATCHFILES+=	0001-Add-cmake-sunos-default_libs.cmake.patch
PATCHFILES+=	0002-Allow-building-clickhouse-with-custom-C-CXX-LD-FLAGS.patch
PATCHFILES+=	0003-Disable-thread-safety-analysis.patch
PATCHFILES+=	0004-Allow-i386-for-system-processor.patch
PATCHFILES+=	0005-utils-Use-GNU-find-grep.patch
PATCHFILES+=	0006-Adjust-log-paths-in-server-config.xml.patch
PATCHFILES+=	0007-Add-lsocket-and-lnsl-to-poco-link.patch
PATCHFILES+=	0008-Rename-tokens-due-to-regset.h-pollution.patch
PATCHFILES+=	0009-std-namespace-fixes.patch
PATCHFILES+=	0010-Missing-includes.patch
PATCHFILES+=	0011-Enable-SSE2-divide-implementation-on-illumos.patch
PATCHFILES+=	0012-Cast-arguments-to-FP-functions.patch
PATCHFILES+=	0013-IBridge-Don-t-set-max-RSS-on-illumos.patch
PATCHFILES+=	0014-More-granular-configuration-of-TCP-keepalives.patch
PATCHFILES+=	0015-QueryProfiler-Only-enable-if-OS-supports-it.patch
PATCHFILES+=	0016-illumos-support-for-pollPid.patch
PATCHFILES+=	0017-Use-statvfs-on-illumos.patch
PATCHFILES+=	0018-Do-not-try-to-increase-the-thread-limit-via-proc.patch
PATCHFILES+=	0020-Use-libunwind-on-illumos.patch
PATCHFILES+=	0021-Enable-memory-stats-on-illumos.patch
PATCHFILES+=	0022-Disable-skim-on-illumos.patch
PATCHFILES+=	0023-wide_integer-invalid-conversion.patch
PATCHFILES+=	0024-Fix-compilation-of-headers-under-C-23.patch
PATCHFILES+=	0025-DependencyGraph-missing-overloads.patch
PATCHFILES+=	0026-parseLDAPServer-std-optional-emplace-failure.patch
PATCHFILES+=	0027-KeeperStateMachine-std-optional-emplace-failure.patch
PATCHFILES+=	0028-KeeperStorage-need-to-explicitly-specify-operator-re.patch
PATCHFILES+=	0029-IPAddressDictionary-use-boost-variant2.patch
PATCHFILES+=	0030-StorageURL-Trying-to-return-std-tuple-from-function-.patch
PATCHFILES+=	0031-MergeTree-Use-logf.patch
PATCHFILES+=	0032-Loggers-unresolved-std-time_put.patch
PATCHFILES+=	0033-config-processor-missing-files-in-link.patch
PATCHFILES+=	0034-library-bridge-missing-files-in-link.patch
PATCHFILES+=	0035-Ensure-that-libunwind-is-linked-in-the-final-objects.patch
PATCHFILES+=	0036-Restore-poco-SUN-files.patch
PATCHFILES+=	0037-poco-foundation-add-illumos-support.patch
PATCHFILES+=	0038-contrib-abseil-cpp-Allow-i386-for-system-processor.patch
PATCHFILES+=	0039-contrib-abseil-cpp-illumos-does-not-have-VDSO-suppor.patch
PATCHFILES+=	0040-contrib-azure-Use-arc4random-and-SIGPIPE-on-illumos.patch
PATCHFILES+=	0041-contrib-azure-forward-declaration-before-unique_ptr.patch
PATCHFILES+=	0042-contrib-boost-Rename-tokens-due-to-regset.h-pollutio.patch
PATCHFILES+=	0043-contrib-c-ares-add-illumos-as-a-platform.patch
PATCHFILES+=	0044-contrib-cctz-Fix-char-array-index-warning.patch
PATCHFILES+=	0045-contrib-curl-Add-illumos-support.patch
PATCHFILES+=	0046-contrib-datasketches-Rename-tokens-due-to-regset.h-p.patch
PATCHFILES+=	0047-contrib-libarchive-Add-illumos-support.patch
PATCHFILES+=	0048-contrib-libpq-Do-not-use-strerror_r-on-illumos.patch
PATCHFILES+=	0049-contrib-libpq-ignore-pg_attribute_printf.patch
PATCHFILES+=	0050-contrib-llvm-project-Disable-locale-static-assertion.patch
PATCHFILES+=	0051-contrib-llvm-project-Enable-xlocale-for-illumos.patch
PATCHFILES+=	0052-contrib-llvm-project-Missing-brace-and-prefer-std-ll.patch
PATCHFILES+=	0053-contrib-llvm-project-Rename-tokens-due-to-regset.h-p.patch
PATCHFILES+=	0054-contrib-llvm-project-ignore-__sentinel.patch
PATCHFILES+=	0055-contrib-miniselect-cast-argument-to-log.patch
PATCHFILES+=	0056-contrib-rocksdb-illumos-does-not-have-dirent-d_type-.patch
PATCHFILES+=	0057-contrib-rocksdb-re-order-structs-to-fix-compilation-.patch
PATCHFILES+=	0058-contrib-s2geometry-Find-endian.h-on-illumos.patch
PATCHFILES+=	0059-contrib-s2geometry-use-floating-point-parameters-to-.patch
PATCHFILES+=	0060-contrib-s2geometry-using-std-ldexp.patch
PATCHFILES+=	0061-contrib-zlib-ng-Use-posix_memalign-on-illumos.patch

# Be specific about which commit we're pulling the patches from.
GC_COMMIT=	362f169d81253185a688f81c19a110dfe714ba20
PATCH_SITES+=	https://raw.githubusercontent.com/oxidecomputer/garbage-compactor/${GC_COMMIT}/clickhouse/patches/

PATCH_DIST_STRIP=	-p1

WRKSRC=		${WRKDIR}/${DISTNAME:S/src-bundle-//}

TOOL_DEPENDS+=	findutils-[0-9]*:../../sysutils/findutils
TOOL_DEPENDS+=	nasm-[0-9]*:../../devel/nasm

.include "../../mk/bsd.prefs.mk"

# Must be DEPENDS rather than bl3 to avoid llvm interference.
PKGSRC_COMPILER=	clang
TOOL_DEPENDS+=		clang-[0-9]*:../../lang/clang

CHECK_PORTABILITY_SKIP+=	contrib/google-protobuf/post_process_dist.sh
CHECK_PORTABILITY_SKIP+=	contrib/icu/tools/release/c/os-mapping/testTimezones.sh
CHECK_PORTABILITY_SKIP+=	contrib/libuv/autogen.sh
CHECK_PORTABILITY_SKIP+=	contrib/protobuf/post_process_dist.sh

CFLAGS.SunOS+=		-D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -D__EXTENSIONS__
CFLAGS.SunOS+=		-DHAVE_STRERROR_R -DSTRERROR_R_INT
CFLAGS.SunOS+=		-fno-use-cxa-atexit

CXXFLAGS.SunOS+=	-fcxx-exceptions -fexceptions -frtti

# XXX: add to clang
CFLAGS.SunOS+=		-D__illumos__
CXXFLAGS.SunOS+=	-D__illumos__

CMAKE_ARGS+=	-DABSL_CXX_STANDARD="20"
CMAKE_ARGS+=	-DCMAKE_C_FLAGS="${CFLAGS}"
CMAKE_ARGS+=	-DCMAKE_CXX_FLAGS="${CXXFLAGS}"
CMAKE_ARGS+=	-DCOMPILER_CACHE=disabled
CMAKE_ARGS+=	-DENABLE_AMQPCPP=off
CMAKE_ARGS+=	-DENABLE_AVRO=off
CMAKE_ARGS+=	-DENABLE_CAPNP=off
CMAKE_ARGS+=	-DENABLE_CLICKHOUSE_BENCHMARK=off
CMAKE_ARGS+=	-DENABLE_CLICKHOUSE_ODBC_BRIDGE=off
CMAKE_ARGS+=	-DENABLE_HDFS=off
CMAKE_ARGS+=	-DENABLE_LDAP=off
CMAKE_ARGS+=	-DENABLE_MSGPACK=off
CMAKE_ARGS+=	-DENABLE_MYSQL=off
CMAKE_ARGS+=	-DENABLE_ORC=off
CMAKE_ARGS+=	-DENABLE_PARQUET=off
CMAKE_ARGS+=	-DENABLE_S3=off
CMAKE_ARGS+=	-DENABLE_SENTRY=off
CMAKE_ARGS+=	-DENABLE_TESTS=off
CMAKE_ARGS+=	-DUSE_SENTRY=off

CONF_FILES+=	share/examples/clickhouse/clickhouse-client/config.xml \
		${PKG_SYSCONFDIR}/clickhouse-client/config.xml
CONF_FILES+=	share/examples/clickhouse/clickhouse-keeper/keeper_config.xml \
		${PKG_SYSCONFDIR}/clickhouse-keeper/keeper_config.xml
CONF_FILES+=	share/examples/clickhouse/clickhouse-server/config.xml \
		${PKG_SYSCONFDIR}/clickhouse-server/config.xml
CONF_FILES+=	share/examples/clickhouse/clickhouse-server/users.xml \
		${PKG_SYSCONFDIR}/clickhouse-server/users.xml

# Conflicts with bundled zlib
pre-build:
	${RM} -f ${BUILDLINK_DIR}/include/zconf.h
	${RM} -f ${BUILDLINK_DIR}/include/zlib.h

# Rather than carrying additional patches we just fix these in post.
post-install:
	${RM} -rf ${DESTDIR}${PREFIX}/cmake
	${RM} -rf ${DESTDIR}${PREFIX}/lib

.include "../../devel/cmake/build.mk"
.include "../../mk/bsd.pkg.mk"
