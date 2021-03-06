cmake_minimum_required(VERSION 3.19)

# Prohibit in-source tree builds.
# CMake will be banning this in a bit.
# When we can adjust cmake_minimum_required to that version, remove this block.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are strictly prohibited. Please see BUILDING.md and use that CMake command line as an example.")
endif()

include(cmake/Policies.cmake)

project(collab-vm-server)

include(cmake/CollabVM.cmake)

# TODO: collabvm_targetize should set this as a per-project param.
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
	message(STATUS "Adding MSVC band-aid compile flags")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /D_CRT_SECURE_NO_WARNINGS")

	if(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
		# MSVC seems to need another param to enable the "conformant preprocessor".
		# Not that building WORKS on MSVC, because "conformant" isn't really all THAT conformant,
		# but it's trying!
		message(STATUS "Adding (REAL) MSVC band-aid compile flags...")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
	endif()
endif()

# Dependencies
find_package(Boost REQUIRED COMPONENTS system filesystem program_options)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# Git tag target.
# TODO: Generate in ${PROJECT_BINARY_DIR}/core/ probably
add_custom_target(__collabvm_gittag
		COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/cmake/GitTag.cmake
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		SOURCES ${PROJECT_BINARY_DIR}/Version.h)
set_source_files_properties(${PROJECT_BINARY_DIR}/Version.h PROPERTIES GENERATED TRUE)


# Include module subdirectories
add_subdirectory(core)
add_subdirectory(proto)
add_subdirectory(api)

