#pragma once

#include <stdlib.h>
#include <vector>
#include <list>
#include <string> 
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "camera.hpp"
#include "prime_shapes.hpp"
#include "model.hpp"
#include "shader.hpp"
#include <iomanip>


#define INITED 1
#define SIZEOFARR(arr) sizeof(arr)/sizeof(arr)

class engine{
public:
	engine();
	~engine();

	void init();
	void start();
private:
	int window_h, window_w;
	int flags = 0;

	GLuint VBO, VAO, NB, VAO_light, VBO_cube;

	std::vector <Shader> shaders;
	std::vector <Model> models;

	Camera c;
	GLFWwindow* window = 0;

	void draw_simple();
	void animate();
	void set_model_position();
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};