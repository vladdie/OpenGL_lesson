###引言
&emsp;&emsp;一个OpenGL程序可以用多种方式和shader通信。注意这种通信是单向的，因为shader的输出只能是渲染到某些目标，比如颜色和深度缓存。OpenGL的部分状态可以被shader访问，因此程序改变OpenGL某些状态就可以与shader进行通信了。例如一个程序想把光的颜色传给shader，可以直接调用OpenGL接口，就像使用固定功能流水线时做的那样。不过，使用OpenGL状态并不是设置shader中使用数据的直观方式。比如一个shader需要一个表示时间变化的变量来计算动画，在OpenGL状态中就没有现成的变量可用。当然，你可以使用没有用到的“镜面光截止角度（cutoffangle）”这样一个变量表示时间，但显然让人难以接受。幸运的是，GLSL允许用户自定义变量，实现OpenGL应用程序与shader通信。有了这个功能，你就可以命名一个叫做timeElapsed的变量表示经过的时间。
上文的讨论涉及到了GLSL提供的两种类型修饰符（更多的类型将在后面提到）：
> 
一致变量（Uniform）
属性（Attribute）

&emsp;&emsp;在shader中定义的变量如果用这两种类型修饰符，表示对shader来说，它们是只读的。下面将详细讲述怎样使用这些类型的变量。
还有一种将变量送给shader的方法：使用纹理。一个纹理不止可以表示一张图片，它还可以表示一个数组。事实上，你完全可以决定如何在shader中解释纹理数据，即使它真是一幅图片。
数据类型和变量
下面是GLSL中的基本数据类型：
> 
float
bool
int

浮点类型与C中类似，布尔类型可以为true或false。这些基本类型可以组成2、3或4维向量，如下所示：

fvec{2,3,4} | a vector of 2,3,or 4 floats
------------|----------------------------
bvec{2,3,4} | bool vector
ivec{2,3,4} | vector of integers

GLSL还包括2×2、3×3或4×4型矩阵，因为这些矩阵类型在图形处理中很常用：
> 
mat2
mat3
mat4

此外，还有一组用来实现纹理访问的特殊类型，它们被称为采样器（sampler），在读取纹理值（也称为纹素texel）时用到。下面就是纹理采样用到的数据类型：

sampler1D | for 1D textures
----------|------------------
sampler2D | for 2D textures
sampler3D | for 3D textures
samplerCube | for cube map textures
sampler1DShadow | for shadow maps
sampler2DShadow | for shadow maps

在GLSL中，可以像C一样声明和访问数组，但是不能在声明时初始化数组。GLSL还可以定义结构体：
```cpp
struct dirlight
{
    vec3 direction;
    vec3 color;
};
```
变量声明一个基本类型变量的方法与C类似，你还可以在声明它的同时进行初始化。
```cpp
float a,b;       // two vector (yes, the comments are like in C)
int c = 2;       // c is initialized with 2
bool d = true;  // d is true
```
声明其它类型变量也是按照这种方法，但是初始化与C语言有区别。GLSL非常依赖构造函数实现初始化和类型转换。、
```cpp
float b = 2;          // incorrect, there is no automatic type casting
float e = (float)2; // incorrect, requires constructors for type casting
int a = 2;
float c = float(a); // correct. c is 2.0
vec3 f;                // declaring f as a vec3
vec3 g = vec3(1.0,2.0,3.0); // declaring and initializing g
```
在GLSL中使用一些变量初始化其它变量是非常灵活的。你只需要给出需要的数据成员即可。请看下面的例子：
```cpp
vec2 a = vec2(1.0,2.0);
vec2 b = vec2(3.0,4.0);
vec4 c = vec4(a,b)   // c = vec4(1.0,2.0,3.0,4.0);
vec2 g = vec2(1.0,2.0);
float h = 3.0;
vec3 j = vec3(g,h);
```
矩阵的初始化也是类似方法，矩阵包含很多种构造函数，下面的例子给出了一些初始化矩阵的构造函数：
```cpp
mat4 m = mat4(1.0)   // initializing the diagonal of the matrix with 1.0
vec2 a = vec2(1.0,2.0);
vec2 b = vec2(3.0,4.0);
mat2 n = mat2(a,b); // matrices are assigned in column major order
mat2 k = mat2(1.0,0.0,1.0,0.0); // all elements are specified
```
下面的例子给出了初始化结构体的方法：
```cpp
struct dirlight     // type definition
{
    vec3 direction;
    vec3 color;
};
dirlight d1;
dirlight d2 = dirlight(vec3(1.0,1.0,0.0),vec3(0.8,0.8,0.4));
```
在GLSL中还有一些实用的选择子（selector），可以简化我们的操作并让代码更简洁。访问一个向量可以使用如下的方法：
```cpp
vec4 a = vec4(1.0,2.0,3.0,4.0);
float posX = a.x;
float posY = a[1];
vec2 posXY = a.xy;
float depth = a.w;
```
在上面的代码片段中，可以使用`x,y,z,w`来访问向量成员。如果是颜色的话可以使用`r,g,b,a`,如果是纹理坐标的话可以使用`s,t,p,q`。注意表示纹理坐标通常是使用`s,t,r,q`,但r已经表示颜色中的红色（red）了，所以纹理坐标中需要使用p来代替。矩阵的选择子可以使用一个或两个参数，比如m[0]或者m[2][3]。第一种情况选择了第一列，第二种情况选择了一个数据成员。
对于结构体来说，可以像在C语言中一样访问其成员。所以访问前面定义的结构体，可以使用如下的代码：
```cpp
d1.direction = vec3(1.0,1.0,1.0);
```
变量修饰符
修饰符给出了变量的特殊含义，GLSL中有如下修饰符：

