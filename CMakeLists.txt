project(cetoBigTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC")

OPTION( BUILD_EXE "build exe" TRUE )
OPTION( BUILD_TEST "build testcase" FALSE )
# include header file
include_directories(
	./src/include/container/
	./src/include/os
	./src/include/binary
	./src/include/mem
	./src/include/debug
	./src/include/tools
)
# cpp file
	add_library(container STATIC
		./src/container/cetoMemTableSL.cpp
	)
IF(BUILD_EXE)

ENDIF()

IF(BUILD_TEST)
# build testcase
ENDIF()
