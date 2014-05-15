//Include GLFW
#define WIDTH 800
#define HEIGHT 450
#include <glfw/glfw3.h>
//The "extern" keyword here is to access the variable "window" declared in 0x_xxxx.cpp
//This is a hack to keep the tutorials simple.Please avoid this.
//��˼������һ�������ⲿ����window���ӵȷ�����ֻ��Ϊ�˼򻯽̳�
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}


//Initial position : on +Z
glm::vec3 position = glm::vec3(0,0,5);
//Initial horizontal angle : toward -Z,����Z�ᷴ��н�
float horizontalAngle=3.14f;
//Initial vertical angle : none����xozƽ��н�
float verticalAngle=0.0f;
//Initial Field of View
float initialFoV =45.0f;
//3 units/second
float speed =3.0f;
float mouseSpeed =0.005f;

void computeMatricesFromInputs()
{
	//glfwGetTime is called only once, the first time this function is called
	static double lastTime=glfwGetTime();

	//Compute time difference between current and last frame
	double currentTime=glfwGetTime();
	float deltaTime=float(currentTime-lastTime);

	//Get mouse position
	double xpos,ypos;
	glfwGetCursorPos(window,&xpos,&ypos);

	//Reset mouse position for next frame
	glfwSetCursorPos(window,WIDTH/2,HEIGHT/2);

	//Compute new orientation
	horizontalAngle += mouseSpeed*float(WIDTH/2 - xpos);
	verticalAngle += mouseSpeed*float(HEIGHT/2 - ypos);

	//Direction : Spherical coordinates to Cartesian coordinates conversion
	//direction:ʵ�ַ��������굽ֱ�������ת��,�����һ���뾶ͶӰ��(x,y,z)�������ֵ
	glm::vec3 direction(
		cos(verticalAngle)*sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle)*cos(horizontalAngle)
		);

	//Right vector,��direction��ֱ
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle-3.14f/2.0f),
		0,
		cos(horizontalAngle-3.14f/2.0f)
		);

	//Up vector�����
	glm::vec3 up=glm::cross(right,direction);
	
	//Move forward
	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
	{
		position += direction*deltaTime*speed;
	}
	//Move backward
	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		position -= direction*deltaTime*speed;
	}
	//Strafe right
	if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		position += right*deltaTime*speed;
	}
	//Strafe left
	if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		position -=right*deltaTime*speed;
	}
	
	float FoV=initialFoV;

	//Projection matrix :45�� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV,4.0f/3.0f,0.1f,100.0f);
	//Camera matrix
	ViewMatrix =glm::lookAt(
		position,			//Camera is here
		position+direction, //and looks here : at the same position,plus "direction"
		up					//Head is up (set to 0,-1,0 to look upside-down)
		);
	//For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}