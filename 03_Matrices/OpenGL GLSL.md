###����
&emsp;&emsp;һ��OpenGL��������ö��ַ�ʽ��shaderͨ�š�ע������ͨ���ǵ���ģ���Ϊshader�����ֻ������Ⱦ��ĳЩĿ�꣬������ɫ����Ȼ��档OpenGL�Ĳ���״̬���Ա�shader���ʣ���˳���ı�OpenGLĳЩ״̬�Ϳ�����shader����ͨ���ˡ�����һ��������ѹ����ɫ����shader������ֱ�ӵ���OpenGL�ӿڣ�����ʹ�ù̶�������ˮ��ʱ����������������ʹ��OpenGL״̬����������shader��ʹ�����ݵ�ֱ�۷�ʽ������һ��shader��Ҫһ����ʾʱ��仯�ı��������㶯������OpenGL״̬�о�û���ֳɵı������á���Ȼ�������ʹ��û���õ��ġ�������ֹ�Ƕȣ�cutoffangle��������һ��������ʾʱ�䣬����Ȼ�������Խ��ܡ����˵��ǣ�GLSL�����û��Զ��������ʵ��OpenGLӦ�ó�����shaderͨ�š�����������ܣ���Ϳ�������һ������timeElapsed�ı�����ʾ������ʱ�䡣
���ĵ������漰����GLSL�ṩ�������������η�����������ͽ��ں����ᵽ����
> 
һ�±�����Uniform��
���ԣ�Attribute��

&emsp;&emsp;��shader�ж���ı���������������������η�����ʾ��shader��˵��������ֻ���ġ����潫��ϸ��������ʹ����Щ���͵ı�����
����һ�ֽ������͸�shader�ķ�����ʹ������һ������ֹ���Ա�ʾһ��ͼƬ���������Ա�ʾһ�����顣��ʵ�ϣ�����ȫ���Ծ��������shader�н����������ݣ���ʹ������һ��ͼƬ��
�������ͺͱ���
������GLSL�еĻ����������ͣ�
> 
float
bool
int

����������C�����ƣ��������Ϳ���Ϊtrue��false����Щ�������Ϳ������2��3��4ά������������ʾ��
fvec{2,3,4} | a vector of 2,3,or 4 floats
------------|----------------------------
bvec{2,3,4} | bool vector
ivec{2,3,4} | vector of integers

GLSL������2��2��3��3��4��4�;�����Ϊ��Щ����������ͼ�δ����кܳ��ã�
> 
mat2
mat3
mat4

���⣬����һ������ʵ��������ʵ��������ͣ����Ǳ���Ϊ��������sampler�����ڶ�ȡ����ֵ��Ҳ��Ϊ����texel��ʱ�õ������������������õ����������ͣ�
sampler1D | for 1D textures
----------|------------------
sampler2D | for 2D textures
sampler3D | for 3D textures
samplerCube | for cube map textures
sampler1DShadow | for shadow maps
sampler2DShadow | for shadow maps

