#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <string> 
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "prime_shapes.hpp"

#define INITED 1
#define SIZEOFARR(arr) sizeof(arr)/sizeof(arr)

class engine{
public:
	engine();
	~engine();

	void init();
	void start();
private:
	float scale = 1;
	int window_h, window_w;
	int flags = 0;
	int shader;
	GLuint VBO, VAO;

	GLFWwindow* window = 0;

	void read_file(const char * vertex_file_path, std::string &data);
	void draw_simple();
	void load_simple_VAO();
	void load_shaders(const char * vertex_file_path,const char * fragment_file_path);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};