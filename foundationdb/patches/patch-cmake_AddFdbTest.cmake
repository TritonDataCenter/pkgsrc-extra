$NetBSD$

Do not register the python venv tests: the venv setup pip-installs from
the network at test time.  Neutering add_python_venv_test drops every
test that requires the venv fixture.

--- cmake/AddFdbTest.cmake.orig	2026-07-12 00:00:00.000000000 +0000
+++ cmake/AddFdbTest.cmake
@@ -601,19 +601,13 @@
 string(APPEND test_venv_cmd "&& pip install setuptools ")
 string(APPEND test_venv_cmd "&& pip install -r ${CMAKE_SOURCE_DIR}/tests/TestRunner/requirements.txt")
 string(APPEND test_venv_cmd "&& (cd ${CMAKE_BINARY_DIR}/bindings/python && python3 setup.py install) ")
-add_test(
-  NAME test_venv_setup
-  COMMAND bash -c ${test_venv_cmd}
-  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
-set_tests_properties(test_venv_setup PROPERTIES FIXTURES_SETUP test_virtual_env_setup TIMEOUT 120)
-set_tests_properties(test_venv_setup PROPERTIES RESOURCE_LOCK TEST_VENV_SETUP)

 # Run the test command under Python venv as a cmd (Windows) or bash (Linux/Apple) script, which allows && or || chaining.
 function(add_python_venv_test)
   set(oneValueArgs NAME WORKING_DIRECTORY TEST_TIMEOUT)
   set(multiValueArgs COMMAND)
   cmake_parse_arguments(T "" "${oneValueArgs}" "${multiValueArgs}" "${ARGN}")
-  if(OPEN_FOR_IDE)
+  if(TRUE)
     return()
   endif()
   if(NOT T_NAME)
