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
#include <iomanip>

#include "time.hpp"
#include "text.hpp"
#include "camera.hpp"
#include "prime_shapes.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "math_shapes.cpp"
#include "key_input.cpp"
#include "utils.hpp"

#define INITED 1
#define SIZEOFARR(arr) sizeof(arr)/sizeof(arr)


class engine{
public:
	engine();
	~engine();

	safe_vec_ref<Shader> set_shader(const char *path_vrt, const char *path_frg);
	safe_vec_ref<Model> set_model(Model &&m);

	void init();
	void start();
private:
	int window_h, window_w;
	int flags = 0;

	GLuint VBO, VAO, NB, VAO_light, VBO_cube;

	std::vector <Shader> shaders;
	std::vector <Model> models;

	Text t;
	Camera c;
	GLFWwindow* window = 0;
	Input input;

	void draw_simple();
	void animate();
	void set_model_position();
	void set_key_action();
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	// static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};