��GLSL�У�������Cһ�������ͷ������飬���ǲ���������ʱ��ʼ�����顣GLSL�����Զ���ṹ�壺
```cpp
struct dirlight
{
    vec3 direction;
    vec3 color;
};
```
��������һ���������ͱ����ķ�����C���ƣ��㻹��������������ͬʱ���г�ʼ����
```cpp
float a,b;       // two vector (yes, the comments are like in C)
int c = 2;       // c is initialized with 2
bool d = true;  // d is true
```
�����������ͱ���Ҳ�ǰ������ַ��������ǳ�ʼ����C����������GLSL�ǳ��������캯��ʵ�ֳ�ʼ��������ת������
```cpp
float b = 2;          // incorrect, there is no automatic type casting
float e = (float)2; // incorrect, requires constructors for type casting
int a = 2;
float c = float(a); // correct. c is 2.0
vec3 f;                // declaring f as a vec3
vec3 g = vec3(1.0,2.0,3.0); // declaring and initializing g
```
��GLSL��ʹ��һЩ������ʼ�����������Ƿǳ����ġ���ֻ��Ҫ������Ҫ�����ݳ�Ա���ɡ��뿴��������ӣ�
```cpp
vec2 a = vec2(1.0,2.0);
vec2 b = vec2(3.0,4.0);
vec4 c = vec4(a,b)   // c = vec4(1.0,2.0,3.0,4.0);
vec2 g = vec2(1.0,2.0);
float h = 3.0;
vec3 j = vec3(g,h);
```
����ĳ�ʼ��Ҳ�����Ʒ�������������ܶ��ֹ��캯������������Ӹ�����һЩ��ʼ������Ĺ��캯����
```cpp
mat4 m = mat4(1.0)   // initializing the diagonal of the matrix with 1.0
vec2 a = vec2(1.0,2.0);
vec2 b = vec2(3.0,4.0);
mat2 n = mat2(a,b); // matrices are assigned in column major order
mat2 k = mat2(1.0,0.0,1.0,0.0); // all elements are specified
```
��������Ӹ����˳�ʼ���ṹ��ķ�����
```cpp
struct dirlight     // type definition
{
    vec3 direction;
    vec3 color;
};
dirlight d1;
dirlight d2 = dirlight(vec3(1.0,1.0,0.0),vec3(0.8,0.8,0.4));
```
��GLSL�л���һЩʵ�õ�ѡ���ӣ�selector�������Լ����ǵĲ������ô������ࡣ����һ����������ʹ�����µķ�����
```cpp
vec4 a = vec4(1.0,2.0,3.0,4.0);
float posX = a.x;
float posY = a[1];
vec2 posXY = a.xy;
float depth = a.w;
```
������Ĵ���Ƭ���У�����ʹ��`x,y,z,w`������������Ա���������ɫ�Ļ�����ʹ��`r,g,b,a`,�������������Ļ�����ʹ��`s,t,p,q`��ע���ʾ��������ͨ����ʹ��`s,t,r,q`,��r�Ѿ���ʾ��ɫ�еĺ�ɫ��red���ˣ�����������������Ҫʹ��p�����档�����ѡ���ӿ���ʹ��һ������������������m[0]����m[2][3]����һ�����ѡ���˵�һ�У��ڶ������ѡ����һ�����ݳ�Ա��
���ڽṹ����˵����������C������һ���������Ա�����Է���ǰ�涨��Ľṹ�壬����ʹ�����µĴ��룺
```cpp
d1.direction = vec3(1.0,1.0,1.0);
```
�������η�
���η������˱��������⺬�壬GLSL�����������η���
const  | ����һ�������ڳ�����
-------|---------------------------
attribute | �治ͬ����仯��ȫ�ֱ�������OpenGLӦ�ó��򴫸�����shader��������η�ֻ�����ڶ���shader�У���shader������һ��ֻ��������
uniform | �治ͬͼԪ�仯��ȫ�ֱ�������������glBegin/glEnd�����ã�����OpenGLӦ�ó��򴫸�shader��������η������ڶ����Ƭ��shader�У���shader������һ��ֻ��������
varying | ���ڶ���shader��Ƭ��shader�䴫�ݵĲ�ֵ���ݣ��ڶ���shader�п�д����Ƭ��shader��ֻ����

#### һ�±�����Uniform Variables��
&emsp;&emsp;��ͬ�ڶ���������ÿ�����������Լ���ֵ��һ��һ�±�����һ��ͼԪ�Ļ��ƹ������ǲ���ı�ģ�������ֵ������`glBegin/glEnd`�����á�һ�±����ʺ�������һ��ͼԪ�С�һ֡������һ�������ж������ֵ��һ�±����ڶ���`shader`��Ƭ��`shader`�ж���ֻ���ġ���������Ҫ��ñ������ڴ��е�λ�ã������Ϣֻ�������ӳ���֮��ſɻ�á�ע�⣬��ĳЩ���������ڻ�ô洢λ��ǰ������ʹ�ó��򣨵���`glUseProgram`������ȡһ��һ�±����Ĵ洢λ��ֻ��Ҫ��������shader�ж���ı��������ɣ�
```cpp
GLint glGetUniformLocation(GLuint program, const char *name);
```
**������**
program | the hanuler to the program
--------|----------------------------
name | the name of the variable

&emsp;&emsp;����ֵ���Ǳ���λ�ã������ô���Ϣ���ñ�����ֵ�����ݱ������������Ͳ�ͬ����һϵ�к���������������һ�±������������ø���ֵ��һ�麯�����£�
```cpp
void glUniform1f(GLint location, GLfloat v0);
void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
```
����
```cpp
GLint glUniform{1,2,3,4}fv(GLint location, GLsizei count, GLfloat *v);
```
**������**
location | the previously queried location
---------|--------------------------------
v0,v1,v2,v3 | float values
count | the number of elements in the array
v | an array of floats

