#include "common/texture.hpp"

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

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

	//直接取值，没有滤波
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	//3线性采样
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;

}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char* imagepath)
{
	unsigned char header[124];

	//try to open the file
	ifstream file;
	file.open(imagepath,ios::in | ios::binary);
	if (file.fail())
	{
		cerr<<"Open the file failed!"<<endl;
		return 0;
	}

	//verify the type of file
	char filecode[4];
	file.read(filecode,4);	//0~3
	//cout<<file.tellg()<<endl; //the result is 4
	if(strncmp(filecode,"DDS ",4)!=0)
	{
		file.close();
		return 0;
	}

	//get the surface desc,不包括"DDS "(0~3)，从4开始读
	file.read((char*)header,124);

	unsigned int height =*(unsigned int*)&(header[8]);
	unsigned int width =*(unsigned int*)&(header[12]);
	unsigned int linearSize =*(unsigned int*)&(header[16]);
	unsigned int mipMapCount =*(unsigned int*)&(header[24]);
	unsigned int fourCC =*(unsigned int*)&(header[80]);

	//文件头之后是真正的数据：紧接着是mipmap层级
	unsigned char* buffer;
	unsigned int bufsize;
	//how big is it going to be including all mipmaps?
	bufsize = mipMapCount >1 ? linearSize*2 : linearSize;
	buffer = new unsigned char[bufsize];
	file.read((char*)buffer,bufsize);
	file.close();

	//处理三种格式：DXT1、DXT3,DXT5
	unsigned int components = (fourCC == FOURCC_DXT1) ? 3:4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format=GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	default:
		delete [] buffer;
		return 0;
	}

	GLuint textureID;
	glGenTextures(1,&textureID);

	//"Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D,textureID);

	//逐个填充mipmap
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8:16;
	unsigned int offset = 0;

	//load the mipmaps
	for (unsigned int level=0;level<mipMapCount && (width || height);++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D,level,format,width,height,0,size,buffer+offset);
		offset += size;
		width /= 2;
		height /= 2;
	}

	delete [] buffer;

	return textureID;
}
