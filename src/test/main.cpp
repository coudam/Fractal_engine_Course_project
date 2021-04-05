#include "../../engine/engine.hpp"

#define MODELS_NUM 4
#define MODELS_DISTANCE 6.

void init_scene(engine& e) {
	safe_vec_ptr<Shader> light_obj_shader = e.set_shader("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag");
    safe_vec_ptr<Shader> obj_shader = e.set_shader("../../src/shaders/src/light_shader.vert", "../../src/shaders/src/light_shader.frag");

    // models.push_back(Model(&shaders[1], 0, GL_TRIANGLE_STRIP, Shapes::sphere, glm::vec3(0.f, 0.f, 0.f), 3, 40));
    // models.push_back(Model(&shaders[1], 0, GL_TRIANGLE_STRIP, voxel)); 
    // models.push_back(Model(&(shaders[0]), 0, GL_TRIANGLES, "../../models/dragon_1.obj"));
    // models.push_back(Model(&shaders[0], 0, GL_TRIANGLE_STRIP, Shapes::sphere, glm::vec3(0.f, 0.f, 0.f), 3, 50));

	safe_vec_ptr<Model> sphere = e.set_model(Model(obj_shader, GL_TRIANGLE_STRIP, Shapes::sphere, glm::vec3(0.f, 0.f, 0.f), 3, 40));
    sphere->set_model_settings(TRANSLATE, glm::vec3(0.f, 10.f, 10.f));
    sphere->set_model_settings(COLOR, glm::vec3(1.0f, 1.0f, 1.0f));
    sphere->set_model_settings(SCALE, 0.1f);


    std::vector<safe_vec_ptr<Model>> models;
    models.push_back(e.set_model(Model(light_obj_shader, GL_TRIANGLES, "../../models/dragon_1.obj")));
	// safe_vec_ptr<Model> dragon = ;
    for (int i = 1; i < MODELS_NUM*MODELS_NUM*MODELS_NUM; ++i) {
        models.push_back(e.set_model(Model(*models[0])));
    }

    for (int k = 0; k < MODELS_NUM; ++k) {
        for (int i = 0; i < MODELS_NUM; ++i) {
            for (int j = 0; j < MODELS_NUM; ++j) {
                models[k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j]->set_model_settings(TRANSLATE, glm::vec3(MODELS_NUM*MODELS_DISTANCE/2 - i*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - k*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - j*MODELS_DISTANCE));
                models[k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j]->set_model_settings(COLOR, glm::vec3(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
                models[k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j]->set_model_settings(SCALE, 0.27f);
            }
        }
    }

}

int main(int argc, char const *argv[])
{
	engine e;
	e.init();

	init_scene(e);



	e.start();
	return 0;
}