#include "stdafx.h"

#include <iostream>
using namespace std;

#include <gl/glew.h>
#include <glfw/glfw3.h>

int main()
{
	//GLuint image=loadBMP_custom("uvtemplate.bmp");
	if (!glfwInit())
	{
		cerr<<"Failed to initialize GLFW"<<endl;
		return -1;
	}

	for (int i=0;i<10000;++i)
	{
		cout<<glfwGetTime()<<endl;
	}
	return 0;
}