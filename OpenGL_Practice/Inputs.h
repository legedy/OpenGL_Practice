#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

typedef int(*scrollCallback)(GLFWwindow* window, double x, double y);
typedef int(*mouseMoveCallback)(GLFWwindow* window, double x, double y);
typedef int(*mousePressCallback)(GLFWwindow* window, int state);
typedef int(*keyPressCallback)(GLFWwindow* window, int state);

struct keyToFunc {
	int button;
	mousePressCallback func;
};

class Input {
public:
	Input(GLFWwindow* window);

	void registerScroll(scrollCallback callback);
	void registerMousePos(mouseMoveCallback callback);
	void registerMouse(int button, mousePressCallback callback);
	void registerKey(int key, keyPressCallback callback);
private:
	std::vector<scrollCallback> scrollCallbacks;
	std::vector<mouseMoveCallback> mouseMoveCallbacks;
	std::vector<keyToFunc> mousePressCallbacks;
	std::vector<keyToFunc> keyPressCallbacks;

	void onScroll(GLFWwindow* window, double x, double y);
	void onMouseMoved(GLFWwindow* window, double x, double y);
	void onMousePress(GLFWwindow* window, int state);
	void onKeyPress(GLFWwindow* window, int state);
	
	static void _onScroll(GLFWwindow* win, double xOffset, double yOffset);
	static void _onMouseMoved(GLFWwindow* win, double xPos, double yPos);
	static void _onMousePress(GLFWwindow* win, int button, int action, int mods);
	static void _onKeyPress(GLFWwindow* win, int key, int scancode, int action, int mods);
};

#endif