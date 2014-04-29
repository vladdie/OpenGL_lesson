&emsp;&emsp;要创建顶点数组对象，首先要调用`glGenVertexArrays()`,这样将会创建所要求数目的未初始化对象：
```cpp
void glGenVertexArrays(GLsizei n,GLuint *arrays);
```
&emsp;&emsp;返回n个当前未使用的名字，用作数组arrays中的顶点数组对象。返回的名字标记为是用来分配额外的缓冲区对象，并且用表示未初始化的顶点数组集合的默认状态之来进行初始化
&emsp;&emsp;创建了自己的顶点数组对象之后，需要初始化新的对象，并且把要使用的顶点数组数据的集合与单个已分配的对象关联起来。使用`glBindVertexArray()`函数来做到这一点。一旦初始化了所有的顶点数组对象，就可以使用`glBindVertexArray()`在建立的不同顶点数组集合之间切换。
```cpp
GLvoid glBindVertexArray(GLuint array);
```
`glBindVertexArray()`做3件事。

* 当使用的值array不是零并且是从`glGenVertexArrays()`返回的值时，创建一个新的顶点数组对象并且分配该名字
* 当绑定到之前创建的一个顶点数组对象的时候，该顶点数组对象变成活动的，这还会影响到存储在该对象中的顶点数组状态。
* 当绑定到一个为零的array值时，OpenGL停止使用顶点数组对象并且返回顶点数组的默认状态。

&emsp;&emsp;如果array不是之前从`glGenVertexArrays()`返回的值；如果它是`glDeleteVertexArrays()`已经释放的值；如果调用了任何一个`gl*Pointer()`函数来指定一个顶点数组，而在绑定了一个非零项点数组对象的时候，它没有和一个缓冲区对象关联起来(例如，使用一个客户端顶点数据存储)，将会产生GL_INVALID_OPERATION错误。
&emsp;&emsp;要删除顶点数组对象并释放它们的名字以便使用，调用`glDeleteVertexArrays()`如果使用缓冲区对象存储数据，当引用它们的顶点数组对象删除的时候，这些缓冲区对象没有删除。它们继续存在(直到删除它们)。唯一的变化是，如果缓冲区对象当前是绑定的，当删除顶点数组对象时，它们变成了未绑定的。
```cpp
void glDeleteVertexArrays(GLsizei n,GLuint *arrays);
```
&emsp;&emsp;删除arrays中指定的n个数组对象，使这些名字随后可以作为顶点数组重用。如果删除了一个绑定的顶点数组，该顶点数组的绑定变成0(就好像使用了0值调用了glBindBuffer())，默认的顶点数组变成当前的顶点数组。arrays中未使用的名字会释放掉，但是，当前顶点数组的状态没有改变。
&emsp;&emsp;最后，如果需要确定一个特定的值是否可以表示一个已分配的(但不必是已初始化的)顶点数组对象，可以调用`glIsVertexArray()`来检查。
```cpp
GLboolean glIsVertexArray(GLuint array);
```
&emsp;&emsp;如果array是之前`glGenVertexArrays()`产生的一个顶点数组对象的名字，但是随后没有删除，返回GL_TRUE。如果是0或者一个并非定点数组对象的名字的非零值，返回GL_FALSE。