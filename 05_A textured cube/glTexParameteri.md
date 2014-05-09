### Name
```cpp
void glTexParameteri(GLenum target, GLenum pname, GLint param);
```

����   | ����
-------|-----
target | GL_TEXTURE_1D��GL_TEXTURE_2D���������õ�������һά�Ļ��Ƕ�ά��
pname | GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T,GL_TEXTURE_MAG_FILTER,GL_TEXTURE_MIN_FILTER,ָ���˲�������������ϸȡֵ�Լ�˵�����±�
param | �ڶ�������pname��ֵ

����                  | ȡֵ
----------------------|--------------------
GL_TEXTURE_WRAP_S     |  GL_CLAMP,GL_REPEAT
GL_TEXTURE_WRAP_T     | GL_CLAMP,GL_REPEAT
GL_TEXTURE_MAG_FILTER | GL_NEAREST,GL_LINEAR
GL_TEXTURE_MIN_FILTER | GL_NEAREST,GL_LINEAR,GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST_MIPMAP_LINEAR,GL_LINEAR_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_LINEAR

**NOTE:** ���궨�壬�������궨��Ϊ(x,y,z,w)(w=0��ʾ������ȡ1��ʾ����)����������Ҳ����ˣ������������꣬����ȡ1,2,3,4ά����,(s,t,r,q)����ά�������곣��(s,t)��ʾ��Ŀǰ����r���꣬q������w
> 
GL_TEXTURE_MAG_FILTER ָ��Ϊ�Ŵ��˲��ķ���
GL_TEXTURE_MIN_FILTER ָ��Ϊ��С�˲��ķ���
GL_CLAMP              ������������н�ȡ������1����������ֵ����Ϊ1������С��0��ֵ����Ϊ0����ȡ����������һ�����ͱ�����ֻ����һ���������ĳ���
GL_REPEAT             s,t�����Ͽ����ظ�ӳ��

����                      | ȡֵ
--------------------------|--------------------
GL_NEAREST                | ������������������ĵ���������(�����)
GL_LINEAR                 | ��������������ĵ��ĸ����صļ�Ȩƽ��ֵ(˫���Բ���)
GL_NEAREST_MIPMAP_NEAREST | ѡ�����ڽ�������Ԫֵ
GL_LINEAR_MIPMAP_NEAREST  | ���Եؾ����ڽ�������Ԫ
GL_NEAREST_MIPMAP_LINEAR  | ���������ڵ�mipmap�������Ԫ����֮������ֵ��������������ѡ�����ڽ�������Ԫ����ȡ����֮������Ծ���ֵ
GL_LINEAR_MIPMAP_LINEAR   | ���������ڵ�mipmap�������Ԫ����֮������ֵ��ʹ�����Ծ��ͼ��������������Ե�ֵ��Ȼ��������������ٴν������Ծ���(�����Բ���)����������˫���Բ�����mipmap�������Ծ���

**PS:** �ο�OpenGL���ָ��(ԭ���6��)��9��
