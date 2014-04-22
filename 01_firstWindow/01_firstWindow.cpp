// 01_firstWindow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;
//Include GLEW.Always include it before gl.h and glfw.h,since it's a bit magic
#include <gl/glew.h>
//Include GLFW
#include <glfw/glfw3.h>
GLFWwindow* window;		//global variable

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

	//Create a window
	glfwWindowHint(GLFW_SAMPLES,4); //4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);	//use OpenGL 4.0.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Open a window and create its OpenGL context
	window=glfwCreateWindow(1920,1080,"01_firstWindow",NULL,NULL);
	if (window==NULL)
	{
		cerr<<"Failed to open GLFW window.Maybe your GPU is not supported!"<<endl;
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

	//Dark blue background
	glClearColor(0.0f,0.0f,0.4f,0.0f);
	do 
	{
		//Draw nothing,see you in 02_the_first_triangle

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Check if the ESC key was pressed or the window was closed 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	//Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