&emsp;&emsp;��integer����Ҳ��һ�����Ƶĺ���������Ҫ��i�滻�����е�f����bool����û��ר�ŵĺ�����������ʹ��������0��1����ʾ��١�һ����ʹ����һ�±������飬��ô�ͱ���ʹ�������汾�ĺ�����
��sampler������ʹ�ú���glUniform1i��glUniform1iv��
����Ҳ��һ��GLSL���������ͣ�����Ҳ��һ����Ծ���ĺ�����
```cpp
GLint glUniformMatrix{2,3,4}fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
```
**������**
location | the previously queried location.
---------|----------------------------------
count | the number of matrices. 1 if a single matrix is being set, or n for an array of n matrices.
transpose | wheter to transpose the matrix values. A value of 1 indicates that the matrix values are specified in row major order, zero is column major order
v | an array of floats.

**NOTE:**����һ��Ҫע����ǣ�ʹ����Щ����֮�󣬱�����ֵ�����ֵ������ٴ�����֮ʱ��һ�������������ӣ����б�����ֵ��������Ϊ0��
�����һЩʾ�����롣����һ��shader��ʹ�������±�����
```cpp
uniform float specIntensity;
uniform vec4 specColor;
uniform float t[2];
uniform vec4 colors[3];
```
��OpenGL�����п���ʹ������Ĵ���������Щ������
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

&emsp;&emsp;ע������һ�����飨�����е�t����������Ԫ�����������е�colors��specColor���������м��count����ָ��shader������������Ԫ����������������OpenGL�����������ġ�������ȻspecColor����4��ֵ����glUniform4fv�����еĲ�����1����Ϊ��ֻ��һ����������һ������specColor�ķ�����
```cpp
loc2 = glGetUniformLocation(p,"specColor");
glUniform4f(loc2,sc[0],sc[1],sc[2],sc[3]);
```
GLSL�л����Ի�ȡ������ĳ�������ĵ�ַ�����磬���Ի��t[1]�ĵ�ַ������Ĵ���Ƭ��չʾ������t����Ԫ�ص���һ�ַ�����
```cpp
loct0 = glGetUniformLocation(p,"t[0]");
glUniform1f(loct0,threshold[0]);

loct1 = glGetUniformLocation(p,"t[1]");
glUniform1f(loct1,threshold[1]);
```
**NOTE:**ע����`glGetUniformLocation`��ʹ�÷�����ָʾ�ı�����

#### ���Ա�����Attribute Variables��
&emsp;&emsp;��ǰһ���ᵽ��һ�±���ֻ�����һ��ͼԪȫ�壬����˵������`glBegin��glEnd`֮��ı䡣���Ҫ���ÿ���������ñ������Ǿ���Ҫ���Ա����ˡ���ʵ�����Ա����������κ�ʱ�̸��¡��ڶ���shader�����Ա�����ֻ���ġ���Ϊ���������Ƕ������ݣ�������Ƭ��shader�в���ֱ��Ӧ�á���һ�±������ƣ���������Ҫ��ñ������ڴ��е�λ�ã������Ϣֻ�������ӳ���֮��ſɻ�á�ע�⣬��ĳЩ���������ڻ�ô洢λ��ǰ������ʹ�ó���
```cpp
GLint glGetAttribLocation(GLuint program,char *name);
```
**������**
program | the handle to the program
----------|----------------------------
name | the name of the variable

�����������õķ��ر����ڴ洢���еĵ�ַ������Ϳ���Ϊ��ָ��һ��ֵ������һ�±�����ÿ���������Ͷ��ж�Ӧ�ĺ�����
```cpp
void glVertexAttrib1f(GLint location, GLfloat v0);
void glVertexAttrib2f(GLint location, GLfloat v0, GLfloat v1);
void glVertexAttrib3f(GLint location, GLfloat v0, GLfloat v1,GLfloat v2);
void glVertexAttrib4f(GLint location, GLfloat v0, GLfloat v1,,GLfloat v2, GLfloat v3);
```
����
```cpp
GLint glVertexAttrib{1,2,3,4}fv(GLint location, GLfloat *v);
```
**������**
location | the previously queried location.
---------|------------------------------------
v0,v1,v2,v3 | float values.
v | an array of floats.

