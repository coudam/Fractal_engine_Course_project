#include "engine.hpp"


engine::engine(): window_w(600), window_h(800) {
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

    if( !glfwInit() )
       exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( window_h, window_w, "play graund", NULL, NULL );
    if( !window )
    {
       std::cerr << "Error on window creating" << std::endl;
       glfwTerminate();
       return;
    }

    glfwMakeContextCurrent( window );
    glfwSetKeyCallback(window, key_callback);  
    glEnable(GL_DEPTH_TEST);

    GLenum err = glewInit();
    if (err != GLEW_OK){
       printf("glew error\n");
       exit(1);
    }
    
    load_shaders("../../src/shaders/src/shader.vert", "../../src/shaders/src/shader.frag");
    load_simple_VAO();

    flags |= INITED;
    printf("inited\n");
    return;
} 

void engine::load_simple_VAO() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel), voxel, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); 
    glBindVertexArray(0);
}

void engine::draw_simple() {
    glUseProgram(shader); 
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 42);
    glBindVertexArray(0); 
}

void engine::start() {

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        draw_simple();
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    return;
}


void engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        scale += 0.05;
    }
}

void engine::read_file(const char * vertex_file_path, std::string &data){
    std::ifstream f(vertex_file_path);
    std::string line;
    data = "";
    if (f.is_open()){
        while ( getline (f, line) ){
            data.append(line);
            data.append("\n");
        }
        f.close();
    } else 
    printf("failt to read\n");
}

void engine::load_shaders(const char * vertex_file_path, const char * fragment_file_path){

    int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    printf("%d\n", VertexShaderID);
    int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    read_file(vertex_file_path, VertexShaderCode);
    read_file(fragment_file_path, FragmentShaderCode);
    std::cout << VertexShaderCode << '\n';
    std::cout << FragmentShaderCode << '\n';

    GLint Result = GL_FALSE;
    int InfoLogLength;

    printf("Компиляция шейдера: %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }

    printf("Компиляция шейдера: %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn\n");
    shader = glCreateProgram();
    glAttachShader(shader, VertexShaderID);
    glAttachShader(shader, FragmentShaderID);
    glLinkProgram(shader);

    // Проверяем шейдерную программу
    glGetProgramiv(shader, GL_LINK_STATUS, &Result);
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(shader, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
}
