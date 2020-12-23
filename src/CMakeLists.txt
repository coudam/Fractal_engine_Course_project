cmake_minimum_required (VERSION 3.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

project (Fractal_engine)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable (Fractal_engine main.cpp)

target_link_libraries(Fractal_engine 
	${Vulkan_LIBRARIES} 
	${GLFW_LIBRARIES} 
	${glm_LIBRARIES}
	glfw
)
target_include_directories(Fractal_engine 
	PUBLIC ${Vulkan_INCLUDE_DIRS}
	PUBLIC ${glm_INCLUDE_DIR}
	PUBLIC ${GLFW3_INCLUDE_DIR}
)
