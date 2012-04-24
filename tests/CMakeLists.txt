include_directories(
					../src
					../include
	)
SET ( CMAKE_CXX_FLAGS  "-pthread" )
SET ( CMAKE_EXE_LINKER_FLAGS  "-pthread" )

#TARGET_LINK_LIBRARIES(pthreads)
add_executable(tests 
		TestIntervalTree.cpp
		Test.cpp
		)
