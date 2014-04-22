// 00_environment.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//��Ҫ���������,ע��string�����������Ҫ��ת���ַ�'\'
const string additional_include_directories="AdditionalIncludeDirectories=\"..\\include\"";		//"���Ӱ���Ŀ¼" ����ʹ�þ���·���������õ������·��
const string preprocessor_definitions="PreprocessorDefinitions=\"WIN32;_DEBUG;_CONSOLE;GLEW_STATIC\"";	//"Ԥ����������" ����÷ֺŸ���
const string additional_dependencies="AdditionalDependencies=\"glfw3dll.lib opengl32.lib glu32.lib glew32s.lib\"";	//"����������"    ����ÿո����
const string additional_library_directories="AdditionalLibraryDirectories=\"..\\lib\"";			//"���ӿ�Ŀ¼"    ͬ�����·��
const string ingnore_default_library_names="IgnoreDefaultLibraryNames=\"LIBCMT;msvcrt\"";		//"�����ض���"    ����÷ֺŸ���

int _tmain(int argc, _TCHAR* argv[])
{
	string project_name;
	vector<const string> vcproj_content;//���������ļ�����
	ifstream f_file_read;
	ofstream f_file_write;
	cout<<"������Ŀ������,����00_config��"<<endl;
	cin>>project_name;
	project_name="..\\"+project_name+"\\"+project_name+".vcproj";						//xxx.vcproj�ļ���·��
	f_file_read.open(project_name.c_str(),ios::in);
	if (!f_file_read)
	{
		cout<<"�ļ���ʧ�ܣ����Ŀ¼���ļ�·���Ƿ���ȷ��������ʹ�á�"<<endl;
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
		}
		else
		{//û��229������
			vector<const string>::iterator it=vcproj_content.begin();
			string blank="				";//xml�ļ�����룬ǰ���пհ�
			vcproj_content.insert(it+43,blank+additional_include_directories);
			vcproj_content[44]=blank+preprocessor_definitions;					//�滻ԭ���ж����ǲ�������
			vcproj_content.insert(it+63,blank+additional_dependencies);
			vcproj_content.insert(it+65,blank+additional_library_directories);
			vcproj_content.insert(it+66,blank+ingnore_default_library_names);

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

