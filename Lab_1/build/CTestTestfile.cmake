# CMake generated Testfile for 
# Source directory: C:/Labs_OOP
# Build directory: C:/Labs_OOP/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(MyProjectTests "C:/Labs_OOP/build/Debug/tests.exe")
  set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Labs_OOP/CMakeLists.txt;36;add_test;C:/Labs_OOP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(MyProjectTests "C:/Labs_OOP/build/Release/tests.exe")
  set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Labs_OOP/CMakeLists.txt;36;add_test;C:/Labs_OOP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(MyProjectTests "C:/Labs_OOP/build/MinSizeRel/tests.exe")
  set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Labs_OOP/CMakeLists.txt;36;add_test;C:/Labs_OOP/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(MyProjectTests "C:/Labs_OOP/build/RelWithDebInfo/tests.exe")
  set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Labs_OOP/CMakeLists.txt;36;add_test;C:/Labs_OOP/CMakeLists.txt;0;")
else()
  add_test(MyProjectTests NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
