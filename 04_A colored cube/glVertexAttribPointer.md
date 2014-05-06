### glVertexAttribPointer
#### 简介
```cpp
void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,const GLvoid * pointer);
```

参数       | 含义
-----------|------
index      | 指定要修改的顶点属性索引值
size       | 指定每个顶点属性组件的数量。必须是1，2，3，或4，的初始值是4
type       | 指定数组中每个组件的数据类型。可用的符号常量有GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,GL_UNSIGNED_SHORT, GL_FIXED, 和 GL_FLOAT，初始值为GL_FLOAT
normalized | 指定当被访问时，固定点数据值是否应该被归一化（GL_TRUE）或者直接转换为固定点值（GL_FALSE），详细解释见下描述
stride     | 指定连续顶点属性之间的偏移量。如果为0，那么顶点属性会被理解为：它们是紧密排列在一起的。初始值为0
pointer    | 指定一个指针，指向数组中第一个顶点属性的第一个组件,初始值为0

#### 描述
&emsp;&emsp;glVertexAttribPointer 指定了渲染时索引值为 index 的顶点属性数组的数据格式和位置。size指定每个属性值的组件数量且必须为1、2、3、4之一。type指定每个组件的数据格式，stride指定了一个属性到下一个属性之间的步长（这就允许属性值被存储在单一数组或者不同的数组中）。当数组中的值被访问并被转换至浮点值时，如果normalized被设置为GL_TRUE，意味着整数型的值会被映射至区间[-1,1]（有符号整数），或者区间[0,1]（无符号整数），反之，这些值会被直接转换为浮点值而不进行归一化处理。
&emsp;&emsp;如果一个名称非零的缓冲对象被绑定至GL_ARRAY_BUFFER目标（见glBindBuffer）且此时一个定点属性数组被指定了，那么pointer被当做该缓冲对象数据存储区的字节偏移量。并且，缓冲对象绑定（GL_ARRAY_BUFFER_BINDING）会被存为索引为index的顶点属性数组客户端状态（GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING）；（Also, the buffer object binding (GL_ARRAY_BUFFER_BINDING) is saved as generic vertex attribute array client-side state (GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING) for index index.）
&emsp;&emsp;当一个顶点属性数组被指定时，除了当前的顶点数组缓冲对象绑定，size, type, normalized, stride, 和 pointer 也会被存为客户端状态
要启用或者禁用顶点属性数组，调用glEnableVertexAttribArray和glDisableVertexAttribArray传入参数index。如果启用，那么当glDrawArrays或者glDrawElements被调用时，顶点属性数组会被使用。
