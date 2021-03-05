#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string> 
#include <fstream>
#include <iostream>
#include <sstream>


class Shader{
public:
	Shader(const char *vertex_file_path,const char *fragment_file_path);
	// ~Shader();
	operator int() const;

private:
	int shader_id;

	void read_file(const char *vertex_file_path, std::string &data);
};