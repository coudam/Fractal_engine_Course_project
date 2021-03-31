#include "engine.hpp"

int *Window_width;
int *Window_hight;

#define FPS_FRAMES 20
#define MODELS_NUM 3
#define MODELS_DISTANCE 6.

static float pos_x = 0., pos_y = 0.;
static bool first_mouse = true, line_mode = false;
static float delta_time, last_frame, current_frame;
static float fps_count = 0;
static std::list<float> fps_q(FPS_FRAMES); 
Camera *camera;

float cur_time , delta, last_time;


engine::engine(): window_h(1300), window_w(1000) {
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


    window = glfwCreateWindow(window_h, window_w, "play graund", NULL, NULL);
    if(!window)
    {
       std::cerr << "Error on window creating" << std::endl;
       glfwTerminate();
       return;
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    GLenum err = glewInit();
    if (err != GLEW_OK){
       printf("glew error\n");
       exit(1);
    }
    
    camera = &c;   

    shaders.push_back(Shader("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag"));
    shaders.push_back(Shader("../../src/shaders/src/light_shader.vert", "../../src/shaders/src/light_shader.frag"));
    shaders.push_back(Shader("../../src/shaders/src/text.vert", "../../src/shaders/src/text.frag"));

    models.push_back(Model(&(shaders[1]), 0, GL_TRIANGLE_STRIP)); //standart cube
    models.push_back(Model(&(shaders[0]), 0, "../../models/dragon_1.obj", GL_TRIANGLES));

    for (int i = 1; i < MODELS_NUM*MODELS_NUM*MODELS_NUM; ++i) {
        models.push_back(Model(models[1]));
    }

    set_model_position(); 

    Time::timer("set_shader", &Text::set_shader, &t, &(shaders[2]));
    // t.set_shader(&(shaders[2]));

    flags |= INITED;
    return;
} 

void engine::set_model_position() {
    models[0].set_model_settings(TRANSLATE, glm::vec3(0.f, 10.f, 10.f));
    models[0].set_model_settings(COLOR, glm::vec3(1.0f, 1.0f, 1.0f));
    models[0].set_model_settings(SCALE, 0.1f);

    for (int k = 0; k < MODELS_NUM; ++k) {
        for (int i = 0; i < MODELS_NUM; ++i) {
            for (int j = 0; j < MODELS_NUM; ++j) {
                models[1+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(TRANSLATE, glm::vec3(MODELS_NUM*MODELS_DISTANCE/2 - i*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - k*MODELS_DISTANCE,
                                                                                                          MODELS_NUM*MODELS_DISTANCE/2 - j*MODELS_DISTANCE));
                models[1+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(COLOR, glm::vec3(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
                models[1+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(SCALE, 0.27f);
            }
        }
    }
}

void engine::animate() { 
    for (int k = 0; k < MODELS_NUM; ++k) {
        for (int i = 0; i < MODELS_NUM; ++i) {
            for (int j = 0; j < MODELS_NUM; ++j) {
                models[1+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].set_model_settings(ROTATE_Y, models[1+k*MODELS_NUM*MODELS_NUM+i*MODELS_NUM+j].rotate_y + delta_time*10.f);
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

        glfwPollEvents();

        last_time = glfwGetTime();
        draw_simple();
        cur_time = glfwGetTime();
        delta = cur_time - last_time;
        last_time = cur_time;
        std::cout << "draw : " << delta << '\n';

        animate();

        last_time = glfwGetTime();
        glfwSwapBuffers(window);
        // glFlush();
        // glfwSwapInterval(0);
        cur_time = glfwGetTime();
        delta = cur_time - last_time;
        last_time = cur_time;
        std::cout << "swap : " << delta << '\n';
        // glfwWaitEvents();
    }

    glfwTerminate();
    return;
}

void engine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

}

void engine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (first_mouse)
    {
        pos_x = xpos;
        pos_y = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - pos_x;
    float yoffset = pos_y - ypos;

    pos_x = xpos;
    pos_y = ypos;
    camera->process_mouse_movement(xoffset, yoffset);
}


void engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // std::cout << "delta : " << delta_time << " key : " << key << " " << action << " key pressed\n";
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        line_mode ^= true;
        if (line_mode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        camera->process_keyboard(key, delta_time, glfwGetKey(window, key));
    } 
}

void engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera->process_mouse_scroll(yoffset);
}



//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh//tresh

// void engine::set_proj(int id) {
//   glm::mat4 view = camera->get_view_matrix();
//   glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)window_w / (float)window_h, 0.1f, 1000.0f);

//   shaders[id].setMat4("view", view);
//   // shaders[1].setMat4("view", view);

//   shaders[id].setMat4("projection", projection);
//   // shaders[1].setMat4("projection", projection);

// }


// void engine::load_simple_VAO() {
//   std::cout << "SDAKSGKJHJDFL\n";
//   // glBufferData(GL_ARRAY_BUFFER, sizeof(voxel), voxel, GL_STATIC_DRAW);
//   // std::cout << vrt_load_arr.size() << '\n';
//   glGenBuffers(1, &NB);
//   glGenBuffers(1, &VBO);
//   glGenBuffers(1, &VBO_cube);
//   glGenVertexArrays(1, &VAO);
//   glGenVertexArrays(1, &VAO_light);
    
// // model
//   glBindVertexArray(VAO);

//   glBindBuffer(GL_ARRAY_BUFFER, NB);
//   glBufferData(GL_ARRAY_BUFFER, models[0].normals.size() * sizeof(glm::vec3), models[0].normals.data(), GL_STATIC_DRAW);
//   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
//   glEnableVertexAttribArray(2);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, models[0].vertices.size() * sizeof(glm::vec3), models[0].vertices.data(), GL_STATIC_DRAW);
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//   glEnableVertexAttribArray(0); 

// // light 
//   glBindVertexArray(VAO_light);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
//   glBufferData(GL_ARRAY_BUFFER, models[1].vertices.size() * sizeof(glm::vec3), models[1].vertices.data(), GL_STATIC_DRAW);
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   
//   glEnableVertexAttribArray(0);


//   glBindVertexArray(0);
// }

// void engine::set_light() {
//   glm::vec3 pos = {10.0f, 20.0f, 0.0f};

//   shaders[0].setVec3("objectColor", 0.2f, 0.2f, 0.2f);
//   shaders[0].setVec3("lightColor", 0.0f, 1.0f, 1.0f);
//   shaders[0].setVec3("lightPos", pos);
//   shaders[0].setVec3("viewPos", camera->position);

// }
