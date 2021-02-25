cmake_minimum_required (VERSION 3.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O2 -g -lGL")
set(ENGINE_SOURSE_DIR ${PROJECT_SOURCE_DIR})

project(engine)

find_package(glfw3 REQUIRED)
#find_package(glm REQUIRED)

add_library(engine 
	STATIC ./engine/engine.cpp
)

add_subdirectory(./test)

target_link_libraries(engine 
	${GLFW_LIBRARIES} 
	glfw
)

target_include_directories(engine 
	PUBLIC ${GLFW3_INCLUDE_DIR}
)

#-lm -lGL -lm -lpthread -ldl -lrt -lm -ldl  -lX11 -lpthread -lxcb -lXau -lXdmcp