cmake_minimum_required(VERSION 3.0.2)
include(GNUInstallDirs)

project(unsandbox
	VERSION 2
	LANGUAGES C)

add_executable(unsandbox unsandbox.c)
target_link_libraries(unsandbox ${CMAKE_DL_LIBS})

install(
	TARGETS unsandbox
	DESTINATION ${CMAKE_INSTALL_BINDIR})
