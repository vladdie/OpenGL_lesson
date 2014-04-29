// 03_Matrices.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include <gl/glew.h>

#include <glfw/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

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

	window=glfwCreateWindow(1366,768,"03_Matrices",NULL,NULL);
	if (window==NULL)
	{
		cerr<<"Failed to open GLFW window.Maybe your GPU is not supported!"<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental=true;
	if (glewInit()!=GLEW_OK)
	{
		cerr<<"Failed to initialize GLEW!"<<endl;
		return -1;
	}

	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

	glClearColor(0.0f,0.0f,0.4f,0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Create and compile our GLSL program from the shaders
	GLuint programID=LoadShaders("SimpleTransform.vertexshader","SingleColor.fragmentshader");

	//Get a handle for our "MVP" uniform
	GLuint MatrixID=glGetUniformLocation(programID,"MVP");

	//Projection matrix:45° Field of view,4:3 ratio,display range: 0.1 <-> 100 units
	glm::mat4 Projection=glm::perspective(45.0f,16.0f/9.0f,0.1f,100.0f);

	//Camera matrix
	glm::mat4 View=glm::lookAt(
		glm::vec3(4,3,3),	//Camera is at (4,3,3),in World Space
		glm::vec3(0,0,0),	//and look at the origin (0,0,0)
		glm::vec3(0,1,0)	//Head is up (set to 0,-1,0 to look upside-down)
		);		
	//Model matrix: an identity matrix (model will be at the origin)
	glm::mat4 Model= glm::mat4(1.0f);	//Changes for each model!

	//Our ModelViewProjection:multiplication of our 3 matrices
	glm::mat4 MVP=Projection*View*Model;	//Remember,matrix multiplication is the other way around

	//triangle vertex
	static const GLfloat gl_vertex_buffer_data[]={
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,
	};
	static const GLushort gl_element_buffer_data[]={0,1,2};

	GLuint vertex_buffer;
	glGenBuffers(1,&vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(gl_vertex_buffer_data),gl_vertex_buffer_data,GL_STATIC_DRAW);

	do 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		//Send our transformattion to the currently bound shader
		//in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);

		//First attribute buffer:vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer);
		glVertexAttribPointer(
			0,	//attribute. No particular reason for 0,but must match the layout in the shader
			3,	//size
			GL_FLOAT,	//type
			GL_FALSE,	//normalized
			0,	//stride,即跳跃
			(void*)0	//array buffer offset
			);

		//Draw the triangle!
		glDrawArrays(GL_TRIANGLES,0,3);	//3 indices starting at 0->1 triangle

		glDisableVertexAttribArray(0);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);

	//Cleanup VBO and shader
	glDeleteBuffers(1,&vertex_buffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1,&VertexArrayID);

	glfwTerminate();

	return 0;
}
