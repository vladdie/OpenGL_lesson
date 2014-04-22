### OpenGL学习笔记，使用VS2008+glfw+glew+glm
-----------------------
#### 配置环境
配置环境：
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
		glfw3dll.lib
		opengl32.lib
		glu32.lib
		glew32s.lib
	5.忽略特定库，添加LIBCMT
