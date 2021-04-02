#include "key_input.hpp"

// void Input::add_key_input(int key, std::function<void(int, float)> f, int events){
// 	if (glfwGetKeyScancode(key) == -1) {std::cout << "undefinet key : " << key << '\n'; return;}
// 	keys[key] = KEY(f, event_map[events]); 
// }	

// void Input::process(float delta){
// 	for (auto& [key, info] : keys)  {
// 		int e = glfwGetKey(window, key);
// 		std::cout << key << " " << e << '\n';
// 		if (e == GLFW_RELEASE && !info.action) {continue;}
// 		if (info.event & event_map[e]) {
// 			info.callback(key, delta);
// 		}
// 		info.action = true;
// 	}
// }
