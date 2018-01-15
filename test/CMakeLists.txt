PROJECT(cetoBigTable)

# include test include dir
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include/
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/
)

# cpp file
	ADD_LIBRARY(gtest STATIC
		${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/src/gtest-all.cc
	)
