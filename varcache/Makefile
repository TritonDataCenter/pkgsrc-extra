#
# This is not a normal package, it is a standalone Makefile to help generate
# varcache entries that speed up builds by precomputing expensive variables.
#

BUILTINS!=	ls -1 ../../*/*/builtin.mk ../../mk/*.builtin.mk

#
# Be specific about which matches we want to include.  We would rather be
# missing a few variables than include anything which could cause problems.
#
VC_MATCH:=	^(BUILTIN_LIB_FOUND|BUILTIN_PKG|FIND_FILES)
VC_MATCH:=	${VC_MATCH}|^(H_|PC_|SH_|_BLTN_H_)
VC_MATCH:=	${VC_MATCH}|(DBM_H |_DRV |_PC )
VC_MATCH:=	${VC_MATCH}|^(BIN|BINUTILS)_FILE
VC_MATCH:=	${VC_MATCH}|^(XAUTH|XINIT)

#
# With X11_TYPE=modular we could end up with a situation where an X11 pkgsrc
# package happens to be installed, and will then be detected as a builtin due
# to X11BASE being set to LOCALBASE.  Include bsd.prefs.mk first to get the
# default setting, and then override it.
#
.include "../../mk/bsd.prefs.mk"

X11BASE:=	/nonexistent"

show-varcache:
	@{ ${MAKEVARS:@t@ \
		printf "%s %s\n" ${t:Q} ${${t:Q}:Q}; \
		@} } | ${SORT} | uniq | ${EGREP} ${VC_MATCH:Q} \
	| ${AWK} ' \
	{ \
		gsub(/${OSX_SDK_PATH:S,/,\\/,g}/, "$${OSX_SDK_PATH}"); \
	} \
	/^BUILTIN_PKG/ && ! $$2 { \
		next; \
	} \
	{ \
		if (length($$1) >= 31) { \
			print $$1 "=\t" $$2 \
		} else if (length($$1) >= 23) { \
			print $$1 "=\t\t" $$2 \
		} else if (length($$1) >= 15) { \
			print $$1 "=\t\t\t" $$2 \
		} else if (length($$1) >= 7) { \
			print $$1 "=\t\t\t\t" $$2 \
		} else { \
			print $$1 "=\t\t\t\t\t" $$2 \
		} \
	}'

.for builtin in ${BUILTINS}
.  include "${builtin:Q}"
.endfor

.include "../../mk/bsd.pkg.mk"
