cmake_minimum_required(VERSION 2.8.11)


######## project
project(robot)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
	${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})


######## source files
set(test_files
	test/test.cpp
)


######## dependencies
set(LINK_LIBS)

# GMock
if(UNIX)
	set(test_files
		${test_files}
		/usr/src/gmock/gmock-all.cc
	)
endif()


######## output
add_executable(${PROJECT_NAME}-test ${test_files})


######## link
target_link_libraries(${PROJECT_NAME}-test gtest)
