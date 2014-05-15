// 07_Model_loading.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include <gl/glew.h>

#include <glfw/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

#define WIDTH 800
#define HEIGHT 450

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( WIDTH, HEIGHT, "07_Model_loading", NULL, NULL);
	if( window == NULL ){
		cerr<<"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials."<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		cerr<<"Failed to initialize GLEW"<<endl;
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrrayID;
	glGenVertexArrays(1,&VertexArrrayID);
	glBindVertexArray(VertexArrrayID);

	//Create and compile our GLSL program the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader","TextureFragmentShader.fragmentshader");

	//Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID,"MVP");

	//Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");

	//Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID,"myTextureSampler");

	//Read our .obj file
	vector<glm::vec3 > vertices;
	vector<glm::vec2 > uvs;
	vector<glm::vec3 > normals;
	bool res = loadOBJ("cube.obj",vertices,uvs,normals);

	//Load it into VBO
	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1,&uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*uvs.size(),&uvs[0],GL_STATIC_DRAW);

	do 
	{
		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use our shader
		glUseProgram(programID);

		//Compute the MVP matrix from keybord and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		glm::mat4 MVP=ProjectionMatrix*ViewMatrix*ModelMatrix;

		//Send our transformation to the currently bound shader,
		//in the "MVP" uniform
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);

		//Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,Texture);
		//Set our "myTextureSampler" sampler to user Texture Uint0
		glUniform1i(TextureID,0);

		//1st attribute buffer :vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		//2nd attribute buffer :UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		//Draw the triangle !
		glDrawArrays(GL_TRIANGLES,0,vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	//Cleanup VBO and shader
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
	glDeleteProgram(programID);
	glDeleteBuffers(1,&VertexArrrayID);
	glDeleteBuffers(1,&TextureID);

	//Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

