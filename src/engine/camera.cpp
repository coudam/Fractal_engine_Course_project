#include "camera.hpp"

glm::mat4 Camera::get_view_matrix(){
	return glm::lookAt(position, target, up);
}