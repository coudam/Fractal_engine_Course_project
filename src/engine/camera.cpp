#include "camera.hpp"

#define KEY_PRESS 1

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, -1.0f, -1.0f)), movement_speed(4.5f), mouse_sensitivity(0.15f), zoom(45.) {
	position = pos;
	world_up = up;
	Yaw = yaw;
	Pitch = pitch;
	
	update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix() const{
	return glm::lookAt(position, position + front, up);
}

void Camera::update_camera_vectors(){
	glm::vec3 new_front;
	new_front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	new_front.y = sin(glm::radians(Pitch));
	new_front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	// std::cout << glm::to_string(new_front) << '\n' << glm::to_string(front) << '\n';
	front = glm::normalize(new_front);
	right = glm::normalize(glm::cross(front, world_up));
	up	= glm::normalize(glm::cross(right, front));
}

void Camera::process_keyboard(int key, float delta) {
	float velocity = movement_speed * delta;
	if (key == GLFW_KEY_W){
		position += front * velocity;
	} else if (key == GLFW_KEY_S){
		position -= front * velocity;
	} else if (key == GLFW_KEY_A){
		position -= right * velocity;
	} else if (key == GLFW_KEY_D){
		position += right * velocity;
	} 
	// std::cout << "position : " << glm::to_string(position) << '\n';
}

void Camera::process_mouse_movement(float xoffset, float yoffset) {
	// std::cout << "rotate x : " << Yaw << " rotate y : " << Pitch << '\n';
	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;

	Yaw   += xoffset;
	Pitch -= yoffset;

	// if (true){
	// 	if (Pitch > 89.0f)
	// 		Pitch = 89.0f;
	// 	if (Pitch < -89.0f)
	// 		Pitch = -89.0f;
	// }
	if (Yaw > 360) Yaw -= 360; else if (Yaw < -360) Yaw += 360; 
	if (Pitch > 360) Pitch -= 360; else if (Pitch < -360) Pitch += 360;

	update_camera_vectors();
}

void Camera::process_mouse_scroll(float yoffset) {
	zoom -= yoffset / 1.f;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f; 
	// std::cout << "zoom : " << zoom << '\n';
}
