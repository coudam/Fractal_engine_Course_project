#include "engine.hpp"

int *Window_width;
int *Window_hight;

#define FPS_FRAMES 20
#define MODELS_NUM 1
#define MODELS_DISTANCE 6.

static float pos_x = 0., pos_y = 0.;
static bool first_mouse = true, line_mode = false;
static float delta_time, last_frame, current_frame;
static float fps_count = 0;
static std::list<float> fps_q(FPS_FRAMES); 
Camera *camera;

float cur_time , delta, last_time;

engine::engine(): window_h(1000), window_w(1300), c(glm::vec3(0.0f, 15.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -45.0f) {
    Window_hight = &window_h;
    Window_width = &window_w;
    // engine::t = 0;
    std::cout << "engine inited\n";
}

engine::~engine() {
    std::cout << "engine destroed\n";
}

void engine::init() {
    std::cout << std::fixed << std::setprecision(7);

    if (flags & INITED) {
       printf("allrady inited\n");
       return;
    }

    if( !glfwInit() )
       exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // glfwWindowHint( GLFW_DOUBLEBUFFER, GL_FALSE );
    glfwSwapInterval(0);


    window = glfwCreateWindow(window_w, window_h, "play graund", NULL, NULL);
    if(!window)
    {
       std::cerr << "Error on window creating" << std::endl;
       glfwTerminate();
       return;
    }

    glfwMakeContextCurrent(window);

    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    camera = &c;

    input.set_hint(window, &camera);
    set_key_action();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    glfwSwapInterval(0);

    glOrtho(0.0f, window_w, window_h, 0.0f, 0.0f, 1.0f);

    GLenum err = glewInit();
    if (err != GLEW_OK){
       printf("glew error\n");
       exit(1);
    }

    shaders.push_back(Shader("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag"));
    shaders.push_back(Shader("../../src/shaders/src/light_shader.vert", "../../src/shaders/src/light_shader.frag"));
    shaders.push_back(Shader("../../src/shaders/src/text.vert", "../../src/shaders/src/text.frag"));
    shaders.push_back(Shader("../../src/shaders/src/mandelbrot.vert", "../../src/shaders/src/mandelbrot.frag"));


    // models.push_back(Model(&shaders[3], 0, GL_TRIANGLES, plane, plane_normals, plane_uvs, 6));
    // models.push_back(Model(&shaders[1], 0, GL_TRIANGLE_STRIP, Shapes::sphere, glm::vec3(0.f, 0.f, 0.f), 3, 40));
    // // models.push_back(Model(&shaders[2], 0, GL_TRIANGLE_STRIP, voxel)); 
    // models.push_back(Model(&(shaders[0]), 0, GL_TRIANGLES, "../../models/dragon_1.obj"));
    // // models.push_back(Model(&shaders[0], 0, GL_TRIANGLE_STRIP, Shapes::sphere, glm::vec3(0.f, 0.f, 0.f), 3, 50));


    // for (int i = 1; i < MODELS_NUM*MODELS_NUM*MODELS_NUM; ++i) {
    //     models.push_back(Model(models[2]));
    // }

    // Time::timer("set model pos", &engine::set_model_position, this);
    // set_model_position(); 

    t.set_shader(&(shaders[2]));

    flags |= INITED;
    return;
} 


void engine::set_key_action(){
    input.add_key_input(GLFW_KEY_ESCAPE, [this](int key, float delta){glfwSetWindowShouldClose(this->window, true);}, PRESS);
    input.add_key_input(GLFW_KEY_R, [this](int key, float delta){
        line_mode ^= true;
        if (line_mode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }, PRESS);
    input.add_key_input({GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D}, [this](int key, float delta){
        camera->process_keyboard(key, delta);
    }, PRESS | REPEAT);

}

void engine::set_model_position() {
    models[0].set_model_settings(SCALE, 100.f);

    models[1].set_model_settings(TRANSLATE, glm::vec3(0.f, 10.f, 10.f));
    models[1].set_model_settings(COLOR, glm::vec3(0.0f, 1.0f, 1.0f));
    models[1].set_model_settings(SCALE, 0.1f);

    for (int k = 0; k < MODELS_NUM; ++k) {
        for (int i = 0; i < MODELS_NUM; ++i) {
            for (int j = 0; j < MODELS_NUM; ++j) {
                models[2+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(TRANSLATE, glm::vec3(MODELS_NUM*MODELS_DISTANCE/2 - i*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - k*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - j*MODELS_DISTANCE));
                models[2+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(COLOR, glm::vec3(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
                models[2+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(SCALE, 0.27f);
            }
        }
    }
}

void engine::animate() { 
    for (int k = 0; k < MODELS_NUM; ++k) {
        for (int i = 0; i < MODELS_NUM; ++i) {
            for (int j = 0; j < MODELS_NUM; ++j) {
                models[2+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(ROTATE_Y, models[2+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].rotate_y + delta_time*10.f);
            }
        }
    }
}

void engine::draw_simple() {
    for (uint i = 0; i < models.size(); ++i) {
        models[i].draw(*camera);
    }   
}

void engine::start() {
    while (!glfwWindowShouldClose(window)){
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        fps_q.pop_front(); fps_q.push_back(delta_time);
        for (const auto& i : fps_q) fps_count += i;
        fps_count /= FPS_FRAMES;

        glClearColor(0.1f, 0.1f, 0.2f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        t.draw_text("Average time per frame for last " + std::to_string(FPS_FRAMES) + " frames : " + std::to_string(fps_count), 5.0f, window_h - 25., 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
        t.draw_text("fps : " + std::to_string(1 / fps_count), 5.0f, window_h - 50., 0.4f, glm::vec3(0.5, 0.8f, 0.2f));

        input.process(delta_time);
        glfwPollEvents();

        draw_simple();
        animate();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return;
}

void engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera->process_mouse_scroll(yoffset);
}
