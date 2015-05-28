#------------------------------- CEF Sub Process -------------------------------

# Sources -----------

set(CEFSUBPROCESS_SRCS
		main.cpp
		../cefqtclient/clientapp.cpp
		../cefqtclient/clientapp.h
		)

# Target -----------

set(CEF_TARGET "cefsubprocess")

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Executable target.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${CEF_TARGET} WIN32 ${CEFSUBPROCESS_SRCS})
add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
target_link_libraries(${CEF_TARGET}
								libcef_dll_wrapper
								libcef_lib
								${CEF_STANDARD_LIBS})

install(TARGETS ${CEF_TARGET} DESTINATION "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")
