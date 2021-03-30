#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "prime_shapes.hpp"
#include "shader.hpp"
#include "camera.hpp"

extern int *Window_hight;
extern int *Window_width;

enum SETTINGS{
	ROTATE_X,
	ROTATE_Y,
	TRANSLATE,
	SCALE,
	COLOR
};

class Model{
public:
	Model(){}
	Model(const Model &m);
	Model(Shader *s, GLuint vao, const char * path, GLenum mode = GL_TRIANGLES);
	Model(Shader *s, GLuint vao, GLenum mode = GL_TRIANGLES, const float *vert = voxel, const float *normals = voxel_normals, const float *uvs = voxel_uvs, int num = 14);

	void draw(const Camera &c, const Model &l = Model());
	int size() const;

	// template<typename T> void set_model_settings(SETTINGS settings, T &&value);
	template<typename T> //wierd shat; very dengerous dont do that at home)))
	void set_model_settings(SETTINGS settings, T &&value){
		switch (settings) {
			case ROTATE_X:
				rotate_x = *reinterpret_cast<float*>(&value);
				break;
			case ROTATE_Y:
				rotate_y = *reinterpret_cast<float*>(&value);
				break;
			case TRANSLATE:
				translate = *reinterpret_cast<glm::vec3*>(&value);
				break;
			case SCALE:
				scale = glm::vec3(*reinterpret_cast<float*>(&value));
				break;
			case COLOR:
				object_color = *reinterpret_cast<glm::vec3*>(&value);
				break;
			// default: 
		}
	} //


	Shader *shader;

	float rotate_x, rotate_y;
	glm::vec3 scale, translate, object_color;

	glm::mat4 transform;
	std::vector <glm::vec3> vertices;
    std::vector <glm::vec3> normals;
    std::vector <glm::vec2> uvs;
	GLuint VBO, VAO, NB;
	GLenum DRAW_MODE;
	int num_of_points;

private:
	const char * path;
    
    void load_VAO();
	
};


class Light : public Model{
public:
	Light();
	~Light();

private:	
};