cmake_minimum_required (VERSION 3.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O2 -g -lglfw -lGLEW -lGL")
set(ENGINE_SOURSE_DIR ${PROJECT_SOURCE_DIR})

project(engine)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)

add_library(engine STATIC 
	./engine/time.hpp
	./engine/engine.cpp
	./engine/model.cpp
	./engine/camera.cpp
	./engine/shader.cpp
	./engine/light.cpp
	./engine/text.cpp
	./engine/math_shapes.cpp
)

target_link_libraries(engine 
	glfw
	GLEW
	GL
	${FREETYPE_LIBRARIES}
	${ZLIB_LIBRARIES}
)

target_include_directories(engine 
	PUBLIC ${GLFW3_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}
)

add_subdirectory(./test)
