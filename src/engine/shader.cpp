#include "shader.hpp"

Shader::operator int() const {
	return shader_id;
}

void Shader::read_file(const char * vertex_file_path, std::string &data){
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

Shader::Shader(const char * vertex_file_path, const char * fragment_file_path){

    int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    printf("shaderid : %d\n", VertexShaderID);
    int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    read_file(vertex_file_path, VertexShaderCode);
    read_file(fragment_file_path, FragmentShaderCode);
    // std::cout << VertexShaderCode << '\n';
    // std::cout << FragmentShaderCode << '\n';

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

    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к ней\n");
    shader_id = glCreateProgram();
    glAttachShader(shader_id, VertexShaderID);
    glAttachShader(shader_id, FragmentShaderID);
    glLinkProgram(shader_id);

    // Проверяем шейдерную программу
    glGetProgramiv(shader_id, GL_LINK_STATUS, &Result);
    glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(shader_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
}
