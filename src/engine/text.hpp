#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils.hpp"
#include "shader.hpp"

extern int *Window_hight;
extern int *Window_width;

class Text
{
public:
	Text() {}
	void draw_text(const std::string &&text, float x, float y, float scale, glm::vec3 color);
	void set_shader(const safe_vec_ptr<Shader> &s); 

	safe_vec_ptr<Shader> shader;
private:	
	struct Character {
	    unsigned int TextureID;
	    glm::ivec2   Size;
	    glm::ivec2   Bearing;
	    unsigned int Advance;
	};

	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
	static bool initing;
};