const  | 声明一个编译期常量。
-------|---------------------------
attribute | 随不同顶点变化的全局变量，由OpenGL应用程序传给顶点shader。这个修饰符只能用在顶点shader中，在shader中它是一个只读变量。
uniform | 随不同图元变化的全局变量（即不能在glBegin/glEnd中设置），由OpenGL应用程序传给shader。这个修饰符能用在顶点和片断shader中，在shader中它是一个只读变量。
varying | 用于顶点shader和片断shader间传递的插值数据，在顶点shader中可写，在片断shader中只读。

#### 一致变量（Uniform Variables）
&emsp;&emsp;不同于顶点属性在每个顶点有其自己的值，一个一致变量在一个图元的绘制过程中是不会改变的，所以其值不能在`glBegin/glEnd`中设置。一致变量适合描述在一个图元中、一帧中甚至一个场景中都不变的值。一致变量在顶点`shader`和片断`shader`中都是只读的。首先你需要获得变量在内存中的位置，这个信息只有在连接程序之后才可获得。注意，对某些驱动程序，在获得存储位置前还必须使用程序（调用`glUseProgram`）。获取一个一致变量的存储位置只需要给出其在shader中定义的变量名即可：
```cpp
GLint glGetUniformLocation(GLuint program, const char *name);
```
**参数：**

program | the hanuler to the program
--------|----------------------------
name | the name of the variable

&emsp;&emsp;返回值就是变量位置，可以用此信息设置变量的值。根据变量的数据类型不同，有一系列函数可以用来设置一致变量。用来设置浮点值的一组函数如下：
```cpp
void glUniform1f(GLint location, GLfloat v0);
void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
```
或者
```cpp
GLint glUniform{1,2,3,4}fv(GLint location, GLsizei count, GLfloat *v);
```
**参数：**

location | the previously queried location
---------|--------------------------------
v0,v1,v2,v3 | float values
count | the number of elements in the array
v | an array of floats

&emsp;&emsp;对integer类型也有一组类似的函数，不过要用i替换函数中的f。对bool类型没有专门的函数，但可以使用整数的0和1来表示真假。一旦你使用了一致变量数组，那么就必须使用向量版本的函数。
对sampler变量，使用函数glUniform1i和glUniform1iv。
矩阵也是一种GLSL的数据类型，所以也有一组针对矩阵的函数：
```cpp
GLint glUniformMatrix{2,3,4}fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
```
**参数：**

location | the previously queried location.
---------|----------------------------------
count | the number of matrices. 1 if a single matrix is being set, or n for an array of n matrices.
transpose | wheter to transpose the matrix values. A value of 1 indicates that the matrix values are specified in row major order, zero is column major order
v | an array of floats.

