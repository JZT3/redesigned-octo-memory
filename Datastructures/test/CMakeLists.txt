cmake_minimum_required(VERSION 4.2.3)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723 # release 1.17.0
)

FetchContent_MakeAvailable(googletest)

if(MSYS)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()


include(CMakeDependentOption)
include(GNUInstallDirs)
set(GOOGLETEST_VERSION 1.17.0)

# Note that googlemock target already builds googletest.
option(BUILD_GMOCK "Builds the googlemock subproject" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON)
option(GTEST_HAS_ABSL "Use Abseil and RE2. Requires Abseil and RE2 to be separately added to the build." OFF)

if(GTEST_HAS_ABSL)
  if(NOT TARGET absl::base)
    find_package(absl REQUIRED)
  endif()
  if(NOT TARGET re2::re2)
    find_package(re2 REQUIRED)
  endif()
endif()


# Create unit test malloc executable 
add_executable(unit_test_memalloc  mem_alloc_unit_test.cpp)

target_link_libraries(unit_test_memalloc
  PRIVATE
    memalloc_lib
    gtest_main
    gmock_main
  )


target_include_directories(unit_test_memalloc
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} # for test specific header files
)



#target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(unit_test_memalloc)


#if(BUILD_GMOCK)
#  add_subdirectory( googlemock )
#else()
#  add_subdirectory( googletest )
#endif()

enable_testing()
