#include "../../engine/engine.hpp"

int main(int argc, char const *argv[])
{
	engine e;
	e.init();


    e.input.add_key_input(GLFW_KEY_Q, [&e](int key, float delta){ e.models[0].zoom+=e.models[0].zoomspeed; e.models[0].zoomspeed = e.models[0].zoom / 100.;},  REPEAT);
    e.input.add_key_input(GLFW_KEY_E, [&e](int key, float delta){ e.models[0].zoom-=e.models[0].zoomspeed; e.models[0].zoomspeed = e.models[0].zoom / 100.;},  REPEAT);

    e.input.add_key_input(GLFW_KEY_UP, [&e](int key, float delta){ e.models[0].t.y+=e.models[0].tspeed; e.models[0].tspeed =  e.models[0].zoom / 50.;}, PRESS | REPEAT);
    e.input.add_key_input(GLFW_KEY_DOWN, [&e](int key, float delta){ e.models[0].t.y-=e.models[0].tspeed; e.models[0].tspeed =  e.models[0].zoom / 50.;}, PRESS | REPEAT);
    e.input.add_key_input(GLFW_KEY_LEFT, [&e](int key, float delta){ e.models[0].t.x-=e.models[0].tspeed; e.models[0].tspeed =  e.models[0].zoom / 50.;}, PRESS | REPEAT);
    e.input.add_key_input(GLFW_KEY_RIGHT, [&e](int key, float delta){ e.models[0].t.x+=e.models[0].tspeed; e.models[0].tspeed =  e.models[0].zoom / 50.;}, PRESS | REPEAT);

    e.models.push_back(Model(&e.shaders[3], 0, GL_TRIANGLES, plane, plane_normals, plane_uvs, 6));
    e.models[0].set_model_settings(SCALE, 100.f);
	
	e.start();
	return 0;
}