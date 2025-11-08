cmake_minimum_required(VERSION 3.5.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)
set(CXX_STANDARD 23)

include(GNUInstallDirs)

set(dirs 
"graphics" "image_processing" "io" "math" "physics" "qt" "signal_processing" "testing" "utils")


message(STATUS "cpp_utils_dirs: ${dirs}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

foreach(dir ${dirs})
	install(DIRECTORY ${dir} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpp_utils)
endforeach()
