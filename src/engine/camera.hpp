#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string> 
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>


class Camera{
public:
	glm::vec3 world_up;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 position;

	float Yaw;
	float Pitch;

	float movement_speed, mouse_sensitivity, scale_speed;
	float zoom;

	Camera(glm::vec3 pos = glm::vec3(0.0f, 15.0f, 15.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = -45.0f);

	void process_keyboard(int key, float delta, int action);
	void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = false);
	void process_mouse_scroll(float yoffset);

	glm::mat4 get_view_matrix() const;
private:
	void update_camera_vectors();
};