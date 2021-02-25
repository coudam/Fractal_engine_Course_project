#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <time.h>
#include <fstream>
#include <iostream>


#define INITED 1

class engine{
public:
	// engine();
	// ~engine();

	void init(int h = 600, int w = 800);
	void start();
private:
	int window_h, window_w;
	int flags = 0;


	GLFWwindow* window = 0;
};