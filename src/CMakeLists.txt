include_directories(
		../include
		../arch
		../os
)

add_library(conqur 
	Logger.cpp
	GraphFactory.cpp
	FileGraphLoader.cpp
	)

