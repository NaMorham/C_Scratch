cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(lltest VERSION 1.0.0)

option(USE_COLOURS "Enable ANSI colour in logging and output" on)

if (USE_COLOURS)
    add_definitions( -DUSE_COLOUR )
endif ()
add_definitions( -DLL_ALLOW_TEST )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LLTEST_BUILD_DIR "${PROJECT_SOURCE_DIR}/build/test")

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LLTEST_BUILD_DIR}/files")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LLTEST_BUILD_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${LLTEST_BUILD_DIR}/bin")

# read the build number from file
file (STRINGS "test/buildNumber.txt" LLTEST_BUILD_NUM)
message(DEBUG "Got build number ${LLTEST_BUILD_NUM} from file")

# Create the version file
configure_file(include/lltest_version.h.in ${PROJECT_SOURCE_DIR}/include/lltest_version.h)

set(COMMON_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/../common/include/")
set(COMMON_SRC_PATH "${PROJECT_SOURCE_DIR}/../common/src/")

# add_library(SqrtLibrary STATIC mysqrt.cxx ${PROJECT_SOURCE_DIR}/Table.h)


set(COMMON_SRCS
        ${COMMON_SRC_PATH}/Utils.c
    )
message("Common sources: ${COMMON_SRCS}")

set(COMMON_HDRS
        ${COMMON_INCLUDE_PATH}/Utils.h
    )
message("Common headers: ${COMMON_HDRS}")

set(SRCS
        ${PROJECT_SOURCE_DIR}/test/main.c
        ${PROJECT_SOURCE_DIR}/src/ll_node.c
    )
message("Project sources: ${SRCS}")

set(HDRS
        ${PROJECT_SOURCE_DIR}/include/ll_node.h
    )
message("Project headers: ${HDRS}")

add_executable(lltest ${COMMON_SRCS} ${COMMON_HDRS} ${SRCS} ${HDRS} )

target_include_directories(lltest PUBLIC ${COMMON_INCLUDE_PATH} ${PROJECT_SOURCE_DIR}/include )
