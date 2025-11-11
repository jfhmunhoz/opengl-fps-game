#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Window{
public:
	int init();
	GLFWwindow* getGLFWWindow();
	bool shouldClose();
	void swapBuffers();
	void pollEvents();

private:
	int success;
	float screenRatio;
	GLFWwindow* window;
}

#endif
