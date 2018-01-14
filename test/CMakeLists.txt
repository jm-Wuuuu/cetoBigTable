PROJECT(cetoBigTable)

# include test include dir
INCLUDE_DIRECTORIES(
	../thirdparty/googletest/googletest/include/
	../thirdparty/googletest/googletest/
)

# cpp file
	ADD_LIBRARY(gtest STATIC
		../thirdparty/googletest/googletest/src/gtest-all.cc
	)
