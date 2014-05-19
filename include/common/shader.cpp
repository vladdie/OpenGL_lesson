#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include "shader.hpp"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
	//Create the shaders
	GLuint VertexShaderID=glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);

	//Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path,ios::in);
	if (VertexShaderStream.is_open())
	{
		string Line="";
		while(getline(VertexShaderStream,Line))
			VertexShaderCode+="\n"+Line;
		VertexShaderStream.close();
	} 
	else
	{
		cerr<<"Impossible to open:"<<vertex_file_path<<"Are you in the right directory? Don't forget to read the FAQ!"<<endl;
		cin.get();
		return 0;
	}

	//Read the Fragment Shader code from the file
	string FragmentShderCode;
	ifstream FragmentShaderStream(fragment_file_path,ios::in);
	if (FragmentShaderStream.is_open())
	{
		string Line="";
		while(getline(FragmentShaderStream,Line))
			FragmentShderCode+="\n"+Line;
		FragmentShaderStream.close();
	}
	
	GLint Result=GL_FALSE;
	int InfoLogLength;

	//Compile Vertex Shader
	cout<<"Compiling shader:"<<vertex_file_path<<endl;
	char const* VertexSourcePointer=VertexShaderCode.c_str();
	glShaderSource(VertexShaderID,1,&VertexSourcePointer,NULL);
	glCompileShader(VertexShaderID);

	//Check Vertex Shader
	glGetShaderiv(VertexShaderID,GL_COMPILE_STATUS,&Result);
	glGetShaderiv(VertexShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);
	if (InfoLogLength>0)
	{
		vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID,InfoLogLength,NULL,&VertexShaderErrorMessage[0]);
		cerr<<&VertexShaderErrorMessage[0]<<endl;
	}

	//Compile Fragment Shader
	cout<<"Compiling shader:"<<fragment_file_path<<endl;
	char const* FragmentSourcePointer=FragmentShderCode.c_str();
	glShaderSource(FragmentShaderID,1,&FragmentSourcePointer,NULL);
	glCompileShader(FragmentShaderID);

	//Check Fragment Shader
	glGetShaderiv(FragmentShaderID,GL_COMPILE_STATUS,&Result);
	glGetShaderiv(FragmentShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);
	if (InfoLogLength>0)
	{
		vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID,InfoLogLength,NULL,&FragmentShaderErrorMessage[0]);
		cerr<<&FragmentShaderErrorMessage[0]<<endl;
	}

	//Link the program
	cout<<"Linking program"<<endl;
	GLuint ProgramID=glCreateProgram();
	glAttachShader(ProgramID,VertexShaderID);
	glAttachShader(ProgramID,FragmentShaderID);
	glLinkProgram(ProgramID);

	//Check the program
	glGetProgramiv(ProgramID,GL_LINK_STATUS,&Result);
	glGetProgramiv(ProgramID,GL_INFO_LOG_LENGTH,&InfoLogLength);
	if (InfoLogLength>0)
	{
		vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID,InfoLogLength,NULL,&ProgramErrorMessage[0]);
		cerr<<&ProgramErrorMessage[0]<<endl;
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}