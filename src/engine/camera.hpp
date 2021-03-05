#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
	Camera();
	~Camera();


	glm::mat4 get_view_matrix();
private:
	glm::vec3 up;
	glm::vec3 position;
	glm::vec3 zoom;
	glm::vec3 target;

};