// 05_A textured cube.cpp : 定义控制台应用程序的入口点。
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

#include <common/loadBMP_custom.hpp>
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

	//window=glfwCreateWindow(800,450,"05_A textured cube",glfwGetPrimaryMonitor(),NULL);
	window=glfwCreateWindow(800,450,"05_A textured cube",NULL,NULL);
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

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it coloser to the camera than the former one
	glDepthFunc(GL_LESS);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//Create and compile our GLSL program from the shaders
	GLuint programID=LoadShaders("TransformVertexShader.vertexshader","TextureFragmentShader.fragmentshader");
	
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
	
	//Load the texture using the methods we write just now
	GLuint Texture=loadBMP_custom("uvtemplate.bmp");

	//Get a handle for our "myTextureSampler" uniform
	GLuint TextureID=glGetUniformLocation(programID,"myTextureSampler");

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
	
	//Two UV coordinates for each vertex. They were created with Blender. You'll learn shortly how to do this yourself
	static const GLfloat g_uv_buffer_data[]={
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
		0.335973f, 1.0f-0.335903f,
		1.000023f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.336024f, 1.0f-0.671877f,
		0.667969f, 1.0f-0.671889f,
		1.000023f, 1.0f-0.000013f,
		0.668104f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.000059f, 1.0f-0.000004f,
		0.335973f, 1.0f-0.335903f,
		0.336098f, 1.0f-0.000071f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.336024f, 1.0f-0.671877f,
		1.000004f, 1.0f-0.671847f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.668104f, 1.0f-0.000013f,
		0.335973f, 1.0f-0.335903f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.668104f, 1.0f-0.000013f,
		0.336098f, 1.0f-0.000071f,
		0.000103f, 1.0f-0.336048f,
		0.000004f, 1.0f-0.671870f,
		0.336024f, 1.0f-0.671877f,
		0.000103f, 1.0f-0.336048f,
		0.336024f, 1.0f-0.671877f,
		0.335973f, 1.0f-0.335903f,
		0.667969f, 1.0f-0.671889f,
		1.000004f, 1.0f-0.671847f,
		0.667979f, 1.0f-0.335851f
	};

	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
	
	GLuint uvbuffer;
	glGenBuffers(1,&uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_uv_buffer_data),g_uv_buffer_data,GL_STATIC_DRAW);

	do 
	{
		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除颜色缓冲以及深度缓冲

		//Use our shader
		glUseProgram(programID);

		//Send our transformation to the currently bound shader,in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);

		//Bind our texture in Texture Uint 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,Texture);
		//Set our "myTextureSampler" sampler to user Texture Uint 0
		glUniform1i(TextureID,0);
	
		//First attribute buffer:vertices
		glEnableVertexAttribArray(0);	//0，第一个属性，即layout=0那个属性值
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);	//激活顶点缓冲区
		glVertexAttribPointer(
			0,	//must match the layout in the shader
			3,	//size ,vec3
			GL_FLOAT,	//type
			GL_FALSE,	//normalized
			0,	//stride
			(void*)0	//array buffer offset
		);
		
		//Second attribute buffer:colors
		glEnableVertexAttribArray(1);	//1, The second attribute:color
		glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);	//激活颜色缓冲区
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		
		//Draw the triangle!
		glDrawArrays(GL_TRIANGLES,0,12*3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	//Cleanup VBO and shader
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1,&TextureID);
	glDeleteVertexArrays(1,&VertexArrayID);

	glfwTerminate();

	return 0;
}

