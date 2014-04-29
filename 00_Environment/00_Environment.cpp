// 00_Environment.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
using namespace std;

//需要插入的内容,注意string中如果带引号要用转义字符'\'
const string additional_include_directories="AdditionalIncludeDirectories=\"..\\include\"";		//"附加包含目录" 可以使用绝对路径，这里用的是相对路径
const string preprocessor_definitions="PreprocessorDefinitions=\"WIN32;_DEBUG;_CONSOLE;GLEW_STATIC\"";	//"预处理器定义" 多个用分号隔开
const string additional_dependencies="AdditionalDependencies=\"glfw3dll.lib opengl32.lib glu32.lib glew32s.lib\"";	//"附加依赖库"    多个用空格隔开
const string additional_library_directories="AdditionalLibraryDirectories=\"..\\lib\"";			//"附加库目录"    同理，相对路径
const string ingnore_default_library_names="IgnoreDefaultLibraryNames=\"LIBCMT;msvcrt\"";		//"忽略特定库"    多个用分号隔开
const string relative_path="RelativePath=\".\\ReadMe.md\"";										//把ReadMe.txt改为ReadMe.md，配置文件相应地方也要改

bool Rename_ReadMe(const string &project_name)
{
	string file_name="..\\"+project_name+"\\ReadMe.txt";
	string file_ori=file_name;
	if (!_access(file_name.c_str(),0))
	{
		int dot_index=file_name.find_last_of(".");
		int file_path_length=file_name.length();
		file_name.replace(dot_index+1,file_path_length-1,"md");
		if (!rename(file_ori.c_str(),file_name.c_str()))
		{
			cout<<"Sucess to rename the file ReadMe.txt to ReadMe.md"<<endl;
			return true;
		}
		else
		{
			cerr<<"Failed to rename the file ReadMe.txt!"<<endl;
			return false;
		}
	}
	else
	{
		cerr<<"Failed to Access the file ReadMe.txt!Mybe you have alreadly renamed it,Make sure ReadMe.txt is exist"<<endl;
		return false;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	string project_name;
	vector<const string> vcproj_content;//保存配置文件内容
	ifstream f_file_read;
	ofstream f_file_write;
	cout<<"输入项目的名字,例如00_config："<<endl;
	cin>>project_name;

	//重命名ReadMe.txt文件
	Rename_ReadMe(project_name);
	project_name="..\\"+project_name+"\\"+project_name+".vcproj";						//xxx.vcproj文件的路径
	f_file_read.open(project_name.c_str(),ios::in);
	if (!f_file_read)
	{
		cout<<"文件打开失败！检查目录及文件路径是否正确或者正在使用。"<<endl;
		return -1;
	}
	else
	{
		//逐行读取*.vcproj文件中的内容
		string line;
		int line_count=0;//统计行数
		while(getline(f_file_read,line))
		{
			vcproj_content.push_back(line);
			line_count++;
		}
		f_file_read.close();

		if (229==line_count)
		{//如果行数等于229，则说明环境已经配置好了，不再处理，否则配置文件
			cout<<"该文件已经配置过，请勿重复配置"<<endl;
		}
		else
		{//没有229行则处理
			string blank="				";//xml文件里对齐，前面有空白
			vector<const string>::iterator it=vcproj_content.begin();
			vcproj_content.insert(it+43,blank+additional_include_directories);
			vcproj_content[44]=blank+preprocessor_definitions;					//替换原有行而不是插入新行
			vcproj_content.insert(it+63,blank+additional_dependencies);
			vcproj_content.insert(it+65,blank+additional_library_directories);
			vcproj_content.insert(it+66,blank+ingnore_default_library_names);
			vcproj_content[222]=blank+relative_path;

			f_file_write.open(project_name.c_str(),ios::out);
			while(it!=vcproj_content.end()&&f_file_write)
			{
				cout<<it->data()<<endl;
				f_file_write<<it->data()<<endl;
				++it;
			}
			f_file_write.close();
		}	
	}

	return 0;
}
