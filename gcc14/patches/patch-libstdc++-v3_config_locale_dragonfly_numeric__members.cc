$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/numeric_members.cc.orig	2024-10-15 15:55:33.000000000 +0000
+++ libstdc++-v3/config/locale/dragonfly/numeric_members.cc
@@ -44,8 +44,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
       if (!_M_data)
 	_M_data = new __numpunct_cache<char>;
 
+#if !defined(__illumos__)
       if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_grouping = "";
 	  _M_data->_M_grouping_size = 0;
@@ -59,6 +61,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 
 	  for (size_t __j = 0; __j < __num_base::_S_iend; ++__j)
 	    _M_data->_M_atoms_in[__j] = __num_base::_S_atoms_in[__j];
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -114,6 +117,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	      _M_data->_M_grouping_size = __len;
 	    }
 	}
+#endif
 
       // NB: There is no way to extract this info from posix locales.
       // _M_truename = __nl_langinfo_l(YESSTR, __cloc);
@@ -140,8 +144,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
       if (!_M_data)
 	_M_data = new __numpunct_cache<wchar_t>;
 
+#if !defined(__illumos__)
       if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_grouping = "";
 	  _M_data->_M_grouping_size = 0;
@@ -158,6 +164,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	  for (size_t __j = 0; __j < __num_base::_S_iend; ++__j)
 	    _M_data->_M_atoms_in[__j] =
 	      static_cast<wchar_t>(__num_base::_S_atoms_in[__j]);
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -212,6 +219,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	      _M_data->_M_grouping_size = __len;
 	    }
 	}
+#endif
 
       // NB: There is no way to extract this info from posix locales.
       // _M_truename = __nl_langinfo_l(YESSTR, __cloc);
