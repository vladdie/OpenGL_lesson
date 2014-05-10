#include "stdafx.h"

#include <iostream>
using namespace std;

#include <gl/glew.h>
#include <Windows.h>
#include <common/loadBMP_custom.hpp>

int main()
{
	GLuint image=loadBMP_custom("uvtemplate.bmp");
	
	return 0;
}