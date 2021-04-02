#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <functional>
#include <complex>

#include "model.hpp"


struct Shapes{
	// static void sphere(Model &&a, glm::vec3 &&translate = glm::vec3(0.f, 0.f, 0.f), float r = 0.5, int p = 100){ sphere(a.vertices, a.normals, std::forward< glm::vec3 &&>(translate), r, p); }

	static void sphere(Model &model, glm::vec3 &&translate = glm::vec3(0.f, 0.f, 0.f), float r = 0.5, int p = 100){
		model.vertices.clear();
		model.normals.clear();

		float Fi, Teta;
		std::vector<std::vector<glm::vec3>> tmp;
		// translate.z -= r/2.;

		for (int i = 0; i < p; ++i) {
			Fi = M_PI / (p-1) * i;
			std::vector<glm::vec3> t;
			for (int j = 0; j < p; ++j) {
				glm::vec3 point(translate);
				Teta = 2 * M_PI / (p) * j;
				point.x += r * sin(Fi) * cos(Teta);
				point.y += r * sin(Fi) * sin(Teta);
				point.z += r * cos(Fi);
				t.push_back(point);
			}	
			tmp.push_back(t);
		}

		for (int i = 0; i < p-1; ++i) {
			for (int k = 0; k < p; ++k) {
				model.vertices.push_back(tmp[i][k]);
				model.normals.push_back(tmp[i][k]);

				model.vertices.push_back(tmp[i+1][k]);
				model.normals.push_back(tmp[i+1][k]);

				model.vertices.push_back(tmp[i][(k+1)%p]);
				model.normals.push_back(tmp[i][(k+1)%p]);


				model.vertices.push_back(tmp[i+1][k]);
				model.normals.push_back(tmp[i+1][k]);

				model.vertices.push_back(tmp[i+1][(k+1)%p]);
				model.normals.push_back(tmp[i+1][(k+1)%p]);

				model.vertices.push_back(tmp[i][(k+1)%p]);
				model.normals.push_back(tmp[i][(k+1)%p]);

			}
		}
	}	
};
