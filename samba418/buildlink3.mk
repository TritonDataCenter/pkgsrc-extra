# $NetBSD: buildlink3.mk,v 1.16 2023/08/14 05:25:03 wiz Exp $

BUILDLINK_TREE+=	samba

.if !defined(SAMBA_BUILDLINK3_MK)
SAMBA_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.samba+=	samba>=4.9.4
BUILDLINK_ABI_DEPENDS.samba?=	samba>=4.18.5nb1
BUILDLINK_PKGSRCDIR.samba?=	../../extra/samba418

.include "../../archivers/libarchive/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/cmocka/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/popt/buildlink3.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../devel/talloc/buildlink3.mk"
.include "../../devel/tevent/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../textproc/jansson/buildlink3.mk"
.endif	# SAMBA_BUILDLINK3_MK

BUILDLINK_TREE+=	-samba
