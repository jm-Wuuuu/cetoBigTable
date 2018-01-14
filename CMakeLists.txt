PROJECT(cetoBigTable)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC")

OPTION( BUILD_TEST "build testcase" FALSE )

# include header file
INCLUDE_DIRECTORIES(
	./src/include/container/
	./src/include/os
	./src/include/binary
	./src/include/mem
	./src/include/debug
	./src/include/tools
)
# cpp file
	ADD_LIBRARY(container STATIC
		./src/container/cetoMemTableSL.cpp
	)

IF(BUILD_TEST)
# build testcase
ADD_SUBDIRECTORY(test)
ENDIF()
