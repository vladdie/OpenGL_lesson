    控制台应用程序：03_Matrices 项目概述
========================================================================
主要讲了一下OpenGL中的坐标

* 观察坐标系
* 世界坐标系
* 模型坐标系

OpenGL中的各种矩阵

* 平移、旋转、缩放
* 投影矩阵
* 视图LookAt

C++和GLSL中如何变换

几个函数解释一下
> - void glUniformMatrix4fv(GLint location,  GLsizei count,  GLboolean transpose,  const GLfloat *value);
**参数列表：**
location
指明要更改的uniform变量的位置
count
指明要更改的矩阵个数
transpose
指明是否要转置矩阵，并将它作为uniform变量的值,OpenGL ES中必须为GL_FALSE。
value
指明一个指向count个元素的指针，用来更新指定的uniform变量。
**描述：**
glUniform更改一个uniform变量或数组的值。要更改的uniform变量的位置由location指定，location的值应该由glGetUniformLocation函数返回。通过调用glUseProgram，glUniform操作的程序对象将成为当前状态的一部分。glUniform{1|2|3|4}{f|i}使用传进来的实参，修改通过location指定的uniform变量。所有在程序对象中定义的活动uniform变量，在程序对象链接成功后都会被初始化为0.直到下一次程序对象链接成功再一次被初始化为0前，它们将保留通过调用glUniform赋给它们的值。glUniform{1|2|3|4}{f|i}v可以用来更改单个uniform变量的值，或者一个uniform变量数组。glUniformMatrix{2|3|4}fv用来更改一个矩阵或一个矩阵数组。
**NOTE:**另外要强调一点的是，glUniformMatrix4fv是默认将数组以列向量的形式存放在矩阵中的，即对于四个向量 (a,b,c,d);(e,f,g,h);(i,j,k, l)；(m, n, o, p)，存放在一个数组中，构成——{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}，那么通过调用glUniformMatrix4fv函数，并且第三个参数传递为GL_FALSE，那么获得的矩阵其实是：[a, e, i, m; b, f, j, n; c, g, k, o; d, h, l, p]。如果要将数组中的元素作为行向量传递到	uniform的矩阵中，那么第三个形参transpose应该传给它GL_TRUE值。	
- void glEnableVertexAttribArray(GLuint index)/void glDisableVertexAttribArray(	GLuint index);
Specifies the index of the generic vertex attribute to be enabled or disabled.