#include "model.hpp"

// Model::Model(){
// 	std::cout << "create model \n";
// }

Model::Model(const char * path, 
	std::vector <glm::vec3> *vrt, 
	std::vector <glm::vec2> *uvs, 
	std::vector <glm::vec3> *normls): path(path), out_vertices(vrt), out_uvs(uvs), out_normals(normls){

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

	int k = 0;
	while( 1 ){
		// ++k;
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
    	vrt->push_back(v);
    }
    for( unsigned int i=0; i<uvIndices.size(); i++ ){
    	glm::vec3 u = temp_normals[uvIndices[i]-1];
    	uvs->push_back(u);
    }
    for( unsigned int i=0; i<normalIndices.size(); i++ ){
    	glm::vec3 n = temp_normals[normalIndices[i]-1];
    	normls->push_back(n);
    }


}