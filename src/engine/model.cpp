#include "model.hpp"

int Model::size() const{
	return vertices.size();
}


Model::Model(const Model &m): 
			num_of_points(m.num_of_points), scale(m.scale), translate(m.translate), object_color(m.object_color), VAO(m.VAO), rotate_x(m.rotate_x), rotate_y(m.rotate_y), DRAW_MODE(m.DRAW_MODE), shader(m.shader) {
}

// template<typename F>
// Model::Model(Shader *s, GLuint vao, F f, GLenum mode):
// 			scale(0.2f), translate(glm::vec3(0.f)), object_color(glm::vec3(1.f, 1.f, 1.f)), VAO(vao), rotate_x(0), rotate_y(0), DRAW_MODE(mode), shader(s){
// }

Model::Model(safe_vec_ref<Shader> &s, GLenum mode, const float *vert, const float *norm, const float *uv, int num):
			scale(0.2f), translate(glm::vec3(0.f)), object_color(glm::vec3(1.f, 1.f, 1.f)), rotate_x(0), rotate_y(0), DRAW_MODE(mode), shader(s){ 
	std::cout << "load primar shape \n";
	if (vert)
		for (int i = 0; i < num; ++i)
			vertices.push_back(glm::vec3(vert[i*3], vert[i*3+1], vert[i*3+2]));
	if (norm)
		for (int i = 0; i < num; ++i)
			normals.push_back(glm::vec3(norm[i*3], norm[i*3+1], norm[i*3+2]));
	if (uv)
		for (int i = 0; i < num; ++i)
			uvs.push_back(glm::vec2(uv[i*2], uv[i*2+1]));

	load_VAO();
	num_of_points = size();
}	

Model::Model(safe_vec_ref<Shader> &s, GLenum mode, const char *path):
			scale(0.2f), translate(glm::vec3(0.f)), object_color(glm::vec3(1.f, 1.f, 1.f)), rotate_x(0), rotate_y(0), DRAW_MODE(mode), path(path), shader(s){ 

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::cout << "start to loat model/ path : " << path << '\n';

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		return;
	}

	while( 1 ){
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		// std::cout << res << " " << k <<'\n'; 

		if (res == EOF)
			break;

		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		} else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		} else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9 and matches != 6){
				// std::cout << k << " " << matches << '\n';
				// int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
				// if (matches != 6){
				printf("File can't be read by our simple parser: Try exporting with other options\n");
				return;
				// }
			} 
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			// uvIndices.push_back(uvIndex[0]);
			// uvIndices.push_back(uvIndex[1]);
			// uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		glm::vec3 v = temp_vertices[vertexIndices[i]-1];
		vertices.push_back(v);
	}
	for( unsigned int i=0; i<uvIndices.size(); i++ ){
		glm::vec3 u = temp_normals[uvIndices[i]-1];
		uvs.push_back(u);
	}
	for( unsigned int i=0; i<normalIndices.size(); i++ ){
		glm::vec3 n = temp_normals[normalIndices[i]-1];
		normals.push_back(n);
	}

	load_VAO();
	num_of_points = size();
}

void Model::load_VAO() {
	// NB = 0; VBO = 0; VAO = 0;
	glGenBuffers(0, &VBO); // problemes !!!!!
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NB);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// std::cout << "VAO : " << VAO << " NB : " << NB << " VBO : " << VBO << '\n';

	glBindBuffer(GL_ARRAY_BUFFER, NB);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0); 

	glBindVertexArray(0);

	std::cout << "VAO loaded : " << VAO << '\n';
}

void Model::draw(const Camera &c, const Model &l) {
	// float last_frame = glfwGetTime();
	// float current_frame;
 //    float delta_time;

	int id;
	glGetIntegerv(GL_CURRENT_PROGRAM,&id);
	// std::cout << path << " " << id << " shader program\n";
	if (id != *shader){
		glUseProgram(*shader);
	}
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translate);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotate_x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotate_y), glm::vec3(0, 1, 0));

	glm::mat4 view = c.get_view_matrix();
	glm::mat4 projection = glm::perspective(glm::radians(c.zoom), (float)(*Window_width) / (float)(*Window_hight), 0.1f, 1000.0f);
	
	// current_frame = glfwGetTime();
 //    delta_time = current_frame - last_frame;
 //    last_frame = current_frame;
 //    std::cout << "culcula : " << delta_time << ' ';

	(*shader).setMat4("view", view);
	(*shader).setMat4("projection", projection);
	(*shader).setMat4("model", model);
	(*shader).setVec3("objectColor", object_color);
	(*shader).setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	(*shader).setVec3("viewPos", c.position);
	(*shader).setVec3("lightPos", glm::vec3(0.f, 10.f, 10.f));

	// current_frame = glfwGetTime();
 //    delta_time = current_frame - last_frame;
 //    last_frame = current_frame;
 //    std::cout << "loading : " << delta_time << ' ';
	// std::cout<< size() << '\n';	
	// std::cout << glm::to_string(c.position) << "   /    obj color " <<  glm::to_string(object_color) << "    /   model " <<  glm::to_string(model) << '\n';

	// std::cout << "VAO : " << VAO << " NB : " << NB << " VBO : " << VBO << '\n';
	glBindVertexArray(VAO);
	glDrawArrays(DRAW_MODE, 0, num_of_points);
	glBindVertexArray(0);

	// current_frame = glfwGetTime();
 //    delta_time = current_frame - last_frame;
 //    last_frame = current_frame;
 //    std::cout << "drawing : " << delta_time << '\n';
}
