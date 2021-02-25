#include "engine.hpp"

void engine::init(int h, int w) {
	window_h = h; window_w = w;
	if (flags & INITED) {
		printf("allrady inited\n");
		return;
	}
	
	if( !glfwInit() )
		return;

	window = glfwCreateWindow( window_h, window_w, "play graund", NULL, NULL );
	if( !window )
	{
		std::cerr << "Error on window creating" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent( window );
	
	flags |= INITED;
	printf("inited\n");
	return;
} 

void engine::start() {

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();



		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return;
}