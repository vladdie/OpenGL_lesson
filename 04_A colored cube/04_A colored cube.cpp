// 04_A colored cube.cpp : 定义控制台应用程序的入口点。
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

	//window=glfwCreateWindow(800,600,"04_A colored cube",glfwGetPrimaryMonitor(),NULL);
	window=glfwCreateWindow(800,600,"04_A colored cube",NULL,NULL);
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
	GLuint programID=LoadShaders("TransformVertexShader.vertexshader","ColorFragmentShader.fragmentshader");
	
	//Create a handle for our 'MVP' uniform
	GLuint MatrixID=glGetUniformLocation(programID,"MVP");

	//Projection Matrix
	glm::mat4 Projection=glm::perspective(45.0f,4.0f/3.0f,0.1f,100.0f);
	//Camera matrix
	glm::mat4 View=glm::lookAt(
		glm::vec3(4,3,-3),
		glm::vec3(0,0,0),
		glm::vec3(0,1,0)
		);
	//Model matrix:an identity matrix(model will be at the origin)
	glm::mat4 Model=glm::mat4(1.0f);
	//Our ModelViewProjection:multiplication of our 3 matrices
	glm::mat4 MVP=Projection*View*Model;

	//Our vertices.Three consecutive floats give a 3D vertex;Three consecutive vertices give a triangle.
	//A cube has 6 faces with 2 triangles each,so this makes 6*2=12 triangles,and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[]={
		-1.0f,-1.0f,-1.0f,	//triangle 1:begin
		-1.0f,-1.0f,1.0f,
		-1.0f,1.0f,1.0f,	//triangle 1:end
		1.0f, 1.0f,-1.0f,	//triangle 2:begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,	//triangle 2:end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	
	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
	
	do 
	{
		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除颜色缓冲以及深度缓冲

		//Use our shader
		glUseProgram(programID);

		//Send our transformation to the currently bound shader,in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);
	
		//First attribute buffer:vertices
		glEnableVertexAttribArray(0);	//0，第一个属性，即layout=0那个属性值
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(
			0,	//must match the layout in the shader
			3,	//size ,vec3
			GL_FLOAT,	//type
			GL_FALSE,	//normalized
			0,	//stride
			(void*)0	//array buffer offset
		);

		//Draw the triangle!
		glDrawArrays(GL_TRIANGLES,0,12*3);
		glDisableVertexAttribArray(0);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	//Cleanup VBO and shader
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1,&VertexArrayID);

	glfwTerminate();

	return 0;
}

