#### glfwSetInputMode()
```cpp
void glfwSetInputMode(GLFWwindow* window,int mode,int value)
```

����  | ȡֵ
-------|--------------------
window | ��Ҫ�����õĴ���
mode   | ����ȡֵGLFW_CURSOR,GLFW_STICKY_KEYS,GLFW_STICKY_MOUSE_BUTTONS
value  | ָ��������ģʽ����ֵ
���`mode`ȡֵΪ`GLFW_CURSOR`,`value`ֻ���ǣ�

* GLFW_CURSOR_NORMAL ���ɼ�����������
* GLFW_CURSOR_HIDDEN ������Ƶ������ϵ�ʱ�򲻿ɼ�
* GLFW_CURSOR_DISABLED �������������������κ��ƶ�����

���`mode`ȡֵ`GLFW_STICKY_KEYS`,`value`Ҫôȡ`GL_TRUE`����ճ�ͼ�������`GL_FALSE`�����������������ճ�ͼ���һ���������Ա�֤`glfwGetKey`����һ�μ�ʱ�м��ڵ���֮ǰ�Ѿ����ͷ�����Ȼ����`GLFW_PRESS`������ֻ���ļ��Ƿ񱻰��£����ǲ�����ʲôʱ����ߺ���˳��ʱ������
���`mode`ȡֵ`GLFW_STICKY_MOUSE_BUTTONS`,`value`Ҫôȡֵ`GL_TRUE`����ճ���������`GL_FALSE`����������ճ�ͼ�һ����ֻ�����Ǽ��̰�����Ϊ������ϵİ�ť,`glfwGetMouseButton`����`GLFW_PRESS`