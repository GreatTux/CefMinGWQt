#----------------------------- CEF MinGW Qt Project ----------------------------

cmake_minimum_required(VERSION 3.1.0)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Project name.
project(cefmingwqt)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

# Determine the project architecture.
if(NOT DEFINED PROJECT_ARCH)
	if(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set(PROJECT_ARCH "x86_64")
	else()
		set(PROJECT_ARCH "x86")
	endif()
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Macros.

# Add a logical target that can be used to link the specified libraries into an
# executable target.
macro(ADD_LOGICAL_TARGET target debug_lib release_lib)
	add_library(${target} ${CEF_LIBTYPE} IMPORTED)
	set_target_properties(${target} PROPERTIES
	 IMPORTED_LOCATION "${release_lib}"
	 IMPORTED_LOCATION_DEBUG "${debug_lib}"
	 IMPORTED_LOCATION_RELEASE "${release_lib}"
	 )
endmacro()

# Source include directory.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Allow C++ programs to use stdint.h macros specified in the C99 standard that
# aren't in the C++ standard (e.g. UINT8_MAX, INT64_MIN, etc).
add_definitions(-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS)

set(CEF_LIBTYPE                 STATIC)
set(CEF_COMPILER_FLAGS          "-fno-strict-aliasing -fstack-protector -funwind-tables -fvisibility=hidden --param=ssp-buffer-size=4 -pipe -pthread -Wall -Wno-missing-field-initializers -Wno-unused-parameter")
set(CEF_C_COMPILER_FLAGS        "-std=c99")
set(CEF_CXX_COMPILER_FLAGS      "-fno-exceptions -fno-rtti -fno-threadsafe-statics -fvisibility-inlines-hidden -std=gnu++11 -Wsign-compare")
set(CEF_COMPILER_FLAGS_DEBUG    "-O0 -g")
set(CEF_COMPILER_FLAGS_RELEASE  "-O2 -fdata-sections -ffunction-sections -fno-ident -DNDEBUG -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2")
set(CEF_LINKER_FLAGS            "-fPIC -pthread -Wl,-rpath,.")
set(CEF_LINKER_FLAGS_RELEASE    "-Wl,-O1 -Wl,--as-needed -Wl,--gc-sections")

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# -Wno-unused-local-typedefs      = Don't warn about unused local typedefs
CHECK_C_COMPILER_FLAG(-Wno-unused-local-typedefs COMPILER_SUPPORTS_NO_UNUSED_LOCAL_TYPEDEFS)
if(COMPILER_SUPPORTS_NO_UNUSED_LOCAL_TYPEDEFS)
 set(CEF_C_COMPILER_FLAGS      "${CEF_C_COMPILER_FLAGS} -Wno-unused-local-typedefs")
endif()

# -Wno-literal-suffix             = Don't warn about invalid suffixes on literals
CHECK_CXX_COMPILER_FLAG(-Wno-literal-suffix COMPILER_SUPPORTS_NO_LITERAL_SUFFIX)
if(COMPILER_SUPPORTS_NO_LITERAL_SUFFIX)
 set(CEF_CXX_COMPILER_FLAGS    "${CEF_CXX_COMPILER_FLAGS} -Wno-literal-suffix")
endif()

# -Wno-narrowing                  = Don't warn about type narrowing
CHECK_CXX_COMPILER_FLAG(-Wno-narrowing COMPILER_SUPPORTS_NO_NARROWING)
if(COMPILER_SUPPORTS_NO_NARROWING)
 set(CEF_CXX_COMPILER_FLAGS    "${CEF_CXX_COMPILER_FLAGS} -Wno-narrowing")
endif()

if(PROJECT_ARCH STREQUAL "x86_64")
 # 64-bit architecture.
 set(CEF_COMPILER_FLAGS        "${CEF_COMPILER_FLAGS} -m64 -march=x86-64")
 set(CEF_LINKER_FLAGS          "${CEF_LINKER_FLAGS} -m64")
elseif(PROJECT_ARCH STREQUAL "x86")
 # 32-bit architecture.
 set(CEF_COMPILER_FLAGS        "${CEF_COMPILER_FLAGS} -msse2 -mfpmath=sse -mmmx -m32")
 set(CEF_LINKER_FLAGS          "${CEF_LINKER_FLAGS} -m32")
endif()

# Allow the Large File Support (LFS) interface to replace the old interface.
add_definitions(-D_FILE_OFFSET_BITS=64)

# CEF directory paths.
set(CEF_RESOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
set(CEF_BINARY_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")
set(CEF_BINARY_DIR_DEBUG    "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
set(CEF_BINARY_DIR_RELEASE  "${CMAKE_CURRENT_SOURCE_DIR}/Release")

# CEF library paths.
set(CEF_LIB_DEBUG   "${CEF_BINARY_DIR_DEBUG}/libcef.lib")
set(CEF_LIB_RELEASE "${CEF_BINARY_DIR_RELEASE}/libcef.lib")

#
# Post-configuration actions.
#

# Merge compiler/linker flags.
set(CMAKE_C_FLAGS                     "${CEF_COMPILER_FLAGS} ${CEF_C_COMPILER_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG               "${CEF_COMPILER_FLAGS_DEBUG} ${CEF_C_COMPILER_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE             "${CEF_COMPILER_FLAGS_RELEASE} ${CEF_C_COMPILER_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS                   "${CEF_COMPILER_FLAGS} ${CEF_CXX_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG             "${CEF_COMPILER_FLAGS_DEBUG} ${CEF_CXX_COMPILER_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE           "${CEF_COMPILER_FLAGS_RELEASE} ${CEF_CXX_COMPILER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS            "${CEF_LINKER_FLAGS} ${CEF_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG      "${CEF_LINKER_FLAGS_DEBUG} ${CEF_EXE_LINKER_FLAGS_DEBUG}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${CEF_LINKER_FLAGS_RELEASE} ${CEF_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS         "${CEF_LINKER_FLAGS} ${CEF_SHARED_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${CEF_LINKER_FLAGS_DEBUG} ${CEF_SHARED_LINKER_FLAGS_DEBUG}")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CEF_LINKER_FLAGS_RELEASE} ${CEF_SHARED_LINKER_FLAGS_RELEASE}")

# Include target subdirectories.

add_subdirectory(libcef_dll)
add_subdirectory(cefqtclient)
add_subdirectory(cefsubprocess)

# Install
install(DIRECTORY Resources/ DESTINATION "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")

# Display configuration settings.

message(STATUS "*** CONFIGURATION SETTINGS ***")
message(STATUS "Generator:                    ${CMAKE_GENERATOR}")
message(STATUS "Platform:                     ${CMAKE_SYSTEM_NAME}")
message(STATUS "Project architecture:         ${PROJECT_ARCH}")
message(STATUS "Build type:                   ${CMAKE_BUILD_TYPE}")

set(LIBRARIES ${CEF_STANDARD_LIBS})
message(STATUS "Standard libraries:           ${LIBRARIES}")

get_directory_property(DEFINITIONS COMPILE_DEFINITIONS)
message(STATUS "Compiler definitions:         ${DEFINITIONS}")

message(STATUS "C_FLAGS:                      ${CMAKE_C_FLAGS}")
message(STATUS "C_FLAGS_DEBUG:                ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C_FLAGS_RELEASE:              ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CXX_FLAGS:                    ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX_FLAGS_DEBUG:              ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX_FLAGS_RELEASE:            ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "EXE_LINKER_FLAGS:             ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "EXE_LINKER_FLAGS_DEBUG:       ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "EXE_LINKER_FLAGS_RELEASE:     ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
message(STATUS "SHARED_LINKER_FLAGS:          ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "SHARED_LINKER_FLAGS_DEBUG:    ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
message(STATUS "SHARED_LINKER_FLAGS_RELEASE:  ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