**NOTE:**还有一点要注意的是：使用这些函数之后，变量的值将保持到程序再次连接之时。一旦进行重新连接，所有变量的值将被重置为0。
最后是一些示例代码。假设一个shader中使用了如下变量：
```cpp
uniform float specIntensity;
uniform vec4 specColor;
uniform float t[2];
uniform vec4 colors[3];
```
在OpenGL程序中可以使用下面的代码设置这些变量：
```cpp
GLint loc1,loc2,loc3,loc4;
float specIntensity = 0.98;
float sc[4] = {0.8,0.8,0.8,1.0};
float threshold[2] = {0.5,0.25};
float colors[12] = {
    0.4,0.4,0.8,1.0,
    0.2,0.2,0.4,1.0,
    0.1,0.1,0.1,1.0
    };

loc1 = glGetUniformLocation(p,"specIntensity");
glUniform1f(loc1,specIntensity);

loc2 = glGetUniformLocation(p,"specColor");
glUniform4fv(loc2,1,sc);

loc3 = glGetUniformLocation(p,"t");
glUniform1fv(loc3,2,threshold);

loc4 = glGetUniformLocation(p,"colors");
glUniform4fv(loc4,3,colors);
```

&emsp;&emsp;注意设置一个数组（例子中的t）与设置四元向量（例子中的colors和specColor）的区别。中间的count参数指在shader中声明的数组元素数量，而不是在OpenGL程序中声明的。所以虽然specColor包含4个值，但glUniform4fv函数中的参数是1，因为它只是一个向量。另一种设置specColor的方法：
```cpp
loc2 = glGetUniformLocation(p,"specColor");
glUniform4f(loc2,sc[0],sc[1],sc[2],sc[3]);
```
GLSL中还可以获取数组中某个变量的地址。比如，可以获得t[1]的地址。下面的代码片段展示了设置t数组元素的另一种方法：
```cpp
loct0 = glGetUniformLocation(p,"t[0]");
glUniform1f(loct0,threshold[0]);

loct1 = glGetUniformLocation(p,"t[1]");
glUniform1f(loct1,threshold[1]);
```
**NOTE:**注意在`glGetUniformLocation`中使用方括号指示的变量。

#### 属性变量（Attribute Variables）
&emsp;&emsp;在前一节提到，一致变量只能针对一个图元全体，就是说不能在`glBegin和glEnd`之间改变。如果要针对每个顶点设置变量，那就需要属性变量了。事实上属性变量可以在任何时刻更新。在顶点shader中属性变量是只读的。因为它包含的是顶点数据，所以在片断shader中不能直接应用。与一致变量相似，首先你需要获得变量在内存中的位置，这个信息只有在连接程序之后才可获得。注意，对某些驱动程序，在获得存储位置前还必须使用程序。
```cpp
GLint glGetAttribLocation(GLuint program,char *name);
```
**参数：**

program | the handle to the program
----------|----------------------------
name | the name of the variable

上述函数调用的返回变量在存储器中的地址。下面就可以为它指定一个值，类似一致变量，每种数据类型都有对应的函数。
```cpp
void glVertexAttrib1f(GLint location, GLfloat v0);
void glVertexAttrib2f(GLint location, GLfloat v0, GLfloat v1);
void glVertexAttrib3f(GLint location, GLfloat v0, GLfloat v1,GLfloat v2);
void glVertexAttrib4f(GLint location, GLfloat v0, GLfloat v1,,GLfloat v2, GLfloat v3);
```
或者
```cpp
GLint glVertexAttrib{1,2,3,4}fv(GLint location, GLfloat *v);
```
**参数：**

location | the previously queried location.
---------|------------------------------------
v0,v1,v2,v3 | float values.
v | an array of floats.

&emsp;&emsp;对于integer类型，也有一组类似的函数。与一致变量不同，这里向量版的函数并不支持对向量数组的赋值，所以函数参数用向量或是分别指定的效果没有太大区别，就好像OpenGL中glColor3f和glColor3fv的关系。下面是一个简单的例子，假定顶点shader中声明了一个名为height的浮点属性变量，在程序连接之后可以进行如下操作：
```cpp
loc = glGetAttribLocation(p,"height");
```
在执行渲染的代码中间可以为shader中的变量赋值：
```cpp
glBegin(GL_TRIANGLE_STRIP);
    glVertexAttrib1f(loc,2.0);
    glVertex2f(-1,1);
    glVertexAttrib1f(loc,2.0);
    glVertex2f(1,1);
    glVertexAttrib1f(loc,-2.0);
    glVertex2f(-1,-1);
    glVertexAttrib1f(loc,-2.0);
    glVertex2f(1,-1);
glEnd();
```
顶点数组和属性变量也可以一起使用。首先需要使能数组，使用如下函数：
```cpp
void glEnableVertexAttribArray(GLint loc);
```
**参数：**
> loc – the location of the variable.

