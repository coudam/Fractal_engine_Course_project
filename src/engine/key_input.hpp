#pragma once
#include <iostream>
#include <map>
#include <GLFW/glfw3.h> 
#include <functional>

#include "camera.hpp"


enum EVENT{
	PRESS = 1,
	RELEASE = 2,
	REPEAT = 4,
	NONE = 8
};

static std::map<int, EVENT> event_map = {{GLFW_PRESS, PRESS}, {GLFW_RELEASE, RELEASE}};

class Input{
public:
	Input() {}
	Input(GLFWwindow *w) : window(w) {}
	void set_hint(GLFWwindow *w, Camera **c) {window = w; camera = c;}

	void add_key_input(int key, std::function<void(int, float)> f, int events){
		// if (key == -1) {std::cout << "undefinet key : " << key << '\n'; return;}
		keys[key] = KEY(f, events); 
	}	

	void add_key_input(std::vector<int> &&key, std::function<void(int, float)> f, int events){
		for (auto &i : key) keys[i] = KEY(f, events);
	}	

	void process(float delta){
		
		// mouse //

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
	    if (first_mouse) {
	        pos_x = xpos;
	        pos_y = ypos;
	        first_mouse = false;
	    }

	    float xoffset = xpos - pos_x;
	    float yoffset = pos_y - ypos;

	    pos_x = xpos;
	    pos_y = ypos;

	    (*camera)->process_mouse_movement(xoffset, -yoffset);

	    // key //

		for (auto& [key, info] : keys) {
			int e = glfwGetKey(window, key);
			// std::cout << key << " " << e << " " << info.action << " " << info.event << "\n";

			if 		(e == GLFW_RELEASE &&  info.action == NONE)			     				info.action = NONE;
			else if (e == GLFW_RELEASE && (info.action == PRESS || info.action == REPEAT))  info.action = RELEASE;
			else if (e == GLFW_PRESS   && (info.action == PRESS || info.action == REPEAT))  info.action = REPEAT;
			else if (e == GLFW_PRESS   && (info.action == NONE || info.action == RELEASE))  info.action = PRESS;

			if (info.event & info.action){
				info.callback(key, delta);
			}
		}
	}

private:
	struct KEY{
		KEY():action(RELEASE) {}
		KEY(std::function<void(int, float)> f, int e): callback(f), action(RELEASE) ,event(e) {}
	
		std::function<void(int, float)> callback;
		EVENT action;
		int event;
 	};

 	double pos_x = 0, pos_y = 0; 
 	bool first_mouse = true ;
 	GLFWwindow *window;
 	Camera **camera;
	std::map<int, KEY> keys;
};