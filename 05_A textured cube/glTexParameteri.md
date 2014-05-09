### Name
```cpp
void glTexParameteri(GLenum target, GLenum pname, GLint param);
```

参数   | 含义
-------|-----
target | GL_TEXTURE_1D或GL_TEXTURE_2D，表明所用的纹理是一维的还是二维的
pname | GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T,GL_TEXTURE_MAG_FILTER,GL_TEXTURE_MIN_FILTER,指定滤波方法，参数详细取值以及说明见下表
param | 第二个参数pname的值

参数                  | 取值
----------------------|--------------------
GL_TEXTURE_WRAP_S     |  GL_CLAMP,GL_REPEAT
GL_TEXTURE_WRAP_T     | GL_CLAMP,GL_REPEAT
GL_TEXTURE_MAG_FILTER | GL_NEAREST,GL_LINEAR
GL_TEXTURE_MIN_FILTER | GL_NEAREST,GL_LINEAR,GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST_MIPMAP_LINEAR,GL_LINEAR_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_LINEAR

**NOTE:** 坐标定义，物体坐标定义为(x,y,z,w)(w=0表示向量，取1表示坐标)；纹理坐标也是如此，类似与点的坐标，可以取1,2,3,4维坐标,(s,t,r,q)，二维纹理坐标常用(s,t)表示，目前忽略r坐标，q类似与w
> 
GL_TEXTURE_MAG_FILTER 指定为放大滤波的方法
GL_TEXTURE_MIN_FILTER 指定为缩小滤波的方法
GL_CLAMP              对纹理坐标进行截取：大于1的纹理像素值都置为1，所有小于0的值都置为0，截取适用于想在一个大型表面上只出现一份纹理拷贝的场合
GL_REPEAT             s,t方向上可以重复映射

参数                      | 取值
--------------------------|--------------------
GL_NEAREST                | 采用坐标最靠近像素中心的纹理像素(点采样)
GL_LINEAR                 | 采用最靠近像素中心的四个像素的加权平均值(双线性采样)
GL_NEAREST_MIPMAP_NEAREST | 选择最邻近的纹理单元值
GL_LINEAR_MIPMAP_NEAREST  | 线性地均和邻近的纹理单元
GL_NEAREST_MIPMAP_LINEAR  | 从两个相邻的mipmap层的纹理单元均和之后的最佳值，从两个纹理中选择最邻近的纹理单元，并取她们之间的线性均和值
GL_LINEAR_MIPMAP_LINEAR   | 从两个相邻的mipmap层的纹理单元均和之后的最佳值，使用线性均和计算出两个纹理各自的值，然后对两个计算结果再次进行线性均和(三线性采样)，即对两个双线性采样的mipmap进行线性均和

**PS:** 参考OpenGL编程指南(原书第6版)第9章
