cmake_minimum_required(VERSION 3.24)

project(aqua-platform-desktop VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Dependencies ---

set(AQUA_RUNTIME_DIR
	"${CMAKE_CURRENT_LIST_DIR}/../aqua-runtime"
	CACHE PATH
	"Path to the aqua-runtime repository")

# Ensure the runtime doesn't build extras when embedded.
set(AQUA_RUNTIME_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(AQUA_RUNTIME_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if (EXISTS "${AQUA_RUNTIME_DIR}/CMakeLists.txt")
	add_subdirectory(
		"${AQUA_RUNTIME_DIR}"
		"${CMAKE_BINARY_DIR}/_deps/aqua-runtime"
		EXCLUDE_FROM_ALL)
else()
	message(FATAL_ERROR
		"aqua-runtime not found at '${AQUA_RUNTIME_DIR}'. Set AQUA_RUNTIME_DIR.")
endif()

# --- Library ---

add_library(aqua_platform_desktop STATIC
	src/desktop_platform.cpp
	src/desktop_window.cpp
)

target_compile_features(aqua_platform_desktop PUBLIC cxx_std_23)

target_include_directories(aqua_platform_desktop
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(aqua_platform_desktop
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
		FILES
			include/aqua/platform/desktop/desktop_platform.hpp
			include/aqua/platform/desktop/desktop_window.hpp
)

target_link_libraries(aqua_platform_desktop
	PUBLIC
		aqua-runtime
)

if (MSVC)
	target_compile_options(aqua_platform_desktop PRIVATE /W4)
else()
	target_compile_options(aqua_platform_desktop PRIVATE -Wall -Wextra -Wpedantic)
endif()
