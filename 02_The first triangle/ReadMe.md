========================================================================
    控制台应用程序：02_The first triangle 项目概述
========================================================================
配置环境：
> 
本程序是基于OpenGL,GLFW,GLEW,GLM，项目如果要正常运行，需要正确配置环境
1.C/C++->常规->附加包含目录，添加include文件夹，include目录结构如下：
├─GL
├─GLFW
└─glm
	├─detail
	├─gtc
	├─gtx
	└─virtrev
2.C/C++->常规->预处理器定义,添加GLEW_STATIC
3.链接器->常规->附加库目录，添加lib文件夹,其中包含两个文件glew32s.lib;glfw3dll.lib
4.链接器->输入->附加依赖项，添加
4.链接器->输入->附加依赖项，添加
	glfw3dll.lib
	opengl32.lib
	glu32.lib
	glew32s.lib
5.忽略特定库，添加LIBCMT

**NOTE:**关于shader.cpp和shader.hpp文件需要注意的地方，我将这两个文件放到了common文件夹下，
而common文件夹放在了include文件夹下,在用shader.hpp时，记得在项目-->源文件-->添加-->现有项 把
shader.cpp添加进来，否则在编译的时候会提示无法解析LoadShaders这个函数，还有就是如果提示预编译头
的问题可以在项目属性里C/C++-->预编译头-->创建/使用预编译头 设置为不使用预编译头
	
	
	