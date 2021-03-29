#include "engine.hpp"

static glm::vec3 translate = {0., -0.5, 0.};
static float scale = 0.1, scale_step = 0.001;
static float rotate_x = 0, rotate_y = 0, rotate_step = 0.01;
static float pos_x = 0., pos_y = 0.;
static bool mouse_pressed = false, mouse_pressed_first = false;
static bool event = true, first_mouse = true;
static float delta_time, last_frame, current_frame;
Camera *camera;

engine::engine(): window_w(1000), window_h(1300) {
    // engine::t = 0;
    std::cout << "engine inited\n";
}

engine::~engine() {
    std::cout << "engine destroed\n";
}

void engine::init() {
    if (flags & INITED) {
       printf("allrady inited\n");
       return;
    }

    models.push_back(Model("../../models/dragon_1.obj"));

    if( !glfwInit() )
       exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

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


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glewInit();
    if (err != GLEW_OK){
       printf("glew error\n");
       exit(1);
    }
    camera = &c;    
    shaders.push_back(Shader("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag"));
    shaders.push_back(Shader("../../src/shaders/src/light_shader.vert", "../../src/shaders/src/light_shader.frag"));
    load_simple_VAO();

    flags |= INITED;
    return;
} 

void engine::load_simple_VAO() {

    // glBufferData(GL_ARRAY_BUFFER, sizeof(voxel), voxel, GL_STATIC_DRAW);
    // std::cout << vrt_load_arr.size() << '\n';
    glGenBuffers(1, &NB);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO_cube);
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO_light);
    
// model
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, NB);
    glBufferData(GL_ARRAY_BUFFER, models[0].normals.size() * sizeof(glm::vec3), models[0].normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, models[0].vertices.size() * sizeof(glm::vec3), models[0].vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); 

// light 
    glBindVertexArray(VAO_light);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel), voxel, GL_STATIC_DRAW); //14 vert
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);
}

void engine::set_light() {
    glm::vec3 pos = {2.0f, 2.0f, 0.0f};

    shaders[0].setVec3("objectColor", 0.2f, 0.2f, 0.2f);
    shaders[0].setVec3("lightColor", 0.0f, 1.0f, 1.0f);
    shaders[0].setVec3("lightPos", pos);
    shaders[0].setVec3("viewPos", camera->position);

}

void engine::set_lighing_cube() {
    glm::vec3 pos = {2.0f, 2.0f, 0.0f};

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::translate(model, pos);
    shaders[1].setMat4("model", model);
}

void engine::set_proj(int id) {
    glm::mat4 view = camera->get_view_matrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)window_w / (float)window_h, 0.1f, 1000.0f);

    shaders[id].setMat4("view", view);
    // shaders[1].setMat4("view", view);

    shaders[id].setMat4("projection", projection);
    // shaders[1].setMat4("projection", projection);

}


void engine::draw_simple() {

    glUseProgram(shaders[0]); 
    set_proj(0);
    set_light();
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES, 0, models[0].size());


    glUseProgram(shaders[1]); 
    set_proj(1);
    set_lighing_cube();
    glBindVertexArray(VAO_light);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

    glBindVertexArray(0);

}

void engine::start() {
    while (!glfwWindowShouldClose(window))
    {
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1, 0.1, 0.2, 0.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();
        
        draw_simple();
        event = false; 

        glfwSwapBuffers(window);
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
    std::cout << "delta : " << delta_time << " key : " << key << " " << action << " key pressed\n";
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else {
        camera->process_keyboard(key, delta_time, glfwGetKey(window, key));
    } 
}

void engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera->process_mouse_scroll(yoffset);
}

