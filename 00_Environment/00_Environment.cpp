// 00_Environment.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
using namespace std;

//��Ҫ���������,ע��string�����������Ҫ��ת���ַ�'\'
const string additional_include_directories="AdditionalIncludeDirectories=\"..\\include\"";		//"���Ӱ���Ŀ¼" ����ʹ�þ���·���������õ������·��
const string preprocessor_definitions="PreprocessorDefinitions=\"WIN32;_DEBUG;_CONSOLE;GLEW_STATIC\"";	//"Ԥ����������" ����÷ֺŸ���
const string additional_dependencies="AdditionalDependencies=\"glfw3dll.lib opengl32.lib glu32.lib glew32s.lib\"";	//"����������"    ����ÿո����
const string additional_library_directories="AdditionalLibraryDirectories=\"..\\lib\"";			//"���ӿ�Ŀ¼"    ͬ�����·��
const string ingnore_default_library_names="IgnoreDefaultLibraryNames=\"LIBCMT;msvcrt\"";		//"�����ض���"    ����÷ֺŸ���
const string relative_path="RelativePath=\".\\ReadMe.md\"";										//��ReadMe.txt��ΪReadMe.md�������ļ���Ӧ�ط�ҲҪ��

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
			cout<<"Success to rename the file ReadMe.txt to ReadMe.md"<<endl;
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
	vector<const string> vcproj_content;//���������ļ�����
	ifstream f_file_read;
	ofstream f_file_write;
	cout<<"������Ŀ������,����00_config��"<<endl;
	//��Ŀ�����пո������޸�Ϊgetline()
	getline(cin,project_name);

	//������ReadMe.txt�ļ�
	Rename_ReadMe(project_name);
	project_name="..\\"+project_name+"\\"+project_name+".vcproj";						//xxx.vcproj�ļ���·��
	f_file_read.open(project_name.c_str(),ios::in);
	if (!f_file_read)
	{
		cout<<"�ļ���ʧ�ܣ����Ŀ¼���ļ�·���Ƿ���ȷ��������ʹ�á�"<<endl;
		cin.get();
		return -1;
	}
	else
	{
		//���ж�ȡ*.vcproj�ļ��е�����
		string line;
		int line_count=0;//ͳ������
		while(getline(f_file_read,line))
		{
			vcproj_content.push_back(line);
			line_count++;
		}
		f_file_read.close();

		if (229==line_count)
		{//�����������229����˵�������Ѿ����ú��ˣ����ٴ������������ļ�
			cout<<"���ļ��Ѿ����ù��������ظ�����"<<endl;
			cin.get();
		}
		else
		{//û��229������
			string blank="				";//xml�ļ�����룬ǰ���пհ�
			vector<const string>::iterator it=vcproj_content.begin();
			vcproj_content.insert(it+43,blank+additional_include_directories);
			vcproj_content[44]=blank+preprocessor_definitions;					//�滻ԭ���ж����ǲ�������
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