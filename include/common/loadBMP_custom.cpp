#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#include <gl/glew.h>
#include "common/loadBMP_custom.hpp"

GLuint loadBMP_custom(const char * imagepath)
{

	//Data read from the header of the BMP file
	unsigned char header[54];		//Each BMP file begins by a 54-bytes header
	unsigned int dataPos;		//Position in the file where the actual data begins
	unsigned int width,height;
	unsigned int imageSize;		//=width*height*3
	//Actual RGB data
	unsigned char* data;

	//Open the file
	ifstream file;
	file.open(imagepath,ios::in|ios::out|ios::binary);
	if (file.fail())
	{
		cerr<<"Open the file failed!"<<endl;
		return 0;
	}
	file.seekg(54,ios::beg);
	int cur_position=file.tellg();
	if (cur_position!=54)
	{
		cerr<<"Not a correct BMP file"<<endl;
		return 0;
	}
	else
	{
		file.seekg(0,ios::beg);
		file.read((char*)header,54);
	}

	//Check the two first bytes are really 'B' and 'M'
	if (header[0]!='B' || header[1]!='M')
	{
		cerr<<"Not a correct BMP file!"<<endl;
		return 0;
	}
	
	//Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E])!=0)
	{	//压缩说明，为0说明不压缩
		cerr<<"Not a correct BMP file"<<endl;
		return 0;
	}
	if (*(int*)&(header[0x1C])!=24)
	{	//每个像素的位数
		cerr<<"Not a 24bpp BMP file"<<endl;
		return 0;
	}
	//Read ints from the byte array,
	//(int*)指针强制转换,四个字节,按照内存中存放顺序反着读
	dataPos=*(int*)&(header[0x0A]);	//00000036H=54
	imageSize=*(int*)&(header[0x22]);	//00000000H=0
	width=*(int*)&(header[0x12]);		//00000200H=512
	height=*(int*)&(header[0x16]);	//00000200H=512

	//Some BMP files are misformatted, guess missing information
	if (imageSize==0)
	{	//3: one byte for each Red,Green and Blue component
		imageSize=width*height*3;
	}
	if (dataPos==0)
	{	// The BMP header is done that way
		dataPos=54;
	}

	// Now we know the size of the image. Create a buffer
	data=new unsigned char[imageSize];

	//Read the actual data from the file into the buffer
	file.seekg(dataPos,ios::beg);
	file.read((char*)data,imageSize);

	//Everything is in memory now, the file can be closed
	file.close();
	
	//Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1,&textureID);

	//"Bind" the newly created texture:all future texture function will modify this texture
	glBindTexture(GL_TEXTURE_2D,textureID);

	//Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,data);

	//OpenGL has now copied the data.Free our own version
	delete [] data;

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	return textureID;

}