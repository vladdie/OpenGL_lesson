* 1.创建缓冲区对象

```cpp
//在buffers数组中返回当前n个未使用的名称，表示缓冲区对象
void glGenBuffers(GLsizei n, GLuint* buffers);
//判断是否是缓冲区对象
GLboolean glIsBuffer(GLuint buffer);
```
* 2.激活缓冲区对象

```cpp
//指定当前活动缓冲区对象
void glBindBuffer(GLenum target, GLuint buffer );
```
* 3.用数据分配和初始化缓冲区对象

```cpp
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
```

参数            | 含义
----------------|------
target | 指定目标缓冲区对象，符号常量必须是GL_ARRAY_BUFFER,BL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,GL_TRANSFORM_FEEDBACK_BUFFER,or GL_UNIFORM_BUFFER
size | 指定缓冲区的大小(以字节对象的新数据存储)
data | 指定一个指针指向将要被复制到数据存储区用来初始化的数据，或者为空，没有数据被赋值
usage | 指定数据存储的预期使用模式，符号常量必须是GL_STREAM_DRAW,GL_STREAM_READ,GL_STREAM_COPY,GL_STATIC_DRAW,GL_STATIC_READ,GL_STATIC_COPY,GL_DYNAMIC_DRAW,GL_DYNAMIC_READ,或者GL_DYNAMIC_COPY

**NOTE:** usage可以分为两部分，第一，访问的频率(修改和使用)，第二，访问的本质
第一部分取值可以是：

参数    | 含义
--------|------
STREAM  | 数据存储区内容顶多使用几次但是最多只修改一次
STATIC  | 数据存储区内容将使用很多次但是最多只修改一次 
DYNAMIC | 数据存储区内容将使用很多次并且反复修改 

第二部分取值可以是：

参数 | 含义
-----|------
DRAW | 数据存储区的内容由应用程序修改，并且作为GL绘图和图像指定函数的源数据
READ | 数据从一个GL缓冲区复制而来，并且可以由应用程序作为数据值使用
COPY | 数据从一个GL缓冲区复制而来，并且作为绘图和图像指定函数源数据

* 4.更新缓冲区数据值

```cpp
//提供对缓冲区对象包含的整个数据集合的更新
//access:GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE
GLvoid *glMapBuffer(GLenum target, GLenum access);
//表示当前绑定缓冲区对象的更新已经完成，与
GLboolean *glUnMapBuffer(GLenum target);
```
* 5.在缓冲区对象之间复制数据

```cpp
//把数据从readbuffer相关联的缓冲区对象复制到writebuffer的缓冲区对象
//从readoffset开始移动size个数据到writeoffset中
void glCopyBufferSubData(GLenum readbuffer, GLenum writebuffer, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);
```
* 6.清除缓冲区对象

```cpp
void glDeleteBuffers(GLsizei n,GLuint* buffers);
```