cmake_minimum_required (VERSION 3.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O2 -g -lglfw -lGLEW -lGL")
set(ENGINE_SOURSE_DIR ${PROJECT_SOURCE_DIR})

project(engine)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_library(engine 
	STATIC ./engine/engine.cpp
)

target_link_libraries(engine 
	glfw
	GLEW
	GL
)

target_include_directories(engine 
	PUBLIC ${GLFW3_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

add_subdirectory(./test)
