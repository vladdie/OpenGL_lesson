// 02_The first triangle.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;
//Include GLEW.Always include it before gl.h and glfw.h,since it's a bit magic
#include <gl/glew.h>
//Include GLFW
#include <glfw/glfw3.h>
//Include GLM
#include <glm/glm.hpp>
using namespace glm;

int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize GLFW
	if (!glfwInit())
	{
		cerr<<"Failed to initialize GLFW!"<<endl;
		return -1;
	}

	//��������
	glfwWindowHint(GLFW_SAMPLES,4); //4x antialiasing
//	glfwWindowHint(GLFW_VERSION_MAJOR,4); //We want OpenGL 4.4
//	glfwWindowHint(GLFW_VERSION_MINOR,0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Open a window and create its OpenGL context
	GLFWwindow* window;		//ȫ�ֱ��� 
	window=glfwCreateWindow(1920,1080,"02_The first triangle",NULL,NULL);
	if (window==NULL)
	{
		cerr<<"Failed to open GLFW window.Maybe your GPU is not supported!"<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	if (glewInit()!=GLEW_OK)
	{
		cerr<<"Failed to initialize GLEW"<<endl;
		return -1;
	}
	//Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//OpenGL�����Ĵ����ɹ�,���������������(VAO)
	GLuint VertexArrayID;
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//An array of 3 vectors which represents 3 vertices{X,Y,Z}
	static const GLfloat g_vertex_buffer_data[]={
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,
	};
	
	//��һ����ͨ���������������δ���OpenGL

	//This  will identify our vertex buffer
	GLuint vertexbuffer;
	//Generate 1 buffer,put the resulting identifier in vertexbuffer
	glGenBuffers(1,&vertexbuffer);
	//The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);

	//Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);

	do 
	{
		//Draw whatever we want,first attribute buffer:vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(
			0,		//attribute 0.No particular reason for 0,but must match the layout in the shader.
			3,		//size
			GL_FLOAT,//type
			GL_FALSE,//normalized?
			0,		//stride,��Ծ��0����
			(void*)0//array buffer offset
			);
		//Draw the triangle!
		glDrawArrays(GL_TRIANGLES,0,3);// Starting from vertex 0;3 vertices total ->1 triangle
		glDisableVertexAttribArray(0);
		
		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Check if the ESC key was pressed or the window was closed 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	glfwTerminate();
	return 0;
}
