#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include<vector>
#include<map>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

typedef void(*scrollCallback)(GLFWwindow* window, double x, double y);
typedef void(*mouseMoveCallback)(GLFWwindow* window, double x, double y);
typedef void(*mousePressCallback)(GLFWwindow* window, int state);
typedef void(*keyPressCallback)(GLFWwindow* window, int state);

class Input {
public:
	Input(GLFWwindow* window);

	void registerScroll(scrollCallback callback);
	void registerMousePos(mouseMoveCallback callback);
	void registerMouse(int button, mousePressCallback callback);
	void registerKey(int key, keyPressCallback callback);
private:
	// This is going to be array of functions which will be called in a bulk whenever the event fires.
	std::vector<scrollCallback> scrollCallbacks;
	std::vector<mouseMoveCallback> mouseMoveCallbacks;

	// A look up table which stores each keybinds to array of functions which will be called when event fires.
	std::map<int, std::vector<mousePressCallback>> mousePressCallbacks;
	std::map<int, std::vector<keyPressCallback>> keyPressCallbacks;

	void onScroll(GLFWwindow* window, double x, double y);
	void onMouseMoved(GLFWwindow* window, double x, double y);
	void onMousePress(GLFWwindow* window, int button, int state);
	void onKeyPress(GLFWwindow* window, int key, int scancode, int state);
	
	static void _onScroll(GLFWwindow* win, double xOffset, double yOffset);
	static void _onMouseMoved(GLFWwindow* win, double xPos, double yPos);
	static void _onMousePress(GLFWwindow* win, int button, int action);
	static void _onKeyPress(GLFWwindow* win, int key, int scancode, int action, int mod);

	void USER_POINTER_EXCEPTION();
};

#endif