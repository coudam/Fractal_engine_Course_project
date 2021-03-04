#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class Model{
public:
	Model(const char * path, std::vector<glm::vec3> *vrt, std::vector<glm::vec2> *uvs, std::vector<glm::vec3> *normls);
	// Model();
	// ~Model();

private:
	const char * path;
    std::vector <glm::vec3> *out_vertices;
    std::vector <glm::vec2> *out_uvs;
    std::vector <glm::vec3> *out_normals;
	
};