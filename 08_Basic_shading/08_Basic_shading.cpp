// 08_Basic_shading.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <vector>
#include <iostream>
using namespace std;

#include <gl/glew.h>
#include <glfw/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

#define WIDTH 800
#define HEIGHT 450

int _tmain(int argc, _TCHAR* argv[])
{
	if (!glfwInit())
	{
		cerr<<"Failed to initialize GLFW"<<endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	window=glfwCreateWindow(WIDTH,HEIGHT,"08_Basic_shading!",NULL,NULL);
	if (NULL == window)
	{
		cerr<<"Failed to open GLFW window. If you have an Intel GPU, they are not 4.0 compatible. Try the 2.1 version of the tutorials."<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cerr<<"Failed to initialize GLEW"<<endl;
		return -1;
	}

	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
	glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);

	glClearColor(0.0f,0.0f,0.4f,0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

	//Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	//Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");

	//Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	//Read our .obj file
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);
	
	//Load it into a VBO
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*uvs.size(), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);

	//Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID,"LightPosition_worldspace");

	do 
	{
		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use our shader
		glUseProgram(programID);

		//Compute the MVP matrix from keybord and mouse input
		computeMatricesFromInputs();
		mat4 ProjectionMatrix = getProjectionMatrix();
		mat4 ViewMatrix = getViewMatrix();
		mat4 ModelMatrix = mat4(1.0);
		mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//Send our transformation to the currently bound shader, in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		vec3 lightPos = vec3(4,4,4);
		glUniform3f(LightID,lightPos.x, lightPos.y, lightPos.z);

		//Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		//Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID,0);

		//1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,			//attribute
			3,			//size
			GL_FLOAT,	//type
			GL_FALSE,	//normalized?
			0,			//stride
			(void*)0
		);
		
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		//Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	//Clean VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}

