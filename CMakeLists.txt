cmake_minimum_required(VERSION 3.24)

project(aqua-platform-desktop VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

# For single-config generators (e.g. Ninja/Makefiles), default to Debug unless
# the user explicitly sets CMAKE_BUILD_TYPE.
if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" )
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# --- Dependencies ---

# aqua-runtime is vendored as a git submodule.
set(AQUA_RUNTIME_DIR
	"${CMAKE_CURRENT_LIST_DIR}/external/aqua-runtime"
	CACHE PATH
	"Path to the aqua-runtime repository")

# Ensure the runtime doesn't build extras when embedded.
set(AQUA_RUNTIME_BUILD_TESTS OFF CACHE BOOL "Build Aqua Runtime tests" FORCE)
set(AQUA_RUNTIME_BUILD_EXAMPLES OFF CACHE BOOL "Build Aqua Runtime examples" FORCE)

if (NOT EXISTS "${AQUA_RUNTIME_DIR}/CMakeLists.txt")
	message(FATAL_ERROR
		"aqua-runtime not found at '${AQUA_RUNTIME_DIR}'. "
		"Did you forget to init/update submodules? "
		"Try: git submodule update --init --recursive")
endif()

add_subdirectory(
	"${AQUA_RUNTIME_DIR}"
	"${CMAKE_BINARY_DIR}/_deps/aqua-runtime"
	EXCLUDE_FROM_ALL)

# --- Library ---

add_library(aqua_platform_desktop STATIC
	src/desktop_platform.cpp
	src/desktop_window.cpp
)

target_compile_features(aqua_platform_desktop PUBLIC cxx_std_23)

target_include_directories(aqua_platform_desktop
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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
