// 01_firstWindow.cpp : 定义控制台应用程序的入口点。
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

	//创建窗口
	glfwWindowHint(GLFW_SAMPLES,4); //4x antialiasing
//	glfwWindowHint(GLFW_VERSION_MAJOR,3); //We want OpenGL 4.4
//	glfwWindowHint(GLFW_VERSION_MINOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Open a window and create its OpenGL context
	GLFWwindow* window;		//全局变量 
	window=glfwCreateWindow(1092,1080,"01_firstWindow",NULL,NULL);
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
	do 
	{
		//Draw nothing,see you in 02

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Check if the ESC key was pressed or the window was closed 
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
	
	return 0;
}

