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
	
	//One color for each vertex.They were generated randomly.
	static const GLfloat g_color_buffer_data[]={
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
	
	GLuint colorbuffer;
	glGenBuffers(1,&colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer_data),g_color_buffer_data,GL_STATIC_DRAW);

	do 
	{
		//Enable depth test
		glEnable(GL_DEPTH_TEST);
		//Accept fragment if it coloser to the camera than the former one
		glDepthFunc(GL_LESS);

		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除颜色缓冲以及深度缓冲

		//Use our shader
		glUseProgram(programID);

		//Send our transformation to the currently bound shader,in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);
	
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
		glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);	//激活颜色缓冲区
		glVertexAttribPointer(
			1,
			3,
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
	glDeleteBuffers(1,&colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1,&VertexArrayID);

	glfwTerminate();

	return 0;
}

