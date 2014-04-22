========================================================================
    控制台应用程序：00_environment 项目概述
========================================================================
	这个程序主要是用来处理运行glfw，glew，glm运行库时的环境配置问题
每个项目的环境配置信息保存在项目文件夹下的.vcproj文件中，我们可
以直接编辑而不用每次都去VS里项目的属性中配置。

	以00_config项目为例，在00_config文件夹下有个00_config.vcproj文件，
打开00_config.vcproj文件，找到我们需要改动的地方：

44	AdditionalIncludeDirectories="C:\Users\Administrator\Documents\Visual Studio 2008\Projects\OpenGL_lesson\include"
45	PreprocessorDefinitions="WIN32;_DEBUG;_CONSOLE;GLEW_STATIC"

64	AdditionalDependencies="glfw3dll.lib opengl32.lib glu32.lib glew32s.lib"
66	AdditionalLibraryDirectories="C:\Users\Administrator\Documents\Visual Studio 2008\Projects\OpenGL_lesson\lib"
67	IgnoreDefaultLibraryNames="msvcrt;LIBCMT"

所以我们只需要在我们新建的项目中对应的行插入这些内容就可以了,注意这些行号都是插入以后的行号，注意
换算	

/////////////////////////////////////////////////////////////////////////////