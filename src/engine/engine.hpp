#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
// #include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include <string> 
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>


#define INITED 1

class engine{
public:
	engine();
	~engine();

	void init();
	void start();
private:
	int window_h, window_w;
	int flags = 0;
	int shader;

	GLFWwindow* window = 0;

	void LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};