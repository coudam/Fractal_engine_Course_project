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
	
	LoadShaders("~/Fractal_engine_Course_project/src/shaders/src/shader.vert", "~/Fractal_engine_Course_project/src/shaders/src/shader.frag");
	flags |= INITED;
	printf("inited\n");
	return;
} 

void engine::start() {

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	return;
}


void engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

}

void engine::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    printf("%d\n", VertexShaderID);
    int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Компилируем Вершинный шейдер
    printf("Компиляция шейдера: %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Выполняем проверку Вершинного шейдера
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }

    // Компилируем Фрагментный шейдер
    printf("Компиляция шейдера: %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Проверяем Фрагментный шейдер
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Создаем шейдерную программу и привязываем шейдеры к ней
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");
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
