cmake_minimum_required (VERSION 2.6)
project (conqur)


add_subdirectory(src)
add_subdirectory(tests)
SET ( CMAKE_CXX_FLAGS  "-pthread" )
SET ( CMAKE_EXE_LINKER_FLAGS  "-pthread" "trace.ld" )

TARGET_LINK_LIBRARIES(conqur)
