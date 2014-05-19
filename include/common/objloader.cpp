#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "common/objloader.hpp"

bool loadOBJ(const char* path,
			 std::vector <glm::vec3> &out_vertices,		//������Ҫ�����ж���
			 std::vector <glm::vec2> &out_uvs,			//������Ҫ��������������
			 std::vector <glm::vec3> &out_normals		//��ķ�����
			 )
{
	std::vector<unsigned int> vertexIndices, uvIndices,normalIndices;	//����
	std::vector<glm::vec3 > temp_vertices;	//��ʱ�洢����
	std::vector<glm::vec2 > temp_uvs;		//��ʱ�洢����
	std::vector<glm::vec3 > temp_normals;	//�洢��ʱ������

	std::ifstream file;
	file.open(path,std::ios::in);
	if (file.fail())
	{
		std::cerr<<"Impossible to open the file!"<<std::endl;
		return false;
	}

	std::string lineHeader;
	//read the first word word of the line
	std::string line;
	while (file>>lineHeader)
	{
		/*int index_space=line.find_first_of(" ");
		strncpy()*/
		if ("v" == lineHeader)
		{	//�������ݣ�����һ����3��float
			glm::vec3 vertex;
			file>>vertex.x>>vertex.y>>vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if ("vt" == lineHeader)
		{	//����������
			glm::vec2 uv;
			file>>uv.x>>uv.y;
			uv.y=-uv.y;
			temp_uvs.push_back(uv);
		}
		else if ("vn" == lineHeader)
		{	//������
			glm::vec3 normal;
			file>>normal.x>>normal.y>>normal.z;
			temp_normals.push_back(normal);
		}
		else if ("f" == lineHeader)
		{	//����,����ÿһ��ֵ����һ��ֵ������������
			//�ڶ�������������������������������
			unsigned int vertexIndex[3],uvIndex[3],normalIndex[3];
			char ch;	//����'/'
			file>>vertexIndex[0]>>ch>>uvIndex[0]>>ch>>normalIndex[0]
				>>vertexIndex[1]>>ch>>uvIndex[1]>>ch>>normalIndex[1]
				>>vertexIndex[2]>>ch>>uvIndex[2]>>ch>>normalIndex[2];

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}//else--if
	}//while--file
	
	//��������
	//For each vertex of each triangle
	for (unsigned int i=0;i<vertexIndices.size();++i)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		//OBJ������1��ʼ��C++��0��ʼ
		glm::vec3 vertex = temp_vertices[vertexIndex-1];
		glm::vec2 uv = temp_uvs[uvIndex-1];
		glm::vec3 nomal = temp_normals[normalIndex-1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(nomal);
	}

	file.close();

	return true;
}