&emsp;&emsp;����integer���ͣ�Ҳ��һ�����Ƶĺ�������һ�±�����ͬ������������ĺ�������֧�ֶ���������ĸ�ֵ�����Ժ����������������Ƿֱ�ָ����Ч��û��̫�����𣬾ͺ���OpenGL��glColor3f��glColor3fv�Ĺ�ϵ��������һ���򵥵����ӣ��ٶ�����shader��������һ����Ϊheight�ĸ������Ա������ڳ�������֮����Խ������²�����
```cpp
loc = glGetAttribLocation(p,"height");
```
��ִ����Ⱦ�Ĵ����м����Ϊshader�еı�����ֵ��
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
������������Ա���Ҳ����һ��ʹ�á�������Ҫʹ�����飬ʹ�����º�����
```cpp
void glEnableVertexAttribArray(GLint loc);
```
**������**
> loc �C the location of the variable.

������ʹ�ú����ύ�������ݵ�����ָ�룺
```cpp
void glVertexAttribPointer(GLint loc, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
```
**������**
loc  | the location of the variable.
---- |--------------------------------
size | the number of components per element, for instance: 1 for float; 2 for vec2; 3 for vec3, and so on.
type | The data type associated: GL_FLOAT is an example.
normalized | if set to 1 then the array values will be normalized, converted to a range from -1 to 1 for signed data, or 0 to 1 for unsigned data.
stride | the spacing between elements. Exactly the same as in OpenGL.
pointer | pointer to the array containing the data.
������ʾ�����룬����ִ�г�ʼ���������˶���������������顣
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
#### �ױ������Varying Variables��
&emsp;&emsp;ǰ��˵����shader�����������ͣ�����shader��Ƭ��shader��Ϊ�˼���Ƭ�ϵ�ֵ��������Ҫ���ʶ���Ĳ�ֵ���ݡ����磬��ʹ����Ƭ�Ϲ���ʱ��������Ҫ֪����ǰƬ�ϵķ��ߣ�������OpenGL��ֻΪÿ������ָ���˷��ߡ�����shader���Է�����Щ���ߣ���Ƭ��shader���ܣ���Ϊ������OpenGL������Ϊ���Ա���ָ���ġ�
&emsp;&emsp;����任��������ƶ�����ˮ�ߵ���һ���׶Σ�������׶�ͨ��ʹ��������Ϣ������������ͼԪ�����Ƭ�ϻ�����ÿ��Ƭ�ϣ���һ������ᱻ�Զ����в�ֵ���ṩ��Ƭ��shader����Щ���ǹ̶����ܡ�Ƭ�ϵ���ɫ������ô����ģ�����Ƭ��shader����ɫ�������ͼԪ�Ķ�����ɫ��ֵ�Ľ����
��Ƭ��shader���յ������ֲ�ֵ�����ı��������ǡ��ױ���������͡�GLSL����һЩԤ�ȶ�����ױ����������ǰ���ᵽ����ɫ���û�Ҳ�����Լ������ױ���������Ǳ���ͬʱ�ڶ���shader��Ƭ��shader��������
> varying float intensity;

&emsp;&emsp;һ���ױ�����������ڶ���shader��������Ȼ�����ÿ������ı���ֵ����Ƭ��shader�У������������ͨ����ֵ�õ��Ľ����ע���ʱ���������ֻ���ġ�

���ͺ���
���������
��C�������ƣ�GLSL��������if-else��������䣬for��while��do-while��ѭ����䡣
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
GLSLҲ����ת��䣺
continue |�C available in loops, causes a jump to thenext iteration of the loop
---------|--------------------------------------------------------------------
break |�C available in loops, causes an exit of theloop
discard |discard�ؼ���ֻ����Ƭ��shader��ʹ�ã������ڲ�д��֡���������Ȼ��������£���ֹ��ǰƬ�ϵ�shader����
������C�������ƣ�shaderҲ���ɺ�����ɵĽṹ����������ÿ��shader���������һ�����·�ʽ��������������
> void main()

�����û��������Զ��庯������Щ������C����һ����һ�㶼���з���ֵ������ֵ������û�����ƣ������������顣���������������������η���
in |for input parameters
---|-----------------------
out | for outputs of the function. The returnstatement is also an option for sending the result of a function.
inout | for parameters that are both input andoutput of a function
 
���û��ָ�����η���Ĭ�������Ϊin���͡�
���������Ҫע�⣺

* ���������أ�ֻҪ������ͬ��
* �ڱ�׼��û�ж���ݹ���Ϊ��

��������֮ǰ����һ�����������ӣ�
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