#include "engine.hpp"

static glm::vec3 translate = {0., 0., 0.};
static float scale = 0.5, scale_step = 0.001;
static float rotate_x = 0, rotate_y = 0, rotate_step = 0.01;
static float pos_x, pos_y;
static bool mouse_pressed = false;
static bool event = true;

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

    models.push_back(Model("../../models/dragon_1.obj", &vrt_load_arr, &uvs_load_arr, &normls_load_arr));

    if( !glfwInit() )
       exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glewInit();
    if (err != GLEW_OK){
       printf("glew error\n");
       exit(1);
    }
    
    shaders.push_back(Shader("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag"));
    load_simple_VAO();

    flags |= INITED;
    return;
} 

void engine::load_simple_VAO() {

    // glBufferData(GL_ARRAY_BUFFER, sizeof(voxel), voxel, GL_STATIC_DRAW);
    // std::cout << vrt_load_arr.size() << '\n';
    glGenBuffers(1, &NB);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO_light);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, NB);
    glBufferData(GL_ARRAY_BUFFER, normls_load_arr.size() * sizeof(glm::vec3), &normls_load_arr[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vrt_load_arr.size() * sizeof(glm::vec3), &vrt_load_arr[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); 

    // glBindVertexArray(lightCubeVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);


    glBindVertexArray(0);
}

void engine::draw_simple() {

    if (event) {
        glm::mat4 projection = glm::translate(
            glm::mat4(1.0f),
            translate
        );
        projection = glm::rotate(
            projection,
            rotate_y,
            glm::vec3(-1.0f, 0.0f, 0.0f)
        );
        projection = glm::rotate(
            projection,
            rotate_x,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        projection = glm::scale(
            projection,
            glm::vec3(scale)
        );
        // std::cout << "event\n";
        // std::cout << glm::to_string(projection) << '\n';
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(projection));
    }

    glUseProgram(shaders[0]); 
    glBindVertexArray(VAO); 
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
    glDrawArrays(GL_TRIANGLES, 0, vrt_load_arr.size());
    glBindVertexArray(0);

}

void engine::start() {
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1, 0.1, 0.2, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();
        
        draw_simple();
        event = false; 

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    return;
}

void engine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mouse_pressed ^= true;
}


void engine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (mouse_pressed){
        rotate_x += (xpos - pos_x)*rotate_step;
        rotate_y -= (ypos - pos_y)*rotate_step;
        event = true;
    }
    pos_x = xpos; pos_y = ypos;
    // std::cout << "rotate_x " << rotate_x << " rotate_y " << rotate_y <<'\n';
    // std::cout << "x : " << xpos << " y : " << ypos << '\n';
}

void engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // std::cout << key << " " << action << " key pressed\n";
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_UP && action != GLFW_RELEASE) {
        scale += scale_step;
        event = true;
    } else if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE) {
        scale -= scale_step;
        event = true;
    } else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        translate.y += 0.05;
        event = true;
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        translate.y -= 0.05;
        event = true;
    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        translate.x -= 0.05;
        event = true;
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        translate.x += 0.05;
        event = true;
    }
}

