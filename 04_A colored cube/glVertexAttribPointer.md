### glVertexAttribPointer
#### ���
```cpp
void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,const GLvoid * pointer);
```

����       | ����
-----------|------
index      | ָ��Ҫ�޸ĵĶ�����������ֵ
size       | ָ��ÿ���������������������������1��2��3����4���ĳ�ʼֵ��4
type       | ָ��������ÿ��������������͡����õķ��ų�����GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,GL_UNSIGNED_SHORT, GL_FIXED, �� GL_FLOAT����ʼֵΪGL_FLOAT
normalized | ָ����������ʱ���̶�������ֵ�Ƿ�Ӧ�ñ���һ����GL_TRUE������ֱ��ת��Ϊ�̶���ֵ��GL_FALSE������ϸ���ͼ�������
stride     | ָ��������������֮���ƫ���������Ϊ0����ô�������Իᱻ���Ϊ�������ǽ���������һ��ġ���ʼֵΪ0
pointer    | ָ��һ��ָ�룬ָ�������е�һ���������Եĵ�һ�����,��ʼֵΪ0

#### ����
&emsp;&emsp;glVertexAttribPointer ָ������Ⱦʱ����ֵΪ index �Ķ���������������ݸ�ʽ��λ�á�sizeָ��ÿ������ֵ����������ұ���Ϊ1��2��3��4֮һ��typeָ��ÿ����������ݸ�ʽ��strideָ����һ�����Ե���һ������֮��Ĳ����������������ֵ���洢�ڵ�һ������߲�ͬ�������У����������е�ֵ�����ʲ���ת��������ֵʱ�����normalized������ΪGL_TRUE����ζ�������͵�ֵ�ᱻӳ��������[-1,1]���з�������������������[0,1]���޷�������������֮����Щֵ�ᱻֱ��ת��Ϊ����ֵ�������й�һ������
&emsp;&emsp;���һ�����Ʒ���Ļ�����󱻰���GL_ARRAY_BUFFERĿ�꣨��glBindBuffer���Ҵ�ʱһ�������������鱻ָ���ˣ���ôpointer�������û���������ݴ洢�����ֽ�ƫ���������ң��������󶨣�GL_ARRAY_BUFFER_BINDING���ᱻ��Ϊ����Ϊindex�Ķ�����������ͻ���״̬��GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING������Also, the buffer object binding (GL_ARRAY_BUFFER_BINDING) is saved as generic vertex attribute array client-side state (GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING) for index index.��
&emsp;&emsp;��һ�������������鱻ָ��ʱ�����˵�ǰ�Ķ������黺�����󶨣�size, type, normalized, stride, �� pointer Ҳ�ᱻ��Ϊ�ͻ���״̬
Ҫ���û��߽��ö����������飬����glEnableVertexAttribArray��glDisableVertexAttribArray�������index��������ã���ô��glDrawArrays����glDrawElements������ʱ��������������ᱻʹ�á�
