include_directories(
					../src
					../include
					../arch
	)
SET ( CMAKE_CXX_FLAGS  "-pthread" )
SET ( CMAKE_EXE_LINKER_FLAGS  "-pthread -lconqur" )

LINK_DIRECTORIES(
	../src
)
add_executable(tests 
		TestIntervalTree.cpp
		Test.cpp
		)

TARGET_LINK_LIBRARIES(tests conqur)