接下来使用函数提交包含数据的数组指针：
```cpp
void glVertexAttribPointer(GLint loc, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
```
**参数：**

loc  | the location of the variable.
---- |--------------------------------
size | the number of components per element, for instance: 1 for float; 2 for vec2; 3 for vec3, and so on.
type | The data type associated: GL_FLOAT is an example.
normalized | if set to 1 then the array values will be normalized, converted to a range from -1 to 1 for signed data, or 0 to 1 for unsigned data.
stride | the spacing between elements. Exactly the same as in OpenGL.
pointer | pointer to the array containing the data.

下面是示例代码，首先执行初始化，定义了顶点数组和属性数组。
```cpp
float vertices[8] = {-1,1, 1,1, -1,-1, 1,-1};
float heights[4] = {2,2,-2,-2};
...
loc = glGetAttribLocation(p,"height");

glEnableClientState(GL_VERTEX_ARRAY);
glEnableVertexAttribArray(loc);
glVertexPointer(2,GL_FLOAT,0,vertices);
glVertexAttribPointer(loc,1,GL_FLOAT,0,0,heights);
```
#### 易变变量（Varying Variables）
&emsp;&emsp;前面说过，shader包括两种类型：顶点shader和片断shader。为了计算片断的值，往往需要访问顶点的插值数据。例如，当使用逐片断光照时，我们需要知道当前片断的法线，但是在OpenGL中只为每个顶点指定了法线。顶点shader可以访问这些法线，而片断shader不能，因为法线是OpenGL程序作为属性变量指定的。
&emsp;&emsp;顶点变换后的数据移动到流水线的下一个阶段，在这个阶段通过使用连接信息，生成了所有图元并完成片断化。对每个片断，有一组变量会被自动进行插值并提供给片断shader，这些都是固定功能。片断的颜色就是这么处理的，到达片断shader的颜色就是组成图元的顶点颜色插值的结果。
像片断shader接收到的这种插值产生的变量，就是“易变变量”类型。GLSL包含一些预先定义的易变变量，例如前面提到的颜色。用户也可以自己定义易变变量，它们必须同时在顶点shader和片断shader中声明：
> varying float intensity;

&emsp;&emsp;一个易变变量必须先在顶点shader中声明，然后计算每个顶点的变量值。在片断shader中，接收这个变量通过插值得到的结果，注意此时这个变量是只读的。

语句和函数
控制流语句
与C语言类似，GLSL中有类似if-else的条件语句，for，while，do-while等循环语句。
```cpp
if (bool expression)
    ...
else
    ...

for (initialization; bool expression; loop expression)
    ...

while (bool expression)
    ...

do
    ...
while (bool expression)
```
GLSL也有跳转语句：

continue | available in loops, causes a jump to thenext iteration of the loop
---------|--------------------------------------------------------------------
break | available in loops, causes an exit of theloop
discard | discard关键字只能在片断shader中使用，它将在不写入帧缓存或者深度缓存的情况下，终止当前片断的shader程序。

函数与C语言类似，shader也是由函数组成的结构化程序。至少每类shader都必须包含一个如下方式声明的主函数：
> void main()

此外用户还可以自定义函数。这些函数像C函数一样，一般都会有返回值，返回值的类型没有限制，但不能是数组。函数参数可以有如下修饰符：

in |for input parameters
---|-----------------------
out | for outputs of the function. The returnstatement is also an option for sending the result of a function.
inout | for parameters that are both input andoutput of a function
 
如果没有指定修饰符，默认情况下为in类型。
最后还有两点要注意：

* 允许函数重载，只要参数不同。
* 在标准中没有定义递归行为。

结束本节之前来看一个函数的例子：
```c
vec4 toonify(in float intensity)
{
    vec4 color;
    if (intensity > 0.98)
       color = vec4(0.8,0.8,0.8,1.0);
    else if (intensity > 0.5)
       color = vec4(0.4,0.4,0.8,1.0);
    else if (intensity > 0.25)
       color = vec4(0.2,0.2,0.4,1.0);
    else
       color = vec4(0.1,0.1,0.1,1.0); 

    return(color);
}
```
