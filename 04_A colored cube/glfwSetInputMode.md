#### glfwSetInputMode()
```cpp
void glfwSetInputMode(GLFWwindow* window,int mode,int value)
```

参数  | 取值
-------|--------------------
window | 需要被设置的窗口
mode   | 可以取值GLFW_CURSOR,GLFW_STICKY_KEYS,GLFW_STICKY_MOUSE_BUTTONS
value  | 指定的输入模式的新值
如果`mode`取值为`GLFW_CURSOR`,`value`只能是：

* GLFW_CURSOR_NORMAL 鼠标可见，正常运行
* GLFW_CURSOR_HIDDEN 当鼠标移到窗体上的时候不可见
* GLFW_CURSOR_DISABLED 禁用鼠标和消除对鼠标的任何移动限制

如果`mode`取值`GLFW_STICKY_KEYS`,`value`要么取`GL_TRUE`启用粘滞键，或者`GL_FALSE`禁用它。如果启用了粘滞键，一个按键可以保证`glfwGetKey`在下一次即时有键在调用之前已经被释放了仍然返回`GLFW_PRESS`，当你只关心键是否被按下，但是不管是什么时候或者何种顺序时很有用
如果`mode`取值`GLFW_STICKY_MOUSE_BUTTONS`,`value`要么取值`GL_TRUE`启用粘鼠键，或者`GL_FALSE`禁用它。和粘滞键一样，只不过是键盘按键改为了鼠标上的按钮,`glfwGetMouseButton`返回`GLFW_PRESS`