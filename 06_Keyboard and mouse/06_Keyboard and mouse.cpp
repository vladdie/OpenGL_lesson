// 06_Keyboard and mouse.cpp : 定义控制台应用程序的入口点。
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

#include <common/texture.hpp>
#include <common/shader.hpp>
#include <common/controls.hpp>

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

	//window=glfwCreateWindow(800,450,"05_A textured cube",glfwGetPrimaryMonitor(),NULL);
	window=glfwCreateWindow(WIDTH,HEIGHT,"06_Keyboard and mouse",NULL,NULL);
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
	glfwSetCursorPos(window,WIDTH/2,HEIGHT/2);
	glClearColor(0.0f,0.0f,0.4f,0.0f);

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	//把没有朝向相机的三角形剔除掉
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Create and compile our GLSL program from the shaders
	GLuint programID=LoadShaders("TransformVertexShader.vertexshader","TextureFragmentShader.fragmentshader");

	//Create a handle for our 'MVP' uniform
	GLuint MatrixID=glGetUniformLocation(programID,"MVP");

	//Load the texture using the methods we write just now
	//GLuint Texture=loadBMP_custom("uvtemplate.bmp");
	GLuint Texture=loadDDS("uvtemplate.DDS");

	//Get a handle for our "myTextureSampler" uniform
	GLuint TextureID=glGetUniformLocation(programID,"myTextureSampler");

	//Our vertices.Three consecutive floats give a 3D vertex;Three consecutive vertices give a triangle.
	//A cube has 6 faces with 2 triangles each,so this makes 6*2=12 triangles,and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[]={
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
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
		0.000059f, 0.000004f, 
		0.000103f, 0.336048f, 
		0.335973f, 0.335903f, 
		1.000023f, 0.000013f, 
		0.667979f, 0.335851f, 
		0.999958f, 0.336064f, 
		0.667979f, 0.335851f, 
		0.336024f, 0.671877f, 
		0.667969f, 0.671889f, 
		1.000023f, 0.000013f, 
		0.668104f, 0.000013f, 
		0.667979f, 0.335851f, 
		0.000059f, 0.000004f, 
		0.335973f, 0.335903f, 
		0.336098f, 0.000071f, 
		0.667979f, 0.335851f, 
		0.335973f, 0.335903f, 
		0.336024f, 0.671877f, 
		1.000004f, 0.671847f, 
		0.999958f, 0.336064f, 
		0.667979f, 0.335851f, 
		0.668104f, 0.000013f, 
		0.335973f, 0.335903f, 
		0.667979f, 0.335851f, 
		0.335973f, 0.335903f, 
		0.668104f, 0.000013f, 
		0.336098f, 0.000071f, 
		0.000103f, 0.336048f, 
		0.000004f, 0.671870f, 
		0.336024f, 0.671877f, 
		0.000103f, 0.336048f, 
		0.336024f, 0.671877f, 
		0.335973f, 0.335903f, 
		0.667969f, 0.671889f, 
		1.000004f, 0.671847f, 
		0.667979f, 0.335851f
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

		//Compute the MVP matrix from keybord and mouse input
		computeMatricesFromInputs();
		//Projection Matrix
		glm::mat4 ProjectionMatrix=getProjectionMatrix();
		//Camera matrix
		glm::mat4 ViewMatrix=getViewMatrix();
		//Model matrix:an identity matrix(model will be at the origin)
		glm::mat4 ModelMatrix=glm::mat4(1.0f);
		//Our ModelViewProjection:multiplication of our 3 matrices
		glm::mat4 MVP=ProjectionMatrix*ViewMatrix*ModelMatrix;

		//Send our transformation to the currently bound shader,in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);

		//Bind our texture in Texture Unit 0
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

