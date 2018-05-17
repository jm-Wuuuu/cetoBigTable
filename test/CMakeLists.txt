PROJECT(cetoBigTable)


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test/testcase)
# include test include dir
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include/gtest/
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include/gtest/internal/
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include/
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/
)

# cpp file
ADD_LIBRARY(gtest STATIC
	${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/src/gtest-all.cc
)

# link lib
LINK_LIBRARIES(container binary gtest)

# testcase
ADD_EXECUTABLE(testBinData ./binary/cetoBinDataTest.cpp)