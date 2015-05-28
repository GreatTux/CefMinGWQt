#------------------------------- CEF Qt Client --------------------------------

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

# Sources -----------

qt5_wrap_ui(QT_UI mainwindow.ui)

qt5_wrap_cpp(QT_MOC_CPP mainwindow.h)

qt5_add_resources(QT_RES res.qrc)

set(CEFQTCLIENT_SRCS
		application.h
		clientapp.cpp
		clientapp.h
		clienthandler.cpp
		clienthandler.h
		main.cpp
		mainwindow.cpp
		${QT_MOC_CPP}
		${QT_UI}
		${QT_RES}
		)

# Target -----------

set(CEF_TARGET "cefqtclient")

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Executable target.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${CEF_TARGET} WIN32 ${CEFQTCLIENT_SRCS})
add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
target_link_libraries(${CEF_TARGET}
								Qt5::Core
								Qt5::Gui
								Qt5::Widgets
								libcef_dll_wrapper
								libcef_lib
								${CEF_STANDARD_LIBS})

install(TARGETS ${CEF_TARGET} DESTINATION "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")

