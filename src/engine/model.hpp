#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class Model{
public:
	Model(const char * path);
	// Model();
	// ~Model();
	Model(const float *vert); 
	int size() const;


	float scale, rotate_x, rotate_y;
	glm::vec3 translate;
    glm::vec3 objectColor;

	glm::mat4 transform;
	std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> uvs;
    std::vector <glm::vec3> normals;

private:
	const char * path;
    
	
};