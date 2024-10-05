# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Labs_OOP/Lab_2/built/_deps/googletest-src")
  file(MAKE_DIRECTORY "C:/Labs_OOP/Lab_2/built/_deps/googletest-src")
endif()
file(MAKE_DIRECTORY
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-build"
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Labs_OOP/Lab_2/built/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()