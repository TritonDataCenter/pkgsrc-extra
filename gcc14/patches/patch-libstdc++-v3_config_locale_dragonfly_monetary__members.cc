$NetBSD$

Use the DragonFly locale backend on illumos.

--- libstdc++-v3/config/locale/dragonfly/monetary_members.cc.orig	2024-03-13 11:22:01.065361348 +0000
+++ libstdc++-v3/config/locale/dragonfly/monetary_members.cc
@@ -217,8 +217,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
       if (!_M_data)
 	_M_data = new __moneypunct_cache<char, true>;
 
+#if !defined(__illumos__)
       if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_decimal_point = '.';
 	  _M_data->_M_thousands_sep = ',';
@@ -237,6 +239,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 
 	  for (size_t __i = 0; __i < money_base::_S_end; ++__i)
 	    _M_data->_M_atoms[__i] = money_base::_S_atoms[__i];
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -361,6 +364,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	  _M_data->_M_neg_format = _S_construct_pattern(__nprecedes, __nspace,
 							__nposn);
 	}
+#endif
     }
 
   template<>
@@ -371,8 +375,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
       if (!_M_data)
 	_M_data = new __moneypunct_cache<char, false>;
 
+#if !defined(__illumos__)
       if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_decimal_point = '.';
 	  _M_data->_M_thousands_sep = ',';
@@ -391,6 +397,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 
 	  for (size_t __i = 0; __i < money_base::_S_end; ++__i)
 	    _M_data->_M_atoms[__i] = money_base::_S_atoms[__i];
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -515,6 +522,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	  _M_data->_M_neg_format = _S_construct_pattern(__nprecedes, __nspace,
 							__nposn);
 	}
+#endif
     }
 
   template<>
@@ -556,8 +564,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
       if (!_M_data)
 	_M_data = new __moneypunct_cache<wchar_t, true>;
 
+#if !defined(__illumos__)
       if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_decimal_point = L'.';
 	  _M_data->_M_thousands_sep = L',';
@@ -578,6 +588,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	  for (size_t __i = 0; __i < money_base::_S_end; ++__i)
 	    _M_data->_M_atoms[__i] =
 	      static_cast<wchar_t>(money_base::_S_atoms[__i]);
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -706,6 +717,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 
 	  uselocale((locale_t)__old);
 	}
+#endif
     }
 
   template<>
@@ -716,8 +728,10 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
     if (!_M_data)
       _M_data = new __moneypunct_cache<wchar_t, false>;
 
+#if !defined(__illumos__)
     if (!__cloc)
 	{
+#endif
 	  // "C" locale
 	  _M_data->_M_decimal_point = L'.';
 	  _M_data->_M_thousands_sep = L',';
@@ -738,6 +752,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 	  for (size_t __i = 0; __i < money_base::_S_end; ++__i)
 	    _M_data->_M_atoms[__i] =
 	      static_cast<wchar_t>(money_base::_S_atoms[__i]);
+#if !defined(__illumos__)
 	}
       else
 	{
@@ -866,6 +881,7 @@ _GLIBCXX_BEGIN_NAMESPACE_VERSION
 
 	  uselocale((locale_t)__old);
 	}
+#endif
     }
 
   template<>
