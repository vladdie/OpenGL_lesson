### glUniformMatrix4fv
```cpp
void glUniformMatrix4fv(GLint location,	GLsizei count, GLboolean transpose, const GLfloat *value);
```

参数            | 含义
----------------|------
location | Specifies the location of the uniform value to be modified.
count | Specifies the number of matrices that are to be modified. This should be 1 if the targeted uniform variable is not an array of matrices, and 1 or more if it is an array of matrices.
transpose | Specifies whether to transpose the matrix as the values are loaded into the uniform variable. 
value | Specifies a pointer to an array of count values that will be used to update the specified uniform variable.

**NOTE:** 第三个参数表示是否将矩阵转置加载到内存，GL_FALSE表示转置后按列读取，即不转置按行读取。