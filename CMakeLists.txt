project(cetoBigTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC")

# include header file
include_directories(
	./src/container/
	./src/os
	./src/binary
	./src/mem
	./src/debug
	./src/tools
)

# cpp file
add_library(container STATIC
	./src/container/cetoMemTableSL.cpp
)
