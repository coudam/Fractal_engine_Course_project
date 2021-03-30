cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (test1)

include_directories(test
	${ENGINE_SOURSE_DIR}/engine
)

add_executable(test
	${PROJECT_SOURCE_DIR}/main.cpp
)

target_link_libraries(test PUBLIC
	engine	
)

target_include_directories(test PUBLIC 
	${ENGINE_SOURSE_DIR}/engine
	${PROJECT_BINARY_DIR}
)