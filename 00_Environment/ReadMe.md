========================================================================
    控制台应用程序：00_Environment 项目概述
========================================================================
&emsp;&emsp;每个用Glfw,Glew,OpenGL,Glm的项目，都需要在项目属性中配置相关的附加包含目录，库，等等，我们可以直接改项目的配置
文件来达到同样的目的

**1.修改ReadMe.txt文件**
> 为了保证ReadMe.txt支持Markdown语法，将项目中默认的ReadMe.txt改为ReadMe.md，实现的函数为Rename_ReadMe()函数

**2.修改项目下的*.vcproj文件**
&emsp;&emsp;直接改对应行的内容，新建一个工程*.vcproj有225行，配置好环境后有229行，所以对比不同很容易得到需要插入修改的行,对比发现配置好的文件内容不同的地方如下：
> 
    44	AdditionalIncludeDirectories="&quot;C:\Users\Administrator\Documents\Visual Studio 2008\Projects\OpenGL_lesson\include&quot;"
    45	PreprocessorDefinitions="WIN32;_DEBUG;_CONSOLE;GLEW_STATIC"
    64	AdditionalDependencies="glfw3dll.lib glew32s.lib opengl32.lib glu32.lib"
    66	AdditionalLibraryDirectories="&quot;C:\Users\Administrator\Documents\Visual Studio 2008\Projects\OpenGL_lesson\lib&quot;"
    67	IgnoreDefaultLibraryNames="LIBCMT"
    223 RelativePath=".\ReadMe.md"

**NOTE:** 223行换不换都行，如果不想替换，对应的地方注释掉就行,另外为了简单，我把绝对路劲都换成了相对路径，效果是一样的
