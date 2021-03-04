#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string> 
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "prime_shapes.hpp"
#include "model.hpp"

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
	int shader;
	GLuint VBO, VAO;
	std::vector <Model> models;
	std::vector <glm::vec3> vrt_load_arr; 
	std::vector <glm::vec2> uvs_load_arr;
	std::vector <glm::vec3> normls_load_arr;


	GLFWwindow* window = 0;

	void read_file(const char *vertex_file_path, std::string &data);
	void draw_simple();
	void load_simple_VAO();
	void load_shaders(const char *vertex_file_path,const char *fragment_file_path);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};