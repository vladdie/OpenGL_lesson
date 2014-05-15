#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP
#include <vector>

bool loadOBJ(const char* path,
			 std::vector <glm::vec3> &out_vertices,
			 std::vector <glm::vec2> &out_uvs,
			 std::vector <glm::vec3> &out_normals
			 );
#endif