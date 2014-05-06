* 1.��������������

```cpp
//��buffers�����з��ص�ǰn��δʹ�õ����ƣ���ʾ����������
void glGenBuffers(GLsizei n, GLuint* buffers);
//�ж��Ƿ��ǻ���������
GLboolean glIsBuffer(GLuint buffer);
```
* 2.�����������

```cpp
//ָ����ǰ�����������
void glBindBuffer(GLenum target, GLuint buffer );
```
* 3.�����ݷ���ͳ�ʼ������������

```cpp
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
```

����            | ����
----------------|------
target | ָ��Ŀ�껺�������󣬷��ų���������GL_ARRAY_BUFFER,BL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,GL_TRANSFORM_FEEDBACK_BUFFER,or GL_UNIFORM_BUFFER
size | ָ���������Ĵ�С(���ֽڶ���������ݴ洢)
data | ָ��һ��ָ��ָ��Ҫ�����Ƶ����ݴ洢��������ʼ�������ݣ�����Ϊ�գ�û�����ݱ���ֵ
usage | ָ�����ݴ洢��Ԥ��ʹ��ģʽ�����ų���������GL_STREAM_DRAW,GL_STREAM_READ,GL_STREAM_COPY,GL_STATIC_DRAW,GL_STATIC_READ,GL_STATIC_COPY,GL_DYNAMIC_DRAW,GL_DYNAMIC_READ,����GL_DYNAMIC_COPY

**NOTE:** usage���Է�Ϊ�����֣���һ�����ʵ�Ƶ��(�޸ĺ�ʹ��)���ڶ������ʵı���
��һ����ȡֵ�����ǣ�

����    | ����
--------|------
STREAM  | ���ݴ洢�����ݶ���ʹ�ü��ε������ֻ�޸�һ��
STATIC  | ���ݴ洢�����ݽ�ʹ�úܶ�ε������ֻ�޸�һ�� 
DYNAMIC | ���ݴ洢�����ݽ�ʹ�úܶ�β��ҷ����޸� 

�ڶ�����ȡֵ�����ǣ�

���� | ����
-----|------
DRAW | ���ݴ洢����������Ӧ�ó����޸ģ�������ΪGL��ͼ��ͼ��ָ��������Դ����
READ | ���ݴ�һ��GL���������ƶ��������ҿ�����Ӧ�ó�����Ϊ����ֵʹ��
COPY | ���ݴ�һ��GL���������ƶ�����������Ϊ��ͼ��ͼ��ָ������Դ����

* 4.���»���������ֵ

```cpp
//�ṩ�Ի���������������������ݼ��ϵĸ���
//access:GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE
GLvoid *glMapBuffer(GLenum target, GLenum access);
//��ʾ��ǰ�󶨻���������ĸ����Ѿ���ɣ���
GLboolean *glUnMapBuffer(GLenum target);
```
* 5.�ڻ���������֮�临������

```cpp
//�����ݴ�readbuffer������Ļ����������Ƶ�writebuffer�Ļ���������
//��readoffset��ʼ�ƶ�size�����ݵ�writeoffset��
void glCopyBufferSubData(GLenum readbuffer, GLenum writebuffer, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);
```
* 6.�������������

```cpp
void glDeleteBuffers(GLsizei n,GLuint* buffers);
```