#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Input {
public:
	void registerScroll();
	void registerMousePos();
	void registerMouse();
	void registerKey();
private:
	void onScroll();
	void onMouseMoved();
	void onMousePress();
	void onKeyPress();
	
	static void _onScroll(GLFWwindow* win, double xOffset, double yOffset);
	static void _onMouseMoved(GLFWwindow* win, double xPos, double yPos);
	static void _onMousePress(GLFWwindow* win, int button, int action, int mods);
	static void _onKeyPress(GLFWwindow* win, int key, int scancode, int action, int mods);
};

#endif